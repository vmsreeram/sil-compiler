/*
 *   This file is part of SIL Compiler.
 *
 *  SIL Compiler is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SIL Compiler is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SIL Compiler.  If not, see <http://www.gnu.org/licenses/>.
 */

%{	
#include <stdio.h>
#include <stdlib.h>
#include "../include/AbsSynTree.h"
// #define YYSTYPE double
int yylex();
// void yyerror( char* );
int i;	
%}

%union {
	char* VarName;
	double Value;
	struct Prog* Prog111;
	struct Gdecl_sec* Gdecl_sec111;
	struct Gdecl_list* Gdecl_list111;
	struct Gdecl* Gdecl111;
	struct ret_type* ret_type111;
	struct Glist* Glist111;
	struct Gid* Gid111;
	struct func* func111;
	struct arg_list* arg_list111;
	struct arg_list1* arg_list1111;
	struct arg* arg111;
	struct arg_type* arg_type111;
	struct var_list* var_list111;
	struct Fdef_sec* Fdef_sec111;
	struct Fdef* Fdef111;
	struct func_ret_type* func_ret_type111;
	struct func_name* func_name111;
	struct FargList* FargList111;
	struct ret_stmt* ret_stmt111;
	struct MainBlock* MainBlock111;
	struct Main* Main111;
	struct Ldecl_sec* Ldecl_sec111;
	struct Ldecl_list* Ldecl_list111;
	struct Ldecl* Ldecl111;
	struct type* type111;
	struct Lid_list* Lid_list111;
	struct Lid* Lid111;
	struct stmt_list* stmt_list111;
	struct statement* statement111;
	struct read_stmt* read_stmt111;
	struct write_stmt* write_stmt111;
	struct assign_stmt* assign_stmt111;
	struct cond_stmt* cond_stmt111;
	struct func_stmt* func_stmt111;
	struct func_call* func_call111;
	struct param_list* param_list111;
	struct param_list1* param_list1111;
	struct para* para111;
	struct expr* expr111;
	struct str_expr* str_expr111;
	struct var_expr* var_expr111;
}
%type <Prog111> Prog
%type <Gdecl_sec111> Gdecl_sec
%type <Gdecl_list111> Gdecl_list
%type <Gdecl111> Gdecl
%type <ret_type111> ret_type
%type <Glist111> Glist
%type <Gid111> Gid
%type <func111> func
%type <arg_list111> arg_list
%type <arg_list1111> arg_list1
%type <arg111> arg
%type <arg_type111> arg_type
%type <var_list111> var_list
%type <Fdef_sec111> Fdef_sec
%type <Fdef111> Fdef
%type <func_ret_type111> func_ret_type
%type <func_name111> func_name
%type <FargList111> FargList
%type <ret_stmt111> ret_stmt
%type <MainBlock111> MainBlock
%type <Main111> main
%type <Ldecl_sec111> Ldecl_sec
%type <Ldecl_list111> Ldecl_list
%type <Ldecl111> Ldecl
%type <type111> type
%type <Lid_list111> Lid_list
%type <Lid111> Lid
%type <stmt_list111> stmt_list
%type <statement111> statement
%type <read_stmt111> read_stmt
%type <write_stmt111> write_stmt
%type <assign_stmt111> assign_stmt
%type <cond_stmt111> cond_stmt
%type <func_stmt111> func_stmt
%type <func_call111> func_call
%type <param_list111> param_list
%type <param_list1111> param_list1
%type <para111> para
%type <expr111> expr
%type <str_expr111> str_expr
%type <var_expr111> var_expr

%token <VarName> VAR
%token <Value> NUM

%token BEG END
%token T_INT T_BOOL
%token READ WRITE
%token DECL ENDDECL
// %token VAR NUM
%token IF THEN ELSE ENDIF
%token LOGICAL_AND LOGICAL_NOT LOGICAL_OR
%token EQUALEQUAL LESSTHANOREQUAL GREATERTHANOREQUAL NOTEQUAL
%token WHILE DO ENDWHILE FOR 
%token T F 
%token MAIN RETURN


%left '<' '>'
%left EQUALEQUAL LESSTHANOREQUAL GREATERTHANOREQUAL NOTEQUAL
%left '+' '-'
%left '*' '/'
%left '%'
%left LOGICAL_AND LOGICAL_OR
%left LOGICAL_NOT
%%

	Prog	:	Gdecl_sec Fdef_sec MainBlock 		{ $$ = createProg($1,$2,$3); emitCcode($1,$2,$3,runProg($1,$2,$3)); }
		;
		
	Gdecl_sec:	DECL Gdecl_list ENDDECL				{ $$ = createGdecl_sec($2);/*printf("(dlr2!=NULL) = %d\n",($2!=NULL));*/ }
		;
		
	Gdecl_list: 									{ $$ = createGdecl_list(NULL,NULL); }
		| 	Gdecl Gdecl_list						{ $$ = createGdecl_list($1,$2); }
		;
		
	Gdecl 	:	ret_type Glist ';'					{ $$ = createGdecl($1,$2); }
		;
		
	ret_type:	T_INT			{ $$ = createret_type("int"); /*todo?*/ }
		|	T_BOOL 				{ $$ = createret_type("bool");  }
		;
		
	Glist 	:	Gid				{ $$ = createGlist($1,NULL,NULL);  }
		| 	func 				{ $$ = createGlist(NULL,$1,NULL);  }
		|	Gid ',' Glist 		{ $$ = createGlist($1,NULL,$3);  }
		|	func ',' Glist		{ $$ = createGlist(NULL,$1,$3);  }
		;
	
	Gid	:	VAR					{ $$ = createGid1($1);  }
		|	Gid '[' NUM ']'		{ $$ = createGid2($1,$3);  }

		;
		
	func 	:	VAR '(' arg_list ')'	{ $$ = createfunc($1,$3);  }
		;
			
	arg_list:					{ $$ = createarg_list(NULL);  }
		|	arg_list1			{ $$ = createarg_list($1);  }
		;
		
	// arg_list1:	arg_list1 ';' arg	    { $$ = createarg_list1($3,$1);  }
	// 	|	arg							{ $$ = createarg_list1($1,NULL);  }
	// 	;
	arg_list1:	arg ';' arg_list1	    { $$ = createarg_list1($1,$3);  }
		|	arg							{ $$ = createarg_list1($1,NULL);  }
		;
		
	arg 	:	arg_type var_list		{ $$ = createarg($1,$2);  }
		;
		
	arg_type:	T_INT					{ $$ = createarg_type("int");  }
		|	T_BOOL 		 				{ $$ = createarg_type("bool");  }
		;

	var_list:	VAR 					{ $$ = createvar_list($1,NULL);  }
		|	VAR ',' var_list 			{ $$ = createvar_list($1,$3);  }
		;
		
	Fdef_sec:							{ $$ = createFdef_sec(NULL,NULL);  }
		|	Fdef_sec Fdef				{ $$ = createFdef_sec($1,$2);  }
		;
		
	Fdef	:	func_ret_type func_name '(' FargList ')' '{' Ldecl_sec BEG stmt_list ret_stmt END '}'	{ $$ = create_Fdef($1,$2,$4,$7,$9,$10);  }
		;
		
	func_ret_type:	T_INT				{ $$ = create_func_ret_type("int");  }
		|	T_BOOL						{ $$ = create_func_ret_type("bool");  }
		;
			
	func_name:	VAR						{ $$ = create_func_name($1);  }
		;
		
	FargList:	arg_list				{ $$ = create_FargList($1);  }
		;

	ret_stmt:	RETURN expr ';'			{ $$ = create_ret_stmt($2);  }
		;
			
	MainBlock: 	func_ret_type main '('')''{' Ldecl_sec BEG stmt_list ret_stmt END  '}'					{ $$ = create_MainBlock($1,$2,$6,$8,$9);  }
					  
		;
		
	main	:	MAIN					{ $$ = create_Main(1);  }
		;
		
	Ldecl_sec:	DECL Ldecl_list ENDDECL	{ $$ = create_Ldecl_sec($2);  }
		;

	Ldecl_list:							{ $$ = create_Ldecl_list(NULL,NULL);  }
		|	Ldecl Ldecl_list			{ $$ = create_Ldecl_list($1,$2);  }
		;

	Ldecl	:	type Lid_list ';'		{ $$ = create_Ldecl($1,$2);  }
		;

	type	:	T_INT					{ $$ = create_type("int");  }
		|	T_BOOL						{ $$ = create_type("bool");  }
		;

	Lid_list:	Lid						{ $$ = create_Lid_list($1,NULL);  }
		|	Lid ',' Lid_list			{ $$ = create_Lid_list($1,$3);  }
		;
		
	Lid	:	VAR							{ $$ = create_Lid($1);  }
		;

	stmt_list:	/* NULL */				{ $$ = create_stmt_list(NULL,NULL);  }
		|	statement stmt_list			{ $$ = create_stmt_list($1,$2);  }
	//	|	error ';' 					{ $$ = createGlist($1);  }
		;

	statement:	assign_stmt  ';'		{ $$ = create_statement(1,$1,NULL,NULL,NULL,NULL);  }
		|	read_stmt ';'				{ $$ = create_statement(2,NULL,$1,NULL,NULL,NULL);  }
		|	write_stmt ';'				{ $$ = create_statement(3,NULL,NULL,$1,NULL,NULL);  }
		|	cond_stmt 					{ $$ = create_statement(4,NULL,NULL,NULL,$1,NULL);  }
		|	func_stmt ';'				{ $$ = create_statement(5,NULL,NULL,NULL,NULL,$1);  }
		;

	read_stmt:	READ '(' var_expr ')' 	{ $$ = create_read_stmt($3);  }
		;

	write_stmt:	WRITE '(' expr ')' 		{ $$ = create_write_stmt(1,$3,NULL);  }
		 | WRITE '(''"' str_expr '"'')' { $$ = create_write_stmt(2,NULL,$4);  }

		;
	
	assign_stmt:	var_expr '=' expr 	{ $$ = create_assign_stmt($1,$3);  }
		;

	cond_stmt:	IF expr THEN stmt_list ENDIF 											{ $$ = create_cond_stmt(1,$2,$4,NULL,NULL,NULL);  }
		|	IF expr THEN stmt_list ELSE stmt_list ENDIF 								{ $$ = create_cond_stmt(2,$2,$4,$6,NULL,NULL);  }
		|	WHILE expr DO stmt_list ENDWHILE ';'										{ $$ = create_cond_stmt(3,$2,$4,NULL,NULL,NULL);  }
		 |    FOR '(' assign_stmt  ';'  expr ';'  assign_stmt ')' '{' stmt_list '}'     { $$ = create_cond_stmt(4,$5,$10,NULL,$3,$7);  }

		;
	
	func_stmt:	func_call 				{ $$ = create_func_stmt($1);  }
		;
		
	func_call:	VAR '(' param_list ')'	{ $$ = create_func_call($1,$3); }
		;
		
	param_list:							{ $$ = create_param_list(NULL);  }
		|	param_list1					{ $$ = create_param_list($1);  }
		;
		
	param_list1:	para				{ $$ = create_param_list1($1,NULL);  }
		|	para ',' param_list1		{ $$ = create_param_list1($1,$3);  }
		;

	para	:	expr					{ $$ = create_para($1);  }
		;

	expr	:	NUM 					{ $$ = create_expr(1,$1,NULL,0,NULL,-1,NULL,NULL ); }
		|	'-' NUM						{ $$ = create_expr(1,(-1*($2)),NULL,0,NULL,-1,NULL,NULL );  }
		|	T							{ $$ = create_expr(1,1,NULL,1,NULL,-1,NULL,NULL );  }
		|	F							{ $$ = create_expr(1,0,NULL,1,NULL,-1,NULL,NULL );  }
		
		|	var_expr					{ $$ = create_expr(2,-404,$1,0,NULL,-1,NULL,NULL );  }
		
		|	'(' expr ')'				{ $$ = create_expr(3,-404,NULL,0,$2,214,NULL,NULL );  }
		|	expr '+' expr 				{ $$ = create_expr(3,-404,NULL,0,$1,215,$3,NULL );  }
		|	expr '-' expr	 			{ $$ = create_expr(3,-404,NULL,0,$1,216,$3,NULL );  }
		|	expr '*' expr 				{ $$ = create_expr(3,-404,NULL,0,$1,217,$3,NULL );  }
		|	expr '/' expr 				{ $$ = create_expr(3,-404,NULL,0,$1,218,$3,NULL );  }
		|	expr '%' expr 				{ $$ = create_expr(3,-404,NULL,0,$1,219,$3,NULL );  }
		|	expr '<' expr				{ $$ = create_expr(3,-404,NULL,0,$1,220,$3,NULL );  }
		|	expr '>' expr				{ $$ = create_expr(3,-404,NULL,0,$1,221,$3,NULL );  }
		|	expr GREATERTHANOREQUAL expr { $$ = create_expr(3,-404,NULL,0,$1,222,$3,NULL );  }
		|	expr LESSTHANOREQUAL expr	{ $$ = create_expr(3,-404,NULL,0,$1,223,$3,NULL );  }
		|	expr NOTEQUAL expr			{ $$ = create_expr(3,-404,NULL,0,$1,224,$3,NULL );  }
		|	expr EQUALEQUAL expr		{ $$ = create_expr(3,-404,NULL,0,$1,225,$3,NULL );  }
		|	LOGICAL_NOT expr			{ $$ = create_expr(3,-404,NULL,0,$2,226,NULL,NULL );  }
		|	expr LOGICAL_AND expr		{ $$ = create_expr(3,-404,NULL,0,$1,227,$3,NULL );  }
		|	expr LOGICAL_OR expr		{ $$ = create_expr(3,-404,NULL,0,$1,228,$3,NULL );  }
		
		|	func_call					{ $$ = create_expr(4,-404,NULL,0,NULL,-1,NULL,$1 );  }

		;

	str_expr :  VAR                     { $$ = create_str_expr($1,NULL);  }
             | VAR str_expr        		{ $$ = create_str_expr($1,$2);  }
             ;
	
	var_expr:	VAR						{ $$ = create_var_expr(1,$1,NULL,NULL);  }
		|	var_expr '[' expr ']'		{ $$ = create_var_expr(2,NULL,$1,$3);  }
		;
%%
#include <stdio.h>
#include <ctype.h>
char	*progname;	/* for error messages */
extern int	Lineno = 1;

main(argc, argv)	
	char *argv[];
{
	progname = argv[0];
	yyparse();
}

yyerror(s)	/* called for yacc syntax error */
	char *s;
{
	warning(s, (char *) 0);
}

warning(s, t)	/* print warning message */
	char *s, *t;
{
	fprintf(stderr, "%s: %s", progname, s);
	if (t)
		fprintf(stderr, " %s", t);
	fprintf(stderr, " near line %d\n", Lineno);
}
