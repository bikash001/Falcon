#include "extension.h"

int falc_ext = 0;	// variable names used by falcon extension "_flcn{falc_ext}"


// Inserts a statement stmt in between lhs and rhs
void insert_statement(statement *lhs, statement *stmt, statement *rhs)
{
	lhs->next = stmt;
	stmt->prev = lhs;
	stmt->next = rhs;
	rhs->prev = stmt;
}


tree_expr *binaryopnode(tree_expr *lhs,tree_expr *rhs,enum EXPR_TYPE etype,int ntype) {
    tree_expr *expr=new tree_expr();
    expr->lhs=lhs;
    expr->rhs=rhs;
    expr->expr_type=etype;
    expr->nodetype=ntype;
    return expr;
}

tree_expr *funcallpostfix(tree_expr *t1,enum EXPR_TYPE type,int kernel, tree_expr  *arglist) {
    t1->expr_type=type;
    t1->kernel=kernel;
    if(arglist!=NULL) {
        t1->arglist=new assign_stmt();
        t1->arglist->lhs=NULL;
        t1->arglist->rhs=arglist;
        assign_stmt *ass=t1->arglist;
        while(ass!=NULL) {
            dir_decl *d1=ass->rhs->lhs;
            if(d1!=NULL)d1->isparam=true;
            ass=ass->next;
        }
    }
    return t1;
}

statement *createstmt(STMT_TYPE sttype,tree_expr *expr,char *name,int lineno) {
    statement *ptr=new statement();
    ptr->sttype=sttype;
    ptr->expr1=expr;
    ptr->name=name;
    ptr->lineno=lineno;
    return ptr;
}

assign_stmt *createassignlhsrhs(enum ASSIGN_TYPE x,tree_expr *lhs,tree_expr *rhs) {
    assign_stmt *ptr=new assign_stmt();
    ptr->asstype=x;
    ptr->lhs=lhs;
    ptr->rhs=rhs;
    return ptr;
}



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
