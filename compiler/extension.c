#include<cstdio>
#include <set>
#include <map>
#include <vector>
#include <cstdlib>
#include "falctypes.h"
using namespace std;

std::vector<statement*> foreach_list;
std::vector<statement*> sections_stmts;
extern char* libdtypenames[10];
extern std::map<char*, statement*> fnames;
extern std::map<char*, statement*> fnamescond;
extern tree_expr *binaryopnode(tree_expr *lhs,tree_expr *rhs,enum EXPR_TYPE etype,int ntype);
extern assign_stmt *createassignlhsrhs(enum ASSIGN_TYPE x,tree_expr *lhs,tree_expr *rhs);
extern int CONVERT_VERTEX_EDGE;
int falc_ext = 0;	// variable names used by falcon extension "_flcn{falc_ext}"
int stream_count = 0;
std::map<dir_decl*, statement*> graph_insert_point; //store location to insert gpu graph
extern tree_expr *temp_stmt_add;

// stores dynamic property of each graph
std::map<dir_decl*, std::pair<statement*, std::map<dir_decl*, statement*>*>*> graphs;

// stores set declarations
std::map<dir_decl*, statement*> fx_sets;
//stores collection declaration
std::map<dir_decl*, statement*> fx_collections;
struct comparator;
static void walk_find_prop_util(map<dir_decl*, set<char*, comparator> > &rmp, map<dir_decl*, set<char*, comparator> > &wmp, assign_stmt *astmt, dir_decl *dg);
static void replace_map_variables(map<dir_decl*, set<char*, comparator> > &tab, tree_decl_stmt *params, assign_stmt *args);
static bool same_level(statement *start, statement *end, statement *goal);
static char* create_string(char *str);
static statement* function_end(statement *stmt);
static dir_decl* find_var(map<dir_decl*, set<char*, comparator> > &mp, char *cc);
static void gencode_properties(map<dir_decl*, set<char*, comparator> > &mp, map<dir_decl*, map<dir_decl*, set<char*, comparator> > > &tab, statement *temp);
extern int TOT_GPU_GRAPH;

struct comparator
{
	bool operator()(char *a, char *b) const{
		return strcmp(a, b) < 0;
	}
};


// check if the attribute used is inbuilt
bool is_lib_attr(LIBDATATYPE type, const char *name)
{
	if(type == POINT_TYPE) {
		// "minEdge","maxEdge","x","y","nbrs","inNbrs","outNbrs","isdel"
		int len = strlen(name);
		if(len == 1) {
			if(name[0]=='x' || name[1]=='y') return true;
		} else if(len == 4) {
			return strcmp(name, "nbrs")==0;
		} else if(len == 5) {
			return strcmp(name, "isdel")==0;
		} else if(len == 6) {
			return strcmp(name, "inNbrs")==0;
		} else if(len == 7) {
			if(strcmp("minEdge", name)==0) return true;
			else if(strcmp("maxEdge", name)==0) return true;
			else if(strcmp("outNbrs", name)==0) return true;
		}
	} else if(type == EDGE_TYPE) {
		// "src","dst","weight","isdel"
		int len = strlen(name);
		if(len==3) {
			if(strcmp("src", name)==0) return true;
			else if(strcmp("dst", name)==0) return true;
		} else if(len == 5) {
			return strcmp("isdel", name)==0;
		} else if(len == 6) {
			return strcmp("weight", name)==0;
		}
	}
	return false;
}

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
static void replace_functions(statement *begin, statement *end, dir_decl *p, dir_decl *q, dir_decl *edge)
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
	for(std::vector<statement*>::iterator ii = foreach_list.begin(); ii != foreach_list.end(); ++ii)
	{
		statement *forstmt = *ii;
		if (CONVERT_VERTEX_EDGE==1 && forstmt->itr == POINT_ITYPE && forstmt->stassign != NULL) {
			statement *target = insert_position(forstmt->stassign->rhs->name); //SBLOCK_STMT
			if(target) {
				statement *next_stmt = target->next;	//FOREACH_STMT
				tree_decl_stmt *params = target->prev->stdecl->dirrhs->params;
				dir_decl *graph = NULL;
				extra_ppts *ppts = NULL;
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
        	if(function == NULL) {
				fprintf(stderr, "Error-313: function %s not defined.\n", forstmt->stassign->rhs->name);
				exit(0);
			}

        	// change parameter
        	tree_decl_stmt *params = function->stdecl->dirrhs->params;
			extra_ppts *ppts = NULL;
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
        		empty_stmt->lineno = 1; // used in codegen.c
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


static void change_cpu_graph(statement *forstmt, dir_decl *gpu_graph)
{
	forstmt->expr2->lhs = gpu_graph;		// replace cpu graph by gpu graph
	forstmt->expr2->name = gpu_graph->name;

	statement *target = get_function(forstmt->stassign->rhs->name);
	if(target == NULL) {
		fprintf(stderr, "Error-457: function %s not defined.\n", forstmt->stassign->rhs->name);
		exit(0);
	}
	target->ker = 1;	// set function to kernel

	// change arguments passed while calling kernel
	assign_stmt *arglist = forstmt->stassign->rhs->arglist;
	while(arglist) {
		if(arglist->rhs->lhs->libdtype == GRAPH_TYPE) {
			arglist->rhs->lhs = gpu_graph;
			arglist->rhs->name = malloc(sizeof(char)*(1+strlen(gpu_graph->name)));
			strcpy(arglist->rhs->name, gpu_graph->name);
			// arglist->rhs->name = gpu_graph->name;
			break;
		} else if(arglist->rhs->lhs->it >= 0) {
			arglist->rhs->lhs->parent = gpu_graph;
		}
		arglist = arglist->next;
	}

	// change parameters of kernel
	tree_decl_stmt *params = target->stdecl->dirrhs->params;
	
	while(params) {
		tree_typedecl *type = params->lhs;
		while(type) {
			// graph, point or edge
			if (type->libdatatype >= 0 && type->libdatatype <= 4) {
				params->dirrhs->gpu = 1;
				// if(type->libdatatype == 0) {
				// 	params->dirrhs->ppts = gpu_graph->ppts;
				// }
				break;
			}
			type = type->next;
		}
		params = params->next;
	}
}

// Replaces cpu graphs by gpu graphs in foreach-statement and converts function 
// parameters to gpu type.
static void convert_to_gpu(map<dir_decl*, dir_decl*> &tab)
{
	for(std::vector<statement*>::iterator ii = foreach_list.begin(); ii != foreach_list.end(); ++ii)
	{
		statement *forstmt = *ii;
		
		if(forstmt->stassign) {
			dir_decl *gpu_graph = tab.find(forstmt->expr2->lhs)->second;
			change_cpu_graph(forstmt, gpu_graph);
		}		
	}
}

// Finds local and global variables used in an expression
static void get_variables_util_exp(set<dir_decl *> &lset, set<dir_decl *> &gset, tree_expr *expr)
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
static void get_variables_util(set<dir_decl *> &local_set, set<dir_decl *> &global_rset, set<dir_decl *> &global_wset, statement *begin, statement *end, set<statement*> &visited)
{
	while(begin != NULL && begin != end){
		if(visited.find(begin) != visited.end()) {
			return;
		} else {
			visited.insert(begin);
		}
		if(begin->sttype == DECL_STMT) {
			dir_decl *expr = begin->stdecl->dirrhs;
			while(expr) {
				// printf("TEST %s\n", expr->name);
				if(expr->rhs && expr->rhs->expr_type == VAR) {
					if(local_set.find(expr->rhs->lhs) == local_set.end()) {
						global_rset.insert(expr->rhs->lhs);
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
					global_rset.insert(begin->expr2->lhs);
					// printf("TEST2 %s\n", begin->expr2->lhs->name);
				}
				if(begin->expr4) {	// condition of foreach
					get_variables_util_exp(local_set, global_rset, begin->expr4);
				}
				if(begin->stassign) { // function call
					assign_stmt *astmt = begin->stassign;
					if(astmt->lhs) {
						get_variables_util_exp(local_set, global_rset, astmt->lhs);
					}
					if(astmt->rhs) {
						if(astmt->rhs->expr_type == FUNCALL) {
							// printf("TEST-590 %s\n", astmt->rhs->name);

							statement *target = get_function(astmt->rhs->name);
							if(target == NULL) {
								get_variables_util_exp(local_set, global_wset, astmt->rhs);
								// assign_stmt *tastmt = astmt->rhs->arglist;
								// while(tastmt) {
								// 	if(tastmt->lhs) {
								// 		get_variables_util_exp(local_set, global_wset, tastmt->lhs);
								// 	}
								// 	if(tastmt->rhs) {
								// 		get_variables_util_exp(local_set, global_wset, tastmt->rhs);
								// 	}
								// 	tastmt = tastmt->next;
								// }
								fprintf(stderr, "Error-618: function %s not defined.\n", astmt->rhs->name);
								// exit(0);
							} else {
								tree_decl_stmt *params = target->stdecl->dirrhs->params;
								
								std::set<dir_decl *> lset;
								while(params) {
									lset.insert(params->dirrhs);
									params = params->next;
								}
								get_variables_util(lset, global_rset, global_wset, target->next->next, target->end_stmt, visited);
							}
						} else {
							get_variables_util_exp(local_set, global_rset, astmt->rhs);
						}
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
								global_rset.insert(expr->rhs);
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
							get_variables_util_exp(local_set, global_wset, astmt->lhs);
						}
						if(astmt->rhs) {
							get_variables_util_exp(local_set, global_rset, astmt->rhs);
						}
					}
				}
				if(begin->f2 && begin->f2->stassign) {
					assign_stmt *astmt = begin->f2->stassign;
					if(astmt->lhs) {
						get_variables_util_exp(local_set, global_wset, astmt->lhs);
					}
					if(astmt->rhs) {
						get_variables_util_exp(local_set, global_rset, astmt->rhs);
					}
				}
				if(begin->f3 && begin->f3->stassign) {
					assign_stmt *astmt = begin->f3->stassign;
					if(astmt->lhs) {
						get_variables_util_exp(local_set, global_wset, astmt->lhs);
					}
					if(astmt->rhs) {
						get_variables_util_exp(local_set, global_rset, astmt->rhs);
					}
				}
			} else if(begin->sttype == ASSIGN_STMT) {
				assign_stmt *astmt = begin->stassign;
				while(astmt) {	
					if(astmt->lhs) {
						get_variables_util_exp(local_set, global_wset, astmt->lhs);
					}
					if(astmt->rhs) {
						get_variables_util_exp(local_set, global_rset, astmt->rhs);
					}
					astmt = astmt->next;
				}
			} else if(begin->sttype == FOR_EBLOCK_STMT) {
				get_variables_util(local_set, global_rset, global_wset, begin->start_stmt, begin, visited);
			} else if(begin->sttype == EBLOCK_STMT) {
				if(begin->start_stmt) {
					get_variables_util(local_set, global_rset, global_wset, begin->start_stmt, begin, visited);
				}
			} else if(begin->sttype == DOWHILEEXPR_STMT) {
				get_variables_util_exp(local_set, global_rset, begin->expr1);
				get_variables_util(local_set, global_rset, global_wset, begin->start_stmt, begin, visited);
			} else {
				if(begin->expr1) {
					get_variables_util_exp(local_set, global_rset, begin->expr1);
				}
				if(begin->expr2) {
					get_variables_util_exp(local_set, global_rset, begin->expr2);
				}
				if(begin->expr3) {
					get_variables_util_exp(local_set, global_rset, begin->expr3);
				}
				if(begin->expr4) {
					get_variables_util_exp(local_set, global_rset, begin->expr4);
				}
				if(begin->expr5) {
					get_variables_util_exp(local_set, global_rset, begin->expr5);
				}
				if(begin->f1) {
					get_variables_util(local_set, global_rset, global_wset, begin->f1, end, visited);
				}
				if(begin->f2) {
					get_variables_util(local_set, global_rset, global_wset, begin->f2, end, visited);
				}
				if(begin->f3) {
					get_variables_util(local_set, global_rset, global_wset, begin->f3, end, visited);
				}
			}
		}
		begin = begin->next;
	}
}

// Walks through expression and replaces old_decl by new_decl.
static void walk_exp(dir_decl* old_decl, dir_decl* new_decl, tree_expr *expr)
{
	if(expr == NULL) {
		return;
	}
	if(expr->expr_type == VAR) {
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
				if(astmt->lhs) {	// perhaps this is not required here since only read
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
				if(astmt->lhs) { // perhaps this is not required here since only read
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

static dir_decl* parent_graph(dir_decl *dd)
{
	while(dd->parent && dd->parent->libdtype != GRAPH_TYPE) dd = dd->parent;
	return dd->parent;
}

// Walks through expression to find what attributes are used
static void walk_find_prop(map<dir_decl*, set<char*, comparator> > &mp, tree_expr *expr, dir_decl *dg)
{
	if(expr == NULL || expr->expr_type == VAR) {
		return;
	}
	if(expr->expr_type == STRUCTREF && expr->lhs->expr_type == STRUCTREF) {
		// printf("TEST-3 %s\n", expr->rhs->name);
		if(expr->lhs->lhs->expr_type == VAR && expr->lhs->lhs->lhs->libdtype == GRAPH_TYPE) {
			if(expr->lhs->rhs->expr_type == ARRREF) {
				if(expr->rhs->expr_type == VAR) {
					dir_decl *temp = expr->lhs->lhs->lhs;
					map<dir_decl*, set<char*, comparator> >::iterator itr = mp.find(temp);
					if(itr == mp.end()) {
						// set<char*, comparator> *v = new set<char*, comparator>();
						mp.insert(pair<dir_decl*, set<char*, comparator> >(temp, set<char*, comparator>()));
						// mp[temp] = v;
						// printf("TEST-4 %s %S\n", expr->lhs->name, expr->rhs->name);
					}
					mp[temp].insert(expr->rhs->name);
				}
			}
		} else {
			walk_find_prop(mp, expr->lhs, dg);
			// walk_find_prop(mp, expr->rhs);
		}
	} else if(expr->expr_type == STRUCTREF && expr->lhs->expr_type == VAR) {
		// printf("TEST-1 %s %d\n", expr->lhs->lhs->name, expr->lhs->lhs->libdtype);
		dir_decl *dd = expr->lhs->lhs;
		LIBDATATYPE type = expr->lhs->lhs->libdtype;
		if(type == POINT_TYPE || type == EDGE_TYPE || (type == ITERATOR_TYPE && (dd->it >= 2 && dd->it <= 4))) {
			// printf("TEST-2\n");
			if(expr->rhs->expr_type == VAR) {
				// printf("TEST <--> %s\n", expr->rhs->name);
				dir_decl *temp = parent_graph(expr->lhs->lhs);
				if(temp == NULL) {
					temp = dg;
				}

				bool isLib = false;	// check if attribute is provided by library
				char *name = expr->rhs->name;
				if(expr->lhs->lhs->libdtype == POINT_TYPE) {
					isLib = is_lib_attr(POINT_TYPE, name);
				} else {
					isLib = is_lib_attr(EDGE_TYPE, name);
				}
				if(!isLib) {
					map<dir_decl*, set<char*, comparator> >::iterator itr = mp.find(temp);
					if(itr == mp.end()) {
						// set<char*, comparator> *v = new set<char*, comparator>();
						mp.insert(pair<dir_decl*, set<char*, comparator> >(temp, set<char*, comparator>()));
						// mp[temp] = v;
						// printf("TEST-4 %s %S\n", expr->lhs->name, expr->rhs->name);
					}
					// set<char*, comparator> *v = mp[temp];
					// v->insert(expr->rhs->name);
					mp[temp].insert(expr->rhs->name);
				}
			}
		}
	} else {
		if(expr->lhs) {
			walk_find_prop(mp, expr->lhs, dg);
		}
		if(expr->rhs) {
			walk_find_prop(mp, expr->rhs, dg);
		}
		if(expr->earr_list) {
			assign_stmt *astmt = expr->earr_list;
			while(astmt) {
				if(astmt->lhs) { // perhaps this is not required here since only read
					walk_find_prop(mp, astmt->lhs, dg);
				}
				if(astmt->rhs) {
					walk_find_prop(mp, astmt->rhs, dg);
				}
				astmt = astmt->next;
			}
		}
		if(expr->next) {
			walk_find_prop(mp, expr->next, dg);
		}
		if(expr->arglist) {
			assign_stmt *astmt = expr->arglist;
			while(astmt) {
				if(astmt->lhs) { // perhaps this is not required here since only read
					walk_find_prop(mp, astmt->lhs, dg);
				}
				if(astmt->rhs) {
					walk_find_prop(mp, astmt->rhs, dg);
				}
				astmt = astmt->next;
			}
		}
	}
}

// Walks through expression to find what attributes are used
static void walk_find_var_prop_pair(tree_expr *expr, vector<pair<tree_expr*, char*> > &attr_pair)
{
	if(expr == NULL || expr->expr_type == VAR) {
		return;
	}
	if(expr->expr_type == STRUCTREF && expr->lhs->expr_type == STRUCTREF) {
		// printf("TEST-3 %s\n", expr->rhs->name);
		if(expr->lhs->lhs->expr_type == VAR && expr->lhs->lhs->lhs->libdtype == GRAPH_TYPE) {
			if(expr->lhs->rhs->expr_type == ARRREF) {
				if(expr->rhs->expr_type == VAR) {
					attr_pair.push_back(pair<tree_expr*, char*>(expr->lhs->lhs, expr->rhs->name));
				}
			}
		} else {
			walk_find_var_prop_pair(expr->lhs, attr_pair);
			// walk_find_prop(mp, expr->rhs);
		}
	} else if(expr->expr_type == STRUCTREF && expr->lhs->expr_type == VAR) {
		// printf("TEST-1 %s %d\n", expr->lhs->lhs->name, expr->lhs->lhs->libdtype);
		dir_decl *dd = expr->lhs->lhs;
		LIBDATATYPE type = expr->lhs->lhs->libdtype;
		if(type == POINT_TYPE || type == EDGE_TYPE || (type == ITERATOR_TYPE && (dd->it >= 2 && dd->it <= 4))) {
			// printf("TEST-2\n");
			if(expr->rhs->expr_type == VAR) {
				// printf("TEST <--> %s\n", expr->rhs->name);
				
			}
		}
	} else {
		if(expr->lhs) {
			walk_find_var_prop_pair(expr->lhs, attr_pair);
		}
		if(expr->rhs) {
			walk_find_var_prop_pair(expr->rhs, attr_pair);
		}
		if(expr->earr_list) {
			assign_stmt *astmt = expr->earr_list;
			while(astmt) {
				if(astmt->lhs) { // perhaps this is not required here since only read
					walk_find_var_prop_pair(astmt->lhs, attr_pair);
				}
				if(astmt->rhs) {
					walk_find_var_prop_pair(astmt->rhs, attr_pair);
				}
				astmt = astmt->next;
			}
		}
		if(expr->next) {
			walk_find_var_prop_pair(expr->next, attr_pair);
		}
		if(expr->arglist) {
			assign_stmt *astmt = expr->arglist;
			while(astmt) {
				if(astmt->lhs) { // perhaps this is not required here since only read
					walk_find_var_prop_pair(astmt->lhs, attr_pair);
				}
				if(astmt->rhs) {
					walk_find_var_prop_pair(astmt->rhs, attr_pair);
				}
				astmt = astmt->next;
			}
		}
	}
}


static void walk_util(dir_decl *old_decl, dir_decl *new_decl, statement *stmt)
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

static void walk_find_prop_util(map<dir_decl*, set<char*, comparator> > &rmp, map<dir_decl*, set<char*, comparator> > &wmp, assign_stmt *astmt, dir_decl *dg)
{
	while(astmt) {	
		if(astmt->lhs) {
			walk_find_prop(wmp, astmt->lhs, dg);
		}
		if(astmt->rhs) {
			walk_find_prop(rmp, astmt->rhs, dg);
		}
		astmt = astmt->next;
	}
}

static void walk_find_var_prop_pair_util(assign_stmt *astmt, vector<pair<tree_expr*, char*> > &attr_pair,
	map<dir_decl*, map<dir_decl*, set<char*, comparator> > > &tab)
{
	while(astmt) {	
		if(astmt->lhs) {
			walk_find_var_prop_pair(astmt->lhs, attr_pair);
		}
		if(astmt->rhs) {
			walk_find_var_prop_pair(astmt->rhs, attr_pair);
		}
		astmt = astmt->next;
	}
}

// @params dg: default graph to be used if parent of point or edge is not set
static void find_properties(map<dir_decl*, set<char*, comparator> > &rmp, map<dir_decl*, set<char*, comparator> > &wmp, statement *begin, statement *end, dir_decl *dg, set<statement*> &visited)
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
				if(expr->rhs) { // only check rhs, since lhs is being defined (i.e. local variable)
					walk_find_prop(rmp, expr->rhs, dg);
				}
				expr = expr->nextv;
			}
		} else if(begin->sttype == FOR_STMT) {
			if(begin->f1) walk_find_prop_util(rmp, wmp, begin->f1->stassign, dg);
			if(begin->f2) walk_find_prop_util(rmp, wmp, begin->f2->stassign, dg);
			if(begin->f3) walk_find_prop_util(rmp, wmp, begin->f3->stassign, dg);
		} else if(begin->sttype == ASSIGN_STMT) {
			walk_find_prop_util(rmp, wmp, begin->stassign, dg);
		} else if(begin->sttype != FOREACH_STMT) {
			if(begin->expr1) {
				walk_find_prop(rmp, begin->expr1, dg);
			}
			if(begin->expr2) {
				walk_find_prop(rmp, begin->expr2, dg);
			}
			if(begin->expr3) {
				walk_find_prop(rmp, begin->expr3, dg);
			}
			if(begin->expr4) {
				walk_find_prop(rmp, begin->expr4, dg);
			}
			if(begin->expr5) {
				walk_find_prop(rmp, begin->expr5, dg);
			}				
			if(begin->f1) {
				find_properties(rmp, wmp, begin->f1, end, dg, visited);
			}
			if(begin->f2) {
				find_properties(rmp, wmp, begin->f2, end, dg, visited);
			}
			if(begin->f3) {
				find_properties(rmp, wmp, begin->f3, end, dg, visited);
			}
		} else {
			if(begin->expr4) {	// condition of foreach
				walk_find_prop(rmp, begin->expr4, dg);
			}
			if(begin->stassign) { // function call
				assign_stmt *astmt = begin->stassign;
				if(astmt->lhs) {
					walk_find_prop(wmp, astmt->lhs, dg);
				}
				if(astmt->rhs) {
					assign_stmt *arglist = begin->stassign->rhs->arglist;
					walk_find_prop_util(rmp, wmp, arglist, dg);

					if(astmt->rhs->expr_type == FUNCALL) {
						// printf("TEST-590 %s\n", astmt->rhs->name);

						statement *target = get_function(astmt->rhs->name);
						if(target == NULL) { // may be library function
							fprintf(stderr, "Error-1062: function %s not defined.\n", astmt->rhs->name);
							walk_find_prop(wmp, astmt->rhs, dg);
							// exit(0);
						} else {
							tree_decl_stmt *params = target->stdecl->dirrhs->params;
							
							dir_decl *gp = NULL;
							while(params) {
								if(gp==NULL && params->dirrhs->libdtype == GRAPH_TYPE) {
									gp = params->dirrhs;
								}
								params = params->next;
							}

							find_properties(rmp, wmp, target->next->next, target->end_stmt, gp, visited);
							replace_map_variables(rmp, target->stdecl->dirrhs->params, astmt->rhs->arglist);
							replace_map_variables(wmp, target->stdecl->dirrhs->params, astmt->rhs->arglist);
						}
					} else {
						walk_find_prop(rmp, astmt->rhs, dg);
					}
				}
			}
		}
		
		begin = begin->next;
	}
}

// @params dg: default graph to be used if parent of point or edge is not set
static void find_var_prop_pair(statement *begin, set<statement*> &visited, vector<pair<tree_expr*, char*> > &attr_pair, 
	map<dir_decl*, map<dir_decl*, set<char*, comparator> > > &tab)
{
	while(begin && begin->sttype != FUNCTION_EBLOCK_STMT) {
		if(visited.find(begin) != visited.end()) {
			return;
		} else {
			visited.insert(begin);
		}
		if(begin->sttype == DECL_STMT) {
			dir_decl *expr = begin->stdecl->dirrhs;
			while(expr) {
				if(expr->rhs) { // only check rhs, since lhs is being defined (i.e. local variable)
					walk_find_var_prop_pair(expr->rhs, attr_pair);
				}
				expr = expr->nextv;
			}
		} else if(begin->sttype == FOR_STMT) {
			if(!(begin->prev && (begin->prev->sttype == EMPTY_STMT) && (begin->prev->lineno==2))) {
				// code for copying memory from gpu to cpu.
				map<dir_decl*, set<char*, comparator> > rmp, wmp;
				set<statement*> v;
				find_properties(rmp, wmp, begin, begin->end_stmt, NULL, v);	// find attributes used inside for-loop

				statement *temp = new statement();
				temp->sttype = EMPTY_STMT;
				temp->lineno = 2;

				temp->prev = begin->prev;
				temp->next = begin;
				begin->prev->next = temp;
				begin->prev = temp;
				
				gencode_properties(rmp, tab, temp);
				gencode_properties(wmp, tab, temp);
			}
			begin = begin->end_stmt;
		} else if(begin->sttype == ASSIGN_STMT) {
			walk_find_var_prop_pair_util(begin->stassign, attr_pair, tab);
		} else if(begin->sttype != FOREACH_STMT) {
			if(begin->expr1) {
				walk_find_var_prop_pair(begin->expr1, attr_pair);
			}
			if(begin->expr2) {
				walk_find_var_prop_pair(begin->expr2, attr_pair);
			}
			if(begin->expr3) {
				walk_find_var_prop_pair(begin->expr3, attr_pair);
			}
			if(begin->expr4) {
				walk_find_var_prop_pair(begin->expr4, attr_pair);
			}
			if(begin->expr5) {
				walk_find_var_prop_pair(begin->expr5, attr_pair);
			}				
			if(begin->f1) {
				find_var_prop_pair(begin->f1, visited, attr_pair, tab);
			}
			if(begin->f2) {
				find_var_prop_pair(begin->f2, visited, attr_pair, tab);
			}
			if(begin->f3) {
				find_var_prop_pair(begin->f3, visited, attr_pair, tab);
			}
		} else {
			if(begin->expr4) {	// condition of foreach
				walk_find_var_prop_pair(begin->expr4, attr_pair);
			}
			if(begin->stassign) { // function call
				assign_stmt *astmt = begin->stassign;
				if(astmt->lhs) {
					walk_find_var_prop_pair(astmt->lhs, attr_pair);
				}
				if(astmt->rhs) {
					assign_stmt *arglist = begin->stassign->rhs->arglist;
					walk_find_var_prop_pair_util(arglist, attr_pair, tab);

					if(astmt->rhs->expr_type == FUNCALL) {
						// printf("TEST-590 %s\n", astmt->rhs->name);

						statement *target = get_function(astmt->rhs->name);
						if(target == NULL) {
							fprintf(stderr, "Error-1174: function %s not defined.\n", astmt->rhs->name);
							// exit(0);
						} else {
							tree_decl_stmt *params = target->stdecl->dirrhs->params;
							
							dir_decl *gp = NULL;
							while(params) {
								if(gp==NULL && params->dirrhs->libdtype == GRAPH_TYPE) {
									gp = params->dirrhs;
								}
								params = params->next;
							}
						}

						// find_var_prop_pair(target->next->next, visited, attr_pair);
						// replace_map_variables(rmp, target->stdecl->dirrhs->params, astmt->rhs->arglist);
						// replace_map_variables(wmp, target->stdecl->dirrhs->params, astmt->rhs->arglist);
					} else {
						walk_find_var_prop_pair(astmt->rhs, attr_pair);
					}
				}
			}
		}
		
		begin = begin->next;
	}
}

static statement* get_statement(dir_decl *g, char *name)
{
	map<dir_decl*, statement*> *mp = graphs[g]->second;
	for(map<dir_decl*, statement*>::iterator it=mp->begin(); it!=mp->end(); ++it) {
		if(strcmp(it->first->name, name) == 0) {
			return it->second;
		}
	}
	fprintf(stderr, "Error: statement declaring %s property not found.\n", name);
	exit(0);
}

static void get_property(char **type_ptr, char *size_ptr, statement *stmt)
{
	tree_expr *t1 = stmt->stassign->rhs;
	dir_decl *parent = t1->lhs->lhs;
	extra_ppts *ep = parent->ppts;
	assign_stmt *pt1 = t1->rhs->arglist;
	
	while(ep) {
		if(strcmp(ep->name, pt1->rhs->name) == 0) {
			if(ep->t1->libdatatype == P_P_TYPE) {
				sprintf(size_ptr, "npoints");
			} else if(ep->t1->libdatatype == E_P_TYPE) {
				sprintf(size_ptr, "nedges");
			} else {
				sprintf(size_ptr, "1");
			}
			break;
		}
		ep = ep->next;
	}
	
	*type_ptr = t1->rhs->params->lhs->name;
	// printf("--> %s %p\n", pt1->rhs->name, pt1->rhs->lhs);
	// printf("--> %s", t1->rhs->params->lhs->name);
	// exit(0);
}

/**
* This function finds attributes which are allocated in some gpu and are being used in cpu for loop, and copies the attribute
* from the gpu to cpu before starting of for-loop.
* 
* @params mp: contains cpu-graph and those properties of the graph which are being used in the for-loop
* @params tab: contains cpu graph and it's gpu instances containing the attributes used in gpu
* @params temp: empty statement which is to be filled with copy statements.
**/
static void gencode_properties(map<dir_decl*, set<char*, comparator> > &mp, map<dir_decl*, map<dir_decl*, set<char*, comparator> > > &tab, statement *temp)
{
	char buff[1000];
	int count = 0;
	
	// loop over all the cpu graph and it's atrributes which are being used in the for loop
	for(map<dir_decl*, set<char*, comparator> >::iterator it=mp.begin(); it!=mp.end(); ++it) {
		set<char*, comparator> &v = it->second;		// attributes used in for loop
		char var_name[10];
		snprintf(var_name, 10, "_flcn%d", falc_ext++);	// temporary variable name
		count += sprintf(buff+count, "struct struct_%s %s;\n", it->first->name, var_name); 	// declare temporary graph variable

		// find from which gpu graph what are the attributes need to be copied
		map<dir_decl*, set<char*, comparator> > gps;	// gpu graph and its attributes
		for(set<char*, comparator>::iterator ii=v.begin(); ii!=v.end(); ++ii) {
			dir_decl *d = find_var(tab[it->first], *ii);	// find graph instance where this attribute is modified/allocated
			if(d != NULL && d != it->first) {	// if attribute is allocated in gpu, copy it to cpu
				if(gps.find(d) == gps.end()) {
					gps.insert(pair<dir_decl*, set<char*, comparator> >(d, set<char*, comparator>()));
				}
				gps[d].insert(*ii);
			}

			// store these attributes in cpu copy as we need to allocate memory
			map<dir_decl*, set<char*, comparator> > &tmp = tab[it->first];
			if(tmp.find(it->first) == tmp.end()) {
				tmp.insert(pair<dir_decl*, set<char*, comparator> >(it->first, set<char*, comparator>()));
			}
			tmp[it->first].insert(*ii);
		}

		for(map<dir_decl*, set<char*, comparator> >::iterator jj=gps.begin(); jj!=gps.end(); ++jj) {
			count += sprintf(buff+count, "cudaMemcpy(&%s, (struct struct_%s *)(%s.extra), sizeof(struct struct_%s ),cudaMemcpyDeviceToHost);\n", 
				var_name, it->first->name, jj->first->name, it->first->name);
			char *type, size[10];

			for(set<char*, comparator>::iterator ii=jj->second.begin(); ii!=jj->second.end(); ++ii) {
				get_property(&type, size, get_statement(it->first, *ii));
				count += sprintf(buff+count, "cudaMemcpy(((struct struct_%s *)(%s.extra))->%s, %s.%s, sizeof(%s)*(%s.%s), cudaMemcpyDeviceToHost);\n",
					it->first->name, it->first->name, *ii, var_name, *ii, type, it->first->name, size);
			}
		}
	}

	if(count > 0) {
		temp->name = malloc(sizeof(char)*(1+strlen(buff)));
		strcpy(temp->name, buff);
	}
}

// Utility function to walk through statements and call wal_exp() to replace old variables with new
static void walk_statement(dir_decl* old_decl, dir_decl* new_decl, statement *begin, map<dir_decl*, dir_decl*> &tab)
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
			// if(begin->f1) walk_util(old_decl, new_decl, begin->f1);
			// if(begin->f2) walk_util(old_decl, new_decl, begin->f2);
			// if(begin->f3) walk_util(old_decl, new_decl, begin->f3);
			
			// if(!(begin->prev && (begin->prev->sttype == EMPTY_STMT) && (begin->prev->lineno==2))) {
			// 	// code for copying memory from gpu to cpu.
			// 	map<dir_decl*, set<char*, comparator> > rmp, wmp;
			// 	set<statement*> visited;
			// 	find_properties(rmp, wmp, begin, begin->end_stmt, NULL, visited);

			// 	statement *temp = new statement();
			// 	temp->sttype = EMPTY_STMT;
			// 	temp->lineno = 2;

			// 	temp->prev = begin->prev;
			// 	temp->next = begin;
			// 	begin->prev->next = temp;
			// 	begin->prev = temp;
				
			// 	gencode_properties(rmp, tab, temp);
			// 	gencode_properties(wmp, tab, temp);
			// }

			begin = begin->end_stmt;
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
				walk_statement(old_decl, new_decl, begin->f1, tab);
			}
			if(begin->f2) {
				walk_statement(old_decl, new_decl, begin->f2, tab);
			}
			if(begin->f3) {
				walk_statement(old_decl, new_decl, begin->f3, tab);
			}
		} else {
			if(begin->stassign) {
				assign_stmt *arglist = begin->stassign->rhs->arglist;
				while(arglist) {
					if(arglist->rhs->lhs == old_decl) {
						arglist->rhs->lhs = new_decl;
						arglist->rhs->name = malloc(sizeof(char)*(1+strlen(new_decl->name)));
						strcpy(arglist->rhs->name, new_decl->name);
						// arglist->rhs->name = parent_graph->name;
						break;
					}
					arglist = arglist->next;
				}
			}
		}
		
		begin = begin->next;
	}
}

// Inserts a statement stmt in between lhs and rhs
static void insert_statement(statement *lhs, statement *stmt, statement *rhs)
{
	lhs->next = stmt;
	stmt->prev = lhs;
	stmt->next = rhs;
	rhs->prev = stmt;
}

// Creates a declaration statement.
static statement* create_decl_statement(LIBDATATYPE type)
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

static statement* create_gettype_stmt(dir_decl *graph, dir_decl *ngraph)
{
	tree_expr *arg1 = new tree_expr(graph);
	arg1->name = malloc(sizeof(char)*(1+strlen(graph->name)));
	strcpy(arg1->name, graph->name);

	// dir_decl *arg6=new dir_decl();
 //    arg6->name=malloc(sizeof(char)*10);
 //    snprintf(arg6->name, 10, "_flcn%d", falc_ext++);
	// *ngraph = arg6;
	// arg6->gpu = 1;
	// arg6->libdtype = GRAPH_TYPE;

	tree_expr *exp1 = binaryopnode(arg1,NULL,GET_TYPE,-1);
	exp1->rhs=new tree_expr();
	exp1->rhs->name=malloc(sizeof(char)*10);
	strcpy(exp1->rhs->name, "GETTYPE");
	exp1->rhs->expr_type=VAR;
	exp1->rhs->nextv = ngraph;
/*	
	tree_expr *u1=arg1;
	if(u1->expr_type==VAR && ((dir_decl *)(u1->lhs))->libdtype==GRAPH_TYPE){
        dir_decl *dg=u1->lhs;
        tree_typedecl *tpold= dg->tp1;
        tree_typedecl *tp1;
        tp1=new tree_typedecl();
        tp1->libdatatype=GRAPH_TYPE; 
        tp1->name=malloc(sizeof(char)*100);
        strcpy(tp1->name,libdtypenames[tp1->libdatatype]);
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
          if(oldppts->var2!=NULL){
		      }
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
          // tp1->ppts=head;
        }
    }
*/	
	statement *temp3= new statement();
	temp3->sttype = ASSIGN_STMT;
	temp3->stassign=createassignlhsrhs(-1,NULL,exp1);
	
	// statement *temp1 = temp3;
 //  	while(temp1->next!=NULL&&temp1->sttype==ASSIGN_STMT&& temp1->stmtno==temp1->next->stmtno){
	//   temp1=temp1->next;
	// }
	// temp1->stassign->semi=1;    
	return temp3;
}

// Copies graph properties from one graph to another
static void copy_graph_properties(dir_decl *dg, dir_decl *new_graph, set<char*, comparator> &attrs)
{
	if(dg->ppts!=NULL){
      extra_ppts *newppts=NULL,*oldppts=dg->ppts,*head = NULL;
      
      while(oldppts){
        if(attrs.find(oldppts->name) != attrs.end()) {
	        if(newppts == NULL) {
				newppts = new extra_ppts();
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
	        } else {
		        newppts->next= new extra_ppts();
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
		    }
	    }
        oldppts=oldppts->next;
      }
      new_graph->ppts=head;
    }
}

// Creates assignment statement
static statement* create_assign_statement(dir_decl *lhs, dir_decl *rhs)
{
	// copy graph properties
	// copy_graph_properties(rhs, lhs);
		
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
    stmt->lineno = 1111;
    return stmt;
}

// Replaces cpu graph by gpu graph in the function where cpu graph is defined
// Search cpu graph in all the statements following its declaration and replace it with gpu copy except in for stmt
static void replace_graphs(map<dir_decl*, dir_decl*> &tab)
{
	for(map<dir_decl*, dir_decl*>::iterator itr=tab.begin(); itr!=tab.end(); ++itr) {
		statement *start = graph_insert_point.find(itr->first)->second->next->next->next;

		walk_statement(itr->first, itr->second, start, tab);
	}
}

// Replaces cpu variables by gpu variables
static void replace(map<dir_decl*, dir_decl*> &tab, map<dir_decl*, statement*> &mp)
{
	for(map<dir_decl*, statement*>::iterator itr=mp.begin(); itr!=mp.end(); ++itr) {
		statement *start = itr->second->next->next->next; // statement should be after assignment statement

		walk_statement(itr->first, tab[itr->first], start, tab);
	}
}


static void insert_node(map<dir_decl*, dir_decl*> &tab, map<dir_decl*, map<dir_decl*, set<char*, comparator> > > &graph_info, map<dir_decl*, statement*> &mp, LIBDATATYPE dtype)
{
	for(map<dir_decl*, statement*>::iterator itr=mp.begin(); itr!=mp.end(); ++itr) {
		statement *st = itr->second;

		if(st->stdecl->dirrhs->tp1) {
			// type
			tree_typedecl *tp = st->stdecl->dirrhs->tp1;
			// printf("TT %s %p %p\n", st->stdecl->dirrhs->name, tp, tp->next);	

			// init_declarator
			tree_typedecl *ptr=new tree_typedecl();
			ptr->libdatatype = tp->libdatatype;
			ptr->name = tp->name;
			// ptr->ppts = tab[tp->d1]->ppts;
			ptr->d1 = NULL;
			for(map<dir_decl*, set<char*, comparator> >::iterator kk=graph_info[tp->d1].begin(); kk!=graph_info[tp->d1].end(); ++kk) {
				if(kk->first->gpu == 1) {
					ptr->d1 = kk->first; // graph in which this set is related to ~ need modification for multiple graph
					break;
				}
			}
			// ptr->ppts = NULL;
			// ptr->d1 = tp->d1;
			ptr->next = tp->next;	

			dir_decl *dd = new dir_decl();
			dd->name = malloc(sizeof(char)*10);
			dd->libdtype = dtype;
			dd->gpu = 1;
			snprintf(dd->name, 10, "_flcn%d", falc_ext++);
			dd->tp1 = ptr;
			tab[itr->first] = dd;
			// dd->tp1 = tp;

			// declaration specifier
			tree_typedecl *dsp = new tree_typedecl();
		    dsp->libdatatype = dtype;
		    dsp->name = malloc(sizeof(char )*10);
		    strcpy(dsp->name,libdtypenames[dtype]);
		    
			// type declaration
			tree_decl_stmt *tstmt=new tree_decl_stmt();
		    tstmt->lhs = dsp;
		    tstmt->dirrhs = dd;
		    
			statement *stmt = new statement();
			stmt->sttype = DECL_STMT;
	  		stmt->stdecl = tstmt;
	  		insert_statement(st, stmt, st->next);
	  		stmt->lineno = 99999;
	  		// dd->tp1->d1->gpu==1;

	  		statement *astmt = create_assign_statement(dd, itr->first);
	  		insert_statement(stmt, astmt, stmt->next);
	  	}
	}

}

static void print_graph_properties(map<dir_decl*, vector<char*>*> &mp)
{
	for(map<dir_decl*, vector<char*>*>::iterator it=mp.begin(); it!=mp.end(); ++it) {
		vector<char*> *v = it->second;
		printf("*****GRAPH %s*****\n", it->first->name);
		for(int ii=0; ii<v->size(); ++ii) {
			printf("-->%s\n", (*v)[ii]);
		}
	}
}

static dir_decl* find_var(map<dir_decl*, set<char*, comparator> > &mp, char *cc)
{
	for(map<dir_decl*, set<char*, comparator> >::iterator ii=mp.begin(); ii!=mp.end(); ++ii) {
		if(ii->first->gpu > 0) {
			if(ii->second.find(cc) != ii->second.end()) {
				return ii->first;
			}
		}
	}
	return NULL;
}

// Inserts a new graph node
// Generate a copy of each graph in the gpu
static void insert_graph_node(map<dir_decl*, map<dir_decl*, set<char*, comparator> > > &tab)
{
	// map<dir_decl*, dir_decl*> tab;	// stores gpu graph corresponding to cpu copy
	map<dir_decl*, map<dir_decl*, set<char*, comparator> > >::iterator ii;
	// map<dir_decl*, map<dir_decl*, set<char*, comparator> > > wmp;
	// if(graph_insert_point.size() > 0) {
	// 	vector<statement*> visited;
	// 	map<dir_decl*, map<dir_decl*, set<char*, comparator> > > rmp;
	// 	map<dir_decl*, statement*>::iterator jj = graph_insert_point.begin();
	// 	find_properties(rmp, wmp, jj->second->next, function_end(jj->second), jj->first, visited);
	// 	copy(wmp, rmp);
	// }
	statement *end = NULL;

	// create statement which creates gpu graph
	for(map<dir_decl*, statement*>::iterator itr=graph_insert_point.begin(); itr!=graph_insert_point.end(); itr++) {
		// statement *begin = itr->second;
		end = itr->second->next;
		// statement *stmt = create_decl_statement(GRAPH_TYPE);
		// insert_statement(begin, stmt, end);
	
		// tab[itr->first] = stmt->stdecl->dirrhs;
		// stmt->stdecl->dirrhs->libstable = itr->first->libstable;

		// stmt = create_assign_statement(stmt->stdecl->dirrhs, itr->first);
		// insert_statement(end->prev, stmt, end);

		ii = tab.find(itr->first);
		if(ii != tab.end()) {
			for(map<dir_decl*, set<char*, comparator> >::iterator jj=ii->second.begin(); jj!=ii->second.end(); ++jj) {
				dir_decl *dd = jj->first;
				statement *stmt = create_gettype_stmt(itr->first, dd);	// create graph declaration statement
				insert_statement(end->prev, stmt, end);		// insert statement
				// tab[itr->first] = dd;					// remember gpu copy
				dd->libstable = itr->first->libstable;
				stmt = create_assign_statement(dd, itr->first);		// create statement to copy cpu graph properties to gpu
				
				// copy graph properties
				copy_graph_properties(itr->first, dd, jj->second);		// copy only required properties which are used in gpu kernel
				insert_statement(end->prev, stmt, end);
			}
		}
	}
	
	// convert_to_gpu(tab); 	// replace cpu graph by its gpu copy in foreach stmt, change function to kernel and cpu parameters to gpu parameters
	// replace_graphs(tab);	// replace cpu graph by its gpu copy in each stmt following its declaration
	// tab.clear();
	
	// find graph attributes which are used in cpu
	if(end != NULL) {
		vector<pair<tree_expr*, char*> > v;	// stores <graph, attribute_name> pair; first arg is the parent of the graph, i.e tree_expr->lhs is the graph
		set<statement*> visited;
		find_var_prop_pair(end, visited, v, tab);	// find all the attributes corresponding to each graph

		// replace all uses of cpu graph with gpu graphs which contains the attributes used here
		for(vector<pair<tree_expr*, char*> >::iterator ii=v.begin(); ii!=v.end(); ++ii) {
			dir_decl *d = find_var(tab.find(ii->first->lhs)->second, ii->second);

			// if no gpu graph uses this attribute, store it in cpu_graph set. This cpu_graph set contains all attributes which had to have memory in cpu
			if(d == NULL) {	
				map<dir_decl*, set<char*, comparator> > &mp = tab[ii->first->lhs];
				if(mp.find(ii->first) == mp.end()) {	// keep track of the attributes which has to have memory in cpu
					mp.insert(pair<dir_decl*, set<char*, comparator> >(ii->first->lhs, set<char*, comparator>()));
				}
				mp[ii->first->lhs].insert(ii->second);
			} else if(d != ii->first->lhs){ // if gpu graph found, replace the cpu graph with this graph
				ii->first->lhs = d;
			}
		}
	}

	// remove cpu attributes not required.
	for(map<dir_decl*, map<dir_decl*, set<char*, comparator> > >::iterator ii=tab.begin(); ii!=tab.end(); ++ii) {
		map<dir_decl*, set<char*, comparator> >::iterator jj = ii->second.find(ii->first);	// find cpu attributes
		if(jj != ii->second.end()) {	// some attributes need allocation
			extra_ppts *ppts = jj->first->ppts;
			while(ppts) {
				if(jj->second.find(ppts->name) == jj->second.end()) {	// if an attribute is not found, it means we don't need to allocate memory in cpu
					ppts->mem_allocate = false;
				}
				ppts = ppts->next;
			}
		} else {	// no attributes need allocation
			extra_ppts *ppts = ii->first->ppts;
			while(ppts) {
				ppts->mem_allocate = false;
				ppts = ppts->next;
			}
		}
	}

	map<dir_decl*, dir_decl*> stab;
	insert_node(stab, tab, fx_sets, SET_TYPE);	// replace cpu sets by gpu sets
	replace(stab, fx_sets);

	// tab.clear();
	// insert_node(tab, fx_collections, COLLECTION_TYPE);	// replace cpu collection by gpu collection
	// replace(tab, fx_collections);
}

void print_map(map<dir_decl*, statement*> &mp)
{
	for(map<dir_decl*, statement*>::iterator itr=mp.begin(); itr!=mp.end(); ++itr) {
		printf("--> %s\n", itr->first->name);
	}
}

static statement* function_end(statement *stmt)
{
	while(stmt && stmt->sttype != FUNCTION_EBLOCK_STMT) {
		if(stmt->end_stmt) stmt = stmt->end_stmt;
		stmt = stmt->next;
	}
	return stmt;
}

static bool is_dependency(set<dir_decl*> &rset, set<dir_decl*> &wset)
{
	for(set<dir_decl*>::iterator ii=rset.begin(); ii!=rset.end(); ++ii) {
		if(wset.find(*ii) != wset.end()) {
			return true;
		}
	}
	return false;
}

static bool is_dependency(set<char*, comparator> &rset, set<char*, comparator> &wset)
{
	for(set<char*, comparator>::iterator ii=rset.begin(); ii!=rset.end(); ++ii) {
		if(wset.find(*ii) != wset.end()) {
			return true;
		}
	}
	return false;
}

static bool is_dependency(map<dir_decl*, set<char*, comparator> > &rmap, map<dir_decl*, set<char*, comparator> > &wmap)
{
	map<dir_decl*, set<char*, comparator> >::iterator jj;
	for(map<dir_decl*, set<char*, comparator> >::iterator ii=rmap.begin(); ii!=rmap.end(); ++ii) {
		jj = wmap.find(ii->first);
		if(jj != wmap.end()) {
			if(is_dependency(ii->second, jj->second)) {
				return true;
			}
		}
	}
	return false;
}

static void copy(map<dir_decl*, set<char*, comparator> > &lhs, map<dir_decl*, set<char*, comparator> > &rhs)
{
	for(map<dir_decl*, set<char*, comparator> >::iterator ii=rhs.begin(); ii!=rhs.end(); ++ii) {
		map<dir_decl*, set<char*, comparator> >::iterator jj = lhs.find(ii->first);
		if(jj != lhs.end()) {
			ii->second.insert(jj->second.begin(), jj->second.end());
		} else {
			lhs[ii->first] = ii->second;
		}
	}
}


static void replace_map_variables(map<dir_decl*, set<char*, comparator> > &tab, tree_decl_stmt *params, assign_stmt *args)
{
	int count = 0;
	while(params && args) {
		if(args->rhs->lhs->libdtype == GRAPH_TYPE && params->dirrhs->libdtype == GRAPH_TYPE) {
			if(tab.find(args->rhs->lhs) == tab.end()) {
				if(tab.find(params->dirrhs) != tab.end()) {
					tab[args->rhs->lhs] = tab[params->dirrhs];
					tab.erase(params->dirrhs);
				}
			} else if(tab.find(params->dirrhs) != tab.end()) {
				tab[args->rhs->lhs].insert(tab[params->dirrhs].begin(), tab[params->dirrhs].end());
			}
		}
		params = params->next;
		args = args->next;
		count++;
	}
	// if(params != NULL || args != NULL) {
	// 	printf("Err not same length\n");
	// }
	// printf("LEN %d\n", count);
}

static void check_null(map<dir_decl*, set<char*, comparator>*> &tab, int k)
{
	for(map<dir_decl*, set<char*, comparator>*>::iterator ii=tab.begin(); ii!=tab.end(); ++ii) {
		if(ii->first == NULL) {
			printf("Error-104 %d\n", k);
		} else if (ii->second == NULL) {
			printf("ERROR-105 %d\n", k);
		}
	}
}

static void print(map<dir_decl*, set<char*, comparator>*> &tab, string ss)
{
	cout << "*******" << ss << "*******" << endl;
	for(map<dir_decl*, set<char*, comparator>*>::iterator ii=tab.begin(); ii!=tab.end(); ++ii) {
		cout << "SET " << ii->first->name << endl;
		for(set<char*, comparator>::iterator jj=ii->second->begin(); jj!=ii->second->end(); ++jj) {
			cout << *jj << endl;
		}
	}
	cout << "**************************" << endl;
}

static char* create_string(char *str) {
	char* temp = malloc(sizeof(char)*(1+strlen(str)));
	strcpy(temp, str);
	return temp;
}

static statement* create_empty_stmt(int lineno) {
	statement *stmt = new statement;
	stmt->sttype = EMPTY_STMT;
	stmt->lineno = lineno;
	return stmt;
}

static void insert_parallel_section(vector<statement*> &kernels, int start, int end)
{
	int count = end - start;
	statement *stmt = create_empty_stmt(2);
	char *buff = new char[100];
	snprintf(buff, 100, "#pragma omp sections num_threads(2) \n{\n#pragma omp section\n{\n");
	stmt->name = create_string(buff);
	insert_statement(kernels[start]->prev, stmt, kernels[start]);
	for(int i=start+1; i<=end; ++i) {
		stmt = create_empty_stmt(2);
		snprintf(buff, 100, "}\n#pragma omp section\n{\n");
		stmt->name = create_string(buff);
		insert_statement(kernels[i-1], stmt, kernels[i-1]->next);
	
		if(i != end) {
			stmt = create_empty_stmt(2);
			snprintf(buff, 100, "#pragma omp sections num_threads(2)\n{\n#pragma omp section\n{\n");
			stmt->name = create_string(buff);
			insert_statement(kernels[i]->prev, stmt, kernels[i]);
		}
	}

	stmt = create_empty_stmt(2);
	if(4*(end-start)+1 > 100) {
		delete[] buff;
		buff = new char[4*(end-start)+1];
	}
	for(int i=0; i<end-start; ++i) {
		sprintf(&buff[4*i], "}\n}\n");
	}
	// buff[2*(end-start)] = '\0';
	stmt->name = create_string(buff);
	insert_statement(kernels[end], stmt, kernels[end]->next);
	delete[] buff;
}

static bool found(statement *stmt, statement *end, statement *goal)
{
	if(stmt->f1) {
		return same_level(stmt->f1, end, goal);
	}
	if(stmt->f2) {
		return same_level(stmt->f2, end, goal);
	}
	if(stmt->f3) {
		return same_level(stmt->f3, end, goal);
	}
	return false;
}

static bool same_level(statement *start, statement *end, statement *goal)
{
	statement *curr = start;
	while(curr && curr != end && curr != goal) {
		switch(curr->sttype) {
			case SINGLE_STMT:
			case SWITCH_STMT:
				if(found(curr, NULL, goal)) {
					return false;
				}
				break;
			case SECTIONS_STMT:
			case SECTION_STMT:
			case IF_STMT:
			case WHILE_STMT:
			case DOWHILE_STMT:
			case FOR_STMT:
			case FOREACH_STMT:
				if(found(curr, curr->end_stmt, goal)) {
					return false;
				}
				curr = curr->end_stmt;
				break;
			default:
				break;
		}
		curr = curr->next;
	}
	if(curr == goal) {
		return true;
	} else {
		return false;
	}
}

static void find_attrs_in_kernel(map<dir_decl*, set<char*, comparator> > &rmp, map<dir_decl*, set<char*, comparator> > &wmp,
				map<dir_decl*, vector<statement*> > &kers, statement *foreach_stmt)
{
	assign_stmt *astmt = foreach_stmt->stassign->rhs->arglist;
	while(astmt) {
		if(astmt->rhs && astmt->rhs->expr_type == VAR && astmt->rhs->lhs->libdtype == GRAPH_TYPE) {
			dir_decl *d = astmt->rhs->lhs;
			if(kers.find(d) != kers.end()) {
				kers[d].push_back(foreach_stmt);
			} else {
				kers.insert(pair<dir_decl*, vector<statement*> >(d, vector<statement*>(1, foreach_stmt)));
			}
			// if(graphs.find(d) == graphs.end()) {
			// 	graphs.insert(d);
			// 	if(dev_no > 0) {
			// 		d->dev_no = dev_no;
			// 	}
			// 	dev_no++;
			// } else {
			// 	(*jj)->stream_id = stream_no++;
			// }
			// insert props
			set<statement*> visited;
			statement *target = get_function(foreach_stmt->stassign->rhs->name);
			if(target == NULL) {
				fprintf(stderr, "%s function definition not found.\n", foreach_stmt->stassign->rhs->name);
				exit(1);
			}
			find_properties(rmp, wmp, target->next->next, target->end_stmt, d, visited);
			
			break;
		}
		astmt = astmt->next;
	}
}

// Finds global variables used in kernels
void get_variables(bool isGPU, bool cpuParallelSection = false)
{
	std::set<dir_decl *> gset;	// keeps gpu global variables
	map<dir_decl*, set<char*, comparator> > rmap1, rmap2, wmap1, wmap2, *curr_rmap, *curr_wmap, *next_rmap, *next_wmap;
	curr_rmap = &rmap1;
	next_rmap = &rmap2;
	curr_wmap = &wmap1;
	next_wmap = &wmap2;
	statement *end;
	bool prev_rm = false;
	set<dir_decl*> rset1,rset2,wset1,wset2, *curr_rset, *curr_wset, *next_rset, *next_wset;
	curr_rset = &rset1;
	curr_wset = &wset1;
	next_rset = &rset2;
	next_wset = &wset2;

	vector<statement*> kernels;

	// finds dependency between kernels.
	for(int i=0; i<foreach_list.size(); ++i)
	{
		statement *stmt = foreach_list[i];

		if(stmt->stassign) {
			kernels.push_back(stmt);
			char *name = stmt->stassign->rhs->name;
			statement *target = get_function(name);
			if(target == NULL) {
				fprintf(stderr, "Error-2047: function %s not defined.\n", name);
				exit(0);
			}
			tree_decl_stmt *params = target->stdecl->dirrhs->params;
			
			std::set<dir_decl *> local_set;
			dir_decl *gp = NULL;
			while(params) {
				local_set.insert(params->dirrhs);
				if(gp==NULL && params->dirrhs->libdtype == GRAPH_TYPE) {
					gp = params->dirrhs;
				}
				params = params->next;
			}

			// find global variables
			set<dir_decl*> &k_rset = *curr_rset;
			set<dir_decl*> &k_wset = *curr_wset;
			set<statement*> visited;
			get_variables_util(local_set, k_rset, k_wset, target->next->next, target->end_stmt, visited);
			
			// store gpu variables
			gset.insert(k_rset.begin(), k_rset.end());
			gset.insert(k_wset.begin(), k_wset.end());

			// variables after
			local_set.clear();
			if(i+1 < foreach_list.size()) {
				end = foreach_list[i+1];
			} else {
				end = function_end(stmt);
			}
			set<dir_decl*> rset, wset;
			visited.clear();
			get_variables_util(local_set, rset, wset, stmt->next, end, visited);
			
			bool rm = !(is_dependency(k_rset, wset) || is_dependency(rset, k_wset));
			if(rm || prev_rm) {
				// find attributes of graph
				map<dir_decl*, set<char*, comparator> > &krmap = *curr_rmap, &kwmap = *curr_wmap;
				map<dir_decl*, set<char*, comparator> >::iterator jj;
				visited.clear();
				find_properties(krmap, kwmap, target->next->next, target->end_stmt, gp, visited);
				replace_map_variables(krmap, target->stdecl->dirrhs->params, stmt->stassign->rhs->arglist);
				replace_map_variables(kwmap, target->stdecl->dirrhs->params, stmt->stassign->rhs->arglist);
				
				// attributes after
				map<dir_decl*, set<char*, comparator> > crmap, cwmap;
				if(rm) {
					visited.clear();
					find_properties(crmap, cwmap, stmt, end, NULL, visited);
					
					if(is_dependency(krmap, cwmap) || is_dependency(crmap, kwmap)) { // dependency exist
						rm = false;
					}
				}

				if(prev_rm) {
					if(!(is_dependency(*curr_rset, *next_wset) || is_dependency(*next_rset, *curr_wset) ||
						is_dependency(rset, *next_wset) || is_dependency(*next_rset, wset) || 
						is_dependency(*curr_rmap, *next_wmap) || is_dependency(*next_rmap, *curr_wmap))) {
						foreach_list[i-1]->comma = true;
						// copy data
						if(rm) {
							curr_rset->insert(next_rset->begin(), next_rset->end());
							curr_wset->insert(next_wset->begin(), next_wset->end());
							
							copy(*curr_rmap, *next_rmap);
							copy(*curr_wmap, *next_wmap);
						}
					} else {
						prev_rm = false;
					}

					if(!rm) {
						next_rset->clear();
						next_wset->clear();
						next_rmap->clear();
						next_wmap->clear();							
					}
				}

				if(rm) {	// remove barrier
					prev_rm = true;
					swap(curr_rmap, next_rmap);
					swap(curr_wmap, next_wmap);
					swap(curr_rset, next_rset);
					swap(curr_wset, next_wset);
				} else {
					prev_rm = false;
				}
				curr_rmap->clear();
				curr_wmap->clear();
				curr_rset->clear();
				curr_wset->clear();
			} else {
				prev_rm = false;
				curr_rset->clear();
				curr_wset->clear();
			}
		}
	}

	if(prev_rm) {
		foreach_list[foreach_list.size()-1]->comma = true;
	}

	if(isGPU) {
		for(set<dir_decl *>::iterator ii = gset.begin(); ii != gset.end(); ++ii) {
			(*ii)->gpu = 1;
		}


		// generate multi-gpu code
		set<dir_decl*> graphs;
		int stream_no = 1;
		vector<statement*>::iterator jj = kernels.begin();

		map<dir_decl*, map<dir_decl*, set<char*, comparator> > > tab;
		map<dir_decl*, map<dir_decl*, set<char*, comparator> > >::iterator kk;

		vector<statement*>::iterator start = kernels.end(), end = kernels.end();
		
		for(vector<statement*>::iterator ii=sections_stmts.begin(); ii!=sections_stmts.end(); ++ii) {
			// printf("-->%d\n", (*ii)->lineno);
			int dev_no = 0;
			statement *curr = (*ii)->next;
			set<dir_decl*> seen;	// store those gpu graph which has been used in previous section
			
			while(curr != (*ii)->end_stmt) {
				if(curr->sttype != SECTION_STMT) {
					fprintf(stderr, "%s %d\n", "SECTION not found", curr->lineno);
					exit(1);
				}

				map<dir_decl*, set<char*, comparator> > rmp, wmp;
				map<dir_decl*, vector<statement*> > kers;
				
				for(; jj!=kernels.end(); ++jj) {
					if((*jj)->lineno > curr->end_stmt->lineno) {
						break;
					} else if((*jj)->lineno >= curr->lineno) {
						if(start == kernels.end()) {
							start = jj;
						}
						end = jj;

						find_attrs_in_kernel(rmp, wmp, kers, *jj);
						// assign_stmt *astmt = (*jj)->stassign->rhs->arglist;
						// while(astmt) {
						// 	if(astmt->rhs && astmt->rhs->expr_type == VAR && astmt->rhs->lhs->libdtype == GRAPH_TYPE) {
						// 		dir_decl *d = astmt->rhs->lhs;
						// 		if(kers.find(d) != kers.end()) {
						// 			kers[d].push_back(*jj);
						// 		} else {
						// 			kers.insert(pair<dir_decl*, vector<statement*> >(d, vector<statement*>(1, *jj)));
						// 		}
						// 		// if(graphs.find(d) == graphs.end()) {
						// 		// 	graphs.insert(d);
						// 		// 	if(dev_no > 0) {
						// 		// 		d->dev_no = dev_no;
						// 		// 	}
						// 		// 	dev_no++;
						// 		// } else {
						// 		// 	(*jj)->stream_id = stream_no++;
						// 		// }
						// 		// insert props
						// 		set<statement*> visited;
						// 		statement *target = get_function((*jj)->stassign->rhs->name);
						// 		if(target == NULL) {
						// 			fprintf(stderr, "%s function definition not found.\n", (*jj)->stassign->rhs->name);
						// 			exit(1);
						// 		}
						// 		find_properties(rmp, wmp, target->next->next, target->end_stmt, d, visited);
								
						// 		break;
						// 	}
						// 	astmt = astmt->next;
						// }
					}
				}

				// set<string> attrs;

				// for(map<dir_decl*, set<char*, comparator> >::iterator it1=rmp.begin(); it1!=rmp.end(); ++it1) {
				// 	if(wmp.find(it1->first) != wmp.end()) {
				// 		wmp[it1->first].insert(it1->second.begin(), it1->second.end());
				// 	} else {
				// 		wmp.insert(pair<dir_decl*, set<char*, comparator> >(it1->first, it1->second));
				// 	}
				// }

				copy(wmp, rmp);
				
				// replace graph used in each section by new gpu graph
				for(map<dir_decl*, set<char*, comparator> >::iterator it1=wmp.begin(); it1!=wmp.end(); ++it1) {
					kk = tab.find(it1->first);
					dir_decl *dn = NULL;
					if(kk == tab.end()) {
						dn = new dir_decl();
						dn->dev_no = dev_no;
						dn->gpu = 1;
						dn->libdtype = GRAPH_TYPE;
						char buff[30];
						snprintf(buff, 10, "_flcn%d", falc_ext++);
						dn->name = create_string(buff);

						tab.insert(pair<dir_decl*, map<dir_decl*, set<char*, comparator> > >(it1->first, map<dir_decl*, set<char*, comparator> >()));
						tab[it1->first].insert(pair<dir_decl*, set<char*, comparator> >(dn, it1->second));
					} else {
						int mx_count = 0;
						for(map<dir_decl*, set<char*, comparator> >::iterator it2=kk->second.begin(); it2!=kk->second.end(); ++it2) {
							if(seen.find(it2->first) == seen.end()) {
								int cnt = 0;
								for(set<char*, comparator>::iterator it3=it1->second.begin(); it3!=it1->second.end(); ++it3) {
									if(it2->second.find(*it3) != it2->second.end()) {
										cnt++;
									}
								}
								if(cnt > mx_count) {
									mx_count = cnt;
									dn = it2->first;
								}
							}
						}

						if(dn != NULL) {
							kk->second[dn].insert(it1->second.begin(), it1->second.end());
						} else {
							dn = new dir_decl();
							dn->dev_no = dev_no;
							dn->gpu = 1;
							dn->libdtype = GRAPH_TYPE;
							char buff[30];
							snprintf(buff, 10, "_flcn%d", falc_ext++);
							dn->name = create_string(buff);

							kk->second.insert(pair<dir_decl*, set<char*, comparator> >(dn, it1->second));
						}
					}

					for(vector<statement*>::iterator it2=kers[it1->first].begin(); it2!=kers[it1->first].end(); ++it2) {
						change_cpu_graph(*it2, dn);
					}
					seen.insert(dn);
				}
				// map<dir_decl*, set<char*, comparator>*>::iterator it1 = rmp.find(d);
				// if(it1 != rmp.end()) {
				// 	for(set<char*, comparator>::iterator it2=it1->second->begin(); it2!=it1->second->end(); ++it2) {
				// 		attrs.insert(string(*it2));
				// 	}
				// }
				// it1 = wmp.find(d);
				// if(it1 != wmp.end()) {
				// 	for(set<char*, comparator>::iterator it2=it1->second->begin(); it2!=it1->second->end(); ++it2) {
				// 		attrs.insert(string(*it2));
				// 	}
				// }
				// wmp.clear();
				// rmp.clear();
				
				dev_no++;
				curr = curr->end_stmt->next;
				if(dev_no > TOT_GPU_GRAPH) {
					TOT_GPU_GRAPH = dev_no;
				}
			}
		}

		map<dir_decl*, set<char*, comparator> > rmp, wmp;
		map<dir_decl*, vector<statement*> > kers;

		for(jj=kernels.begin(); jj!=start; ++jj) {
			find_attrs_in_kernel(rmp, wmp, kers, *jj);
		}
		if(end != kernels.end()) {
			++end;
			for(; end!=kernels.end(); ++end) {
				find_attrs_in_kernel(rmp, wmp, kers, *end);
			}
		}
		copy(wmp, rmp);
		for(map<dir_decl*, set<char*, comparator> >::iterator it1=wmp.begin(); it1!=wmp.end(); ++it1) {
			kk = tab.find(it1->first);
			dir_decl *dn = NULL;
			if(kk == tab.end()) {
				dn = new dir_decl();
				dn->dev_no = 0;
				dn->gpu = 1;
				dn->libdtype = GRAPH_TYPE;
				char buff[30];
				snprintf(buff, 10, "_flcn%d", falc_ext++);
				dn->name = create_string(buff);

				tab.insert(pair<dir_decl*, map<dir_decl*, set<char*, comparator> > >(it1->first, map<dir_decl*, set<char*, comparator> >()));
				tab[it1->first].insert(pair<dir_decl*, set<char*, comparator> >(dn, it1->second));
			} else {
				int mx_count = 0;
				dir_decl *defg = NULL;

				for(map<dir_decl*, set<char*, comparator> >::iterator it2=kk->second.begin(); it2!=kk->second.end(); ++it2) {
					int cnt = 0;
					for(set<char*, comparator>::iterator it3=it1->second.begin(); it3!=it1->second.end(); ++it3) {
						if(it2->second.find(*it3) != it2->second.end()) {
							cnt++;
						}
					}
					if(cnt > mx_count) {
						mx_count = cnt;
						dn = it2->first;
					} else if(it2->first->dev_no == 0) {
						defg = it2->first;
					}
				}

				// if no gpu graph which uses this attrs, then map it to graph at device 0
				if(dn == NULL) {
					dn = defg;
				}

				if(dn != NULL) {
					kk->second[dn].insert(it1->second.begin(), it1->second.end());
				} else {
					dn = new dir_decl();
					dn->dev_no = 0;
					dn->gpu = 1;
					dn->libdtype = GRAPH_TYPE;
					char buff[30];
					snprintf(buff, 10, "_flcn%d", falc_ext++);
					dn->name = create_string(buff);

					kk->second.insert(pair<dir_decl*, set<char*, comparator> >(dn, it1->second));
				}
			}

			for(vector<statement*>::iterator it2=kers[it1->first].begin(); it2!=kers[it1->first].end(); ++it2) {
				change_cpu_graph(*it2, dn);
			}
		}

		insert_graph_node(tab);

	} else if(cpuParallelSection) {

		statement *end;
		if(kernels.size() > 0) {
			end = function_end(kernels.back());
		}

		int count = 0;
		for(int j=1; j<kernels.size(); ++j) {
			if(kernels[j-1]->comma && same_level(kernels[j-1], NULL, kernels[j])) {
				count++;
			} else if(count > 0){
				insert_parallel_section(kernels, j-1-count, j-1);
				count = 0;
			}
			kernels[j-1]->comma = false;
			
		}
		kernels.back()->comma = false;
		if(count > 0) {
			insert_parallel_section(kernels, kernels.size()-1-count, kernels.size()-1);
		}
	}
}