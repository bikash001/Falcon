#ifndef EXTENSION_H
#define EXTENSION_H

#include <map>
#include <cstring>
#include "falctypes.h"
#include <cstdlib>
#include <set>
#include <string>
#include <vector>
using namespace std;

extern int falc_ext;
extern bool isGPU;

struct comparator
{
	bool operator()(char *a, char *b) const{
		return strcmp(a, b) < 0;
	}
};

statement* process(std::map<char*, statement*>&, statement*);
bool is_lib_attr(LIBDATATYPE, const char*);

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

inline char* mod_string(char *ptr, char *s)
{
    free(ptr);
    ptr = create_string(s);
    return ptr;
}


assign_stmt *createassignlhsrhs(enum ASSIGN_TYPE x,tree_expr *lhs,tree_expr *rhs);
statement *createstmt(STMT_TYPE sttype,tree_expr *expr,char *name,int lineno);
tree_expr *funcallpostfix(tree_expr *t1,enum EXPR_TYPE type,int kernel, tree_expr  *arglist);
tree_expr *binaryopnode(tree_expr *lhs,tree_expr *rhs,enum EXPR_TYPE etype,int ntype);
statement* insert_statement(statement *lhs, statement *stmt, statement *rhs);
tree_decl_stmt *createdeclstmt(class tree_typedecl *lhs,class tree_id *rhs,class dir_decl *dirrhs);


class FunctionInfo
{
private:
	statement *fnc;
	set<dir_decl*> local_vars;
	set<dir_decl*> global_read, global_write;
	set<char*, comparator> attr_read, attr_write;
public:
	FunctionInfo();
	FunctionInfo(const statement*);
	~FunctionInfo() {}
	string get_function_name() const;
	statement* get_function() const;
	void insert_var(const dir_decl*) const;
	void insert_var_read(dir_decl*);
	void insert_var_write(dir_decl*);
	void insert_global_var(dir_decl*);
	void insert_attr_read(char*);
	void insert_attr_write(char*);
	void insert_local_var(dir_decl*);
	bool is_local_var(const dir_decl*) const;
	void stats() const;
	void swap_local(FunctionInfo &);
	void copy_local(FunctionInfo &);
	void copy_all(FunctionInfo &f);
	bool rw_attr_dep(const FunctionInfo &) const;
	bool empty() const;
	bool attr_write_empty() const;
	set<char*, comparator> get_read_attr();
};


class ValuePair
{
private:
	vector<pair<statement*, set<dir_decl*> > > data;
public:
	void insert(statement*, set<dir_decl*>&);
	int size() const;
	pair<statement*, set<dir_decl*> > get(int) const;
};

#endif