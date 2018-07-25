#include<cstdio>
#include <set>
#include <map>
#include <cstdlib>
#include "falctypes.h"

std::set<statement*> foreach_list;
extern std::map<char*, statement*> fnames;
extern std::map<char*, statement*> fnamescond;
extern tree_expr *binaryopnode(tree_expr *lhs,tree_expr *rhs,enum EXPR_TYPE etype,int ntype);
extern assign_stmt *createassignlhsrhs(enum ASSIGN_TYPE x,tree_expr *lhs,tree_expr *rhs);
extern int CONVERT_VERTEX_EDGE;

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

static statement* get_function(const char *name) {
	for(std::map<char*, statement*>::iterator it = fnames.begin(); it!=fnames.end(); it++) {
		if (strcmp(name, it->first) == 0) {
			return it->second;
		}
	}
	return NULL;
}

// get a name for variable such that it is not defined again in the same scope
char* get_variable(statement *stmt)
{
	char buff[10];
	buff[0] = 'f';
	buff[1] = 'x';
	int x = 0;
	return NULL;
}

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
					if((a==p && b==q) || (a==q && b==p)) {
						// printf("EXTENSION-62\n");
						exp->expr_type = VAR;
						exp->arglist = NULL;
						strcpy(exp->name, "weight");
						curr->stassign->rhs->lhs->lhs = edge;
					}
				}
			}
		} else if (curr->sttype == IF_STMT) {
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
							d->name = malloc(sizeof(char)*4);
							// dir_decl *d = params->dirrhs;
							strcpy(d->name, "e");
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
                strcpy(forstmt->expr1->lhs->name, "e");
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
            strcpy(forstmt->expr1->lhs->name, "p");
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
						point->name = malloc(sizeof(char)*4);
						edge = params->dirrhs;
						strcpy(point->name, "p");
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
        	d1->name = malloc(sizeof(char)*4);
        	strcpy(d1->name, "q");
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
			pointA->name = malloc(sizeof(char)*4);
			strcpy(pointA->name, "p");
			pointA->nodetype = -1;
			tree_expr *pointB = new tree_expr(d1);  		// second argument
			pointB->name = malloc(sizeof(char)*4);
			strcpy(pointB->name, "q");
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