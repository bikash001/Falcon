#ifndef EXTENSION_H
#define EXTENSION_H

#include <map>
#include <cstring>
#include "falctypes.h"
#include <cstdlib>
#include <set>
#include <string>
using namespace std;

extern int falc_ext;

struct comparator
{
	bool operator()(char *a, char *b) const{
		return strcmp(a, b) < 0;
	}
};

statement* process(std::map<char*, statement*> &fnames, statement *head);
bool is_lib_attr(LIBDATATYPE type, const char *name);

inline dir_decl* get_parent_graph(dir_decl *dd)
{
	while(dd->parent && dd->parent->libdtype != GRAPH_TYPE) dd = dd->parent;
	return dd->parent;
}


inline char* create_string(char *str) {
	char* temp = malloc(sizeof(char)*(1+strlen(str)));
	strcpy(temp, str);
	return temp;
}

assign_stmt *createassignlhsrhs(enum ASSIGN_TYPE x,tree_expr *lhs,tree_expr *rhs);
statement *createstmt(STMT_TYPE sttype,tree_expr *expr,char *name,int lineno);
tree_expr *funcallpostfix(tree_expr *t1,enum EXPR_TYPE type,int kernel, tree_expr  *arglist);
tree_expr *binaryopnode(tree_expr *lhs,tree_expr *rhs,enum EXPR_TYPE etype,int ntype);
void insert_statement(statement *lhs, statement *stmt, statement *rhs);
tree_decl_stmt *createdeclstmt(class tree_typedecl *lhs,class tree_id *rhs,class dir_decl *dirrhs);


class FunctionInfo
{
private:
	statement *fnc;
	set<dir_decl*> local_vars;
	set<dir_decl*> global_vars;
public:
	FunctionInfo();
	FunctionInfo(const statement*);
	~FunctionInfo() {}
	string get_function_name() const;
	statement* get_function() const;
	void insert_var(const dir_decl*) const;
	void insert_global_var(dir_decl*);
	void insert_local_var(dir_decl*);
	bool is_local_var(const dir_decl*) const;
};

#endif