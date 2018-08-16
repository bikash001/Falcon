#include<cstdio>
#include <set>
#include <map>
#include <cstdlib>
#include "falctypes.h"
using namespace std;

std::set<statement*> foreach_list;
extern char* libdtypenames[10];
extern std::map<char*, statement*> fnames;
extern std::map<char*, statement*> fnamescond;
extern tree_expr *binaryopnode(tree_expr *lhs,tree_expr *rhs,enum EXPR_TYPE etype,int ntype);
extern assign_stmt *createassignlhsrhs(enum ASSIGN_TYPE x,tree_expr *lhs,tree_expr *rhs);
extern int CONVERT_VERTEX_EDGE;
int falc_ext = 0;	// variable names used by falcon extension "_flcn{falc_ext}"
std::map<dir_decl*, statement*> graph_insert_point; //store location to insert gpu graph
extern tree_expr *temp_stmt_add;

// stores dynamic property of each graph
std::map<dir_decl*, std::pair<statement*, std::map<dir_decl*, statement*>*>*> graphs;

// Returns the pointer to SBLOCK_STMT of function.
// Used to insert new statements at the beginning of a function in case of verted-edge conversion.
static statement* insert_position(const char *name)
{
	for(std::map<char*, statement*>::iterator it = fnames.begin(); it!=fnames.end(); it++)
	{	
		if(strcmp(name, it->first) == 0) { 
			statement *next = it->second->next->next;		// since first next is SBLOCK_STMT
			if (next->sttype == FOREACH_STMT && (next->itr == NBRS_ITYPE || 
				next->itr == INNBRS_ITTYPE || next->itr == OUTNBRS_ITYPE)) {
					return next->prev; // return pointer to SBLOCK_STMT
			} else {
				return NULL;
			}
		}
	}
	return NULL;
}

// Returns the statement which defines a function.
static statement* get_function(const char *name) {
	for(std::map<char*, statement*>::iterator it = fnames.begin(); it!=fnames.end(); it++) {
		if (strcmp(name, it->first) == 0) {
			return it->second;
		}
	}
	return NULL;
}

// Replaces graph functions like getedge and getweight by edge and 
// its field in conversion of vertex based to edge based.
void replace_functions(statement *begin, statement *end, dir_decl *p, dir_decl *q, dir_decl *edge)
{
	// printf("TEST %p %p\n", begin, begin->end_stmt);
	statement *curr = begin;
	while(curr!=NULL && curr!=end) {
		// printf("line-70 %p %d\n", curr, curr->sttype);
		if(curr->sttype == ASSIGN_STMT) {
			tree_expr *exp = curr->stassign->rhs->rhs;
			if(exp && exp->expr_type==FUNCALL) {// && strcmp(exp->name, "getweight")==0) {
				// printf("line %d\n", curr->lineno);
				// printf("l59 %s\n", exp->name);
				if(strcmp(exp->name, "getweight") == 0) {
					assign_stmt *params = exp->arglist;
					dir_decl *a = params->rhs->lhs;
					dir_decl *b = params->next->rhs->lhs;
					if((a==p && b==q)) {
						// printf("EXTENSION-62\n");
						exp->expr_type = VAR;
						exp->arglist = NULL;
						strcpy(exp->name, "weight");
						curr->stassign->rhs->lhs = new tree_expr(edge);
						// curr->stassign->rhs->lhs->lhs = edge;
					}
				} else if(strcmp(exp->name, "getedge") == 0) {
					assign_stmt *params = exp->arglist;
					dir_decl *a = params->rhs->lhs;
					dir_decl *b = params->next->rhs->lhs;
					if((a==p && b==q)) {
						curr->stassign->rhs = new tree_expr(edge);
					}
				}
			}
		} else if (curr->sttype == IF_STMT || curr->sttype == SINGLE_STMT) {
			if(curr->f1) {
				replace_functions(curr->f1, end, p, q, edge);
			}
			if(curr->f2) {
				replace_functions(curr->f2, end, p, q, edge);
			}
		}
		curr = curr->next;
	}
}

// Converts vertex to edge based and vice-versa
void convert_vertex_edge()
{
	for(std::set<statement*>::iterator ii = foreach_list.begin(); ii != foreach_list.end(); ++ii)
	{
		statement *forstmt = *ii;
		if (CONVERT_VERTEX_EDGE==1 && forstmt->itr == POINT_ITYPE) {
			statement *target = insert_position(forstmt->stassign->rhs->name); //SBLOCK_STMT
			if(target) {
				statement *next_stmt = target->next;	//FOREACH_STMT
				tree_decl_stmt *params = target->prev->stdecl->dirrhs->params;
				dir_decl *graph = NULL;
				struct extra_ppts *ppts = NULL;
				dir_decl *d = NULL;

				while(params) {
					tree_typedecl *type = params->lhs;
					while(type) {
						if (type->libdatatype == POINT_TYPE) {
							type->libdatatype = EDGE_TYPE;
							d = new dir_decl(params->dirrhs);
							d->name = malloc(sizeof(char)*10);
							snprintf(d->name, 10, "_flcn%d", falc_ext++);
							// dir_decl *d = params->dirrhs;
							d->libdtype = EDGE_TYPE;
							params->dirrhs = d;
							ppts = d->ppts;
							break;
						} else if(type->libdatatype == GRAPH_TYPE) {
							graph = params->dirrhs;
							break;
						}
						type = type->next;
					}
					params = params->next;
				}

				if (forstmt->expr4) {
					if (next_stmt->itr == OUTNBRS_ITYPE) {
						forstmt->expr4->edge_type = 1;
					} else {
						forstmt->expr4->edge_type = 0;
					}
				}

				// foreach iterator
                forstmt->itr = EDGES_ITYPE;
                snprintf(forstmt->expr1->lhs->name, 10, "_flcn%d", falc_ext-1);
	        	forstmt->expr3 = NULL;


	        	// type declaration
	        	tree_typedecl *ptr = new tree_typedecl();
			    ptr->libdatatype = POINT_TYPE;	//point type
			    ptr->name=malloc(sizeof(char )*10);
			    strcpy(ptr->name, "point ");
			    ptr->ppts = ppts;

			   	// variable
		        dir_decl *pointA = next_stmt->expr2->lhs;
			    pointA->rhs = NULL;
                pointA->parent = graph;
                pointA->libdtype = POINT_TYPE;
                pointA->dtype = -1;
                pointA->forit = 0;
                pointA->ppts = ppts;

                dir_decl *pointB = next_stmt->expr1->lhs;
                pointB->rhs = NULL;
                pointB->parent = graph;
                pointB->libdtype = POINT_TYPE;
                pointB->dtype = -1;
                pointB->forit = 0;
                pointB->ppts = ppts;

                // initializer
		  		tree_expr *expr = new tree_expr(d);
			    
			    tree_expr *src = new tree_expr();
			    src->name = malloc(sizeof(char)*4);
			    strcpy(src->name, "src");
			    src->expr_type = VAR;
			    tree_expr *dst = new tree_expr();
			    dst->name = malloc(sizeof(char)*4);
			    strcpy(dst->name, "dst");
			    dst->expr_type = VAR;

				tree_expr *node1 = binaryopnode(expr,NULL,STRUCTREF,-1);
				tree_expr *node2 = binaryopnode(expr,NULL,STRUCTREF,-1);
				if (next_stmt->itr == 4) { // outnbrs
                    node1->rhs = src;
                    node2->rhs = dst;
                } else {
                    node1->rhs = dst;
                    node2->rhs = src;
                }
	        	
	        	pointA->rhs = node1;
	        	pointB->rhs = node2;
	        	// pointA->nextv = pointB;

	        	// create statement
	        	tree_decl_stmt *tstmt = new tree_decl_stmt();
				tstmt->lhs=ptr;
				tstmt->dirrhs=pointA;
				statement *stmt=new statement();
				stmt->sttype=DECL_STMT;
				stmt->stdecl = tstmt;

				tstmt = new tree_decl_stmt();
				tstmt->lhs = ptr;
				tstmt->dirrhs = pointB;
				statement *stmt2 = new statement();
				stmt2->sttype = DECL_STMT;
				stmt2->stdecl = tstmt;

				target->next = stmt;
				stmt->prev = target;
				stmt->next = stmt2;
				stmt2->prev = stmt;
				
				if (!forstmt->expr4) {
					statement *open_bracket = new statement();
					open_bracket->sttype = SBLOCK_STMT;
					stmt2->next = open_bracket;
					open_bracket->prev = stmt2;
					open_bracket->next = next_stmt->next;
					next_stmt->next->prev = open_bracket;
				} else {
					stmt2->next = next_stmt->next;
					next_stmt->next->prev = stmt2;
				}

				// remove extra close bracket
				statement *end_stmt = next_stmt->end_stmt;
				end_stmt->prev->next = end_stmt->next;
				end_stmt->next->prev = end_stmt->prev;

				// add close bracket at the end of function
				if (!forstmt->expr4) {
					statement *right = target->prev->end_stmt;
					statement *left = right->prev;
					left->next = end_stmt;
					end_stmt->prev = left;
					end_stmt->next = right;
					right->prev = end_stmt;
					end_stmt->sttype = EBLOCK_STMT;
				}
				replace_functions(target->prev, target->prev->end_stmt, pointA, pointB, d);
			}
		} else if (CONVERT_VERTEX_EDGE==2 && forstmt->itr == EDGES_ITYPE) {
			// foreach iterator
            forstmt->itr = POINT_ITYPE;
            snprintf(forstmt->expr1->lhs->name, 10, "_flcn%d", falc_ext++);
        	forstmt->expr3 = NULL;

        	statement *function = get_function(forstmt->stassign->rhs->name);

        	// change parameter
        	tree_decl_stmt *params = function->stdecl->dirrhs->params;
			struct extra_ppts *ppts = NULL;
			dir_decl *point = NULL;		// new parameter of Point type
			dir_decl *edge = NULL;	// old parameter of Edge type
			while(params) {
				tree_typedecl *type = params->lhs;
				while(type) {
					if (type->libdatatype == EDGE_TYPE) {
						type->libdatatype = POINT_TYPE;
						point = new dir_decl(params->dirrhs);
						point->name = malloc(sizeof(char)*10);
						edge = params->dirrhs;
						snprintf(point->name, 10, "_flcn%d", falc_ext++);
						point->libdtype = EDGE_TYPE;
						params->dirrhs = point;
						ppts = point->ppts;
						edge->parent = point->parent;
						break;
					}
					type = type->next;
				}
				params = params->next;
			}

        	// create foreach statement inside the function
        	statement *foreach_stmt = new statement();
        	foreach_stmt->sttype = FOREACH_STMT;
        	foreach_stmt->feb = 1;
        	foreach_stmt->itr = OUTNBRS_ITYPE;
        	dir_decl *d1 = new dir_decl();
        	d1->name = malloc(sizeof(char)*10);
        	snprintf(d1->name, 10, "_flcn%d", falc_ext++);
        	d1->parent = point->parent;
        	d1->libdtype = ITERATOR_TYPE;
        	d1->dtype = -1;
        	d1->forit = -1;
        	d1->it = OUTNBRS_ITYPE;
        	foreach_stmt->expr1 = new tree_expr(d1);
        	foreach_stmt->expr2 = new tree_expr(point);
        	
        	// insert foreach statement
        	statement *right = function->next->next;
        	function->next->next = foreach_stmt;
        	foreach_stmt->prev = function->next;
        	
			// type declaration
        	tree_typedecl *ptr = new tree_typedecl();
		    ptr->libdatatype = EDGE_TYPE;	//EDGE type
		    ptr->name=malloc(sizeof(char )*10);
		    strcpy(ptr->name, "edge ");
		    ptr->ppts = ppts;

		  	tree_expr *lhs = new tree_expr(edge->parent);
			tree_expr *rhs = new tree_expr();
			rhs->name = malloc(sizeof(char)*10);
			strcpy(rhs->name, "getedge");
			rhs->expr_type = VAR;
			tree_expr *node = binaryopnode(lhs, rhs, STRUCTREF, -1);
			node->nodetype = -10;
			node->kernel = 0;

			// create arguments
			tree_expr *pointA = new tree_expr(point);	// first argument
			pointA->name = malloc(sizeof(char)*10);
			snprintf(pointA->name, 10, "_flcn%d", falc_ext-2);
			pointA->nodetype = -1;
			tree_expr *pointB = new tree_expr(d1);  		// second argument
			pointB->name = malloc(sizeof(char)*4);
			snprintf(pointB->name, 10, "_flcn%d", falc_ext-1);
			pointB->nodetype = -1;
			assign_stmt *t1=createassignlhsrhs(-1,NULL,pointA);
			assign_stmt *t2=createassignlhsrhs(-1,NULL,pointB);
			t1->next = t2;

			rhs->expr_type = FUNCALL;
			rhs->arglist = t1;
			edge->rhs = NULL;
			edge->rhs = node;

			// get edge from vertices
        	tree_decl_stmt *tstmt = new tree_decl_stmt();
			tstmt->lhs = ptr;
			tstmt->dirrhs = edge;
			statement *stmt = new statement();
			stmt->sttype = DECL_STMT;
			stmt->stdecl = tstmt;

			// insert declaration statement
			foreach_stmt->next = stmt;
			stmt->prev = foreach_stmt;
        	
        	statement *empty_stmt;
        	if(forstmt->expr4) {
        		empty_stmt = new statement();
        		empty_stmt->sttype = EMPTY_STMT;
        		stmt->next = empty_stmt;
        		empty_stmt->prev = stmt;
        		right->prev = empty_stmt;
	        	empty_stmt->next = right;
        	} else {
        		right->prev = stmt;
	        	stmt->next = right;
        	}

        	// insert close bracket EBLOCK_STMT
        	statement *end_foreach = new statement();
        	end_foreach->sttype = FOREACH_EBLOCK_STMT;
        	foreach_stmt->end_stmt = end_foreach;

        	statement *lstmt = function->end_stmt->prev;
        	statement *rstmt = function->end_stmt;
        	
        	// insert close bracket for conditional foreach
        	if (forstmt->expr4) {
        		statement *eb = new statement();
        		eb->sttype = EBLOCK_STMT;
        		empty_stmt->end_stmt = eb;
        		lstmt->next = eb;
        		eb->prev = lstmt;
        		lstmt = eb;
        	}

        	lstmt->next = end_foreach;
        	end_foreach->prev = lstmt;
        	end_foreach->next = rstmt;
        	rstmt->prev = end_foreach;
		}
	}
}

// Replaces cpu graphs by gpu graphs in foreach-statement and converts function 
// parameters to gpu type.
void convert_to_gpu(map<dir_decl*, dir_decl*> &tab)
{
	for(std::set<statement*>::iterator ii = foreach_list.begin(); ii != foreach_list.end(); ++ii)
	{
		statement *forstmt = *ii;
		dir_decl *parent_graph = tab.find(forstmt->expr2->lhs)->second;
		forstmt->expr2->lhs = parent_graph;		// replace cpu graph by gpu graph
		forstmt->expr2->name = parent_graph->name;

		statement *target = get_function(forstmt->stassign->rhs->name);
		target->ker = 1;	// set function to kernel

		// change argument
		assign_stmt *arglist = forstmt->stassign->rhs->arglist;
		while(arglist) {
			if(arglist->rhs->lhs->libdtype == GRAPH_TYPE) {
				arglist->rhs->lhs = parent_graph;
				arglist->rhs->name = malloc(sizeof(char)*(1+strlen(parent_graph->name)));
				strcpy(arglist->rhs->name, parent_graph->name);
				// arglist->rhs->name = parent_graph->name;
				break;
			} else if(arglist->rhs->lhs->it >= 0) {
				arglist->rhs->lhs->parent = parent_graph;
			}
			arglist = arglist->next;
		}

		tree_decl_stmt *params = target->stdecl->dirrhs->params;
		
		while(params) {
			tree_typedecl *type = params->lhs;
			while(type) {
				// graph, point or edge
				if (type->libdatatype >= 0 && type->libdatatype <= 2) {
					params->dirrhs->gpu = 1;
					// if(type->libdatatype == 0) {
					// 	params->dirrhs->ppts = parent_graph->ppts;
					// }
					break;
				}
				type = type->next;
			}
			params = params->next;
		}		
	}
}

// Finds local and global variables used in an expression
void get_variables_util_exp(set<dir_decl *> &lset, set<dir_decl *> &gset, tree_expr *expr)
{
	if(expr->expr_type == VAR) {
		if(expr->lhs == NULL) {
			// printf("NULL %s\n", expr->name);
			return;	// field of structure
		}
		if(lset.find(expr->lhs) == lset.end()) {
			gset.insert(expr->lhs);
			// printf("TEST7 %s\n", expr->lhs->name);
		} else {
			// printf("TEST8 %s\n", expr->lhs->name);
		}
	} else {
		if(expr->lhs) {
			get_variables_util_exp(lset, gset, expr->lhs);
		}
		if(expr->rhs) {
			get_variables_util_exp(lset, gset, expr->rhs);
		}
		if(expr->earr_list) {
			assign_stmt *astmt = expr->earr_list;
			while(astmt) {
				if(astmt->lhs) {
					get_variables_util_exp(lset, gset, astmt->lhs);
				}
				if(astmt->rhs) {
					get_variables_util_exp(lset, gset, astmt->rhs);
				}
				astmt = astmt->next;
			}
		}
		if(expr->next) {
			get_variables_util_exp(lset, gset, expr->next);
		}
		if(expr->arglist) {
			assign_stmt *astmt = expr->arglist;
			while(astmt) {
				if(astmt->lhs) {
					get_variables_util_exp(lset, gset, astmt->lhs);
				}
				if(astmt->rhs) {
					get_variables_util_exp(lset, gset, astmt->rhs);
				}
				astmt = astmt->next;
			}
		}
	}
}

// Utility function to find global and local variables.
void get_variables_util(set<dir_decl *> &local_set, set<dir_decl *> &global_set, statement *begin, statement *end)
{
	while(begin != NULL && begin != end){
		if(begin->sttype == DECL_STMT) {
			dir_decl *expr = begin->stdecl->dirrhs;
			while(expr) {
				// printf("TEST %s\n", expr->name);
				if(expr->rhs && expr->rhs->expr_type == VAR) {
					if(local_set.find(expr->rhs->lhs) == local_set.end()) {
						global_set.insert(expr->rhs->lhs);
						// printf("TEST1 %s\n", expr->rhs->name);
					}
				}
				local_set.insert(expr);
				expr = expr->nextv;
			}
		} else {
			if(begin->sttype == FOREACH_STMT) {
				local_set.insert(begin->expr1->lhs);
				// printf("TEST3 %s\n", begin->expr1->name);
				if(local_set.find(begin->expr2->lhs) == local_set.end()) {
					global_set.insert(begin->expr2->lhs);
					// printf("TEST2 %s\n", begin->expr2->lhs->name);
				}
				if(begin->expr4) {
					get_variables_util_exp(local_set, global_set, begin->expr4);
				}
				if(begin->stassign) {
					assign_stmt *astmt = begin->stassign;
					if(astmt->lhs) {
						get_variables_util_exp(local_set, global_set, astmt->lhs);
					}
					if(astmt->rhs) {
						get_variables_util_exp(local_set, global_set, astmt->rhs);
					}
				}
			} else if(begin->sttype == FOR_STMT) {
				tree_decl_stmt *stmt = begin->f1->stdecl;
				if(stmt) {
					dir_decl *expr = stmt->dirrhs;
					while(expr) {
						// printf("TEST4 %s\n", expr->name);
						if(expr->rhs && expr->rhs->expr_type == VAR) {
							if(local_set.find(expr->rhs) == local_set.end()) {
								global_set.insert(expr->rhs);
								// printf("TEST5 %s\n", expr->rhs->name);
							}
						}
						local_set.insert(expr);
						expr = expr->nextv;
					}
				} else {
					assign_stmt *astmt = begin->f1->stassign;
					if(astmt == NULL) {
						printf("ASSIGN ERROR - EXTENSION-466\n");
						exit(0);
					} else {
						if(astmt->lhs) {
							get_variables_util_exp(local_set, global_set, astmt->lhs);
						}
						if(astmt->rhs) {
							get_variables_util_exp(local_set, global_set, astmt->rhs);
						}
					}
				}
				if(begin->f2 && begin->f2->stassign) {
					assign_stmt *astmt = begin->f2->stassign;
					if(astmt->lhs) {
						get_variables_util_exp(local_set, global_set, astmt->lhs);
					}
					if(astmt->rhs) {
						get_variables_util_exp(local_set, global_set, astmt->rhs);
					}
				}
				if(begin->f3 && begin->f3->stassign) {
					assign_stmt *astmt = begin->f3->stassign;
					if(astmt->lhs) {
						get_variables_util_exp(local_set, global_set, astmt->lhs);
					}
					if(astmt->rhs) {
						get_variables_util_exp(local_set, global_set, astmt->rhs);
					}
				}
			} else if(begin->sttype == ASSIGN_STMT) {
				assign_stmt *astmt = begin->stassign;
				while(astmt) {	
					if(astmt->lhs) {
						get_variables_util_exp(local_set, global_set, astmt->lhs);
					}
					if(astmt->rhs) {
						get_variables_util_exp(local_set, global_set, astmt->rhs);
					}
					astmt = astmt->next;
				}
			} else {
				if(begin->expr1) {
					get_variables_util_exp(local_set, global_set, begin->expr1);
				}
				if(begin->expr2) {
					get_variables_util_exp(local_set, global_set, begin->expr2);
				}
				if(begin->expr3) {
					get_variables_util_exp(local_set, global_set, begin->expr3);
				}
				if(begin->expr4) {
					get_variables_util_exp(local_set, global_set, begin->expr4);
				}
				if(begin->expr5) {
					get_variables_util_exp(local_set, global_set, begin->expr5);
				}				
				if(begin->f1) {
					get_variables_util(local_set, global_set, begin->f1, end);
				}
				if(begin->f2) {
					get_variables_util(local_set, global_set, begin->f2, end);
				}
				if(begin->f3) {
					get_variables_util(local_set, global_set, begin->f3, end);
				}
			}
		}
		begin = begin->next;
	}
}

int log = 0;
// Walks through expression and replaces old_decl by new_decl.
void walk_exp(dir_decl* old_decl, dir_decl* new_decl, tree_expr *expr)
{
	if(expr == NULL) {
		return;
	}
	if(expr->expr_type == VAR) {
		if(log) {
			printf("LOG %s\n", expr->name);
		}
		if(expr->lhs == old_decl) {
			// printf("TESTING %s %s\n", expr->lhs->name, expr->rhs->name);
			expr->lhs = new_decl;
			expr->name = malloc(sizeof(char)*(1+strlen(new_decl->name)));
			strcpy(expr->name, new_decl->name);
			// expr->name = new_decl->name;
			return;
		}
	} else {
		if(expr->lhs) {
			walk_exp(old_decl, new_decl, expr->lhs);
		}
		if(expr->rhs) {
			walk_exp(old_decl, new_decl, expr->rhs);
		}
		if(expr->earr_list) {
			assign_stmt *astmt = expr->earr_list;
			while(astmt) {
				if(astmt->lhs) {
					walk_exp(old_decl, new_decl, astmt->lhs);
				}
				if(astmt->rhs) {
					walk_exp(old_decl, new_decl, astmt->rhs);
				}
				astmt = astmt->next;
			}
		}
		if(expr->next) {
			walk_exp(old_decl, new_decl, expr->next);
		}
		if(expr->arglist) {
			assign_stmt *astmt = expr->arglist;
			while(astmt) {
				if(astmt->lhs) {
					walk_exp(old_decl, new_decl, astmt->lhs);
				}
				if(astmt->rhs) {
					walk_exp(old_decl, new_decl, astmt->rhs);
				}
				astmt = astmt->next;
			}
		}
	}
}

void walk_util(dir_decl *old_decl, dir_decl *new_decl, statement *stmt)
{
	assign_stmt *astmt = stmt->stassign;
	while(astmt) {	
		if(astmt->lhs) {
			walk_exp(old_decl, new_decl, astmt->lhs);
		}
		if(astmt->rhs) {
			walk_exp(old_decl, new_decl, astmt->rhs);
		}
		astmt = astmt->next;
	}
}

// Utility function to walk through statements and call wal_exp() to replace old variables with new
void walk_statement(dir_decl* old_decl, dir_decl* new_decl, statement *begin)
{
	while(begin && begin->sttype != FUNCTION_EBLOCK_STMT){
		if(begin->sttype == DECL_STMT) {
			dir_decl *expr = begin->stdecl->dirrhs;
			while(expr) {
				// if(expr->rhs && expr->rhs->expr_type == VAR) {
				// 	if(expr->rhs->lhs == old_decl) {
				// 		expr->rhs->lhs = new_decl;
				// 	}
				// }
				if(expr->rhs) {
					if(expr->rhs->expr_type == VAR) {
						if(expr->rhs->lhs == old_decl) {
							expr->rhs->lhs = new_decl;
						}	
					} else {
						walk_exp(old_decl, new_decl, expr->rhs);
					}
				}
				expr = expr->nextv;
			}
		} else if(begin->sttype == FOR_STMT) {
			if(begin->f1) walk_util(old_decl, new_decl, begin->f1);
			if(begin->f2) walk_util(old_decl, new_decl, begin->f2);
			if(begin->f3) walk_util(old_decl, new_decl, begin->f3);
		} else if(begin->sttype == ASSIGN_STMT) {
			walk_util(old_decl, new_decl, begin);
		} else if(begin->sttype != FOREACH_STMT) {
			if(begin->expr1) {
				walk_exp(old_decl, new_decl, begin->expr1);
			}
			if(begin->expr2) {
				walk_exp(old_decl, new_decl, begin->expr2);
			}
			if(begin->expr3) {
				walk_exp(old_decl, new_decl, begin->expr3);
			}
			if(begin->expr4) {
				walk_exp(old_decl, new_decl, begin->expr4);
			}
			if(begin->expr5) {
				walk_exp(old_decl, new_decl, begin->expr5);
			}				
			if(begin->f1) {
				walk_statement(old_decl, new_decl, begin->f1);
			}
			if(begin->f2) {
				walk_statement(old_decl, new_decl, begin->f2);
			}
			if(begin->f3) {
				walk_statement(old_decl, new_decl, begin->f3);
			}
		}
		
		begin = begin->next;
	}
}

// Inserts a statement stmt in between lhs and rhs
void insert_statement(statement *lhs, statement *stmt, statement *rhs)
{
	lhs->next = stmt;
	stmt->prev = lhs;
	stmt->next = rhs;
	rhs->prev = stmt;
}

// Creates a declaration statement.
statement* create_decl_statement(LIBDATATYPE type)
{
	// type declaration
	tree_typedecl *ptr = new tree_typedecl();
    ptr->libdatatype = type;
    ptr->name=malloc(sizeof(char )*10);
    strcpy(ptr->name, libdtypenames[type]);
	
	// declarator
	dir_decl *d = new dir_decl();
	d->name = malloc(sizeof(char)*10);
	snprintf(d->name, 10, "_flcn%d", falc_ext++);
	d->read = 1;
	d->libdtype = type;
	d->gpu = 1;

	tree_decl_stmt *tstmt = new tree_decl_stmt();
	tstmt->lhs=ptr;
	tstmt->dirrhs=d;
	statement *stmt=new statement();
	stmt->sttype=DECL_STMT;
	stmt->stdecl = tstmt;

	return stmt;
}

// Copies graph properties from one graph to another
void copy_graph_properties(dir_decl *dg, dir_decl *new_graph)
{
	if(dg->ppts!=NULL){
      extra_ppts *newppts,*oldppts=dg->ppts,*head;
      newppts=malloc(sizeof(struct extra_ppts));
      newppts->parent=NULL;
      newppts->name=malloc(sizeof(char)*100);
      strncpy(newppts->name,oldppts->name,strlen(oldppts->name));
      newppts->libdtype=oldppts->libdtype;
      newppts->t1=oldppts->t1;//mutliple entries point to same type
      newppts->var2=oldppts->var2;
      newppts->var1=oldppts->var1;
      newppts->var3=oldppts->var3;
      newppts->val2=oldppts->val2;
      newppts->next=NULL;
	  newppts->parent=dg;
      head=newppts;
      oldppts=oldppts->next;
      while(oldppts){
        newppts->next=malloc(sizeof(struct extra_ppts));
        newppts=newppts->next;
        newppts->parent=NULL;
        newppts->name=malloc(sizeof(char)*100);
        strcpy(newppts->name,oldppts->name);
        newppts->libdtype=oldppts->libdtype;
        newppts->t1=oldppts->t1;
        newppts->var2=new dir_decl();
        newppts->val2=oldppts->val2;
        newppts->var2->name=malloc(sizeof(char)*100);
        if(oldppts->var2!=NULL)strncpy(newppts->var2->name,oldppts->var2->name,strlen(oldppts->var2->name));
        newppts->next=NULL;
        oldppts=oldppts->next;
      }
      new_graph->ppts=head;
    }
    
}

// Creates assignment statement
statement* create_assign_statement(dir_decl *lhs, dir_decl *rhs)
{
	// copy graph properties
	copy_graph_properties(rhs, lhs);

	assign_stmt *ptr=new assign_stmt();
    ptr->asstype = AASSIGN;
    tree_expr *exp_lhs = new tree_expr(lhs);
    exp_lhs->name = malloc(sizeof(char)*(1+strlen(lhs->name)));
   	strcpy(exp_lhs->name, lhs->name);
    exp_lhs->kernel = 5;
    tree_expr *exp_rhs = new tree_expr(rhs);
    exp_rhs->name = malloc(sizeof(char)*(1+strlen(rhs->name)));
   	strcpy(exp_rhs->name, rhs->name);
    exp_rhs->kernel = 5;
    ptr->lhs = exp_lhs;
    ptr->rhs = exp_rhs;

    statement *stmt=new statement();
    stmt->sttype= ASSIGN_STMT;
    stmt->stassign = ptr;
    return stmt;
}

// Replaces cpu graph by gpu graph
void replace_graphs(map<dir_decl*, dir_decl*> &tab)
{
	for(map<dir_decl*, dir_decl*>::iterator itr=tab.begin(); itr!=tab.end(); ++itr) {
		statement *start = graph_insert_point.find(itr->first)->second->next->next->next;

		walk_statement(itr->first, itr->second, start);
	}
}

// Inserts a new graph node
void insert_graph_node()
{
	map<dir_decl*, dir_decl*> tab;
	for(map<dir_decl*, statement*>::iterator itr=graph_insert_point.begin(); itr!=graph_insert_point.end(); itr++) {
		statement *begin = itr->second;
		statement *end = itr->second->next;
		statement *stmt = create_decl_statement(GRAPH_TYPE);
		insert_statement(begin, stmt, end);
	
		tab[itr->first] = stmt->stdecl->dirrhs;
		stmt->stdecl->dirrhs->libstable = itr->first->libstable;

		stmt = create_assign_statement(stmt->stdecl->dirrhs, itr->first);
		insert_statement(end->prev, stmt, end);
	}
	convert_to_gpu(tab);
	replace_graphs(tab);
}

// Finds global variables using in kernel
void get_variables()
{
	// for(map<dir_decl*, pair<statement*, map<dir_decl*, statement*>*>*>::iterator ii = graphs.begin(); ii != graphs.end(); ++ii) {
	// 	map<dir_decl*, statement*> *graph = ii->second->second;
	// 	printf("GRAPH %s\n", ii->first->name);
	// 	for(map<dir_decl*, statement*>::iterator itr = graph->begin(); itr!=graph->end(); ++itr) {
	// 		printf("-->%s\n", itr->first->name);
	// 	}
	// }
	// return;

	std::set<dir_decl *> global_set;
	
	for(std::set<statement*>::iterator ii = foreach_list.begin(); ii != foreach_list.end(); ++ii)
	{
		std::set<dir_decl *> local_set;
		statement *forstmt = *ii;
		statement *target = get_function(forstmt->stassign->rhs->name);
		tree_decl_stmt *params = target->stdecl->dirrhs->params;
		
		while(params) {
			local_set.insert(params->dirrhs);
			params = params->next;
		}

		get_variables_util(local_set, global_set, target->next->next, target->end_stmt);
	}

	for(set<dir_decl *>::iterator ii = global_set.begin(); ii != global_set.end(); ++ii) {
		(*ii)->gpu = 1;
	}
}