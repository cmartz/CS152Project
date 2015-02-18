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
Program: PROGRAM IDENT SEMICOLON Block END_PROGRAM {printf("program -> %s\n", yytext);}
         ;

Block: Dec SEMICOLON Dec_prime BEGIN_PROGRAM Stmt SEMICOLON Stmt_prime
       ;

Dec_prime: Dec SEMICOLON Dec_prime
      |
      ;

Dec: IDENT Ident_seq COLON ARRAY L_BRACKET NUMBER R_BRACKET OF INTEGER
      | IDENT Ident_seq COLON INTEGER
      ;

Ident_seq: COMMA IDENT Ident_seq
           |
           ;

Stmt: Var ASSIGN Expr {printf("Stmt -> %s\n", yytext);}
      | Var ASSIGN Bool_exp QUESTION Expr COLON Expr
      | IF Bool_exp THEN Stmt SEMICOLON Stmt_prime Cond_tail
      | WHILE Bool_exp BEGINLOOP Stmt SEMICOLON Stmt_prime ENDLOOP
      | BEGINLOOP Stmt SEMICOLON Stmt_prime ENDLOOP WHILE Bool_exp
      | READ Var Var_prime
      | WRITE Var Var_prime
      | BREAK
      | CONTINUE
      | EXIT
      ;


Stmt_prime: Stmt SEMICOLON Stmt_prime
            |
            ;

Bool_exp: Relation_and_exp
          | Relation_and_exp OR Relation_and_exp
          ;

Relation_and_exp: Relation_exp
                  | Relation_exp AND Relation_exp
                  ;

Relation_exp: NOT Expr Comp Expr
              | NOT FALSE
              | NOT TRUE
              | NOT L_PAREN Bool_exp R_PAREN
              | Expr Comp Expr
              | FALSE
              | TRUE
              | L_PAREN Bool_exp R_PAREN
              ;

Var: IDENT
     | IDENT L_BRACKET Expr R_BRACKET
     ;

Var_prime: COMMA Var Var_prime
           |
           ;

Not_prime: NOT
           |
           ;

Cond_tail: Else_if_seq
           | ENDIF
           | ELSE Stmt SEMICOLON Stmt_prime ENDIF
           | ELSEIF Stmt SEMICOLON Stmt_prime Else_if_seq ENDIF
           | ELSEIF Stmt SEMICOLON Stmt_prime Else_if_seq ELSE Stmt SEMICOLON Stmt_prime ENDIF
           ;

Else_if_seq: ELSEIF Stmt SEMICOLON Stmt_prime Else_if_seq
             |
             ;

Comp: EQ
      | NEQ
      | LT
      | GT
      | LTE
      | GTE
      ;

Expr: Mult_expr Expr_seq
      ;

Expr_seq: ADD Mult_expr Expr_seq
          | SUB Mult_expr Expr_seq
          |
          ;

Mult_expr: Term Mult_expr_seq
            ;

Mult_expr_seq: MULT Term Mult_expr_seq
               | DIV Term Mult_expr_seq
               | MOD Term Mult_expr_seq
               |
               ;

Term: Var
      | NUMBER
      | L_PAREN Expr R_PAREN
      | SUB Var
      | SUB NUMBER
      | SUB L_PAREN Expr R_PAREN
      ;

Neg_prime: SUB
           |
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
