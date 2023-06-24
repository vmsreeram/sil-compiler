#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// ENFORCEINTMAIN should be 1 for valid c code
int PRINTWARNINGS = 0, ENFORCEINTMAIN=1;

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
    char* var_;
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
    int Type;
    int value;
    struct var_expr* vrexpr_;
    int isBool;
    struct expr* expr_l;
    int opType;
    struct expr* expr_r;
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

////////////////////////////////
struct symbolTable
{
    int retTyp; // 1 int; 2 bool
    char* varName;
    int isArr;
        int arrSize;
    
    int isAssnd; // only for non-array as of now
    int valu;

    int arr_val[200];

    struct symbolTable* next;
};
struct symbolTable* GLB_SYMTAB_HEAD;
struct symbolTable* GLB_SYMTAB_TAIL;

struct funcTable
{
    int retTyp; // 1 int; 2 bool
    char* fnName;
    struct symbolTable* LOC_SYMTAB_HEAD;
    struct symbolTable* LOC_SYMTAB_TAIL;
    struct arg_list* argl;
    struct Fdef* fdef;

    struct funcTable* next;
};
struct funcTable* FNTAB_HEAD;
struct funcTable* FNTAB_TAIL;

////////////////////////////////

struct Prog* createProg(struct Gdecl_sec* gds__, struct Fdef_sec* fds__, struct MainBlock* mb__)
{
    struct Prog* prog = (struct Prog*)malloc(sizeof(struct Prog));
    prog->gds_=gds__;
    prog->fds_=fds__;
    prog->mb_=mb__;

    return prog;
}
//struct Fdef_sec*
//struct MainBlock*
struct Gdecl_sec* createGdecl_sec(struct Gdecl_list* gdl__)
{
    struct Gdecl_sec* gdecl_sec = (struct Gdecl_sec*)malloc(sizeof(struct Gdecl_sec));
    gdecl_sec->gdl_=gdl__;

    // printf("Within fn\n");
    // struct Gdecl_list* gdl = gdecl_sec->gdl_;
    // printf("gdl ?\n");
    // if(gdl)
    // {
    //     printf("gdl is not NULL\n");
    // }
    // else
    // {
    //     printf("gdl is NULL\n");
    // }
    // printf("end Within fn\n");

    return gdecl_sec;

}
// struct Gdecl_list* createNullGdecl_list()
// {
//     struct Gdecl_list* gdecl_list = (struct Gdecl_list*)malloc(sizeof(struct Gdecl_list));
//     gdecl_list->gd_=NULL;
//     gdecl_list->next=NULL;
// }
struct Gdecl_list* createGdecl_list(struct Gdecl* gd__,struct Gdecl_list* next_)
{
    struct Gdecl_list* gdecl_list = (struct Gdecl_list*)malloc(sizeof(struct Gdecl_list));
    gdecl_list->gd_=gd__;
    gdecl_list->next=next_;
    
    return gdecl_list;
}
struct Gdecl* createGdecl(struct ret_type* rt__,struct Glist* gl__)
{
    struct Gdecl* gdecl = (struct Gdecl*)malloc(sizeof(struct Gdecl));
    gdecl->rt_=rt__;
    gdecl->gl_=gl__;

    return gdecl;
}
struct ret_type* createret_type(char* rtyp__)
{
    struct ret_type* rtyp = (struct ret_type*)malloc(sizeof(struct ret_type));
    rtyp->rtyp_=rtyp__;

    return rtyp;
}
struct Glist* createGlist(struct Gid* gid__,struct func* func__,struct Glist* next_)
{
    struct Glist* glist = (struct Glist*)malloc(sizeof(struct Glist));
    glist->gid_=gid__;
    glist->func_=func__;
    glist->next=next_;

    return glist;
}
//struct func*
//struct Glist*
struct Gid* createGid1(char* var__)
{
    struct Gid* gid = (struct Gid*)malloc(sizeof(struct Gid));
    gid->type_=1;
    gid->var_=var__;

    return gid;
}
struct Gid* createGid2(struct Gid* gid__,int num__)
{
    struct Gid* gid = (struct Gid*)malloc(sizeof(struct Gid));
    gid->type_=2;
    gid->gid_=gid__;
    gid->num_=num__;

    return gid;
}
struct func* createfunc(char* var__,struct arg_list* argl__)
{
    struct func* fnc = (struct func*)malloc(sizeof(struct func));
    fnc->var_=var__;
    fnc->argl_=argl__;

    return fnc;
}
struct arg_list* createarg_list(struct arg_list1* argl1__)
{
    struct arg_list* agl = (struct arg_list*)malloc(sizeof(struct arg_list));
    agl->argl1_=argl1__;

    return agl;
}
struct arg_list1* createarg_list1(struct arg* arg__,struct arg_list1* next_)
{
    struct arg_list1* agl1 = (struct arg_list1*)malloc(sizeof(struct arg_list1));
    agl1->arg_=arg__;
    agl1->next=next_;

    return agl1;
}
struct arg* createarg(struct arg_type* argtyp__,struct var_list* varlst__)
{
    struct arg* ag = (struct arg*)malloc(sizeof(struct arg));
    ag->argtyp_=argtyp__;
    ag->varlst_=varlst__;
    return ag;
}
struct arg_type* createarg_type(char* argtyp__)
{
    struct arg_type* argt = (struct arg_type*)malloc(sizeof(struct arg_type));
    argt->argtyp_=argtyp__;
    // if(!strcmp(argtyp__,"int"))
    //     argt->Intargtyp_=1;
    // else
    //     argt->Intargtyp_=2;

    // printf("!!!! %s !!!!\n",argt->argtyp_);

    return argt;
}
struct var_list* createvar_list(char* var__,struct var_list* next_)
{
    struct var_list* varl = (struct var_list*)malloc(sizeof(struct var_list));
    varl->next=next_;
    varl->var_=var__;

    return varl;
}
struct Fdef_sec* createFdef_sec(struct Fdef_sec* next_,struct Fdef* fdef__)
{
    struct Fdef_sec* fds = (struct Fdef_sec*)malloc(sizeof(struct Fdef_sec));
    fds->fdef_=fdef__;
    fds->next=next_;

    return fds;
}
/// @brief chatgpt
struct Fdef* create_Fdef(struct func_ret_type* fnrt, struct func_name* fname,
                         struct FargList* fargl, struct Ldecl_sec* ldecs,
                         struct stmt_list* stml, struct ret_stmt* rets) {
    struct Fdef* new_fdef = (struct Fdef*)malloc(sizeof(struct Fdef));
    new_fdef->fnrt_ = fnrt;
    new_fdef->fname_ = fname;
    new_fdef->fargl_ = fargl;
    new_fdef->ldecs_ = ldecs;
    new_fdef->stml_ = stml;
    new_fdef->rets_ = rets;
    return new_fdef;
}
struct func_ret_type* create_func_ret_type(char* fnrettyp) {
    struct func_ret_type* new_frt = (struct func_ret_type*)malloc(sizeof(struct func_ret_type));
    new_frt->fnrettyp_ = fnrettyp;
    return new_frt;
}
struct func_name* create_func_name(char* var) {
    struct func_name* new_fn = (struct func_name*)malloc(sizeof(struct func_name));
    new_fn->var_ = var;
    return new_fn;
}
struct FargList* create_FargList(struct arg_list* argl) {
    struct FargList* new_fal = (struct FargList*)malloc(sizeof(struct FargList));
    new_fal->argl_ = argl;
    return new_fal;
}
struct ret_stmt* create_ret_stmt(struct expr* expr) {
    struct ret_stmt* new_rs = (struct ret_stmt*)malloc(sizeof(struct ret_stmt));
    new_rs->expr_ = expr;
    return new_rs;
}
struct MainBlock* create_MainBlock(struct func_ret_type* fnrt, struct Main* Mn, 
                                    struct Ldecl_sec* Lds, struct stmt_list* smtlst, 
                                    struct ret_stmt* retsmt) {
    struct MainBlock* new_mb = (struct MainBlock*)malloc(sizeof(struct MainBlock));
    new_mb->fnrt_ = fnrt;
    new_mb->Mn_ = Mn;
    new_mb->Lds_ = Lds;
    new_mb->smtlst_ = smtlst;
    new_mb->retsmt_ = retsmt;
    return new_mb;
}
struct Main* create_Main(int isDone) {
    struct Main* new_mn = (struct Main*)malloc(sizeof(struct Main));
    new_mn->isDone_ = isDone;
    return new_mn;
}

struct Ldecl_sec* create_Ldecl_sec(struct Ldecl_list* Ldeclist) {
    struct Ldecl_sec* new_lds = (struct Ldecl_sec*)malloc(sizeof(struct Ldecl_sec));
    new_lds->Ldeclist_ = Ldeclist;
    return new_lds;
}
struct Ldecl_list* create_Ldecl_list(struct Ldecl* Ldl, struct Ldecl_list* next) {
    struct Ldecl_list* new_ldl = (struct Ldecl_list*)malloc(sizeof(struct Ldecl_list));
    new_ldl->Ldl_ = Ldl;
    new_ldl->next = next;
    return new_ldl;
}

struct Ldecl* create_Ldecl(struct type* typ, struct Lid_list* Lidlst) {
    struct Ldecl* new_ld = (struct Ldecl*)malloc(sizeof(struct Ldecl));
    new_ld->typ_ = typ;
    new_ld->Lidlst_ = Lidlst;
    return new_ld;
}

struct type* create_type(char* type) {
    struct type* new_typ = (struct type*)malloc(sizeof(struct type));
    new_typ->type_ = type;
    return new_typ;
}

struct Lid_list* create_Lid_list(struct Lid* Lid, struct Lid_list* next) {
    struct Lid_list* new_lidl = (struct Lid_list*) malloc(sizeof(struct Lid_list));
    new_lidl->Lid_ = Lid;
    new_lidl->next = next;
    return new_lidl;
}

struct Lid* create_Lid(char* var) {
    struct Lid* new_lid = (struct Lid*) malloc(sizeof(struct Lid));
    new_lid->var_ = var;
    return new_lid;
}

struct stmt_list* create_stmt_list(struct statement* smt, struct stmt_list* next) {
    struct stmt_list* new_stmt = (struct stmt_list*) malloc(sizeof(struct stmt_list));
    new_stmt->smt_ = smt;
    new_stmt->next = next;
    return new_stmt;
}

struct statement* create_statement(int type, struct assign_stmt* as_smt, struct read_stmt* read_smt, struct write_stmt* wrt_smt, struct cond_stmt* cnd_smt, struct func_stmt* fn_smt) {
    struct statement* new_state = (struct statement*) malloc(sizeof(struct statement));
    new_state->type = type;
    new_state->as_smt_ = as_smt;
    new_state->read_smt_ = read_smt;
    new_state->wrt_smt_ = wrt_smt;
    new_state->cnd_smt_ = cnd_smt;
    new_state->fn_smt_ = fn_smt;
    return new_state;
}

struct read_stmt* create_read_stmt(struct var_expr* vrexpr) {
    struct read_stmt* new_read = (struct read_stmt*) malloc(sizeof(struct read_stmt));
    new_read->vrexpr_ = vrexpr;
    return new_read;
}

struct write_stmt* create_write_stmt(int type, struct expr* expr, struct str_expr* str_expr) {
    struct write_stmt* new_write = (struct write_stmt*) malloc(sizeof(struct write_stmt));
    new_write->type = type;
    new_write->expr_ = expr;
    new_write->str_expr_ = str_expr;
    return new_write;
}

struct assign_stmt* create_assign_stmt(struct var_expr* vrexpr, struct expr* expr) {
    struct assign_stmt* new_assign = (struct assign_stmt*) malloc(sizeof(struct assign_stmt));
    new_assign->vrexpr_ = vrexpr;
    new_assign->expr_ = expr;
    return new_assign;
}

struct cond_stmt* create_cond_stmt(int type, struct expr* expr, struct stmt_list* smtlst, struct stmt_list* smtlst_else, struct assign_stmt* assmt1, struct assign_stmt* assmt2) {
    struct cond_stmt* new_cond = (struct cond_stmt*) malloc(sizeof(struct cond_stmt));
    new_cond->type = type;
    new_cond->expr_ = expr;
    new_cond->smtlst_ = smtlst;
    new_cond->smtlst_else_ = smtlst_else;
    new_cond->assmt1_ = assmt1;
    new_cond->assmt2_ = assmt2;
    return new_cond;
}

struct func_stmt* create_func_stmt(struct func_call* fncl) {
    struct func_stmt* new_func = (struct func_stmt*) malloc(sizeof(struct func_stmt));
    new_func->fncl_ = fncl;
    return new_func;
}

struct func_call* create_func_call(char* var, struct param_list* prmlst) {
    struct func_call* new_fncl = (struct func_call*) malloc(sizeof(struct func_call));
    new_fncl->var_=var;
    new_fncl->prmlst_ = prmlst;
    return new_fncl;
}

struct param_list* create_param_list(struct param_list1* prmlst1) {
    struct param_list* new_prlst = (struct param_list*)malloc(sizeof(struct param_list));
    new_prlst->prmlst1 = prmlst1;
    return new_prlst;
}

struct param_list1* create_param_list1(struct para* pra, struct param_list1* next) {
    struct param_list1* new_prlst1 = (struct param_list1*)malloc(sizeof(struct param_list1));
    new_prlst1->pra_ = pra;
    new_prlst1->next = next;
    return new_prlst1;
}

struct para* create_para(struct expr* expr) {
    struct para* new_para = (struct para*)malloc(sizeof(struct para));
    new_para->expr_ = expr;
    return new_para;
}

struct expr* create_expr(int Typ,int value, struct var_expr* vrexpr, int isBool_,struct expr* expr_l_,int opTyp,struct expr* expr_r_, struct func_call* fncl) {
    struct expr* new_expr = (struct expr*)malloc(sizeof(struct expr));
    new_expr->Type = Typ;
    new_expr->value = value;
    new_expr->vrexpr_=vrexpr;
    new_expr->isBool=isBool_;
    new_expr->expr_l=expr_l_;
    new_expr->opType=opTyp;
    new_expr->expr_r=expr_r_;
    new_expr->fncl_=fncl;
    return new_expr;
}

struct str_expr* create_str_expr(char* var, struct str_expr* next) {
    struct str_expr* new_str_expr = (struct str_expr*)malloc(sizeof(struct str_expr));
    new_str_expr->var_ = var;
    new_str_expr->next = next;
    return new_str_expr;
}

struct var_expr* create_var_expr(int type, char* var, struct var_expr* vrexpr, struct expr* expr) {
    struct var_expr* new_var_expr = (struct var_expr*)malloc(sizeof(struct var_expr));
    new_var_expr->type = type;
    new_var_expr->var_ = var;
    new_var_expr->vrexpr_ = vrexpr;
    new_var_expr->expr_ = expr;
    return new_var_expr;
}


////////////////////////////////
struct symbolTable* newSymTabEntry(int retTyp_,char* varName_,int isArr_,int arrSize_)
{
    struct symbolTable* st = (struct symbolTable*)malloc(sizeof(struct symbolTable));
    st->retTyp = retTyp_;
    
    st->varName = (char *)malloc(100);
    strcpy(st->varName,varName_);
    st->isArr = isArr_;
    st->arrSize = arrSize_;

    st->isAssnd = 0;

    st->valu = 0;   // default value 0
    for(int i=0;i<arrSize_;i++)
        st->arr_val[i] = 0;
    
    return st;
}
struct funcTable* findByNameInFnTab(char* fnName_)
{
    struct funcTable* cur = FNTAB_HEAD;
    while(cur)
    {
        if(!strcmp(cur->fnName,fnName_))
        {
            return cur;
        }
        else
        {
            cur=cur->next;
        }
    }
    return 0;
}
struct symbolTable* findByNameInSymTab(char* varName_)
{
    struct symbolTable* cur = GLB_SYMTAB_HEAD;
    while(cur)
    {
        if(!strcmp(cur->varName,varName_))
        {
            return cur;
        }
        else
        {
            cur=cur->next;
        }
    }
    return 0;
}

struct symbolTable* findByNameInLOCALSymTab(struct symbolTable* head, char* varName_)
{
    // printf("// findByNameInLOCALSymTab in check for %s.\n",varName_);
    struct symbolTable* cur = head;
    while(cur)
    {
        if(!strcmp(cur->varName,varName_))
        {
            return cur;
        }
        else
        {
            cur=cur->next;
        }
    }
    return 0;
}

int countArgs;
int isMismatchArgList(struct arg_list* fal1,struct arg_list* fal2)
{
    // printf("// 2.first\n");
    if(fal1==0)
    {
        if(fal2)
        {
            return 1;
        }
        else 
        {
            countArgs=0;
            return 0;
        }
    }
    if(fal2==0)
    {
        if(fal1)
        {
            return 1;
        }
        else 
        {
            countArgs=0;
            return 0;
        }
    }
    countArgs=0;
    struct arg_list1* argl11 = fal1->argl1_;
    struct arg_list1* argl12 = fal2->argl1_;
    // printf("// 2.1\n");
    while (argl11->arg_)
    {
    // printf("// 2.11\n");
        struct arg* arg1 = argl11->arg_;
        struct arg* arg2 = argl12->arg_;
    // printf("// 2.111\n");
    // printf("arg1 argtyp = %s\n",arg1->argtyp_->argtyp_);
    // printf("arg2 argtyp = %s\n",arg2->argtyp_->argtyp_);
        if(strcmp(arg1->argtyp_->argtyp_,arg2->argtyp_->argtyp_))
        {
            // printf("/// ret1 as argtyps mismatch\n");
            return 1;
        }

    // printf("// 2.12\n");
        struct var_list* vl1 = arg1->varlst_;
        struct var_list* vl2 = arg2->varlst_;
    // printf("// 2.2\n");
        while (vl1)
        {
    // printf("// 2.3\n");
    countArgs++;
            vl1=vl1->next;
            vl2=vl2->next;
            if((vl1==0)^(vl2==0))return 1;
            else if((vl1==0)&&(vl2==0))break;
        }
        

        argl11=argl11->next;
        argl12=argl12->next;
        if((argl11==0)^(argl12==0))
        {
            return 1;
        }
        else if((argl11==0)&&(argl12==0))
        {
            break;
        }
    }
    // printf("// 2.last\n");
    return 0;
}

int ABORT_NOW;
int evalExpr(struct expr* ex, struct symbolTable* stHead)
{
    // ABORT_NOW = 0;
    if(ex->Type == 1)
    {
        return ex->value;
    }
    else if(ex->Type == 2)
    {
        if(ex->vrexpr_->type == 1)  // VAR
        {
            struct symbolTable* ste = findByNameInLOCALSymTab(stHead,ex->vrexpr_->var_);
            if(ste == 0)
            {
                printf("Error: variable `%s` is not declared\n",ex->vrexpr_->var_);
                ABORT_NOW = 1;
                return -1;
            }
            if(ste->isArr)
            {
                printf("Error: variable `%s` is declared as an array\n",ex->vrexpr_->var_);
                ABORT_NOW = 1;
                return -1;
            }
            if(ste->isAssnd == 0)
            {
                if(PRINTWARNINGS) printf("/* Warning: variable `%s` is unassigned */\n",ex->vrexpr_->var_);
            }
            return ste->valu;
        }
        else if(ex->vrexpr_->type == 2)  // only VAR[NUM] is allowed
        {
            if(ex->vrexpr_->vrexpr_->type != 1)
            {
                printf("Error: only one level of array is permitted in this version of compiler\n");
                ABORT_NOW = 1;
                return -1;
            }
            struct symbolTable* ste = findByNameInLOCALSymTab(stHead,ex->vrexpr_->vrexpr_->var_);
            if(ste == 0)
            {
                printf("Error: variable `%s` is not declared\n",ex->vrexpr_->vrexpr_->var_);
                ABORT_NOW = 1;
                return -1;
            }
            int evalVal = evalExpr(ex->vrexpr_->expr_,stHead);
            if(ste->arrSize<=evalVal || evalVal<0)
            {
                printf("Error: invalid access `%s[%d]`, array limits violated [arrSz=%d]\n",ex->vrexpr_->vrexpr_->var_,evalVal,ste->arrSize);
                ABORT_NOW = 1;
                return -1;
            }
            return ste->arr_val[evalVal];
        }
    }
    else if(ex->Type == 3)
    {
        if(ex->opType==214){
            return evalExpr(ex->expr_l,stHead);
        }
        else if(ex->opType==215){
            // printExpr(ex->expr_l);
            // printf("+");
            // printExpr(ex->expr_r);
            return evalExpr(ex->expr_l,stHead)+evalExpr(ex->expr_r,stHead);
        }
        else if(ex->opType==216){
            // printExpr(ex->expr_l);
            // printf("-");
            // printExpr(ex->expr_r);
            return evalExpr(ex->expr_l,stHead)-evalExpr(ex->expr_r,stHead);
        }
        else if(ex->opType==217){
            // printExpr(ex->expr_l);
            // printf("*");
            // printExpr(ex->expr_r);
            return evalExpr(ex->expr_l,stHead)*evalExpr(ex->expr_r,stHead);
        }
        else if(ex->opType==218){
            // printExpr(ex->expr_l);
            // printf("/");
            // printExpr(ex->expr_r);
            int den = evalExpr(ex->expr_r,stHead);
            if(den == 0)
            {
                ABORT_NOW=1;
                printf("Error: div by zero encountered\n");
                return -1;
            }
            return evalExpr(ex->expr_l,stHead)/den;
        }
        else if(ex->opType==219){
            // printExpr(ex->expr_l);
            // printf("%%");
            // printExpr(ex->expr_r);
            return (evalExpr(ex->expr_l,stHead)%evalExpr(ex->expr_r,stHead));
        }
        else if(ex->opType==220){
            // printExpr(ex->expr_l);
            // printf("<");
            // printExpr(ex->expr_r);
            return (evalExpr(ex->expr_l,stHead)<evalExpr(ex->expr_r,stHead));
        }
        else if(ex->opType==221){
            // printExpr(ex->expr_l);
            // printf(">");
            // printExpr(ex->expr_r);
            return (evalExpr(ex->expr_l,stHead)>evalExpr(ex->expr_r,stHead));
        }
        else if(ex->opType==222){
            // printExpr(ex->expr_l);
            // printf(">=");
            // printExpr(ex->expr_r);
            return (evalExpr(ex->expr_l,stHead)>=evalExpr(ex->expr_r,stHead));
        }
        else if(ex->opType==223){
            // printExpr(ex->expr_l);
            // printf("<=");
            // printExpr(ex->expr_r);
            return (evalExpr(ex->expr_l,stHead)<=evalExpr(ex->expr_r,stHead));
        }
        else if(ex->opType==224){
            // printExpr(ex->expr_l);
            // printf("!=");
            // printExpr(ex->expr_r);
            return (evalExpr(ex->expr_l,stHead)!=evalExpr(ex->expr_r,stHead));
        }
        else if(ex->opType==225){
            // printExpr(ex->expr_l);
            // printf("==");
            // printExpr(ex->expr_r);
            return (evalExpr(ex->expr_l,stHead)==evalExpr(ex->expr_r,stHead));
        }
        else if(ex->opType==226){
            // printf("!");
            // printExpr(ex->expr_l);
            return (!evalExpr(ex->expr_l,stHead));
        }
        else if(ex->opType==227){
            // printExpr(ex->expr_l);
            // printf("&&");
            // printExpr(ex->expr_r);
            return (evalExpr(ex->expr_l,stHead)&&evalExpr(ex->expr_r,stHead));
        }
        else if(ex->opType==228){
            // printExpr(ex->expr_l);
            // printf("||");
            // printExpr(ex->expr_r);
            return (evalExpr(ex->expr_l,stHead)||evalExpr(ex->expr_r,stHead));
        }
    }
    else if(ex->Type == 4)
    {
        // TODO: implement function call
        struct func_call* fncal = ex->fncl_;
        struct funcTable* newfte = findByNameInFnTab(fncal->var_);
        if(newfte == 0)
        {
            printf("Error: function `%s(...)` is not declared\n",fncal->var_);
            return 1;
        }
        struct param_list1* pl1 = fncal->prmlst_->prmlst1;
        // printf("checking params of %s\n",fncal->var_);
        while (pl1)
        {
            if(pl1->pra_==0)break;
            ABORT_NOW=0;
            int __disc_ret__ = evalExpr(pl1->pra_->expr_,stHead);
            if(ABORT_NOW){
                printf("Error: invalid arg in the func `%s`\n",fncal->var_);
                return 1;
            }
            // printf("This expr is valid:");
            // printExpr(pl1->pra_->expr_);
            // printf(".\n");
            pl1 = pl1->next;
        }
        /*done : check number of args in decl and call*/
        countArgs = 0;
        int _discard_ = isMismatchArgList(newfte->argl,newfte->argl);
        int numArgs_FTE = countArgs;

        int numArgs_FS = 0;
        struct param_list1* prl = fncal->prmlst_->prmlst1;
        if(prl!=0)
        while (prl->pra_)
        {
            numArgs_FS++;
            prl=prl->next;
            if(prl==0)break;
        }

        if(numArgs_FTE != numArgs_FS)
        {
            ABORT_NOW=1;
            printf("Error: number of arguments to function `%s` is %d in def but %d in call\n",fncal->var_,numArgs_FTE,numArgs_FS);
            return 1;
        }
        return -1;
    }
}
void printExpr(struct expr* ex);

int runStmLst(struct stmt_list* stml, struct funcTable* fte)
{
    while(stml->smt_)
    {
        // types of statements
        if(stml->smt_->type == 1) {
            struct assign_stmt* asmt = stml->smt_->as_smt_;
            if(asmt->vrexpr_->type==1)
            {
/// local then global
                struct symbolTable* sten = findByNameInLOCALSymTab(fte->LOC_SYMTAB_HEAD,asmt->vrexpr_->var_);
                if(sten == 0)
                {
                    printf("Error: variable `%s` is not declared\n",asmt->vrexpr_->var_);
                    return 1;
                }
                ABORT_NOW=0;
                int evaluatedExpr = evalExpr(asmt->expr_,fte->LOC_SYMTAB_HEAD);
                if(sten->isArr)
                {
                    printf("Error: variable `%s` is declared as an array\n",asmt->vrexpr_->var_);
                    printf("fnstms : Aborting now\n");
                    return 1;
                }
                if(ABORT_NOW)
                {
                    printf("fnstms : Aborting now\n");
                    return 1;
                }
                sten->isAssnd = 1;
                if(sten->retTyp==2)
                {
                    sten->valu = (evaluatedExpr!=0);
                }
                else
                {
                    sten->valu = evaluatedExpr;
                }
            }
            else if(asmt->vrexpr_->type==2)
            {
                if(asmt->vrexpr_->vrexpr_->type!=1)
                {
                    printf("Error: only one level of array is permitted in this version of compiler\n");
                    return 1;
                }
                struct symbolTable* sten = findByNameInSymTab(asmt->vrexpr_->vrexpr_->var_);
                if(sten == 0)
                {
                    printf("Error: array with name `%s` is not declared\n",asmt->vrexpr_->vrexpr_->var_);
                    return 1;
                }
                ABORT_NOW=0;
                int evalVal = evalExpr(asmt->vrexpr_->expr_,fte->LOC_SYMTAB_HEAD);
                if(ABORT_NOW)
                {
                    printf("fnstms : Aborting now\n");
                    return 1;
                }

                if(sten->arrSize<=evalVal || evalVal<0)
                {
                    printf("Error: invalid indexing at `[%d]` to array `%s`\n",evalVal,asmt->vrexpr_->vrexpr_->var_);
                    return 1;
                }
                ABORT_NOW=0;
                int evaluatedExpr = evalExpr(asmt->expr_,fte->LOC_SYMTAB_HEAD);
                if(ABORT_NOW)
                {
                    printf("fnstms : Aborting now\n");
                    return 1;
                }
                if(sten->retTyp==2)
                {
                    sten->arr_val[evalVal] = (evaluatedExpr!=0);
                }
                else
                {
                    sten->arr_val[evalVal]=evaluatedExpr;
                }
                // sten->arr_val[evalVal]=evaluatedExpr;
            }
        } else if(stml->smt_->type == 2) {
            struct read_stmt* rsmt = stml->smt_->read_smt_;

            if(rsmt->vrexpr_->type==1)
            {
/// local then global
                struct symbolTable* sten = findByNameInLOCALSymTab(fte->LOC_SYMTAB_HEAD,rsmt->vrexpr_->var_);
                if(sten == 0)
                {
                    printf("Error: variable `%s` is not declared\n",rsmt->vrexpr_->var_);
                    return 1;
                }
                if(sten->isArr)
                {
                    printf("Error: variable `%s` is declared as an array\n",rsmt->vrexpr_->var_);
                    printf("fnstms : Aborting now\n");
                    return 1;
                }
            }
            else if(rsmt->vrexpr_->type==2)
            {
                if(rsmt->vrexpr_->vrexpr_->type!=1)
                {
                    printf("Error: only one level of array is permitted in this version of compiler\n");
                    return 1;
                }
                struct symbolTable* sten = findByNameInSymTab(rsmt->vrexpr_->vrexpr_->var_);
                if(sten == 0)
                {
                    printf("Error: array with name `%s` is not declared\n",rsmt->vrexpr_->vrexpr_->var_);
                    return 1;
                }
                ABORT_NOW=0;
                int evalVal = evalExpr(rsmt->vrexpr_->expr_,fte->LOC_SYMTAB_HEAD);
                if(ABORT_NOW)
                {
                    printf("fnstms : Aborting now\n");
                    return 1;
                }

                if(sten->arrSize<=evalVal || evalVal<0)
                {
                    printf("Error: invalid indexing at `[%d]` to array `%s`\n",evalVal,rsmt->vrexpr_->vrexpr_->var_);
                    return 1;
                }
            }
        } else if(stml->smt_->type == 3) {
            struct write_stmt* wsmt = stml->smt_->wrt_smt_;
            if(wsmt->type == 1) {
                ABORT_NOW = 0;
                int _discard_ret_ = evalExpr(wsmt->expr_,fte->LOC_SYMTAB_HEAD);
                if(ABORT_NOW) {
                    printf("fnstms write : aborting now\n");
                    return 1;
                }
            } else {
                struct str_expr* stex = wsmt->str_expr_;
                while(stex->var_)
                {
                    struct symbolTable * _discard_ret_ = findByNameInLOCALSymTab(fte->LOC_SYMTAB_HEAD,stex->var_);
                    if(_discard_ret_ == 0)
                    {
                        printf("Error: variable `%s` is not declared\n",stex->var_);
                        return 1;
                    }
                    else if(_discard_ret_->isArr)
                    {
                        printf("Error: variable `%s` is declared as an array\n",stex->var_);
                        return 1;
                    }
                    else if(_discard_ret_->isAssnd == 0)
                    {
                        if(PRINTWARNINGS) printf("/* Warning: variable `%s` is unassigned */\n",stex->var_);
                    }
                    stex = stex->next;
                    if(stex==0)break;
                }
            }
        } else if(stml->smt_->type == 4) {
            struct cond_stmt* cdsmt = stml->smt_->cnd_smt_;
            if(cdsmt->type == 1) {
                ABORT_NOW=0;
                int __disc_ret__ = evalExpr(cdsmt->expr_,fte->LOC_SYMTAB_HEAD);
                if(ABORT_NOW)return 1;
                int ret1 = runStmLst(cdsmt->smtlst_,fte);
                if(ret1)
                {
                    return 1;
                }
            } else if(cdsmt->type == 2) {
                ABORT_NOW=0;
                int __disc_ret__ = evalExpr(cdsmt->expr_,fte->LOC_SYMTAB_HEAD);
                if(ABORT_NOW)return 1;
                int ret1 = runStmLst(cdsmt->smtlst_,fte);
                int ret2 = runStmLst(cdsmt->smtlst_else_,fte);
                if(ret1 || ret2)
                {
                    return 1;
                }
            } else if(cdsmt->type == 3) {
                ABORT_NOW=0;
                int __disc_ret__ = evalExpr(cdsmt->expr_,fte->LOC_SYMTAB_HEAD);
                if(ABORT_NOW)return 1;
                int ret1 = runStmLst(cdsmt->smtlst_,fte);
                if(ret1)
                {
                    return 1;
                }
            } else if(cdsmt->type == 4) {
                ABORT_NOW=0;
                int __disc_ret__ = evalExpr(cdsmt->expr_,fte->LOC_SYMTAB_HEAD);
                if(ABORT_NOW)return 1;
                int ret1 = runStmLst(cdsmt->smtlst_,fte);
                if(ret1)
                {
                    return 1;
                }
                // check both assignment statements
                    // ass1
                        struct assign_stmt* as1 = cdsmt->assmt1_;
                        // expr
                            ABORT_NOW=0;
                            __disc_ret__ = evalExpr(as1->expr_,fte->LOC_SYMTAB_HEAD);
                            if(ABORT_NOW)return 1;
                        // varexpr
                            if(as1->vrexpr_->type==1)
                            {
                                struct symbolTable* sten = findByNameInLOCALSymTab(fte->LOC_SYMTAB_HEAD,as1->vrexpr_->var_);
                                if(sten == 0)
                                {
                                    printf("Error: variable `%s` is not declared\n",as1->vrexpr_->var_);
                                    return 1;
                                }
                                if(sten->isArr)
                                {
                                    printf("Error: variable `%s` is declared as an array\n",as1->vrexpr_->var_);
                                    printf("fnstms : Aborting now\n");
                                    return 1;
                                }
                            }
                            else if(as1->vrexpr_->type==2)
                            {
                                if(as1->vrexpr_->vrexpr_->type!=1)
                                {
                                    printf("Error: only one level of array is permitted in this version of compiler\n");
                                    return 1;
                                }
                                struct symbolTable* sten = findByNameInSymTab(as1->vrexpr_->vrexpr_->var_);
                                if(sten == 0)
                                {
                                    printf("Error: array with name `%s` is not declared\n",as1->vrexpr_->vrexpr_->var_);
                                    return 1;
                                }
                                ABORT_NOW=0;
                                int evalVal = evalExpr(as1->vrexpr_->expr_,fte->LOC_SYMTAB_HEAD);
                                if(ABORT_NOW)
                                {
                                    printf("fnstms : Aborting now\n");
                                    return 1;
                                }

                                if(sten->arrSize<=evalVal || evalVal<0)
                                {
                                    printf("Error: invalid indexing at `[%d]` to array `%s`\n",evalVal,as1->vrexpr_->vrexpr_->var_);
                                    return 1;
                                }
                            }

                    // ass2
                        struct assign_stmt* as2 = cdsmt->assmt2_;
                        // expr
                            ABORT_NOW=0;
                            __disc_ret__ = evalExpr(as2->expr_,fte->LOC_SYMTAB_HEAD);
                            if(ABORT_NOW)return 1;
                        // varexpr
                        if(as2->vrexpr_->type==1)
                            {
                                struct symbolTable* sten = findByNameInLOCALSymTab(fte->LOC_SYMTAB_HEAD,as2->vrexpr_->var_);
                                if(sten == 0)
                                {
                                    printf("Error: variable `%s` is not declared\n",as2->vrexpr_->var_);
                                    return 1;
                                }
                                if(sten->isArr)
                                {
                                    printf("Error: variable `%s` is declared as an array\n",as2->vrexpr_->var_);
                                    printf("fnstms : Aborting now\n");
                                    return 1;
                                }
                            }
                            else if(as2->vrexpr_->type==2)
                            {
                                if(as2->vrexpr_->vrexpr_->type!=1)
                                {
                                    printf("Error: only one level of array is permitted in this version of compiler\n");
                                    return 1;
                                }
                                struct symbolTable* sten = findByNameInSymTab(as2->vrexpr_->vrexpr_->var_);
                                if(sten == 0)
                                {
                                    printf("Error: array with name `%s` is not declared\n",as2->vrexpr_->vrexpr_->var_);
                                    return 1;
                                }
                                ABORT_NOW=0;
                                int evalVal = evalExpr(as2->vrexpr_->expr_,fte->LOC_SYMTAB_HEAD);
                                if(ABORT_NOW)
                                {
                                    printf("fnstms : Aborting now\n");
                                    return 1;
                                }

                                if(sten->arrSize<=evalVal || evalVal<0)
                                {
                                    printf("Error: invalid indexing at `[%d]` to array `%s`\n",evalVal,as2->vrexpr_->vrexpr_->var_);
                                    return 1;
                                }
                            }

            }
        } else /*type=5*/ {
            struct func_stmt* funsmt = stml->smt_->fn_smt_;
            struct funcTable* newfte = findByNameInFnTab(funsmt->fncl_->var_);
            if(newfte == 0)
            {
                printf("Error: function `%s(...)` is not declared\n",funsmt->fncl_->var_);
                return 1;
            }
            struct param_list1* pl1 = funsmt->fncl_->prmlst_->prmlst1;
            // printf("checking params of %s\n",funsmt->fncl_->var_);
            while (pl1)
            {
                if(pl1->pra_==0)break;
                ABORT_NOW=0;
                int __disc_ret__ = evalExpr(pl1->pra_->expr_,fte->LOC_SYMTAB_HEAD);
                if(ABORT_NOW){
                    printf("Error: invalid arg in the func `%s`\n",funsmt->fncl_->var_);
                    return 1;
                }
                // printf("This expr is valid:");
                // printExpr(pl1->pra_->expr_);
                // printf(".\n");
                pl1 = pl1->next;
            }
            // NO EXPLICIT CHECK IS DONE FOR EACH VARIABLE TYPE MATCH AS IN C INT AND BOOL GETS TYPE CASTED AUTOMATICALLY
            /*done : check number of args in decl and call*/
            countArgs = 0;
            int _discard_ = isMismatchArgList(newfte->argl,newfte->argl);
            int numArgs_FTE = countArgs;

            int numArgs_FS = 0;
            struct param_list1* prl = funsmt->fncl_->prmlst_->prmlst1;
            if(prl!=0)
            while (prl->pra_)
            {
                numArgs_FS++;
                prl=prl->next;
                if(prl==0)break;
            }

            if(numArgs_FTE != numArgs_FS)
            {
                printf("Error: number of arguments to function `%s` is %d in def but %d in call\n",funsmt->fncl_->var_,numArgs_FTE,numArgs_FS);
                return 1;
            }
            
        }
        stml = stml->next;
        if(stml==0)break;
    }

    return 0;
}

int runProg(struct Gdecl_sec* gds__,struct Fdef_sec* fds__,struct MainBlock* mb__)
{
    // init vars
    GLB_SYMTAB_HEAD=0;
    GLB_SYMTAB_TAIL=0;
    FNTAB_HEAD=0;
    FNTAB_TAIL=0;
    
    ABORT_NOW = 0;
    
    struct Gdecl_list* gdl = gds__->gdl_;
    while (gdl->gd_)
    {
        // printf("//1\n");
        int RTYP;
        if(!strcmp(gdl->gd_->rt_->rtyp_,"int"))
            RTYP = 1;
        else
            RTYP = 2;
        // printf("//2\n");
        struct Glist* gl = gdl->gd_->gl_;
        // printf("//3\n");
        while (gl)
        {
            // printf("//4\n");
            if(gl->func_)
            {
                // printf("//5\n");
                /*check if it's already declared before*/
                if(findByNameInSymTab(gl->func_->var_))
                {
                    printf("Error: a variable with name `%s` is already declared\n",gl->func_->var_);
                    return 1;
                }
                if(findByNameInFnTab(gl->func_->var_))
                {
                    printf("Error: a function with name `%s` is already declared\n",gl->func_->var_);
                    return 1;
                }

                /*Insert into fnTab*/
                struct funcTable* fnte = (struct funcTable*)malloc(sizeof(struct funcTable));
                if(fnte==0){
                    printf("Error: malloc failed\n");
                    return 1;
                }
                fnte->retTyp = RTYP;
                fnte->fnName=(char *)malloc(100);
                strcpy(fnte->fnName,gl->func_->var_);
                fnte->argl=gl->func_->argl_;
                fnte->LOC_SYMTAB_HEAD=0;
                fnte->LOC_SYMTAB_TAIL=0;
                fnte->fdef=0;

                if(FNTAB_HEAD == 0)
                {
                    FNTAB_HEAD = fnte;
                }
                else
                {
                    FNTAB_TAIL->next = fnte;
                }
                FNTAB_TAIL = fnte;
                FNTAB_TAIL->next = 0;
                // printf("//6\n");
            }
            else 
            {
                // printf("//7\n");
                struct Gid* gid = gl->gid_;
                // /*check if it's already declared before*/    // removed as it is wrong
                // if(findByNameInSymTab(gid->var_))
                // {
                //     printf("Error: a variable with name `%s` is already declared\n",gid->var_);
                //     return 1;
                // }
                // if(findByNameInFnTab(gid->var_))
                // {
                //     printf("Error: a function with name `%s` is already declared\n",gid->var_);
                //     return 1;
                // }
                // printf("//7.1\n");
                /*Insert into symTab*/
                if(gid->type_==1)
                {
                    // printf("//7.11\n");
                    if(findByNameInSymTab(gid->var_))
                    {
                        printf("Error: a variable with name `%s` is already declared\n",gid->var_);
                        return 1;
                    }
                    if(findByNameInFnTab(gid->var_))
                    {
                        printf("Error: a function with name `%s` is already declared\n",gid->var_);
                        return 1;
                    }
                    
                    struct symbolTable* ste = newSymTabEntry(RTYP,gid->var_,0,0);
                    if(ste==0){
                        printf("Error: malloc failed\n");
                        return 1;
                    }
                    if(GLB_SYMTAB_HEAD == 0)
                    {
                        GLB_SYMTAB_HEAD = ste;
                    }
                    else
                    {
                        GLB_SYMTAB_TAIL->next = ste;
                    }
                    GLB_SYMTAB_TAIL = ste;
                    GLB_SYMTAB_TAIL->next = 0;
                    // printf("//7.12\n");
                }
                else
                {
                    // printf("//10\n");
                    struct Gid* gid_in = gid->gid_;
                    if(gid_in->type_!=1)
                    {
                        printf("Error: only one level of array is permitted in this version of compiler\n");
                        return 1;
                    }

                    if(findByNameInSymTab(gid_in->var_))
                    {
                        printf("Error: a variable with name `%s` is already declared\n",gid_in->var_);
                        return 1;
                    }
                    if(findByNameInFnTab(gid_in->var_))
                    {
                        printf("Error: a function with name `%s` is already declared\n",gid_in->var_);
                        return 1;
                    }
                    
                    struct symbolTable* ste = newSymTabEntry(RTYP,gid_in->var_,1,gid->num_);
                    if(ste==0){
                        printf("Error: malloc failed\n");
                        return 1;
                    }
                    if(GLB_SYMTAB_HEAD == 0)
                    {
                        GLB_SYMTAB_HEAD = ste;
                    }
                    else
                    {
                        GLB_SYMTAB_TAIL->next = ste;
                    }
                    GLB_SYMTAB_TAIL = ste;
                    GLB_SYMTAB_TAIL->next = 0;
                    // printf("//11\n");
                }
                // printf("//8\n");
            }
            gl=gl->next;
        }
        // printf("//9\n");
        gdl=gdl->next;
    }
    printf("/* inserted all to resp tabs */\n");
    
    struct Fdef_sec* fds = fds__;
    while (fds->fdef_)
    {
        struct funcTable* fte = findByNameInFnTab(fds->fdef_->fname_->var_);
        
        // should be declared
        if(fte == 0)
        {
            printf("Error: function with name `%s` was not declared\n",fds->fdef_->fname_->var_);
            return 1;
        }
        
        // printf("// 1\n");
        // return type should match
        if(!strcmp(fds->fdef_->fnrt_->fnrettyp_,"int"))
        {
            if(fte->retTyp!=1)
            {
                printf("Error: return type of function with name `%s` mismatched, decl to be bool but def is int\n",fds->fdef_->fname_->var_);
                return 1;
            }
        }
        else if(!strcmp(fds->fdef_->fnrt_->fnrettyp_,"bool"))
        {
            if(fte->retTyp!=2)
            {
                printf("Error: return type of function with name `%s` mismatched, decl to be int but def is bool\n",fds->fdef_->fname_->var_);
                return 1;
            }
        }
        
        // FargList should match        
        if(isMismatchArgList(fds->fdef_->fargl_->argl_,fte->argl))
        {
            printf("Error: mismatch in FargList for def and decl of func `%s`\n",fds->fdef_->fname_->var_);
            return 1;
        }
        // printf("// 3\n");

        // struct symbolTable* var = newSymTabEntry(...);
        // connect local symbol table for FargList
        struct arg_list1* argl = fds->fdef_->fargl_->argl_->argl1_;
        while(argl->arg_)
        {
            //////
            int VTYP=-1;
            if(!strcmp(argl->arg_->argtyp_->argtyp_,"int"))
                VTYP=1;
            else if(!strcmp(argl->arg_->argtyp_->argtyp_,"bool"))
                VTYP=2;
            struct var_list* varl = argl->arg_->varlst_;
            while (varl->var_)
            {
                struct symbolTable* tempSte = newSymTabEntry(VTYP,varl->var_,0,0);
                //
                if(fte->LOC_SYMTAB_HEAD==0)
                {
                    fte->LOC_SYMTAB_HEAD=tempSte;
                }
                else
                {
                    fte->LOC_SYMTAB_TAIL->next=tempSte;
                }
                fte->LOC_SYMTAB_TAIL=tempSte;
                // fte->LOC_SYMTAB_TAIL->next=0;
                fte->LOC_SYMTAB_TAIL->next=GLB_SYMTAB_HEAD;     /// <<<<<<<< 
                //
                varl=varl->next;
                if(varl==0)break;
            }
            //////
            argl = argl->next;
            if(argl==0)
                break;
        }
        
        // connect local symbol table for Ldecl_list
        struct Ldecl_list* ldl = fds->fdef_->ldecs_->Ldeclist_;
        while(ldl->Ldl_)
        {
            //////
            int VTYP=-1;
            if(!strcmp(ldl->Ldl_->typ_->type_,"int"))
                VTYP=1;
            else if(!strcmp(ldl->Ldl_->typ_->type_,"bool"))
                VTYP=2;
            struct Lid_list* lidl = ldl->Ldl_->Lidlst_;
            while (lidl->Lid_)
            {
                struct symbolTable* tempSte = newSymTabEntry(VTYP,lidl->Lid_->var_,0,0);
                //
                if(fte->LOC_SYMTAB_HEAD==0)
                {
                    fte->LOC_SYMTAB_HEAD=tempSte;
                }
                else
                {
                    fte->LOC_SYMTAB_TAIL->next=tempSte;
                }
                fte->LOC_SYMTAB_TAIL=tempSte;
                // fte->LOC_SYMTAB_TAIL->next=0;
                fte->LOC_SYMTAB_TAIL->next=GLB_SYMTAB_HEAD;     /// <<<<<<<< 
                //
                lidl=lidl->next;
                if(lidl==0)break;
            }
            //////
            ldl = ldl->next;
            if(ldl==0)
                break;
        }

        if(fte->LOC_SYMTAB_HEAD==0) // if no local decls, connect to globals
        {
            fte->LOC_SYMTAB_HEAD=GLB_SYMTAB_HEAD;
        }
        

        // connect fdef         // may not be reqd
        fte->fdef=fds->fdef_;

        // traverse statements
        struct stmt_list* stml = fds->fdef_->stml_;
        
        int ret = runStmLst(stml,fte);
        if(ret == 1)
        {
            return 1;
        }
/**
 * @brief TODO
 * check if using vars are in any symtab
 * 
 * do same for main
 * done
 * Later: handle unassigned variable warning for func arglist vars
 */
        fds=fds->next;
        if(fds==0)break;
    }
    printf("/* all function defs done */\n");
    int mainRetType;
    if(!strcmp(mb__->fnrt_->fnrettyp_,"bool"))
    {
        if(ENFORCEINTMAIN)
        {
            printf("Error: return type of main() should be integer\n");
            return 1;
        }
        else
        {
            printf("/* Warning : return type of main() should be integer in c */\n");
        }
        mainRetType=2;
    }
    else mainRetType=1;
    
/////
    struct funcTable* main_fnte = (struct funcTable*)malloc(sizeof(struct funcTable));
    if(main_fnte==0){
        printf("Error: malloc failed\n");
        return 1;
    }
    main_fnte->retTyp = mainRetType;
    main_fnte->fnName=(char *)malloc(100);
    strcpy(main_fnte->fnName,"main");
    main_fnte->argl=0;
    main_fnte->LOC_SYMTAB_HEAD=0;
    main_fnte->LOC_SYMTAB_TAIL=0;
    main_fnte->fdef=0;

    struct Ldecl_list* ldl = mb__->Lds_->Ldeclist_;
    while(ldl->Ldl_)
    {
        //////
        int VTYP=-1;
        if(!strcmp(ldl->Ldl_->typ_->type_,"int"))
            VTYP=1;
        else if(!strcmp(ldl->Ldl_->typ_->type_,"bool"))
            VTYP=2;
        struct Lid_list* lidl = ldl->Ldl_->Lidlst_;
        while (lidl->Lid_)
        {
            struct symbolTable* tempSte = newSymTabEntry(VTYP,lidl->Lid_->var_,0,0);
            //
            if(main_fnte->LOC_SYMTAB_HEAD==0)
            {
                main_fnte->LOC_SYMTAB_HEAD=tempSte;
            }
            else
            {
                main_fnte->LOC_SYMTAB_TAIL->next=tempSte;
            }
            main_fnte->LOC_SYMTAB_TAIL=tempSte;
            // main_fnte->LOC_SYMTAB_TAIL->next=0;
            main_fnte->LOC_SYMTAB_TAIL->next=GLB_SYMTAB_HEAD;     /// <<<<<<<< 
            //
            lidl=lidl->next;
            if(lidl==0)break;
        }
        //////
        ldl = ldl->next;
        if(ldl==0)
            break;
    }
    if(main_fnte->LOC_SYMTAB_HEAD==0) // if no local decls, connect to globals
    {
        main_fnte->LOC_SYMTAB_HEAD=GLB_SYMTAB_HEAD;
    }
    
    // traverse main statements
    struct stmt_list* stml = mb__->smtlst_;
    
    int ret = runStmLst(stml,main_fnte);
    if(ret == 1)
    {
        return 1;
    }
/////
    return 0;
}
////////////////////////////////

void printGid(struct Gid* gid)
{
    if(gid->type_ == 1)
    {
        printf("%s",gid->var_);
    }
    else
    {
        printGid(gid->gid_);
        printf("[%d]",gid->num_);
    }
}
void printVarExpr(struct var_expr* vexpr)
{
    if(vexpr->type == 1)
    {
        printf("%s",vexpr->var_);
    }
    else
    {
        printGid(vexpr->vrexpr_);
        printf("[");
        printExpr(vexpr->expr_);
        printf("]");
    }
}
void printExpr(struct expr* ex)
{
    if(ex->Type>=3)printf("(");
    if(ex->Type==1)
    {
        if(ex->isBool)
        {
            if(ex->value==0)printf("false");
            else printf("true");
        }
        else
        {
            printf("%d",ex->value);
        }
    }
    else if(ex->Type==2)
    {
        printVarExpr(ex->vrexpr_);
    }
    else if(ex->Type==4)
    {
        struct func_call* fncl = ex->fncl_;
        printf("%s(",fncl->var_);
        struct param_list1* prl1 = fncl->prmlst_->prmlst1;
        while (prl1)
        {
            printExpr(prl1->pra_->expr_);
            prl1=prl1->next;
            if(prl1)
                printf(", ");
        }
        
        printf(")");
    }
    else
    {
        if(ex->opType==214){
            printExpr(ex->expr_l);
        }
        else if(ex->opType==215){
            printExpr(ex->expr_l);
            printf("+");
            printExpr(ex->expr_r);
        }
        else if(ex->opType==216){
            printExpr(ex->expr_l);
            printf("-");
            printExpr(ex->expr_r);
        }
        else if(ex->opType==217){
            printExpr(ex->expr_l);
            printf("*");
            printExpr(ex->expr_r);
        }
        else if(ex->opType==218){
            printExpr(ex->expr_l);
            printf("/");
            printExpr(ex->expr_r);
        }
        else if(ex->opType==219){
            printExpr(ex->expr_l);
            printf("%%");
            printExpr(ex->expr_r);
        }
        else if(ex->opType==220){
            printExpr(ex->expr_l);
            printf("<");
            printExpr(ex->expr_r);
        }
        else if(ex->opType==221){
            printExpr(ex->expr_l);
            printf(">");
            printExpr(ex->expr_r);
        }
        else if(ex->opType==222){
            printExpr(ex->expr_l);
            printf(">=");
            printExpr(ex->expr_r);
        }
        else if(ex->opType==223){
            printExpr(ex->expr_l);
            printf("<=");
            printExpr(ex->expr_r);
        }
        else if(ex->opType==224){
            printExpr(ex->expr_l);
            printf("!=");
            printExpr(ex->expr_r);
        }
        else if(ex->opType==225){
            printExpr(ex->expr_l);
            printf("==");
            printExpr(ex->expr_r);
        }
        else if(ex->opType==226){
            printf("!");
            printExpr(ex->expr_l);
        }
        else if(ex->opType==227){
            printExpr(ex->expr_l);
            printf("&&");
            printExpr(ex->expr_r);
        }
        else if(ex->opType==228){
            printExpr(ex->expr_l);
            printf("||");
            printExpr(ex->expr_r);
        }
    }
    if(ex->Type>=3)printf(")");
}
void printeachStmnt(struct statement* stm)
{
    if (stm->type == 1)
    {
        printVarExpr(stm->as_smt_->vrexpr_);
        printf(" = ");
        printExpr(stm->as_smt_->expr_);
        printf(";\n");
    } 
    else if (stm->type == 2)
    {
        printf("scanf(\"%%d\", &");
        printVarExpr(stm->read_smt_->vrexpr_);
        printf(");\n");
    } 
    else if (stm->type == 3)
    {
        if(stm->wrt_smt_->type == 1) {
            printf("printf(\"%%d\\n\", ");
            printExpr(stm->wrt_smt_->expr_);
            printf(");\n");
        } else {
            struct str_expr* strex = stm->wrt_smt_->str_expr_;
            while (strex)
            {
                printf("printf(\"%%d \", ");
                printf("%s",strex->var_);
                printf(");\n");
                strex=strex->next;
            }
            printf("printf(\"\\n\")\n");
        }
    } 
    else if (stm->type == 4)
    {
        struct cond_stmt* cnds = stm->cnd_smt_;
        if(cnds->type == 1) {
            printf("if(");
            printExpr(cnds->expr_);
            printf(")\n{\n");
            struct stmt_list* smt = cnds->smtlst_;
            while (smt->smt_)
            {
                printeachStmnt(smt->smt_);
                smt = smt->next;
            }
            printf("}\n");
        } else if(cnds->type == 2) {
            printf("if(");
            printExpr(cnds->expr_);
            printf(")\n{\n");
            struct stmt_list* smt = cnds->smtlst_;
            while (smt->smt_)
            {
                printeachStmnt(smt->smt_);
                smt = smt->next;
            }
            printf("}\nelse\n{\n");
            smt = cnds->smtlst_else_;
            while (smt->smt_)
            {
                printeachStmnt(smt->smt_);
                smt = smt->next;
            }
            printf("}\n");
        } else if(cnds->type == 3) {
            printf("while(");
            printExpr(cnds->expr_);
            printf(")\n{\n");
            struct stmt_list* smt = cnds->smtlst_;
            while (smt->smt_)
            {
                printeachStmnt(smt->smt_);
                smt = smt->next;
            }
            printf("}\n");
        } else {
            printf("for(");

            printVarExpr(cnds->assmt1_->vrexpr_);
            printf(" = ");
            printExpr(cnds->assmt1_->expr_);
            printf(";");

            printExpr(cnds->expr_);
            printf(";");

            printVarExpr(cnds->assmt2_->vrexpr_);
            printf(" = ");
            printExpr(cnds->assmt2_->expr_);
            printf(")\n{\n");

            struct stmt_list* smt = cnds->smtlst_;
            while (smt->smt_)
            {
                printeachStmnt(smt->smt_);
                smt = smt->next;
            }
            
            printf("}\n");
        }
    } 
    else if (stm->type == 5)
    {
        struct func_call* fncl = stm->fn_smt_->fncl_;
        printf("%s (",fncl->var_);

        struct param_list1* prl1 = fncl->prmlst_->prmlst1;
        while (prl1)
        {
            printExpr(prl1->pra_->expr_);
            prl1=prl1->next;
            if(prl1)
                printf(", ");
        }
        printf(");\n");
    }
    
}
void emitCcode(struct Gdecl_sec* gds__,struct Fdef_sec* fds__,struct MainBlock* mb__,int isAbort)
{
    if(isAbort)
    {
        printf("// emit aborted as abort signal rcvd\n");
        return;
    }
    printf("/* Emitting C Code */\n");
    
    printf("#include <stdio.h>\n#include <stdbool.h>\n\n");

    /// Handle global declarations
    printf("// global declarations\n");
    struct Gdecl_list* gdl = gds__->gdl_;
    while (gdl != 0)
    {
        // printf("//start gdl\n");
        struct Gdecl* gd = gdl->gd_;
        // printf("//start gdl1\n");
        if(gd == 0)break;
        struct ret_type* rt = gd->rt_; 
        // printf("//start gdl2\n");
        struct Glist* gl = gd->gl_;
        // printf("//start gdl3\n");
        while (gl)
        {
            printf("%s ",rt->rtyp_);
            if(gl->func_)
            {
                printf("%s(",gl->func_->var_);
                if(gl->func_->argl_->argl1_)
                {
                    struct arg_list1* argl1 = gl->func_->argl_->argl1_;
                    while (argl1)
                    {
                        char* argtyp;
                        // if(argl1->arg_->argtyp_->Intargtyp_)
                        struct var_list* vrlst = argl1->arg_->varlst_;
                        while (vrlst)
                        {
                            printf("%s %s",argl1->arg_->argtyp_->argtyp_,vrlst->var_);
                            vrlst = vrlst->next;
                            if(vrlst)printf(", ");
                        }

                        argl1 = argl1->next;
                        if(argl1)printf(", ");
                    }
                    
                }
                printf(");\n");
            }
            else
            {
                struct Gid* gid = gl->gid_;
                printGid(gid);
                printf(";\n");
                
            }

            gl = gl->next;
        }
        
        gdl=gdl->next;
        if(gdl==0)break;
        // printf("//one gdl done\n");
    }
    // printf("// all global declarations done\n\n");

    printf("\n// function definitions\n");
    while (fds__!=0)
    {
        struct Fdef* fdef = fds__->fdef_;
        if(fdef==0)
            break;
        printf("%s %s(",fdef->fnrt_->fnrettyp_,fdef->fname_->var_);
        struct arg_list* argl = fdef->fargl_->argl_;
        if(argl->argl1_)
        {
            struct arg_list1* argl1 = argl->argl1_;
            while (argl1)
            {
                char* argtyp;
                // if(argl1->arg_->argtyp_->Intargtyp_)
                struct var_list* vrlst = argl1->arg_->varlst_;
                while (vrlst)
                {
                    printf("%s %s",argl1->arg_->argtyp_->argtyp_,vrlst->var_);
                    vrlst = vrlst->next;
                    if(vrlst)printf(", ");
                }

                argl1 = argl1->next;
                if(argl1)printf(", ");
            }
        }
        printf(")\n{\n");
        
        struct Ldecl_sec* lds = fdef->ldecs_;
        struct Ldecl_list* ldl = lds->Ldeclist_;
        while (ldl->Ldl_)
        {
            struct Ldecl* ldecl = ldl->Ldl_;
            struct Lid_list* lidl = ldecl->Lidlst_;
            while (lidl)
            {
                printf("%s %s;\n",ldecl->typ_->type_,lidl->Lid_->var_);
                lidl=lidl->next;
            }
            ldl = ldl->next;
        }
        printf("\n");
        
        struct stmt_list* stml = fdef->stml_;
        while (stml->smt_)
        {
            printeachStmnt(stml->smt_);
            stml = stml->next;
        }
        
        // print return stmnt
        printf("\nreturn ");
        printExpr(fdef->rets_->expr_);
        printf(";\n}\n");
        fds__=fds__->next;
    }
    // printf("// all function definitions done\n\n");
    
    printf("\n// main\n");
    // struct MainBlock* mb = mb__;
    printf("%s main()\n{\n",mb__->fnrt_->fnrettyp_);

////
    struct Ldecl_sec* lds = mb__->Lds_;
    struct Ldecl_list* ldl = lds->Ldeclist_;
    while (ldl->Ldl_)
    {
        struct Ldecl* ldecl = ldl->Ldl_;
        struct Lid_list* lidl = ldecl->Lidlst_;
        while (lidl)
        {
            printf("%s %s;\n",ldecl->typ_->type_,lidl->Lid_->var_);
            lidl=lidl->next;
        }
        ldl = ldl->next;
    }
    printf("\n");
    
    struct stmt_list* stml = mb__->smtlst_;
    while (stml->smt_)
    {
        printeachStmnt(stml->smt_);
        stml = stml->next;
    }
////
    
    // print return stmnt
    printf("\nreturn ");
    printExpr(mb__->retsmt_->expr_);
    printf(";\n}\n");
    printf("// -o0o0o0o- \n");
}

////////////////////////////////
