#include <stdio.h>
#include <stdlib.h>

struct Prog {
    struct Gdecl_sec* gds_;
    struct Fdef_sec* fds_;
    struct MainBlock* mb_;
};
struct Gdecl_sec {
    struct Gdecl_list* gdl_;
};
struct Gdecl_list {
    struct Gdecl* gd_;
    struct Gdecl_list* next;
};
struct Gdecl {
    struct ret_type* rt_;
    struct Glist* gl_;
};
struct ret_type {
    char* rtyp_;
};
struct Glist {
    struct Gid* gid_;
    struct func* func_;
    struct Glist* next;
};
struct Gid {
    int type_;
    
    //      type_=1
    char* var_;

    //      type_=2
    struct Gid* gid_;
    int num_;
};
struct func {
    char* var_;
    struct arg_list* argl_;
};
struct arg_list {
    struct arg_list1* argl1_;
};
struct arg_list1 {
    struct arg* arg_;
    struct arg_list1* next;
};
struct arg {
    struct arg_type* argtyp_;
    struct var_list* varlst_;
};
struct arg_type {
    char* argtyp_;
    // int Intargtyp_;
};
struct var_list {
    char* var_;
    struct var_list* next;
};
struct Fdef_sec {
    struct Fdef_sec* next;
    struct Fdef* fdef_;
};
struct Fdef {
    struct func_ret_type* fnrt_;
    struct func_name* fname_;
    struct FargList* fargl_;
    struct Ldecl_sec* ldecs_;
    struct stmt_list* stml_;
    struct ret_stmt* rets_;
};
struct func_ret_type {
    char* fnrettyp_;
};
struct func_name {
    char* var_;
};
struct FargList {
    struct arg_list* argl_;
};
struct ret_stmt {
    struct expr* expr_;
};
struct MainBlock {
    struct func_ret_type* fnrt_;
    struct Main* Mn_;
    struct Ldecl_sec* Lds_;
    struct stmt_list* smtlst_;
    struct ret_stmt* retsmt_;
};
struct Main {
    int isDone_;
};
struct Ldecl_sec {
    struct Ldecl_list* Ldeclist_;
};
struct Ldecl_list {
    struct Ldecl* Ldl_;
    struct Ldecl_list* next;
};
struct Ldecl {
    struct type* typ_;
    struct Lid_list* Lidlst_;
};
struct type {
    char* type_;
};
struct Lid_list {
    struct Lid* Lid_;
    struct Lid_list* next;
};
struct Lid {
    char* var_;
};
struct stmt_list {
    struct statement* smt_;
    struct stmt_list* next;
};
struct statement {
    int type;
    struct assign_stmt* as_smt_;
    struct read_stmt* read_smt_;
    struct write_stmt* wrt_smt_;
    struct cond_stmt* cnd_smt_;
    struct func_stmt* fn_smt_;
};
struct read_stmt {
    struct var_expr* vrexpr_;
};
struct write_stmt {
    int type;
    struct expr* expr_;
    struct str_expr* str_expr_;
};
struct assign_stmt {
    struct var_expr* vrexpr_;
    struct expr* expr_;
};
struct cond_stmt {
    int type;

    struct expr* expr_;
    struct stmt_list* smtlst_;
    struct stmt_list* smtlst_else_;
    struct assign_stmt* assmt1_;
    struct assign_stmt* assmt2_;
};
struct func_stmt {
    struct func_call* fncl_;
};
struct func_call {
    struct param_list* prmlst_;
};
struct param_list {
    struct param_list1* prmlst1;
};
struct param_list1 {
    struct para* pra_;
    struct param_list1* next;
};
struct para {
    struct expr* expr_;
};
struct expr {
    int value;
    int sign;
    struct var_expr* vrexpr_;
    int isBool;
    struct func_call* fncl_;
};
struct str_expr {
    char* var_;
    struct str_expr* next;
};
struct var_expr
{
    int type;

    // 1
    char* var_;

    // 2
    struct var_expr* vrexpr_;
    struct expr* expr_;
};

struct Prog* createProg(struct Gdecl_sec* gds__, struct Fdef_sec* fds__, struct MainBlock* mb__);
struct Gdecl_sec* createGdecl_sec(struct Gdecl_list* gdl__);
struct Gdecl_list* createNullGdecl_list();
struct Gdecl_list* createGdecl_list(struct Gdecl* gd__,struct Gdecl_list* next_);
struct Gdecl* createGdecl(struct ret_type* rt__,struct Glist* gl__);
struct ret_type* createret_type(char* rtyp__);
struct Glist* createGlist(struct Gid* gid__,struct func* func__,struct Glist* next_);
struct Gid* createGid1(char* var__);
struct Gid* createGid2(struct Gid* gid__,int num__);
struct func* createfunc(char* var__,struct arg_list* argl__);
struct arg_list* createarg_list(struct arg_list1* argl1__);
struct arg_list1* createarg_list1(struct arg* arg__,struct arg_list1* next_);
struct arg* createarg(struct arg_type* argtyp__,struct var_list* varlst__);
struct arg_type* createarg_type(char* argtyp__);
struct var_list* createvar_list(char* var__,struct var_list* next_);
struct Fdef_sec* createFdef_sec(struct Fdef_sec* next_,struct Fdef* fdef__);
struct Fdef* create_Fdef(struct func_ret_type* fnrt, struct func_name* fname,
                         struct FargList* fargl, struct Ldecl_sec* ldecs,
                         struct stmt_list* stml, struct ret_stmt* rets);
struct func_ret_type* create_func_ret_type(char* fnrettyp);
struct func_name* create_func_name(char* var);
struct FargList* create_FargList(struct arg_list* argl);
struct ret_stmt* create_ret_stmt(struct expr* expr);
struct MainBlock* create_MainBlock(struct func_ret_type* fnrt, struct Main* Mn, 
                                    struct Ldecl_sec* Lds, struct stmt_list* smtlst, 
                                    struct ret_stmt* retsmt);
struct Main* create_Main(int isDone);
struct Ldecl_sec* create_Ldecl_sec(struct Ldecl_list* Ldeclist);
struct Ldecl_list* create_Ldecl_list(struct Ldecl* Ldl, struct Ldecl_list* next);
struct Ldecl* create_Ldecl(struct type* typ, struct Lid_list* Lidlst);
struct type* create_type(char* type);
struct Lid_list* create_Lid_list(struct Lid* Lid, struct Lid_list* next);
struct Lid* create_Lid(char* var);
struct stmt_list* create_stmt_list(struct statement* smt, struct stmt_list* next);
struct statement* create_statement(int type, struct assign_stmt* as_smt, struct read_stmt* read_smt, struct write_stmt* wrt_smt, struct cond_stmt* cnd_smt, struct func_stmt* fn_smt);
struct read_stmt* create_read_stmt(struct var_expr* vrexpr);
struct write_stmt* create_write_stmt(int type, struct expr* expr, struct str_expr* str_expr);
struct assign_stmt* create_assign_stmt(struct var_expr* vrexpr, struct expr* expr);
struct cond_stmt* create_cond_stmt(int type, struct expr* expr, struct stmt_list* smtlst, struct stmt_list* smtlst_else, struct assign_stmt* assmt1, struct assign_stmt* assmt2);
struct func_stmt* create_func_stmt(struct func_call* fncl);
struct func_call* create_func_call(char* var, struct param_list* prmlst);
struct param_list* create_param_list(struct param_list1* prmlst1);
struct param_list1* create_param_list1(struct para* pra, struct param_list1* next);
struct para* create_para(struct expr* expr);
struct expr* create_expr(int Typ,int value, struct var_expr* vrexpr, int isBool_,struct expr* expr_l_,int opTyp,struct expr* expr_r_, struct func_call* fncl);
struct str_expr* create_str_expr(char* var, struct str_expr* next);
struct var_expr* create_var_expr(int type, char* var, struct var_expr* vrexpr, struct expr* expr);