#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include "extension.h"
using namespace std;

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


static void change_func(statement *stmt) {
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
		tree_decl_stmt *nd = NULL;
		dir_decl *graph = NULL;
		while(params->next != NULL) {
			if(params->dirrhs == pt) {
				nd = params;
			} else if(params->lhs->libdatatype == GRAPH_TYPE) {
				graph = params->dirrhs;
			}
			params = params->next;
		}

		char temp[30];
		int nd_count = falc_ext;
		
		// create new node for worklist
		tree_typedecl *p = new tree_typedecl();
		p->datatype = STRUCT_TYPE;
		p->compoundtype = 1;
		snprintf(temp, 30, "struct _flcn%d *", falc_ext);
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
		dir_decl *wklist = d;

		p = new tree_typedecl();
		p->datatype = STRUCT_TYPE;
		p->compoundtype = 1;
		snprintf(temp, 30, "struct _flcn%d *", nd_count);
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
		p->d1 = graph;
		if(graph != NULL) p->ppts = graph->ppts;

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
			snprintf(temp, 30, "struct _flcn%d *", nd_count);
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
	}
}

void process(map<char*, statement*> &fnames) {
	statement *main = get_function(fnames, "main");
	if(main == NULL) {
		fprintf(stderr, "%s\n", "main function does not exist.");
		exit(1);
	}

	for(std::map<char*, statement*>::iterator it=fnames.begin(); it!=fnames.end(); it++) {
		if(check(it->second)) { // check if it satisfies pre-condition
			// remove_code(it->first);
			fprintf(stderr, "FOUND %s\n", it->first);
			change_func(it->second);
		}
	}
}