#include<cstdio>
#include <set>
#include <map>
#include <cstdlib>
#include "falctypes.h"

std::set<statement*> foreach_list;
extern std::map<char*, statement*> fnames;
extern std::map<char*, statement*> fnamescond;
extern tree_expr *binaryopnode(tree_expr *lhs,tree_expr *rhs,enum EXPR_TYPE etype,int ntype);

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
char* get_variable(statement *stmt) {
	char buff[10];
	buff[0] = 'f';
	buff[1] = 'x';
	int x = 0;
	return NULL;
}

void convert_vertex_edge()
{
	for(std::set<statement*>::iterator ii = foreach_list.begin(); ii != foreach_list.end(); ++ii)
	{
		statement *forstmt = *ii;
		if (forstmt->itr == POINT_ITYPE) {
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
			}
		} else if (forstmt->itr == EDGES_ITYPE) {
			// foreach iterator
            forstmt->itr = POINT_ITYPE;
            strcpy(forstmt->expr1->lhs->name, "p");
        	forstmt->expr3 = NULL;

        	statement *function = get_function(forstmt->stassign->rhs->name);

        	// create foreach statement
        	statement *foreach_stmt = new statement();
        	foreach_stmt->sttype = FOREACH_STMT;
        	foreach_stmt->feb = 1;
        	foreach_stmt->itr = POINT_ITYPE;
        	dir_decl *d1 = new dir_decl();
        	d1->name = malloc(sizeof(char)*4);

        	foreach_stmt->expr1 = new tree_expr(d1);
        	foreach_stmt->expr2 = new tree_expr(forstmt->expr1->lhs);
		}
	}
}