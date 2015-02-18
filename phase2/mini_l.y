%{
#define YY_NO_UNPUT
using namespace std;
#include <iostream>
#include <stdio.h>
#include <string>
int yyerror(char *s);
int yylex(void);
extern char * yytext;
%}

%union{
  int		int_val;
  char* string_val;
}

%start Program

%token <string> PROGRAM
%token BEGIN_PROGRAM
%token END_PROGRAM
%token <int_val> INTEGER
%token ARRAY
%token OF
%token IF
%token THEN
%token ENDIF
%token ELSE
%token ELSEIF
%token WHILE
%token DO
%token BEGINLOOP
%token ENDLOOP
%token BREAK
%token CONTINUE
%token EXIT
%token READ
%token WRITE
%token AND
%token OR
%token NOT
%token TRUE
%token FALSE

/* Arithmetic Operators */
%token ADD
%token SUB
%token MULT
%token DIV
%token MOD

/* Comparison Operators */
%token EQ
%token NEQ
%token LT
%token GT
%token LTE
%token GTE

/* Identifiers and Numbers */

%token <int_val> NUMBER
%token <string_val> IDENT

/* Other Special Symbols */
%token SEMICOLON
%token COLON
%token COMMA
%token QUESTION
%token L_BRACKET
%token R_BRACKET
%token L_PAREN
%token R_PAREN
%token ASSIGN


%%
Program: PROGRAM IDENT SEMICOLON Block END_PROGRAM {printf("program -> PROGRAM IDENT SEMICOLON Block END_PROGRAM\n");}
         ;

Block: Dec SEMICOLON Dec_prime BEGIN_PROGRAM Stmt SEMICOLON Stmt_prime {printf("Block -> Dec SEMICOLON Dec_prime BEGIN_PROGRAM Stmt SEMICOLON Stmt_prime\n");}
       ;

Dec_prime: Dec SEMICOLON Dec_prime {printf("Dec_prime -> Dec SEMICOLON Dec_prime\n"); }
      | {printf("Dec_prime -> e\n");}
      ;

Dec: IDENT Ident_seq COLON ARRAY L_BRACKET NUMBER R_BRACKET OF INTEGER {printf("Dec -> IDENT Ident_seq COLON ARRAY L_BRACKET NUMBER R_BRACKET OF INTEGER\n");}
      | IDENT Ident_seq COLON INTEGER {printf("Dec -> IDENT Ident_seq COLON INTEGER\n");}
      ;

Ident_seq: COMMA IDENT Ident_seq {printf("Ident_seq -> COMMA IDENT Ident_seq\n");}
           | {printf("Ident_seq -> e\n");}
           ;

Stmt: Var ASSIGN Expr {printf("Stmt -> Var ASSIGN Expr\n");}
      | Var ASSIGN Bool_exp QUESTION Expr COLON Expr {printf("Stmt -> Var ASSIGN Bool_exp QUESTION Expr COLON Expr\n");}
      | IF Bool_exp THEN Stmt SEMICOLON Stmt_prime Cond_tail {printf("Stmt -> Var ASSIGN Expr\n");}
      | WHILE Bool_exp BEGINLOOP Stmt SEMICOLON Stmt_prime ENDLOOP {printf("Stmt -> WHILE Bool_exp BEGINLOOP Stmt SEMICOLON Stmt_prime ENDLOOP\n");}
      | BEGINLOOP Stmt SEMICOLON Stmt_prime ENDLOOP WHILE Bool_exp {printf("Stmt -> BEGINLOOP Stmt SEMICOLON Stmt_prime ENDLOOP WHILE Bool_expr\n");}
      | READ Var Var_prime {printf("Stmt -> READ Var Var_prime\n");}
      | WRITE Var Var_prime {printf("Stmt -> WRITE Var Var_prime\n");}
      | BREAK {printf("Stmt -> BREAK\n");}
      | CONTINUE {printf("Stmt -> CONTINUE\n");}
      | EXIT {printf("Stmt -> EXIT\n");}
      ;


Stmt_prime: Stmt SEMICOLON Stmt_prime {printf("Stmt_prime -> Stmt SEMICOLON Stmt_prime\n");}
            | {printf("Stmt_prime -> e\n");}
            ;

Bool_exp: Relation_and_exp {printf("Bool_exp -> Relation_and_exp\n");}
          | Relation_and_exp OR Relation_and_exp {printf("Bool_exp -> Relation_and_exp OR Relation_and_exp\n");}
          ;

Relation_and_exp: Relation_exp {printf("Relation_and_exp -> Relation_exp\n");}
                  | Relation_exp AND Relation_exp {printf("Relation_and_exp -> Relation_exp AND Relation_exp\n");}
                  ;

Relation_exp: NOT Expr Comp Expr {printf("Relation_exp -> Expr Comp Expr\n");}
              | NOT FALSE {printf("Relation_exp -> NOT FALSE\n");}
              | NOT TRUE {printf("Relation_exp -> NOT TRUE\n");}
              | NOT L_PAREN Bool_exp R_PAREN {printf("Relation_exp -> NOT L_PAREN Bool_exp R_PAREN\n");}
              | Expr Comp Expr {printf("Relation_exp -> Expr Comp Expr\n");}
              | FALSE {printf("Relation_exp -> FALSE\n");}
              | TRUE {printf("Relation_exp -> TRUE\n");}
              | L_PAREN Bool_exp R_PAREN {printf("Relation_exp -> L_PAREN Bool_exp R_PAREN\n");}
              ;

Var: IDENT {printf("Var -> IDENT\n");}
     | IDENT L_BRACKET Expr R_BRACKET {printf("Var -> IDENT L_BRACKET Expr R_BRACKET\n");}
     ;

Var_prime: COMMA Var Var_prime {printf("Var_prime -> COMMA Var Var_prime\n");}
           | {printf("Var_prime -> e\n")};
           ;

Not_prime: NOT {printf("Not_prime -> NOT\n");}
           | {printf("Not_prime -> e\n");}
           ;

Cond_tail: Else_if_seq {printf("Cond_tail -> Else_if_seq\n");}
           | ENDIF {printf("Cond_tail -> ENDIF\n");}
           | ELSE Stmt SEMICOLON Stmt_prime ENDIF {printf("Cond_tail -> ELSE Stmt SEMICOLON Stmt_prime ENDIF\n");}
           | ELSEIF Stmt SEMICOLON Stmt_prime Else_if_seq ENDIF {printf("Cond_tail -> ELSEIF Stmt SEMICOLON Stmt_prime Else_if_seq ENDIF\n");}
           | ELSEIF Stmt SEMICOLON Stmt_prime Else_if_seq ELSE Stmt SEMICOLON Stmt_prime ENDIF {printf("Cond_tail -> ELSEIF Stmt SEMICOLON Stmt_prime Else_if_seq ELSE Stmt SEMICOLON Stmt_prime ENDIF\n");}
           ;

Else_if_seq: ELSEIF Stmt SEMICOLON Stmt_prime Else_if_seq {printf("Else_if_seq\n");}
             | {printf("Else_if_seq -> e\n");}
             ;

Comp: EQ {printf("Comp -> EQ\n");}
      | NEQ {printf("Comp -> NEQ\n");}
      | LT {printf("Comp -> LT\n");}
      | GT {printf("Comp -> GT\n");}
      | LTE {printf("Comp -> LTE\n");}
      | GTE {printf("Comp -> GTE\n");}
      ;

Expr: Mult_expr Expr_seq {printf("Expr -> Mult_expr Expr_seq\n");}
      ;

Expr_seq: ADD Mult_expr Expr_seq {printf("Expr_seq -> ADD Mult_expr Expr_seq\n");}
          | SUB Mult_expr Expr_seq {printf("Expr_seq -> SUB Mult_expr Expr_seq\n");}
          | {printf("Expr_seq -> e\n");}
          ;

Mult_expr: Term Mult_expr_seq {printf("Mult_expr -> Term Mult_expr_seq\n");}
            ;

Mult_expr_seq: MULT Term Mult_expr_seq {printf("Mult_expr->seq -> MULT Term Mult_expr_seq\n");}
               | DIV Term Mult_expr_seq {printf("Mult_expr->seq -> DIV Term Mult_expr_seq\n");}
               | MOD Term Mult_expr_seq {printf("Mult_expr->seq -> MOD Term Mult_expr_seq\n");}
               | {printf("Mult_expr_seq -> e\n");}
               ;

Term: Var {printf("Term -> Var\n");}
      | NUMBER {printf("Term -> NUMBER\n");}
      | L_PAREN Expr R_PAREN {printf("Term -> L_PAREN Expr R_PAREN\n");}
      | SUB Var {printf("Term -> SUB Var\n");}
      | SUB NUMBER {printf("Term -> SUB NUMBER\n");}
      | SUB L_PAREN Expr R_PAREN{printf("Term -> SUB L_PAREN Expr R_PAREN\n");}
      ;

Neg_prime: SUB {printf("Neg_prime -> SUB\n");}
           | {printf("Neg_prime -> e\n");}
           ;

%%
int yyerror(string s)
{
  extern int yylineno;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c
  cerr << "ERROR: " << s << " at symbol \"" << yytext;
  cerr << "\" on line " << yylineno << endl;
  exit(1);
}
int yyerror(char *s)
{
  return yyerror(string(s));
}
