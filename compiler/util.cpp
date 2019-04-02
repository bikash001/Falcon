#include "util.h"

int falc_ext = 0;	// variable names used by falcon extension "_flcn{falc_ext}"


// Inserts a statement stmt in between lhs and rhs
statement* insert_statement(statement *lhs, statement *stmt, statement *rhs)
{
	lhs->next = stmt;
	stmt->prev = lhs;
	stmt->next = rhs;
	rhs->prev = stmt;
    return stmt;
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


tree_decl_stmt *createdeclstmt(class tree_typedecl *lhs,class tree_id *rhs,class dir_decl *dirrhs) {
    tree_decl_stmt *ptr=new tree_decl_stmt();
    ptr->rhs=rhs;
    ptr->lhs=lhs;
    ptr->dirrhs=dirrhs;
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

FunctionInfo::FunctionInfo() {
    fnc = NULL;
}

FunctionInfo::FunctionInfo(const statement *stmt) {
    fnc = stmt;
}

statement* FunctionInfo::get_function() const {
    return fnc;
}
string FunctionInfo::get_function_name() const {
    if(fnc != NULL) {
        return string(fnc->stdecl->dirrhs->name);
    } else {
        return string();
    }
}
void FunctionInfo::insert_var(const dir_decl* d) const {
    if(is_local_var(d)) {
        insert_local_var(d);
    } else {
        insert_global_var(d);
    }
}
void FunctionInfo::insert_global_var(dir_decl* d) {
    global_read.insert(d);
}
void FunctionInfo::insert_local_var(dir_decl* d) {
    local_vars.insert(d);
}
bool FunctionInfo::is_local_var(const dir_decl* d) const {
    return local_vars.find(d) != local_vars.end();
}
void FunctionInfo::insert_attr_read(char* c) {
    attr_read.insert(c);
}
void FunctionInfo::insert_attr_write(char* c) {
    attr_write.insert(c);
}
void FunctionInfo::insert_var_read(dir_decl* d){
    if(!is_local_var(d)) {
        global_read.insert(d);
    }
}
void FunctionInfo::insert_var_write(dir_decl* d){
    if(!is_local_var(d)) {
        global_write.insert(d);
    }
}
void FunctionInfo::stats() const {
    fprintf(stderr, "%d %d %d %d %d\n", local_vars.size(), global_read.size(), global_write.size(), attr_read.size(), attr_write.size());
}
void FunctionInfo::swap_local(FunctionInfo &f) {
    local_vars.swap(f.local_vars);
}
void FunctionInfo::copy_local(FunctionInfo &f) {
    local_vars.insert(f.local_vars.begin(), f.local_vars.end());
}
void FunctionInfo::copy_all(FunctionInfo &f) {
    global_read.insert(f.global_read.begin(), f.global_read.end());
    global_write.insert(f.global_write.begin(), f.global_write.end());
    attr_read.insert(f.attr_read.begin(), f.attr_read.end());
    attr_write.insert(f.attr_write.begin(), f.attr_write.end());
}
bool FunctionInfo::rw_attr_dep(const FunctionInfo &f) const {
    for(set<char*, comparator>::iterator ii=attr_read.begin(); ii!=attr_read.end(); ++ii) {
        if(f.attr_write.find(*ii) != f.attr_write.end()) {
            return true;
        }
    }
    return false;
}
bool FunctionInfo::empty() const {
    if(!local_vars.empty()) return false;
    if(!global_read.empty() || !global_write.empty()) return false;
    if(!attr_read.empty() || !attr_write.empty()) return false;
    return true;
}
bool FunctionInfo::attr_write_empty() const {
    return attr_write.empty();
}
set<char*, comparator> FunctionInfo::get_read_attr() {
    return attr_read;
}
// void FunctionInfo::intersection(FunctionInfo &f, vector<)

void ValuePair::insert(statement *stmt, set<dir_decl*> &v) {
    data.push_back(make_pair(stmt, v));
}
int ValuePair::size() const {
    return data.size();
}
pair<statement*, set<dir_decl*> > ValuePair::get(int i) const {
    return data[i];
}