#ifndef DATA_H
#define DATA_H

/*
    DATA.H

    defines the data structures needed during compilation of a cbas program into either IR or target code.

*/


#include "targspecifics.h"
#include <stdlib.h>
#include "parser.h"



enum {
    BASE_VOID=0,
    BASE_U8=1,
    BASE_I8=2,
    BASE_U16=3,
    BASE_I16=4,
    BASE_U32=5,
    BASE_I32=6,
    BASE_U64=7,
    BASE_I64=8,
    BASE_F32=9,
    BASE_F64=10,
    BASE_STRUCT=11,
    BASE_FUNCTION=12,
    NBASETYPES=13
};

static inline uint64_t type_promote(uint64_t a, uint64_t b){

    uint64_t promoted_basetype = a;
    uint64_t weaker_basetype = b;
    if(
        (b >= BASE_STRUCT) ||
        (a >= BASE_STRUCT)
    ){
        puts("INTERNAL ERROR! Tried to promote struct or bigger!");
        exit(1);
    }
    if(b == BASE_VOID ||
    a == BASE_VOID){
        puts("INTERNAL ERROR! Tried to promote void!");
        exit(1);
    }

    if(b > a){
        promoted_basetype = b;
        weaker_basetype = a;
    }


    
    if(
        promoted_basetype == BASE_U8 ||
        promoted_basetype == BASE_U16 ||
        promoted_basetype == BASE_U32 ||
        promoted_basetype == BASE_U64
    )
        if(
            weaker_basetype == BASE_I8 ||
            weaker_basetype == BASE_I16 ||
            weaker_basetype == BASE_I32 ||
            weaker_basetype == BASE_I64 
        )
            promoted_basetype++; //become signed.
    return promoted_basetype;

}


/*the "type" struct.*/
typedef struct type{
    uint64_t basetype; /*value from the above enum. Not allowed to be BASE_FUNCTION.*/
    uint64_t pointerlevel;
    uint64_t arraylen;
    uint64_t structid; /*from the list of typedecls.*/
    uint64_t is_lvalue;
    uint64_t funcid; /*if this is a function, what is the function ID? From the list of symdecls.*/
    uint64_t is_function; /*
        is this a function? if this is set, 
        all the "normal" type information here is 
        interpreted as describing the 
        return type.
    */
    char* membername; /*used for struct members and function arguments*/
    char* user_trait_struct; /*For used-defined trait system.*/
}type;





typedef struct{
    char* name;
    struct type* members;
    uint64_t nmembers;
    uint64_t is_incomplete; /*incomplete struct declaration*/
    uint64_t is_noexport;
    uint64_t is_union;
    uint64_t algn; //alignment
    char* user_trait_struct; /*For used-defined trait system.*/
} typedecl;


//Metadata on a typedecl which tells us how it behaves in OOP land.
typedef struct typedecl_oop_metadata{
    int64_t ctor_id; //what is its ctor_id? -1 if it doesn't exist.
    int64_t dtor_id; //same thing again...
    int64_t have_checked; //have we actually checked to see if this type has type metadata?
    char* user_trait_struct; /*For used-defined trait system.*/
} typedecl_oop_metadata;
extern typedecl_oop_metadata* oop_metadata;

uint64_t push_empty_metadata();
void update_metadata(uint64_t declid);


/*Functions and Variables.*/
typedef struct{
    type t;
    char* name;
    type* fargs[MAX_FARGS]; /*function arguments*/
    uint64_t nargs; 		/*Number of arguments to function*/
    void* fbody; /*type is scope*/
    uint8_t* cdata;
    uint64_t cdata_sz;
    uint64_t is_pub;
    uint64_t is_incomplete; /*incomplete symbol, such as a predeclaration or extern.*/
    uint64_t is_codegen; /*Compiletime only?*/
    uint64_t is_impure; /*exactly what it says*/
    uint64_t is_pure;
    uint64_t is_inline;
    uint64_t is_atomic; /*only for global variables.*/
    uint64_t is_volatile; /*again, only for global variables.*/
    uint64_t is_impure_globals_or_asm; /*contains impure behavior.*/
    uint64_t is_impure_uses_incomplete_symbols; /*uses incomplete symbols.*/
    uint64_t is_data; /*only set for data.*/
    uint64_t is_noexport;
    char* user_trait_struct; /*For used-defined trait system.*/
} symdecl;

typedef struct{
    type t;
} symdecl_astexec;


static inline int sym_is_method(symdecl* s){
    if(s->t.is_function == 0) return 0;
    if(s->fargs[0] == NULL) return 0;
    if(s->fargs[0]->membername == NULL) return 0;
    if(streq(s->fargs[0]->membername, "this")){
        if(s->fargs[0]->pointerlevel == 1)
            if(s->fargs[0]->basetype == BASE_STRUCT)
                return 1;
    }
    return 0;
}


typedef struct scope{
    symdecl* syms;
    uint64_t nsyms;
    void* stmts; /**/
    uint64_t nstmts;
    uint64_t is_fbody;
    uint64_t is_loopbody;
    char* user_trait_struct; /*For used-defined trait system.*/
} scope;
typedef struct{
    symdecl_astexec* syms;
    uint64_t nsyms;
    void* stmts; /**/
    uint64_t nstmts;
} scope_astexec;

enum{
    STMT_BAD=0,
    STMT_NOP=1, /*of the form ;, also generated after every single 'end' so that a loop */
    STMT_EXPR=2,
    STMT_LABEL=3,
    STMT_GOTO=4,
    STMT_WHILE=5,
    STMT_FOR=6,
    STMT_IF=7,
    STMT_ELIF=8,
    STMT_ELSE=9,
    STMT_RETURN=10,
    STMT_TAIL=11,
    STMT_ASM=12,
    STMT_CONTINUE=13,
    STMT_BREAK=14,
    STMT_SWITCH=15,
    NSTMT_TYPES
};

#define STMT_MAX_EXPRESSIONS 3
typedef struct stmt{
    scope* whereami; /*scope this statement is in. Not owning.*/
    scope* myscope; /*if this statement has a scope after it (while, for, if, etc) then this is where it goes.*/
    uint64_t kind; /*What type of statement is it?*/
    /*expressions belonging to this statement.*/
    void* expressions[STMT_MAX_EXPRESSIONS];
    uint64_t nexpressions;
    struct stmt* referenced_loop; /*
        break and continue reference 
        a loop construct that they reside in.

        What loop exactly has to be determined in a second pass,
        since the stmt lists are continuously re-alloced.

        Goto also uses this, for its jump target.
    */
    uint64_t symid; /*for tail.*/
    char* referenced_label_name; /*goto gets a label. tail gets a function*/
    char** switch_label_list;
    uint64_t* switch_label_indices; /**/
    uint64_t switch_nlabels; /*how many labels does the switch have in it?*/
    int64_t goto_scopediff; /*how many scopes deep does this go?*/
    int64_t goto_vardiff; /*How many local variables have to be popped to achieve the context switch?*/
    int64_t goto_where_in_scope; /*What exact statement are we going to?*/
    uint64_t linenum;
    uint64_t colnum;
    char* filename;
    char* user_trait_struct; /*For used-defined trait system.*/
} stmt;
typedef struct{
    scope_astexec* whereami; /*scope this statement is in. Not owning.*/
    scope_astexec* myscope; /*if this statement has a scope after it (while, for, if, etc) then this is where it goes.*/
    uint64_t kind; /*What type of statement is it?*/
    /*expressions belonging to this statement.*/
    void* expressions[STMT_MAX_EXPRESSIONS];
    uint64_t nexpressions;
    struct stmt* referenced_loop; /*
        break and continue reference 
        a loop construct that they reside in.

        What loop exactly has to be determined in a second pass,
        since the stmt lists are continuously re-alloced.

        Goto also uses this, for its jump target.
    */
    uint64_t symid; /*for tail.*/
    char* referenced_label_name; /*goto gets a label. tail gets a function*/
    char** switch_label_list;
    uint64_t* switch_label_indices; /**/
    uint64_t switch_nlabels; /*how many labels does the switch have in it?*/
    /*Used for error printing...*/
    int64_t goto_scopediff; /*how many scopes deep does this go?*/
    int64_t goto_vardiff; /*How many local variables have to be popped to achieve the context switch?*/
    int64_t goto_where_in_scope; /*What exact statement are we going to?*/
} stmt_astexec;

enum{
    /*
        LIST OF EXPRESSION TYPES
    */
    //The slash-slash comments indicate the VM implementation status.
    //They will be removed when I am done with the VM's expression executor.
    EXPR_BAD=0,
    EXPR_BUILTIN_CALL=1, //DONE
    EXPR_FCALL=2, //DONE
    EXPR_SIZEOF=3, //DONE
    EXPR_INTLIT=4, //DONE
    EXPR_FLOATLIT=5, //DONE
    EXPR_STRINGLIT=6, //DONE (after lsym and gsym)
    EXPR_LSYM=7, //DONE
    EXPR_GSYM=8, //DONE
    EXPR_SYM=9, //E_WONTFIX
    /*unary postfix operators*/
    EXPR_POST_INCR=10, //DONE
    EXPR_POST_DECR=11, //DONE
    EXPR_INDEX=12, //DONE
    EXPR_MEMBER=13, //DONE
    EXPR_METHOD=14, //DONE
    /*unary prefix operators*/
    EXPR_CAST=15, //DONE
    EXPR_NEG=16, //DONE
    EXPR_COMPL=17, //DONE
    EXPR_NOT=18, //DONE
    EXPR_PRE_INCR=19, //DONE
    EXPR_PRE_DECR=20, //DONE
    /*binary operators starting at the bottom*/
    EXPR_MUL=21, //DONE
    EXPR_DIV=22, //DONE
    EXPR_MOD=23, //DONE
    
    EXPR_ADD=24, //DONE
    EXPR_SUB=25, //DONE
    EXPR_BITOR=26, //DONE
    EXPR_BITAND=27, //DONE
    EXPR_BITXOR=28, //DONE
    EXPR_LSH=29, //DONE
    EXPR_RSH=30, //DONE
    EXPR_LOGOR=31, //DONE
    EXPR_LOGAND=32, //DONE
    EXPR_LT=33, //DONE
    EXPR_GT=34, //DONE
    EXPR_LTE=35, //DONE
    EXPR_GTE=36, //DONE
    EXPR_EQ=37, //DONE
    EXPR_NEQ=38, //DONE
    EXPR_ASSIGN=39, //DONE
    EXPR_MOVE=40, //DONE
    EXPR_CONSTEXPR_FLOAT=41, //DONE
    EXPR_CONSTEXPR_INT=42, //DONE
    EXPR_STREQ=43, //DONE
    EXPR_STRNEQ=44, //DONE
    EXPR_MEMBERPTR=45, //DONE
    EXPR_GETFNPTR=46, //DONE
    EXPR_CALLFNPTR=47, //DONE
    EXPR_GETGLOBALPTR=48, //DONE
    NEXPR_TYPES
};

typedef struct expr_node{
    type t;
    uint64_t kind;
    double fdata;
    uint64_t idata;
    struct expr_node* subnodes[MAX_FARGS];
    uint64_t symid;
    uint64_t fnptr_nargs;
    uint64_t constint_propagator; //for propagating constant integers
    char* symname;  /*if method: this is unmangled. */
    char* method_name; /*if method: this is mangled. */
    uint64_t is_global_variable;
    uint64_t is_function;
    uint64_t is_implied;
    uint64_t was_struct_var;
    type type_to_get_size_of; //sizeof and cast both use this.
    char* user_trait_struct; /*For used-defined trait system.*/
}expr_node;

typedef struct expr_node_astexec{
    type t;
    uint64_t kind;
    double fdata;
    uint64_t idata;
    struct expr_node_astexec* subnodes[MAX_FARGS];
    uint64_t symid;
    uint64_t fnptr_nargs;
    uint64_t constint_propagator; //for propagating constant integers
    char* symname;  /*if method: this is unmangled. */
} expr_node_astexec;

static expr_node expr_node_init(){
    expr_node ee = {0};
    return ee;
}
static void expr_node_destroy(expr_node* ee){
    uint64_t i;
    for(i = 0; i < MAX_FARGS; i++){
        if(ee->subnodes[i]){
            expr_node_destroy(ee->subnodes[i]);
            free(ee->subnodes[i]);
        }
    }
    if(ee->symname)
        free(ee->symname);
    *ee = expr_node_init();
}
static stmt stmt_init(){
    stmt s = {0};
    return s;
}
static scope scope_init(){
    scope s = {0};
    return s;
}
static void scope_destroy(scope* s);
static void stmt_destroy(stmt* s){
    uint64_t i;
    for(i = 0; i < s->nexpressions; i++)
        expr_node_destroy(s->expressions[i]);
    if(s->myscope)
        scope_destroy(s->myscope);	
    /*if(s->myscope2)
        scope_destroy(s->myscope2);*/
    if(s->referenced_label_name)
        free(s->referenced_label_name);
    *s = stmt_init();
}



#define MAX_TYPE_DECLARATIONS 65536
#define MAX_SYMBOL_DECLARATIONS 65536
#define MAX_SCOPE_DEPTH 65536


extern typedecl* type_table;
extern symdecl** symbol_table;
extern uint64_t* parsehook_table;
extern scope** scopestack;
extern stmt** loopstack;
extern uint64_t active_function; //What function are we currently working in? Used to get function arguments.
extern uint64_t ntypedecls;
extern uint64_t nsymbols;
extern uint64_t nscopes;
extern uint64_t nloops; /*Needed for identifying the parent loop.*/
extern uint64_t nparsehooks;

static inline scope* scopestack_gettop(){
    return scopestack[nscopes-1];
}

static inline int peek_is_fname(){
    if(peek()->data != TOK_IDENT) return 0;
    if(nsymbols == 0) return 0;
    for(unsigned long i = 0; i < nsymbols; i++){
        if(streq(peek()->text, symbol_table[i]->name)){
            if(symbol_table[i]->t.is_function)
                return 1;
        }
    }
    return 0;
}

static inline int str_is_fname(char* s){
    for(unsigned long i = 0; i < nsymbols; i++){
        if(streq(s, symbol_table[i]->name)){
            if(symbol_table[i]->t.is_function)
                return 1;
        }
    }
    return 0;
}

static inline int ident_is_used_locally(char* s){
    for(unsigned long i = 0; i < nscopes; i++)
        for(unsigned long j = 0; j < scopestack[i]->nsyms; j++)
            if(streq(s, scopestack[i]->syms[j].name))
                return 1;
    
    for(unsigned long i = 0;i < symbol_table[active_function]->nargs;i++){
        if(streq(s, symbol_table[active_function]->fargs[i]->membername))
            return 1;
    }
    return 0;
}

static inline int ident_forbidden_declaration_check(char* s){
    for(unsigned long i = 0;i < symbol_table[active_function]->nargs;i++){
        if(streq(s, symbol_table[active_function]->fargs[i]->membername))
            return 1;
    }
    //for(unsigned long i = 0; i < nscopes; i++)
    if(nscopes == 0) 
        return 0;
    unsigned long i = nscopes - 1;
    //loop!
    for(unsigned long j = 0; j < scopestack[i]->nsyms; j++){
        if(streq(s, scopestack[i]->syms[j].name))
            return 1;
    }
    return 0;
}


/*Used during initial-pass parsing for error checking. It is insufficient to prevent duplicate labels in a function, ala:
    fn myFunc():
        :myLabel2
        if(1)
            :myLabel //I see nothing!
        end
        if(1)
            :myLabel //I see nothing as well!
        end
        while(0)
            :myLabel //Wow, there are a lot of us!
        end
    end

static inline int label_name_is_already_in_use(char* s){
    for(unsigned long i = 0; i < nscopes; i++)
        for(unsigned long j = 0; j < scopestack[i]->nstmts; j++){
            stmt* in_particular = ((stmt*)scopestack[i]->stmts) + j;
            if( in_particular->kind == STMT_LABEL)
                if( in_particular->referenced_label_name )
                    if(streq(s, in_particular->referenced_label_name)) return 1;
        }
    return 0;
}
*/

static inline void scopestack_push(scope* s){
    scopestack = realloc(scopestack, (++nscopes) * sizeof(scope*));
    scopestack[nscopes-1] = s;
}

static inline void scopestack_pop(){
    if(nscopes == 0)
        parse_error("Tried to pop scope when there was none to pop!");
    nscopes--;
}

static inline void loopstack_push(stmt* s){
    loopstack = realloc(loopstack, (++nloops) * sizeof(stmt*));
    loopstack[nloops-1] = s;
}

static inline void loopstack_pop(){
    if(nloops == 0)
        parse_error("Tried to pop loop when there was none to pop!");
    nloops--;
}


static inline int type_can_be_assigned_integer_literal(type t){
    if(t.arraylen) return 0;
    if(t.pointerlevel) return 1;
    if(t.basetype == BASE_VOID) return 0;
    if(t.basetype >= BASE_STRUCT) return 0;
    return 1;
}

static inline int type_can_be_assigned_float_literal(type t){
    if(t.arraylen) return 0;
    if(t.pointerlevel) return 1;
    if(t.basetype == BASE_VOID) return 0;
    if(t.basetype >= BASE_STRUCT) return 0;
    return 1;
}
static inline int type_should_be_assigned_float_literal(type t){
    if(t.arraylen) return 0;
    if(t.pointerlevel) return 0;
    if(t.basetype == BASE_F64 || 
        t.basetype == BASE_F32) return 1;
    return 0;
}

static inline int peek_ident_is_already_used_globally(){
    uint64_t i;
    if(peek()->data != TOK_IDENT) return 0;
    for(i = 0; i < nsymbols; i++)
        if(streq(peek()->text, symbol_table[i]->name))
            return 1;	
    if(peek_is_typename()) return 1;

    return 0;
}

static inline int ident_is_already_used_globally(char* name){
    uint64_t i;
    for(i = 0; i < nsymbols; i++)
        if(
            streq(name, 
                symbol_table[i]->name
            )
        )
            return 1;	
    for(i = 0; i < ntypedecls; i++)
        if(streq(name, type_table[i].name))
            return 1;
    return 0;
}

static inline int type_can_be_in_expression(type t){
    if(t.arraylen > 0) return 0;
    if(t.pointerlevel > 0) return 1;
    if(t.basetype >= BASE_STRUCT) return 0;
    return 1;
}


static inline int type_can_be_literal(type t){
    if(t.arraylen > 0) return 0;
    if(t.pointerlevel > 0) return 0;
    if(t.basetype >= BASE_STRUCT) return 0;
    if(t.basetype == BASE_VOID) return 0;
    return 1;
}

static inline int type_can_be_variable(type t){
    if(t.is_function) return 0; /*You may not declare a variable whose type is a function. Functions are functions, not variables!*/
    if(t.basetype == BASE_VOID && t.pointerlevel == 0) return 0; /*You may not declare a variable whose type is void.*/
    if(t.basetype == BASE_STRUCT){
        if(t.structid >= ntypedecls) /*You may not have an invalid struct ID.*/
            return 0;
    }
    if(t.basetype > BASE_STRUCT) return 0; /*invalid basetype*/
    if(t.pointerlevel > 65536) return 0; /*May not declare more than 65536 levels of indirection. Mostly as a sanity check.*/
    if(t.arraylen && t.is_lvalue) return 0; /*Arrays are never lvalues.*/
    /*Otherwise: Yes. it is valid.*/
    return 1;
}


static inline uint64_t type_getsz(type t){
    if(t.arraylen){
        type q = {0};
        q = t;
        q.arraylen = 0;
        return t.arraylen * type_getsz(q);
    }
    if(t.pointerlevel) return POINTER_SIZE;
    if(t.basetype == BASE_STRUCT){
        unsigned long sum = 0;
        if(t.structid > ntypedecls)
            parse_error("Asked to determine size of non-existent struct type?");
        /*go through the members and add up how big each one is.*/
        if(type_table[t.structid].is_union){
            unsigned long tt;
            for(unsigned long i = 0; i < type_table[t.structid].nmembers;i++){
                tt = type_getsz(type_table[t.structid].members[i]);
                if(tt > sum)
                    sum = tt;
            }
        }else {
            for(unsigned long i = 0; i < type_table[t.structid].nmembers;i++)
                sum += type_getsz(type_table[t.structid].members[i]);
        }
        return sum;
    }
    if(t.basetype == BASE_U8) return 1;
    if(t.basetype == BASE_I8) return 1;
    if(t.basetype == BASE_U16) return 2;
    if(t.basetype == BASE_I16) return 2;	
    if(t.basetype == BASE_U32) return 4;
    if(t.basetype == BASE_I32) return 4;
    if(t.basetype == BASE_F32) return 4;	
    if(t.basetype == BASE_U64) return 8;
    if(t.basetype == BASE_I64) return 8;
    if(t.basetype == BASE_F64) return 8;
    
    if(t.basetype == BASE_VOID) return 0;
    return 0;
}



static inline type type_init(){
    type t = {0};
    return t;
}
static inline void type_destroy(type* t){
    /*always free membername...*/
    if(t->membername) free(t->membername);
    *t = type_init();
}



static inline symdecl symdecl_init(){
    symdecl s = {0}; return s;
}

static inline void symdecl_destroy(symdecl* t){
    unsigned long i;
    type_destroy(&t->t);
    for(i = 0; i < MAX_FARGS; i++){
        if(t->fargs[i]){
            type_destroy(t->fargs[i]);
            free(t->fargs[i]);
            t->fargs[i] = NULL;
        }
    }
    if(t->name)free(t->name);
    if(t->fbody) scope_destroy(t->fbody);
    if(t->cdata) free(t->cdata);
    *t = symdecl_init();
}

static inline typedecl typedecl_init(){
    typedecl s = {0}; return s;
}

/*Type declarations */
static inline void typedecl_destroy(typedecl* t){
    /*Type declarations own BOTH fargs and members.*/
    if(t->members){
        for(size_t i = 0; i < t->nmembers; i++)
            type_destroy(t->members + i);
        free(t->members);
    }
    if(t->name)free(t->name);
    *t = typedecl_init();
}




static void scope_destroy(scope* s){
    if(s->syms){
        for(unsigned long i = 0; i < s->nsyms; i++)
            symdecl_destroy(&s->syms[i]);
        free(s->syms);
    }
    for(unsigned long i = 0; i < s->nstmts; i++)
        stmt_destroy(s->stmts+i);
    *s = scope_init();
    return;
}


static inline int peek_match_keyw(char* s){
    if(peek() == NULL) return 0;
    if(peek()->data != TOK_KEYWORD) return 0;
    return (ID_KEYW(peek()) == ID_KEYW_STRING(s));
}

static inline int strll_match_keyw(strll* i, char* s){
    if(i->data != TOK_KEYWORD) return 0;
    return (ID_KEYW(i) == ID_KEYW_STRING(s));
}


type parse_type();

//for using uptr...
void set_is_codegen(int);
int get_is_codegen();
void print_manpage(char* subject);


#endif
