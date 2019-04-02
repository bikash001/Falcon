#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include "util.h"
using namespace std;

static void get_variables_info(FunctionInfo&, statement*, statement*, set<statement*>&);
static void util_info(FunctionInfo&, tree_expr*, int);
static statement* check_driver(FunctionInfo&, FunctionInfo&, statement*, char*);
static void find_update_point(set<char*, comparator>&, statement*, statement*, set<statement*>&, dir_decl *dg=NULL, set<dir_decl*> *values=NULL);
static bool walk_find_prop(set<char*, comparator>&, tree_expr*, dir_decl *dg=NULL, set<dir_decl*> *values=NULL);

// Returns the statement which defines a function.
static statement* get_function(const map<char*,statement*> &fnames, const char *name) {
	for(std::map<char*, statement*>::const_iterator it = fnames.begin(); it!=fnames.end(); it++) {
		if (strcmp(name, it->first) == 0) {
			return it->second;
		}
	}
	return NULL;
}

static bool check(const statement *fnc) {
	statement *end = fnc->end_stmt;
	statement *forstmt = fnc->next->next;
	if(forstmt->sttype == FOREACH_STMT && forstmt->end_stmt == end->prev && forstmt->stassign == NULL) {
		statement *ifstmt = forstmt->next;
		if(ifstmt->sttype == IF_STMT) {
			if(ifstmt->end_stmt == forstmt->end_stmt->prev) {
				return true;
			}
		}
	}
	return false;
}

/*
* finds the statements of given type in the top level of the given function
*
* @param begin: statement following the function declaration
* @param end: end statement of the function
* @param sttype: type of the statements to find
* @param v: stores the found statements
* @param visited: keeps track of visited statements
*/
static void find_statements(statement *begin, statement *end, STMT_TYPE sttype, vector<statement*> &v, set<statement*> &visited)
{
	while(begin && (begin != end)) {
		if(visited.find(begin) != visited.end()) {
			return;
		} else {
			visited.insert(begin);
		}
		if(begin->sttype == sttype) {
			v.push_back(begin);
		}
		if(begin->end_stmt && begin->end_stmt != begin) {
			begin = begin->end_stmt;
		} else {
			begin = begin->next;
		}
	}
}

// finds the graph declaration statement which is global
static statement* find_global_graph(statement *curr)
{
	while(curr) {
		if(curr->sttype == DECL_STMT && curr->stdecl->dirrhs && curr->stdecl->dirrhs->procd==0) {
			if(curr->stdecl->lhs->libdatatype == GRAPH_TYPE) {
				return curr;
			}
		}
		if(curr->end_stmt && curr->end_stmt != curr) {
			curr = curr->end_stmt;
		} else {
			curr = curr->next;
		}
	}
	return NULL;
}

/*
* Finds the read/write set in the function and also checks if the pre-condition satisfies
*
* @fin: read/write set for codes inside the condition
* @fout: read/write set for codes outside the condition
* @begin: start of statement
* @end: end of statement
* @visited: keeps track of visited statements
* @vp: stores attributes which are modified inside the condition statement
*/
static bool check_condn(FunctionInfo &fin, FunctionInfo &fout, statement *begin, statement *end, set<statement*> &visited, vector<pair<statement*, set<char*,comparator> > > &vp)
{
	bool stat = false;
	while(begin && (begin != end)) {
		if(visited.find(begin) != visited.end()) {
			return;
		} else {
			visited.insert(begin);
		}

		if(begin->sttype == DECL_STMT) {
			dir_decl *expr = begin->stdecl->dirrhs;
			while(expr) {
				if(expr->rhs) {
					util_info(fout, expr->rhs, 0); // 0 means read and 1 means write
				}
				fout.insert_local_var(expr);
				expr = expr->nextv;
			}
		} else if(begin->sttype == IF_STMT) {
			// check if point attributes is used
			FunctionInfo ft;
			ft.copy_local(fout);
			util_info(ft, begin->expr1, 0);

			// check if same attributes is changed inside
			FunctionInfo f;
			f.copy_local(fout);
			if(begin->f1) {
				get_variables_info(f, begin->f1, begin->end_stmt, visited);
			}
			if(begin->f2) {
				get_variables_info(f, begin->f2, begin->end_stmt, visited);
			}

			// check condition here
			if(ft.rw_attr_dep(f)) {
				// vector<dir_decl*> v;
				// ft.intersection(f, v);
				// vp.insert(begin, v);
				vp.push_back(make_pair(begin, ft.get_read_attr()));

				stat = true;
				fout.copy_all(ft);
				fin.copy_all(f);
			} else {
				fout.copy_all(ft);
				fout.copy_all(f);
			}
			
			begin = begin->end_stmt;
		} else if(begin->sttype == ASSIGN_STMT) {
			assign_stmt *astmt = begin->stassign;
			// check MIN func call here
			if(astmt->rhs && astmt->rhs->expr_type == FUNCALL && strcmp(astmt->rhs->name, "MIN") == 0) {
				assign_stmt *tastmt = astmt->rhs->arglist;
				int count = 0;
				FunctionInfo f;
				f.copy_local(fout);
				while(tastmt) {
					count++;
					if(tastmt->lhs) { // perhaps this is not required here since only read
						util_info(f, tastmt->lhs, 1);
					}
					if(tastmt->rhs) {
						if(count != 2) {
							util_info(f, tastmt->rhs, 1);
						} else {
							util_info(f, tastmt->rhs, 0);
						}
					}
					tastmt = tastmt->next;
				}

				// check condition here
				if(f.rw_attr_dep(f)) {
					vector<dir_decl*> v;
					vp.push_back(make_pair(begin, f.get_read_attr()));

					stat = true;
					fin.copy_all(f);
				} else {
					fout.copy_all(f);
				}
			} else {
				while(astmt) {	
					if(astmt->lhs) {
						util_info(fout, astmt->lhs, 1);
					}
					if(astmt->rhs) {
						util_info(fout, astmt->rhs, 0);
					}
					astmt = astmt->next;
				}	
			}
		} else if(begin->sttype == FOREACH_STMT){
			if(begin->expr4) {	// condition of foreach
				util_info(fout, begin->expr4, 0);
			}
			fout.insert_local_var(begin->expr1->lhs);
			if(begin->stassign) { // function call
				assign_stmt *astmt = begin->stassign;
				while(astmt) {	
					if(astmt->lhs) {
						util_info(fout, astmt->lhs, 1);
					}
					if(astmt->rhs) {
						util_info(fout, astmt->rhs, 0);
					}
					astmt = astmt->next;
				}
			}
		} else {
			if(begin->expr1) {
				util_info(fout, begin->expr1, 0);
			}
			if(begin->expr2) {
				util_info(fout, begin->expr2, 0);
			}
			if(begin->expr3) {
				util_info(fout, begin->expr3, 0);
			}
			if(begin->expr4) {
				util_info(fout, begin->expr4, 0);
			}
			if(begin->expr5) {
				util_info(fout, begin->expr5, 0);
			}				
			if(begin->f1) {
				get_variables_info(fout, begin->f1, end, visited);
			}
			if(begin->f2) {
				get_variables_info(fout, begin->f2, end, visited);
			}
			if(begin->f3) {
				get_variables_info(fout, begin->f3, end, visited);
			}
		}
		
		begin = begin->next;
	}
	return stat;
}


/*
* Initial setup of the target function like parameter change, new variable addition, etc.
* 
* @func: target function defining statement
* @foreachstmt: foreach statement which iterates through the neighbours of the point
* @RETURN: worklist variable
*/

static pair<dir_decl*,int> setup_func(statement *func, dir_decl **graph)
{
	// point over which for-loop iterates
	dir_decl *pt = NULL;
	// dir_decl *pt = foreachstmt->expr2->lhs;

	// find position to insert worklist
	tree_decl_stmt *params = func->stdecl->dirrhs->params;
	tree_decl_stmt *nd = NULL, *prev_param = NULL;

	while(params != NULL) {
		// if(params->dirrhs == pt) {
		// 	nd = params;
		// }
		if(params->lhs->libdatatype == POINT_TYPE) {
			nd = params;
			pt = params->dirrhs;
		}
		 else if(params->lhs->libdatatype == GRAPH_TYPE) {
			*graph = params->dirrhs;
		} else {
			tree_decl_stmt *td = params;
			if(prev_param) {
				prev_param->next = td->next;
			} else {
				func->stdecl->dirrhs->params = td->next;
			}
			if(td->next) {
				params = td->next;
			} else {
				params = prev_param;
			}
			delete td;
		}
		prev_param = params;
		if(params->next) {
			params = params->next;
		} else {
			break;
		}
	}

	char temp[30];
	int nd_count = falc_ext;

	// create new node for worklist
	tree_typedecl *p = new tree_typedecl();
	p->datatype = STRUCT_TYPE;
	p->compoundtype = 1;
	snprintf(temp, 30, "struct _flcn%d", falc_ext);
	p->name = create_string(temp);
	p->def = 0;
	snprintf(temp, 30, "_flcn%d", falc_ext++);
	p->vname = create_string(temp);
	nd->lhs = p;// specifier;

	nd->dirrhs = new dir_decl();
	snprintf(temp, 30, "_flcn%d", falc_ext++);
	nd->dirrhs->name = create_string(temp);
	dir_decl *node = nd->dirrhs;

	// create worklist
	tree_decl_stmt *ptr = new tree_decl_stmt();
	p = new tree_typedecl();
	p->libdatatype = COLLECTION_TYPE;
	p->name = create_string("collection");
	ptr->lhs = p;

	dir_decl *d = new dir_decl();
	snprintf(temp, 30, "_flcn%d", falc_ext++);
	d->name = create_string(temp);
	d->libdtype = COLLECTION_TYPE;
	dir_decl *wklist = d;

	p = new tree_typedecl();
	p->datatype = STRUCT_TYPE;
	p->compoundtype = 1;
	snprintf(temp, 30, "struct _flcn%d", nd_count);
	p->name = create_string(temp);
	p->def = 0;
	snprintf(temp, 30, "_flcn%d", nd_count);
	p->vname = create_string(temp);
	d->tp1 = p;
	ptr->dirrhs = d;

	// insert worklist to parameter list
	params->next = ptr;

	// create a point
	p = new tree_typedecl();
	p->libdatatype = POINT_TYPE;
	p->name = create_string("point ");
	p->d1 = *graph;
	if(*graph != NULL) p->ppts = (*graph)->ppts;

	tree_decl_stmt *tstmt = new tree_decl_stmt();
	tstmt->lhs = p;
	tstmt->dirrhs = pt;
	statement *st = new statement();
	st->sttype = DECL_STMT;
	st->stdecl = tstmt;

	insert_statement(func->next, st, func->next->next);

	// initialize point
	tree_expr *tx = new tree_expr(pt);
	tx->name = create_string(pt->name);
	tx->nodetype = -1;

	// assignment operator
	assign_stmt *as = new assign_stmt();
	as->asstype = AASSIGN;
	as->lhs = tx;
	tx->kernel = 5;
	tx = new tree_expr(node);
	tx->name = create_string(node->name);
	tx->nodetype = -1;
	tree_expr *ex = binaryopnode(tx, NULL, STRUCTREF, -1);
	ex->rhs = new tree_expr();
	ex->rhs->name = create_string("p");
	ex->rhs->expr_type = VAR;
	ex->kernel = 5;
	tx->nodetype = -10;
	as->rhs = ex;

	statement *stmt1 = createstmt(ASSIGN_STMT, NULL, NULL, 0);
	stmt1->stmtno = 0;
	stmt1->stassign = as;

	insert_statement(st, stmt1, st->next);
	return make_pair(wklist,nd_count);
}

/*
* Modify the code inside if-condition of target function for worklist based processing
*
* @ifstmt: pointer to the if statement
* @props: properties which are read in the if-condition
* @nd_count: name of worklist node (struct __flcn<nd_count>)
*/
static int mod_if(statement *ifstmt, set<char*, comparator> &props, dir_decl *wklist, int nd_count) {

	set<dir_decl*> values;	// store 
	set<statement*> visited;
	find_update_point(props, ifstmt, ifstmt->end_stmt, visited, NULL, &values);

	if(!values.empty()) {
		char temp[30];

		// insert into worklist
		for(set<dir_decl*>::iterator ii=values.begin(); ii!=values.end(); ++ii) {
			int tcnt = falc_ext++;
			
			// type specifier
			tree_typedecl *td = new tree_typedecl();
			td->datatype = STRUCT_TYPE;
			td->compoundtype = 1;
			snprintf(temp, 30, "struct _flcn%d", nd_count);
			td->name = create_string(temp);
			td->def = 0;
			snprintf(temp, 30, "_flcn%d", nd_count);
			td->vname = create_string(temp);
			
			dir_decl *d= new dir_decl();
			snprintf(temp, 30, "_flcn%d", tcnt);
			d->name = create_string(temp);

			tree_decl_stmt *tstmt = new tree_decl_stmt();
			tstmt->lhs = td;
			tstmt->dirrhs = d;
			statement *st = new statement();
			st->sttype = DECL_STMT;
			st->stdecl = tstmt;

			insert_statement(ifstmt->end_stmt->prev, st, ifstmt->end_stmt);

			// assign point to node
			// lhs of assignment
			tree_expr *tx = new tree_expr(d);
			tx->name = create_string(d->name);
			tx->nodetype = -1;
			tx = binaryopnode(tx, NULL, STRUCTREF, -1);
			tx->rhs = new tree_expr();
			tx->rhs->name = create_string("p");
			tx->rhs->expr_type = VAR;
			tx->kernel = 5;
			
			// assignment operator
			assign_stmt *as = new assign_stmt();
			as->asstype = AASSIGN;
			as->lhs = tx;
			
			// rhs of assignment
			tx = new tree_expr(*ii);
			tx->name = create_string((*ii)->name);
			tx->nodetype = -1;
			tx->kernel = 5;
			as->rhs = tx;
			as->semi = 1;

			statement *stmt1 = createstmt(ASSIGN_STMT, NULL, NULL, 0);
			stmt1->stmtno = 0;
			stmt1->stassign = as;

			insert_statement(ifstmt->end_stmt->prev, stmt1, ifstmt->end_stmt);

			// assign props to node
			for(set<char*, comparator>::iterator jj=props.begin(); jj!=props.end(); jj++) {
				// lhs of assignment
				tx = new tree_expr(d);
				tx->name = create_string(d->name);
				tx->nodetype = -1;
				tx = binaryopnode(tx, NULL, STRUCTREF, -1);
				tx->rhs = new tree_expr();
				tx->rhs->name = create_string(*jj);
				tx->rhs->expr_type = VAR;
				tx->kernel = 5;
				
				// assignment operator
				assign_stmt *as = new assign_stmt();
				as->asstype = AASSIGN;
				as->lhs = tx;
				
				// rhs of assignment
				tx = new tree_expr(*ii);
				tx->name = create_string((*ii)->name);
				tx->nodetype = -1;
				tx = binaryopnode(tx, NULL, STRUCTREF, -1);
				tx->rhs = new tree_expr();
				tx->rhs->name = create_string(*jj);
				tx->rhs->expr_type = VAR;
				tx->kernel = 5;
				as->rhs = tx;

				stmt1 = createstmt(ASSIGN_STMT, NULL, NULL, 0);
				stmt1->stmtno = 0;
				stmt1->stassign = as;

				insert_statement(ifstmt->end_stmt->prev, stmt1, ifstmt->end_stmt);
			}

			// insert node to worklist
			tx = new tree_expr(wklist);
			tx->nodetype = -10;
			tx->name = create_string(wklist->name);
			tx = binaryopnode(tx, NULL, STRUCTREF, -1);
			tx->rhs = new tree_expr();
			tx->rhs->name = create_string("add");
			tx->rhs->expr_type = VAR;
			tx->kernel = 0;

			// argument
			tree_expr *ex = new tree_expr(d);
			ex->nodetype = -1;
			ex->name = create_string(d->name);

			tx->rhs = funcallpostfix(tx->rhs, FUNCALL, 0, ex);

			stmt1 = createstmt(ASSIGN_STMT, NULL, NULL, 0);
			stmt1->stassign = createassignlhsrhs(-1, NULL, tx);

			insert_statement(ifstmt->end_stmt->prev, stmt1, ifstmt->end_stmt);
		}
		return nd_count;
	} else {
		fprintf(stderr, "%s %d\n", "empty values", ifstmt->sttype);
		for(set<char*, comparator>::iterator ii=props.begin(); ii!=props.end(); ++ii) {
			fprintf(stderr, "-->%s\n", *ii);
		}
	}
	return -1;
}

/*
* Process MIN function call in target functions for worklist based processing
*
* @cstmt: pointer to the MIN function call
* @props: properties read in the MIN function
* @nd_count: name of worklist node (struct __flcn<nd_count>)
*/
static int mod_minf(statement *cstmt, set<char*,comparator> &props, dir_decl *wklist, int nd_count) {
	set<dir_decl*> values;	// store 
	set<statement*> visited;
	// find_update_point(props, cstmt, cstmt->next, visited, NULL, &values);
	walk_find_prop(props, cstmt->stassign->rhs->arglist->rhs, NULL, &values);

	if(!values.empty()) {
		char temp[30];
		
		// declare a variable
		statement *stmtptr;
		stmtptr = new statement();
		stmtptr->sttype = DECL_STMT;
		tree_typedecl *td = new tree_typedecl();
		td->datatype = INT_TYPE;
		td->name = create_string("int ");
		dir_decl *d = new dir_decl();
		snprintf(temp, 30, "_flcn%d", falc_ext++);
		d->name = create_string(temp);
		stmtptr->stdecl = createdeclstmt(td, NULL, d);
		d->rhs = binaryopnode(NULL,NULL,-1,TREE_INT);
    	d->rhs->ival = 0;
    	d->rhs->dtype = 0;
    	insert_statement(cstmt->prev, stmtptr, cstmt);

    	// replace third argument to min function
    	assign_stmt *astmt = cstmt->stassign->rhs->arglist;
    	astmt = astmt->next->next;
    	astmt->rhs->name = mod_string(astmt->rhs->name, d->name);
    	astmt->rhs->lhs = d;

    	// create if statement
    	tree_expr *texp = new tree_expr(d);
    	texp->name = create_string(d->name);
    	stmtptr = createstmt(IF_STMT, texp,NULL,0);
    	insert_statement(cstmt, stmtptr, cstmt->next);

    	statement *st = createstmt(SBLOCK_STMT,NULL,NULL,0);
    	stmtptr->f1 = st;
    	stmtptr->f2 = NULL;

    	// temp statement required for if condition
    	statement *temp3 = createstmt(ASSIGN_STMT,NULL,NULL,0);
    	temp3->stassign=createassignlhsrhs(-1,NULL,texp);
    	st->prev = temp3;
    	temp3->next = st;
    	temp3->prev = cstmt;

    	statement *st1 = createstmt(EBLOCK_STMT,NULL,NULL,0);
    	st->next = st1;
    	st1->prev = st;
    	st1->next = NULL;
    	stmtptr->end_stmt = st1;


		// insert into worklist
		for(set<dir_decl*>::iterator ii=values.begin(); ii!=values.end(); ++ii) {
			int tcnt = falc_ext++;
			
			// type specifier
			tree_typedecl *td = new tree_typedecl();
			td->datatype = STRUCT_TYPE;
			td->compoundtype = 1;
			snprintf(temp, 30, "struct _flcn%d", nd_count);
			td->name = create_string(temp);
			td->def = 0;
			snprintf(temp, 30, "_flcn%d", nd_count);
			td->vname = create_string(temp);
			
			dir_decl *d= new dir_decl();
			snprintf(temp, 30, "_flcn%d", tcnt);
			d->name = create_string(temp);

			// tree_decl_stmt *tstmt = new tree_decl_stmt();
			// tstmt->lhs = td;
			// tstmt->dirrhs = d;
			statement *st = new statement();
			st->sttype = DECL_STMT;
			// st->stdecl = tstmt;
			st->stdecl = createdeclstmt(td, NULL, d);

			insert_statement(st1->prev, st, st1);

			// assign point to node
			// lhs of assignment
			tree_expr *tx = new tree_expr(d);
			tx->name = create_string(d->name);
			tx->nodetype = -1;
			tx = binaryopnode(tx, NULL, STRUCTREF, -1);
			tx->rhs = new tree_expr();
			tx->rhs->name = create_string("p");
			tx->rhs->expr_type = VAR;
			tx->kernel = 5;
			
			// assignment operator
			assign_stmt *as = new assign_stmt();
			as->asstype = AASSIGN;
			as->lhs = tx;
			
			// rhs of assignment
			tx = new tree_expr(*ii);
			tx->name = create_string((*ii)->name);
			tx->nodetype = -1;
			tx->kernel = 5;
			as->rhs = tx;
			as->semi = 1;

			statement *stmt1 = createstmt(ASSIGN_STMT, NULL, NULL, 0);
			stmt1->stmtno = 0;
			stmt1->stassign = as;

			insert_statement(st1->prev, stmt1, st1);

			// assign props to node
			for(set<char*, comparator>::iterator jj=props.begin(); jj!=props.end(); jj++) {
				// lhs of assignment
				tx = new tree_expr(d);
				tx->name = create_string(d->name);
				tx->nodetype = -1;
				tx = binaryopnode(tx, NULL, STRUCTREF, -1);
				tx->rhs = new tree_expr();
				tx->rhs->name = create_string(*jj);
				tx->rhs->expr_type = VAR;
				tx->kernel = 5;
				
				// assignment operator
				assign_stmt *as = new assign_stmt();
				as->asstype = AASSIGN;
				as->lhs = tx;
				
				// rhs of assignment
				tx = new tree_expr(*ii);
				tx->name = create_string((*ii)->name);
				tx->nodetype = -1;
				tx = binaryopnode(tx, NULL, STRUCTREF, -1);
				tx->rhs = new tree_expr();
				tx->rhs->name = create_string(*jj);
				tx->rhs->expr_type = VAR;
				tx->kernel = 5;
				as->rhs = tx;

				stmt1 = createstmt(ASSIGN_STMT, NULL, NULL, 0);
				stmt1->stmtno = 0;
				stmt1->stassign = as;

				insert_statement(st1->prev, stmt1, st1);
			}

			// insert node to worklist
			tx = new tree_expr(wklist);
			tx->nodetype = -10;
			tx->name = create_string(wklist->name);
			tx = binaryopnode(tx, NULL, STRUCTREF, -1);
			tx->rhs = new tree_expr();
			tx->rhs->name = create_string("add");
			tx->rhs->expr_type = VAR;
			tx->kernel = 0;

			// argument
			tree_expr *ex = new tree_expr(d);
			ex->nodetype = -1;
			ex->name = create_string(d->name);

			tx->rhs = funcallpostfix(tx->rhs, FUNCALL, 0, ex);

			stmt1 = createstmt(ASSIGN_STMT, NULL, NULL, 0);
			stmt1->stassign = createassignlhsrhs(-1, NULL, tx);

			insert_statement(st1->prev, stmt1, st1);

		}

		return nd_count;

	} else {
		fprintf(stderr, "%s %d\n", "empty values", cstmt->sttype);
		for(set<char*, comparator>::iterator ii=props.begin(); ii!=props.end(); ++ii) {
			fprintf(stderr, "-->%s\n", *ii);
		}
	}

	return -1;
}

/*
* Checks if the function can be converted into worklist based
*
* @param fnc: definition of the function
*/
static bool check_func(const statement *fnc, const statement *main, dir_decl **graph, pair<dir_decl*, int> &pr) {
	vector<statement*> v;
	set<statement*> visited;
	find_statements(fnc->next, fnc->end_stmt, FOREACH_STMT, v, visited);

	// should have at least one foreach which iterates through the neighbours of the point
	if(v.empty()) {
		return false;
	}

	vector<pair<statement*, set<char*, comparator> > > vp;
	vector<statement*> fstmts;
	FunctionInfo fiin, fiout;
	statement *prev = fnc->next;
	for(int i=0; i<v.size(); ++i) {
		// fprintf(stderr, "ITR %d\n", v[i]->itr);
		if(v[i]->itr >=2 && v[i]->itr <= 4) { // neighbour iterator
			visited.clear();
			// fiout.swap_local(fiin);
			get_variables_info(fiout, prev, v[i], visited);
			visited.clear();
			FunctionInfo fin, fout;
			fin.copy_local(fiout);
			fout.copy_local(fiout);
			
			if(check_condn(fin, fout, v[i], v[i]->end_stmt, visited, vp)) {
				// copy data to fiin, fiout
				fiin.copy_all(fin);
				fiout.copy_all(fout);
				fstmts.push_back(v[i]);
			} else {
				// copy data to fiout
				fiout.copy_all(fin);
				fiout.copy_all(fout);
			}

			// get_variables_info(fiin, prev, v[i]->end_stmt, visited);

			prev = v[i]->end_stmt->next;
		} else {
			visited.clear();
			// fiout.swap_local(fiin);
			get_variables_info(fiout, prev, v[i]->end_stmt, visited);

			prev = v[i]->end_stmt->next;
		}
	}
	visited.clear();
	// fiout.swap_local(fiin);
	get_variables_info(fiout, prev, fnc->end_stmt, visited);

	// check function
	if(fiin.empty()) return false;
	// if(!fiout.empty()) return false;

	// check driver code
	FunctionInfo fdi, fdo;
	statement *whstmt = check_driver(fdi, fdo, main, fnc->stdecl->dirrhs->name);
	if(whstmt == NULL) return false; // function can't be converted
	if(!fdi.attr_write_empty()) false;

	// compare info of function with driver


	// modify function
	dir_decl *wklist = NULL;
	int nd_count; 	// node for worklist (name should be __flcn<nd_count>)
	pr = setup_func(fnc, graph);
	wklist = pr.first;
	nd_count = pr.second;
	for(int i=0; i<vp.size(); ++i) {
		if(vp[i].first->sttype == IF_STMT) {
			mod_if(vp[i].first, vp[i].second, wklist, nd_count);
		} else {
			mod_minf(vp[i].first, vp[i].second, wklist, nd_count);
		}
	}

	return true;
}

static int find_while(statement *begin, statement *end, char *fnc, statement **stmtptr)
{
	while(begin && begin->sttype != FUNCTION_EBLOCK_STMT && begin != end){
		if(begin->sttype == WHILE_STMT) {

			if(find_while(begin->next, begin->end_stmt, fnc, stmtptr) == 1) {
				*stmtptr = begin;
				return 2;
			}
			begin = begin->end_stmt;
		} else if(begin->sttype == FOREACH_STMT && begin->stassign != NULL) {
			if(strcmp(begin->stassign->rhs->name, fnc) == 0) {
				return 1;
			} 
		} else { 
			int ret = 0;
			if(begin->f1) {
				if(begin->f1->end_stmt) {
					ret = find_while(begin->f1, begin->f1->end_stmt, fnc, stmtptr);
					if(ret) return ret;
				} else {
					ret = find_while(begin->f1, end, fnc, stmtptr);
					if(ret) return ret;
				}
			}
			if(begin->f2) {
				if(begin->f2->end_stmt) {
					ret = find_while(begin->f2, begin->f2->end_stmt, fnc, stmtptr);
					if(ret) return ret;
				} else {
					ret = find_while(begin->f2, end, fnc, stmtptr);
					if(ret) return ret;
				}
			}
			if(begin->f3) {
				if(begin->f3->end_stmt) {
					ret = find_while(begin->f3, begin->f3->end_stmt, fnc, stmtptr);
					if(ret) return ret;
				} else {
					ret = find_while(begin->f3, end, fnc, stmtptr);
					if(ret) return ret;
				}
			}
		}
		begin = begin->next;
	}
	return 0;
}


static statement* check_driver(FunctionInfo &fi, FunctionInfo &fo, statement *begin, char *fname)
{
	statement *stmt = NULL;
	find_while(begin->next, begin->end_stmt, fname, &stmt);
	if(stmt == NULL) {
		// fprintf(stderr, "ERROR: worklist-342 %p\n", stmt);
		return NULL;
	}
	set<statement*> v;
	FunctionInfo tmp;
	get_variables_info(tmp, begin->next, stmt, v);
	fi.copy_local(tmp);
	fo.copy_local(tmp);
	get_variables_info(fi, stmt->next, stmt->end_stmt, v);
	get_variables_info(fo, stmt->end_stmt->next, begin->end_stmt, v);
	return stmt;
}

/*
* Utility function for get_variables_info. It extracts variables or attributes from the given expression
*
* @param fi: stores al the info
* @param exp: expression from where info is extracted
* @param atype: access type {0=read, 1=write}
*/
static void util_info(FunctionInfo &fi, tree_expr *expr, int atype) {
	if(expr == NULL) {
		return;
	} else if(expr->expr_type == VAR) {
		if(atype == 0) {
			fi.insert_var_read(expr->lhs);
		} else {
			fi.insert_var_write(expr->lhs);
		}
		return;
	}
	if(expr->expr_type == STRUCTREF && expr->lhs->expr_type == STRUCTREF) {
		// printf("TEST-3 %s\n", expr->rhs->name);
		if(expr->lhs->lhs->expr_type == VAR && expr->lhs->lhs->lhs->libdtype == GRAPH_TYPE) {
			if(expr->lhs->rhs->expr_type == ARRREF) {
				if(expr->rhs->expr_type == VAR) {
					dir_decl *temp = expr->lhs->lhs->lhs;
					if(atype == 0) {
						fi.insert_attr_read(expr->rhs->name);
					} else {
						fi.insert_attr_write(expr->rhs->name);
					}
				}
			}
		} else { // if point has struct property
			util_info(fi, expr->lhs, atype);
			// walk_find_prop(mp, expr->rhs);
		}
	} else if(expr->expr_type == STRUCTREF && expr->lhs->expr_type == VAR) {
		// printf("TEST-1 %s %d\n", expr->lhs->lhs->name, expr->lhs->lhs->libdtype);
		dir_decl *dd = expr->lhs->lhs;
		if(dd == NULL) {
			fprintf(stderr, "NULL %s\n", expr->lhs->name);
		}
		LIBDATATYPE type = expr->lhs->lhs->libdtype;
		if(type == POINT_TYPE || type == EDGE_TYPE || (type == ITERATOR_TYPE && (dd->it >= 2 && dd->it <= 4))) {
			// printf("TEST-2\n");
			if(expr->rhs->expr_type == VAR) {
				// printf("TEST <--> %s\n", expr->rhs->name);
				// dir_decl *temp = get_parent_graph(expr->lhs->lhs);
				// if(temp == NULL) {
				// 	temp = dg;
				// }

				bool isLib = false;	// check if attribute is provided by library
				char *name = expr->rhs->name;
				if(expr->lhs->lhs->libdtype == POINT_TYPE) {
					isLib = is_lib_attr(POINT_TYPE, name);
				} else {
					isLib = is_lib_attr(EDGE_TYPE, name);
				}
				if(!isLib) {
					if(atype == 0) {
						fi.insert_attr_read(expr->rhs->name);
					} else {
						fi.insert_attr_write(expr->rhs->name);
					}
				}
			}
		}
	} else {
		if(expr->lhs) {
			util_info(fi, expr->lhs, 0);
		}
		if(expr->rhs) {
			util_info(fi, expr->rhs, 0);
		}
		if(expr->earr_list) {
			assign_stmt *astmt = expr->earr_list;
			while(astmt) {
				if(astmt->lhs) { // perhaps this is not required here since only read
					util_info(fi, astmt->lhs, 1);
				}
				if(astmt->rhs) {
					util_info(fi, astmt->rhs, 0);
				}
				astmt = astmt->next;
			}
		}
		if(expr->next) {
			util_info(fi, expr->next, 0);
		}
		if(expr->arglist) {
			assign_stmt *astmt = expr->arglist;
			int wt = 0;
			if(strcmp(expr->name, "MIN") == 0) wt = 1;
			int count = 0;
			while(astmt) {
				count++;
				if(astmt->lhs) { // perhaps this is not required here since only read
					util_info(fi, astmt->lhs, 1);
				}
				if(astmt->rhs) {
					if(count != 2) {
						util_info(fi, astmt->rhs, wt);
					} else {
						util_info(fi, astmt->rhs, 0);
					}
				}
				astmt = astmt->next;
			}
		}
	}
}



/*
* Extracts read/write set of variables and point attributes
*
* @param fi: stores all the info
* @param begin: beginning statement (inclusive)
* @param end: end statement (exclusive)
* @param visited: keeps track of visited statements
*/
static void get_variables_info(FunctionInfo &fi, statement *begin, statement *end, set<statement*> &visited)
{
	while(begin && (begin != end)) {
		if(visited.find(begin) != visited.end()) {
			return;
		} else {
			visited.insert(begin);
		}

		if(begin->sttype == DECL_STMT) {
			dir_decl *expr = begin->stdecl->dirrhs;
			while(expr) {
				if(expr->rhs) {
					util_info(fi, expr->rhs, 0); // 0 means read and 1 means write
				}
				fi.insert_local_var(expr);
				expr = expr->nextv;
			}
		} else if(begin->sttype == ASSIGN_STMT) {
			assign_stmt *astmt = begin->stassign;
			while(astmt) {	
				if(astmt->lhs) {
					util_info(fi, astmt->lhs, 1);
				}
				if(astmt->rhs) {
					util_info(fi, astmt->rhs, 0);
				}
				astmt = astmt->next;
			}
		} else if(begin->sttype == FOREACH_STMT){
			if(begin->expr4) {	// condition of foreach
				util_info(fi, begin->expr4, 0);
			}
			fi.insert_local_var(begin->expr1->lhs);
			if(begin->stassign) { // function call
				assign_stmt *astmt = begin->stassign;
				while(astmt) {	
					if(astmt->lhs) {
						util_info(fi, astmt->lhs, 1);
					}
					if(astmt->rhs) {
						util_info(fi, astmt->rhs, 0);
					}
					astmt = astmt->next;
				}
			}
		} else {
			if(begin->expr1) {
				util_info(fi, begin->expr1, 0);
			}
			if(begin->expr2) {
				util_info(fi, begin->expr2, 0);
			}
			if(begin->expr3) {
				util_info(fi, begin->expr3, 0);
			}
			if(begin->expr4) {
				util_info(fi, begin->expr4, 0);
			}
			if(begin->expr5) {
				util_info(fi, begin->expr5, 0);
			}				
			if(begin->f1) {
				get_variables_info(fi, begin->f1, end, visited);
			}
			if(begin->f2) {
				get_variables_info(fi, begin->f2, end, visited);
			}
			if(begin->f3) {
				get_variables_info(fi, begin->f3, end, visited);
			}
		}
		
		begin = begin->next;
	}
}


// Walks through expression to find what attributes are used
static bool walk_find_prop(set<char*, comparator> &v, tree_expr *expr, dir_decl *dg=NULL, set<dir_decl*> *values=NULL)
{
	if(expr == NULL || expr->expr_type == VAR) {
		return false;
	}
	if(expr->expr_type == STRUCTREF && expr->lhs->expr_type == VAR) {
		// printf("TEST-1 %s %d\n", expr->lhs->lhs->name, expr->lhs->lhs->libdtype);
		dir_decl *dd = expr->lhs->lhs;
		LIBDATATYPE type = expr->lhs->lhs->libdtype;
		if(type == POINT_TYPE || type == EDGE_TYPE || (type == ITERATOR_TYPE && (dd->it >= 2 && dd->it <= 4))) {
			// printf("TEST-2\n");
			if(expr->rhs->expr_type == VAR) {
				// printf("TEST <--> %s\n", expr->rhs->name);
				dir_decl *temp = get_parent_graph(expr->lhs->lhs);
				// if(temp == NULL) {
				// 	temp = dg;
				// }

				bool isLib = false;	// check if attribute is provided by library
				char *name = expr->rhs->name;
				if(expr->lhs->lhs->libdtype == POINT_TYPE) {
					isLib = is_lib_attr(POINT_TYPE, name);
				} else {
					isLib = is_lib_attr(EDGE_TYPE, name);
				}
				if(!isLib) {
					// fprintf(stderr, "TST %d\n", values == NULL);
					if(values != NULL) {
						if(v.find(name) != v.end()) {
							values->insert(expr->lhs->lhs);
							return true;
						}
					} else {
						v.insert(name);
					}
				}
			}
		}
	} else {
		if(expr->lhs) {
			walk_find_prop(v, expr->lhs, dg, values);
		}
		if(expr->rhs) {
			walk_find_prop(v, expr->rhs, dg, values);
		}
		if(expr->earr_list) {
			assign_stmt *astmt = expr->earr_list;
			while(astmt) {
				if(astmt->lhs) { // perhaps this is not required here since only read
					walk_find_prop(v, astmt->lhs, dg, values);
				}
				if(astmt->rhs) {
					walk_find_prop(v, astmt->rhs, dg, values);
				}
				astmt = astmt->next;
			}
		}
		if(expr->next) {
			walk_find_prop(v, expr->next, dg, values);
		}
		if(expr->arglist) {
			assign_stmt *astmt = expr->arglist;
			while(astmt) {
				if(astmt->lhs) { // perhaps this is not required here since only read
					walk_find_prop(v, astmt->lhs, dg, values);
				}
				if(astmt->rhs) {
					walk_find_prop(v, astmt->rhs, dg, values);
				}
				astmt = astmt->next;
			}
		}
	}
	return false;
}

static bool walk_find_prop_util(set<char*, comparator> &v, assign_stmt *astmt, dir_decl *dg=NULL, set<dir_decl*> *values=NULL)
{
	while(astmt) {
		if(astmt->lhs && astmt->asstype == AASSIGN) {
			walk_find_prop(v, astmt->lhs, dg, values);
		}
		if(astmt->rhs && astmt->asstype == -1) {// if function call
			walk_find_prop(v, astmt->rhs, dg, values);
		}
		astmt = astmt->next;
	}
	return false;
}

// @params dg: default graph to be used if parent of point or edge is not set
static void find_update_point(set<char*, comparator> &v, statement *begin, statement *end, set<statement*> &visited, dir_decl *dg=NULL, set<dir_decl*> *values=NULL)
{
	while(begin && (begin != end)) {
		if(visited.find(begin) != visited.end()) {
			return;
		} else {
			visited.insert(begin);
		}
		if(begin->sttype == DECL_STMT) {
			// dir_decl *expr = begin->stdecl->dirrhs;
			// while(expr) {
			// 	if(expr->rhs) { // only check rhs, since lhs is being defined (i.e. local variable)
			// 		walk_find_prop(rmp, expr->rhs, dg);
			// 	}
			// 	expr = expr->nextv;
			// }
		} else if(begin->sttype == FOR_STMT) {
			// if(begin->f1) walk_find_prop_util(rmp, wmp, begin->f1->stassign, dg);
			// if(begin->f2) walk_find_prop_util(rmp, wmp, begin->f2->stassign, dg);
			// if(begin->f3) walk_find_prop_util(rmp, wmp, begin->f3->stassign, dg);
		} else if(begin->sttype == ASSIGN_STMT) {
			walk_find_prop_util(v, begin->stassign, dg, values);
		} else if(begin->sttype != FOREACH_STMT) {
			// if(begin->expr1) {
			// 	walk_find_prop(rmp, begin->expr1, dg);
			// }
			// if(begin->expr2) {
			// 	walk_find_prop(rmp, begin->expr2, dg);
			// }
			// if(begin->expr3) {
			// 	walk_find_prop(rmp, begin->expr3, dg);
			// }
			// if(begin->expr4) {
			// 	walk_find_prop(rmp, begin->expr4, dg);
			// }
			// if(begin->expr5) {
			// 	walk_find_prop(rmp, begin->expr5, dg);
			// }				
			if(begin->f1) {
				find_update_point(v, begin->f1, end, visited, dg, values);
			}
			if(begin->f2) {
				find_update_point(v, begin->f2, end, visited, dg, values);
			}
			if(begin->f3) {
				find_update_point(v, begin->f3, end, visited, dg, values);
			}
		} else {
			// if(begin->expr4) {	// condition of foreach
			// 	walk_find_prop(rmp, begin->expr4, dg);
			// }
			if(begin->stassign) { // function call
				assign_stmt *astmt = begin->stassign;
				if(astmt->lhs && astmt->asstype == AASSIGN) {
					walk_find_prop(v, astmt->lhs, dg, values);
				}
				// if(astmt->rhs) {
				// 	assign_stmt *arglist = begin->stassign->rhs->arglist;
				// 	walk_find_prop_util(rmp, wmp, arglist, dg);

				// 	if(astmt->rhs->expr_type == FUNCALL) {
				// 		// printf("TEST-590 %s\n", astmt->rhs->name);

				// 		statement *target = get_function(astmt->rhs->name);
				// 		if(target == NULL) { // may be library function
				// 			fprintf(stderr, "Error-1062: function %s not defined.\n", astmt->rhs->name);
				// 			walk_find_prop(wmp, astmt->rhs, dg);
				// 			// exit(0);
				// 		} else {
				// 			tree_decl_stmt *params = target->stdecl->dirrhs->params;
							
				// 			dir_decl *gp = NULL;
				// 			while(params) {
				// 				if(gp==NULL && params->dirrhs->libdtype == GRAPH_TYPE) {
				// 					gp = params->dirrhs;
				// 				}
				// 				params = params->next;
				// 			}

				// 			find_update_point(rmp, wmp, target->next->next, target->end_stmt, gp, visited);
				// 			replace_map_variables(rmp, target->stdecl->dirrhs->params, astmt->rhs->arglist);
				// 			replace_map_variables(wmp, target->stdecl->dirrhs->params, astmt->rhs->arglist);
				// 		}
				// 	} else {
				// 		walk_find_prop(rmp, astmt->rhs, dg);
				// 	}
				// }
			}
		}
		
		begin = begin->next;
	}
}


static pair<dir_decl*,int> change_func(statement *stmt, dir_decl **graph) {
	statement *forstmt = stmt->next->next;
	statement *ifstmt = forstmt->next;
	set<char*, comparator> props;	// store properties of node/edge
	walk_find_prop(props, ifstmt->expr1);	// find attributes used in if-condition

	set<dir_decl*> values;	// store 
	set<statement*> visited;
	find_update_point(props, ifstmt, ifstmt->end_stmt, visited, NULL, &values);

	if(!values.empty()) {
		// point over which for-loop iterates
		dir_decl *pt = forstmt->expr2->lhs;

		// find position to insert worklist
		tree_decl_stmt *params = stmt->stdecl->dirrhs->params;
		tree_decl_stmt *nd = NULL, *prev_param = NULL;
		// dir_decl *graph = NULL;
		
		while(params != NULL) {
			if(params->dirrhs == pt) {
				nd = params;
			} else if(params->lhs->libdatatype == GRAPH_TYPE) {
				*graph = params->dirrhs;
			} else {
				tree_decl_stmt *td = params;
				if(prev_param) {
					prev_param->next = td->next;
				} else {
					stmt->stdecl->dirrhs->params = td->next;
				}
				if(td->next) {
					params = td->next;
				} else {
					params = prev_param;
				}
				delete td;
			}
			prev_param = params;
			if(params->next) {
				params = params->next;
			} else {
				break;
			}
		}

		char temp[30];
		int nd_count = falc_ext;
		
		// create new node for worklist
		tree_typedecl *p = new tree_typedecl();
		p->datatype = STRUCT_TYPE;
		p->compoundtype = 1;
		snprintf(temp, 30, "struct _flcn%d", falc_ext);
		p->name = create_string(temp);
		p->def = 0;
		snprintf(temp, 30, "_flcn%d", falc_ext++);
		p->vname = create_string(temp);
		nd->lhs = p;// specifier;
		
		nd->dirrhs = new dir_decl();
		snprintf(temp, 30, "_flcn%d", falc_ext++);
		nd->dirrhs->name = create_string(temp);
		dir_decl *node = nd->dirrhs;

		// create worklist
		tree_decl_stmt *ptr = new tree_decl_stmt();
		p = new tree_typedecl();
		p->libdatatype = COLLECTION_TYPE;
		p->name = create_string("collection");
		ptr->lhs = p;

		dir_decl *d = new dir_decl();
		snprintf(temp, 30, "_flcn%d", falc_ext++);
		d->name = create_string(temp);
		d->libdtype = COLLECTION_TYPE;
		dir_decl *wklist = d;

		p = new tree_typedecl();
		p->datatype = STRUCT_TYPE;
		p->compoundtype = 1;
		snprintf(temp, 30, "struct _flcn%d", nd_count);
		p->name = create_string(temp);
		p->def = 0;
		snprintf(temp, 30, "_flcn%d", nd_count);
		p->vname = create_string(temp);
		d->tp1 = p;
		ptr->dirrhs = d;

		// insert worklist to parameter list
		params->next = ptr;

		// create a point
		p = new tree_typedecl();
		p->libdatatype = POINT_TYPE;
		p->name = create_string("point ");
		p->d1 = *graph;
		if(*graph != NULL) p->ppts = (*graph)->ppts;

		tree_decl_stmt *tstmt = new tree_decl_stmt();
		tstmt->lhs = p;
		tstmt->dirrhs = pt;
		statement *st = new statement();
		st->sttype = DECL_STMT;
		st->stdecl = tstmt;

		insert_statement(stmt->next, st, stmt->next->next);

		// initialize point
		tree_expr *tx = new tree_expr(pt);
		tx->name = create_string(pt->name);
		tx->nodetype = -1;

		// assignment operator
		assign_stmt *as = new assign_stmt();
		as->asstype = AASSIGN;
		as->lhs = tx;
		tx->kernel = 5;
		tx = new tree_expr(node);
		tx->name = create_string(node->name);
		tx->nodetype = -1;
		tree_expr *ex = binaryopnode(tx, NULL, STRUCTREF, -1);
		ex->rhs = new tree_expr();
		ex->rhs->name = create_string("p");
		ex->rhs->expr_type = VAR;
		ex->kernel = 5;
		tx->nodetype = -10;
		as->rhs = ex;

		statement *stmt1 = createstmt(ASSIGN_STMT, NULL, NULL, 0);
		stmt1->stmtno = 0;
		stmt1->stassign = as;

		insert_statement(st, stmt1, st->next);

		// insert into worklist
		for(set<dir_decl*>::iterator ii=values.begin(); ii!=values.end(); ++ii) {
			int tcnt = falc_ext++;
			
			// type specifier
			tree_typedecl *td = new tree_typedecl();
			td->datatype = STRUCT_TYPE;
			td->compoundtype = 1;
			snprintf(temp, 30, "struct _flcn%d", nd_count);
			td->name = create_string(temp);
			td->def = 0;
			snprintf(temp, 30, "_flcn%d", nd_count);
			td->vname = create_string(temp);
			
			dir_decl *d= new dir_decl();
			snprintf(temp, 30, "_flcn%d", tcnt);
			d->name = create_string(temp);

			tree_decl_stmt *tstmt = new tree_decl_stmt();
			tstmt->lhs = td;
			tstmt->dirrhs = d;
			statement *st = new statement();
			st->sttype = DECL_STMT;
			st->stdecl = tstmt;

			insert_statement(ifstmt->end_stmt->prev, st, ifstmt->end_stmt);

			// assign point to node
			// lhs of assignment
			tree_expr *tx = new tree_expr(d);
			tx->name = create_string(d->name);
			tx->nodetype = -1;
			tx = binaryopnode(tx, NULL, STRUCTREF, -1);
			tx->rhs = new tree_expr();
			tx->rhs->name = create_string("p");
			tx->rhs->expr_type = VAR;
			tx->kernel = 5;
			
			// assignment operator
			assign_stmt *as = new assign_stmt();
			as->asstype = AASSIGN;
			as->lhs = tx;
			
			// rhs of assignment
			tx = new tree_expr(*ii);
			tx->name = create_string((*ii)->name);
			tx->nodetype = -1;
			tx->kernel = 5;
			as->rhs = tx;
			as->semi = 1;

			statement *stmt1 = createstmt(ASSIGN_STMT, NULL, NULL, 0);
			stmt1->stmtno = 0;
			stmt1->stassign = as;

			insert_statement(ifstmt->end_stmt->prev, stmt1, ifstmt->end_stmt);

			// assign props to node
			for(set<char*, comparator>::iterator jj=props.begin(); jj!=props.end(); jj++) {
				// lhs of assignment
				tx = new tree_expr(d);
				tx->name = create_string(d->name);
				tx->nodetype = -1;
				tx = binaryopnode(tx, NULL, STRUCTREF, -1);
				tx->rhs = new tree_expr();
				tx->rhs->name = create_string(*jj);
				tx->rhs->expr_type = VAR;
				tx->kernel = 5;
				
				// assignment operator
				assign_stmt *as = new assign_stmt();
				as->asstype = AASSIGN;
				as->lhs = tx;
				
				// rhs of assignment
				tx = new tree_expr(*ii);
				tx->name = create_string((*ii)->name);
				tx->nodetype = -1;
				tx = binaryopnode(tx, NULL, STRUCTREF, -1);
				tx->rhs = new tree_expr();
				tx->rhs->name = create_string(*jj);
				tx->rhs->expr_type = VAR;
				tx->kernel = 5;
				as->rhs = tx;

				stmt1 = createstmt(ASSIGN_STMT, NULL, NULL, 0);
				stmt1->stmtno = 0;
				stmt1->stassign = as;

				insert_statement(ifstmt->end_stmt->prev, stmt1, ifstmt->end_stmt);
			}

			// insert node to worklist
			tx = new tree_expr(wklist);
			tx->nodetype = -10;
			tx->name = create_string(wklist->name);
			tx = binaryopnode(tx, NULL, STRUCTREF, -1);
			tx->rhs = new tree_expr();
			tx->rhs->name = create_string("add");
			tx->rhs->expr_type = VAR;
			tx->kernel = 0;

			// argument
			ex = new tree_expr(d);
			ex->nodetype = -1;
			ex->name = create_string(d->name);

			tx->rhs = funcallpostfix(tx->rhs, FUNCALL, 0, ex);

			stmt1 = createstmt(ASSIGN_STMT, NULL, NULL, 0);
			stmt1->stassign = createassignlhsrhs(-1, NULL, tx);

			insert_statement(ifstmt->end_stmt->prev, stmt1, ifstmt->end_stmt);
		}
		return make_pair(wklist,nd_count);
	}
	return make_pair(NULL,0);
}

static bool walk_statement(statement *begin, statement *end, char *fnc, statement **call, dir_decl *wklist, statement **graph_decl=NULL) {
	while(begin && begin->sttype != FUNCTION_EBLOCK_STMT && begin != end){
		if(begin->sttype == WHILE_STMT) {

			if(walk_statement(begin->next, begin->end_stmt, fnc, call, wklist, graph_decl)) {
				// remove while loop
				statement *tcall = *call;
				tcall->expr2 = new tree_expr(wklist);//;
				tcall->expr2->name = create_string(wklist->name);
				tcall->expr3 = NULL;
				tcall->expr4 = NULL;
				tcall->itr = 5;
				assign_stmt *as = tcall->stassign->rhs->arglist;
				
				// remove args not required
				assign_stmt *prev_arg = NULL;
				int count = 0;
				while(as->next) as = as->next;
				// while(as) {
				// 	if(as->rhs->expr_type == VAR) {
				// 		if(as->rhs->lhs->libdtype != POINT_TYPE || as->rhs->lhs->libdtype != GRAPH_TYPE) {
				// 			assign_stmt *temp = as;
				// 			if(prev_arg) {
				// 				prev_arg->next = temp->next;
				// 			} else {
				// 				tcall->stassign->rhs->arglist = temp->next;
				// 			}
				// 			if(temp->next) {
				// 				as = temp->next;
				// 			} else {
				// 				as = prev_arg;
				// 			}
				// 			delete temp;
				// 			count++;
				// 		}
				// 	}
				// 	prev_arg = as;
				// 	if(as->next) {
				// 		as = as->next;
				// 	} else {
				// 		break;
				// 	}
				// }
				// fprintf(stderr, "COUNT: %d\n", count);
				
				as->rhs = new tree_expr(wklist);
				as->rhs->name = create_string(wklist->name);
				// as->rhs->it = 5;

				begin->prev->next = tcall;
				tcall->prev = begin->prev;
				tcall->next = begin->end_stmt->next;
				begin->end_stmt->next->prev = tcall;
				return false;
			}
			begin = begin->end_stmt;
		} else if(begin->sttype == DECL_STMT) {
			if(begin->stdecl->lhs->libdatatype == GRAPH_TYPE && graph_decl != NULL) {
				*graph_decl = begin;
				fprintf(stderr, "%s\n", "GRAPH FOUND");
			}
		} else if(begin->sttype == FOREACH_STMT && begin->stassign != NULL) {
			if(strcmp(begin->stassign->rhs->name, fnc) == 0) {
				*call = begin;
				return true;	
			} 
		} else { 
			if(begin->f1) {
				if(begin->f1->end_stmt) {
					if(walk_statement(begin->f1, begin->f1->end_stmt, fnc, call, wklist, graph_decl)) return true;
				} else {
					if(walk_statement(begin->f1, end, fnc, call, wklist, graph_decl)) return true;
				}
			}
			if(begin->f2) {
				if(begin->f2->end_stmt) {
					if(walk_statement(begin->f2, begin->f2->end_stmt, fnc, call, wklist, graph_decl)) return true;
				} else {
					if(walk_statement(begin->f2, end, fnc, call, wklist, graph_decl)) return true;
				}
			}
			if(begin->f3) {
				if(begin->f3->end_stmt) {
					if(walk_statement(begin->f3, begin->f3->end_stmt, fnc, call, wklist, graph_decl)) return true;
				} else {
					if(walk_statement(begin->f3, end, fnc, call, wklist, graph_decl)) return true;
				}
			}
		}
		begin = begin->next;
	}
	return false;
}

statement* process(map<char*, statement*> &fnames, statement *head) {
	statement *main = get_function(fnames, "main");
	dir_decl *graph = NULL;
	if(main == NULL) {
		fprintf(stderr, "%s\n", "main function does not exist.");
		exit(1);
	}
	
	int cnt = 0;
	dir_decl *wklist = NULL;
	statement *graph_decl = NULL;
	for(std::map<char*, statement*>::iterator it=fnames.begin(); it!=fnames.end(); it++) {
		fprintf(stderr, "CHECKING %s\n", it->first);
		pair<dir_decl*, int> pr;
		if(check_func(it->second, main, &graph, pr)) { // check if it satisfies pre-condition
			// remove_code(it->first);
			fprintf(stderr, "FOUND %s\n", it->first);
			// pair<dir_decl*, int> pr = change_func(it->second, &graph);
			cnt = pr.second;
			if(pr.first) {
				it->second->expr4 = NULL;
				wklist = pr.first;
				statement *call = NULL;

				// remove while loop from main function
				walk_statement(main, main->end_stmt, it->first, &call, pr.first, &graph_decl);
			} else {
				fprintf(stderr, "%s\n", "EMPTY attrs");
			}
			return NULL;
		}
	}

	// move graph declaration to top.
	if(graph_decl != NULL) {
		graph_decl->prev->next = graph_decl->next;
		graph_decl->next->prev = graph_decl->prev;
		insert_statement(head, graph_decl, head->next);
	} else {
		graph_decl = find_global_graph(head);
		if(graph_decl == NULL) {
			return NULL;
		}
	}

	// Define struct node
	char temp[50];
	tree_typedecl *tp = new tree_typedecl();
	tp->datatype = STRUCT_TYPE;
	tp->compoundtype = 1;
	snprintf(temp, 50, "struct _flcn%d", cnt);
	tp->name = create_string(temp);
	tp->def = 1;
	snprintf(temp, 50, "_flcn%d", cnt);
	tp->vname = create_string(temp);

	// struct_declaration_list
	tree_typedecl *td = new tree_typedecl();
	td->libdatatype = POINT_TYPE;
	td->name = create_string("point ");
	dir_decl *d = new dir_decl();
	d->name = create_string("p");
	tree_decl_stmt *tds = createdeclstmt(td, NULL, d);
	d->ppts = graph->ppts;

	td = new tree_typedecl();
	td->datatype = INT_TYPE;
	td->name = create_string("int ");
	d = new dir_decl();
	d->name = create_string("dist");
	tds->next = createdeclstmt(td, NULL, d);

	tp->list = tds;
	statement *stmt = new statement();
	stmt->sttype = DECL_STMT;
	stmt->stdecl = createdeclstmt(tp, NULL, NULL);

	stmt->next = head;
	head->prev = stmt;
	head = stmt;


	// Define collection
	tp = new tree_typedecl();
	tp->libdatatype = COLLECTION_TYPE;
	tp->name = create_string("collection");
	d = new dir_decl();
	d->isparam = true;
	d->libdtype = COLLECTION_TYPE;
	d->name = create_string(wklist->name);
	tds = createdeclstmt(tp, NULL, d);
	stmt = new statement();
	stmt->sttype = DECL_STMT;
	stmt->stdecl = tds;	

	tree_typedecl *p = new tree_typedecl();
	p->datatype = STRUCT_TYPE;
	p->compoundtype = 1;
	snprintf(temp, 30, "struct _flcn%d", cnt);
	p->name = create_string(temp);
	p->def = 0;
	snprintf(temp, 30, "_flcn%d", cnt);
	p->vname = create_string(temp);
	d->tp1 = p;

	insert_statement(head, stmt, head->next);

	// insert OrderByIntValue
	tree_expr *tx = new tree_expr(wklist);
	tx->name = create_string(wklist->name);
	tx->lhs->ordered = true;
	tree_expr *bx = binaryopnode(tx, NULL, STRUCTREF, -1);
	bx->rhs = new tree_expr();
	bx->rhs->name = create_string("OrderByIntValue");
	bx->rhs->expr_type = FUNCALL;
	bx->kernel = 0;
	bx->nodetype = -10;

	// assignment_expression	
	tree_expr *t = new tree_expr();
	t->name = create_string("dist");
	t->nodetype = -10;

	assign_stmt *as = createassignlhsrhs(-1, NULL, t);
	t = binaryopnode(NULL, NULL, -1, TREE_INT);
	t->ival = 2;
	t->dtype = 0;
	as->next = createassignlhsrhs(-1, NULL, t);
	bx->kernel = 0;
	bx->rhs->arglist = as;

	stmt = createstmt(ASSIGN_STMT, NULL, NULL, 0);
	stmt->stassign = createassignlhsrhs(-1, NULL, bx);

	insert_statement(main->next, stmt, main->next->next);

	// insert start node to worklist
	
	// type specifier
	td = new tree_typedecl();
	td->datatype = STRUCT_TYPE;
	td->compoundtype = 1;
	snprintf(temp, 30, "struct _flcn%d", cnt);
	td->name = create_string(temp);
	td->def = 0;
	snprintf(temp, 30, "_flcn%d", cnt);
	td->vname = create_string(temp);
	
	int tcnt = falc_ext++;
	d= new dir_decl();
	snprintf(temp, 30, "_flcn%d", tcnt);
	d->name = create_string(temp);

	tree_decl_stmt *tstmt = new tree_decl_stmt();
	tstmt->lhs = td;
	tstmt->dirrhs = d;
	statement *st = new statement();
	st->sttype = DECL_STMT;
	st->stdecl = tstmt;

	insert_statement(stmt, st, stmt->next);
	stmt = st;


	// assign point to node
	// lhs of assignment
	tx = new tree_expr(d);
	tx->name = create_string(d->name);
	tx->nodetype = -1;
	tx = binaryopnode(tx, NULL, STRUCTREF, -1);
	tx->rhs = new tree_expr();
	tx->rhs->name = create_string("p");
	tx->rhs->expr_type = VAR;
	tx->kernel = 5;
	
	// assignment operator
	as = new assign_stmt();
	as->asstype = AASSIGN;
	as->lhs = tx;
	
	// rhs of assignment
	tx = new tree_expr(graph);
	tx->name = create_string(graph->name);
	tx->nodetype = -10;
	tx = binaryopnode(tx, NULL, STRUCTREF, -1);
	tx->rhs = new tree_expr();
	tx->rhs->name = create_string("points");
	tx->rhs->expr_type = ARRREF;
	tx->kernel = 0;

	// array exp
	t = binaryopnode(NULL, NULL, -1, TREE_INT);
	t->ival = 0;
	t->dtype = 0;
	assign_stmt *as2 = createassignlhsrhs(-1, NULL, t);
	tx->rhs->earr_list = as2;

	as->rhs = tx;

	statement *stmt1 = createstmt(ASSIGN_STMT, NULL, NULL, 0);
	stmt1->stmtno = 0;
	stmt1->stassign = as;

	insert_statement(stmt, stmt1, stmt->next);
	stmt = stmt1;


	// assign props
	tx = new tree_expr(d);
	tx->name = create_string(d->name);
	tx->nodetype = -1;
	tx = binaryopnode(tx, NULL, STRUCTREF, -1);
	tx->rhs = new tree_expr();
	tx->rhs->name = create_string("dist");
	tx->rhs->expr_type = VAR;
	tx->kernel = 5;
	
	// assignment operator
	as = new assign_stmt();
	as->asstype = AASSIGN;
	as->lhs = tx;
	as->semi = 1;

	// rhs of assignment
	tx = binaryopnode(NULL, NULL, -1, TREE_INT);
	tx->ival = 0;
	tx->dtype = 0;
	
	as->rhs = tx;

	stmt1 = createstmt(ASSIGN_STMT, NULL, NULL, 0);
	stmt1->stmtno = 0;
	stmt1->stassign = as;

	insert_statement(stmt, stmt1, stmt->next);
	stmt = stmt1;

	tx = new tree_expr(wklist);
	tx->nodetype = -10;
	tx->name = create_string(wklist->name);
	tx = binaryopnode(tx, NULL, STRUCTREF, -1);
	tx->rhs = new tree_expr();
	tx->rhs->name = create_string("add");
	tx->rhs->expr_type = VAR;
	tx->kernel = 0;

	// argument
	tree_expr *ex = new tree_expr(d);
	ex->nodetype = -1;
	ex->name = create_string(d->name);

	tx->rhs = funcallpostfix(tx->rhs, FUNCALL, 0, ex);

	stmt1 = createstmt(ASSIGN_STMT, NULL, NULL, 0);
	stmt1->stassign = createassignlhsrhs(-1, NULL, tx);

	insert_statement(stmt, stmt1, stmt->next);

	return head;
}