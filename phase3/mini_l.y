%{
#define YY_NO_UNPUT
using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <unordered_map>

int yyerror(char *s);
int yyerror(string s);
int yylex(void);
extern char * yytext;

enum Symtype { INT, INTARR };
struct Sym
{
    int val;
    string name;
    Symtype type;
};

unordered_map <string, Sym> sym_table;
void add_sym(Sym sym);

string program_name;
stringstream code;
%}

%error-verbose
%union{
  int		int_val;
  char* string_val;
}

%start Program

%token PROGRAM
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

%type<string_val> Var
%type<int_val> Expr
%type<int_val> Term

%%
Program: PROGRAM IDENT SEMICOLON {program_name = $2;}Block END_PROGRAM {}
         ;

Block: Dec SEMICOLON Dec_prime BEGIN_PROGRAM Stmt SEMICOLON Stmt_prime {}
       ;

Dec_prime: Dec SEMICOLON Dec_prime {}
      | {}
      ;

Dec: IDENT Ident_seq COLON ARRAY L_BRACKET NUMBER R_BRACKET OF INTEGER {
                                                                            Sym sym;
                                                                            sym.name = $1;
                                                                            sym.type = INTARR;
                                                                            add_sym(sym);
                                                                            code << ".[] " << $1 << ", " << $6 << endl;
                                                                       }
      | IDENT Ident_seq COLON INTEGER {
                                        Sym sym;
                                        sym.name = $1;
                                        sym.type = INT;
                                        add_sym(sym);
                                        code << ". " << $1 << endl;
                                      }
    ;

Ident_seq: COMMA IDENT {
  Sym sym;
  sym.name = $2;
  sym.type = INT;
  add_sym(sym);
  code << ". " << $2 << endl;
} Ident_seq
           |
           ;

Stmt: Var ASSIGN Expr {
  if(sym_table.find($1) == sym_table.end())
  {
    string errormsg = "Undefined variable";
    errormsg = errormsg + $1;
    yyerror(errormsg);
  }
  else
  {
    sym_table.find($1)->second.val = $3;
    code << "= " << $1 << ", " << $3 << endl;
  }
}
      | Var ASSIGN Var {
  if(sym_table.find($1) == sym_table.end())
  {
    string errormsg = "Undefined variable ";
    errormsg = errormsg + $1;
    yyerror(errormsg);
  }
  else
  {
    sym_table.find($1)->second.val = sym_table.find($3)->second.val;
    code << "= " << $1 << ", " << $3 << endl;
  }
}
      | Var ASSIGN Bool_exp QUESTION Expr COLON Expr {}
      | IF Bool_exp THEN Stmt SEMICOLON Stmt_prime Cond_tail {}
      | WHILE Bool_exp BEGINLOOP Stmt SEMICOLON Stmt_prime ENDLOOP {}
      | BEGINLOOP Stmt SEMICOLON Stmt_prime ENDLOOP WHILE Bool_exp {}
      | READ Var Var_prime {}
      | WRITE Var Var_prime {}
      | BREAK {}
      | CONTINUE {}
      | EXIT {}
      ;


Stmt_prime: Stmt SEMICOLON Stmt_prime {}
            | {}
            ;

Bool_exp: Relation_and_exp Or_seq {}
          ;

Or_seq: OR Relation_and_exp Or_seq {}
          | {}
          ;

Relation_and_exp: Relation_exp And_seq {}
                  ;

And_seq: AND Relation_exp And_seq {}
         | {}
         ;

Relation_exp: NOT Expr Comp Expr {}
              | NOT FALSE {}
              | NOT TRUE {}
              | NOT L_PAREN Bool_exp R_PAREN {}
              | Expr Comp Expr {}
              | FALSE {}
              | TRUE {}
              | L_PAREN Bool_exp R_PAREN {}
              ;

Var: IDENT {
  $$ = $1;
}
     | IDENT L_BRACKET Expr R_BRACKET {
}
     ;

Var_prime: COMMA Var Var_prime {}
           | {}
           ;

Not_prime: NOT {}
           | {}
           ;

Cond_tail: Else_if_seq {}
           | ENDIF {}
           | ELSE Stmt SEMICOLON Stmt_prime ENDIF {}
           | ELSEIF Stmt SEMICOLON Stmt_prime Else_if_seq ENDIF {}
           | ELSEIF Stmt SEMICOLON Stmt_prime Else_if_seq ELSE Stmt SEMICOLON Stmt_prime ENDIF {}
           ;

Else_if_seq: ELSEIF Stmt SEMICOLON Stmt_prime Else_if_seq {}
             | {}
             ;

Comp: EQ {}
      | NEQ {}
      | LT {}
      | GT {}
      | LTE {}
      | GTE {}
      ;

Expr: Term ADD Expr {
  $$ = $1 + $3;
  code << "+ " << $$ << ", " << $1 << ", " << $3 << endl;
}
      | Term SUB Expr {
  $$ = $1 - $3;
}
      | Term MULT Expr {
  $$ = $1 * $3;
}
      | Term DIV Expr {
  $$ = $1 / $3;
}
      | Term {
  $$ = $1;
}


Term: Var {
}
      | NUMBER {
  $$ = $1;
}
      | L_PAREN Expr R_PAREN {
  $$ = $2;
}
      | SUB Var {
  $$ = -1 * sym_table.find($2)->second.val;
}
      | SUB NUMBER {
  $$ = -1 * $2;
}
      | SUB L_PAREN Expr R_PAREN{
  $$ = -1 * ($3);
}
      ;

Neg_prime: SUB {}
           | {}
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

void add_sym(Sym sym)
{
    if(sym_table.find(sym.name) == sym_table.end())
    {
        //symbol does not exist. Insert it.
        sym_table[sym.name] = sym;

    }
    else
    {
        //symbol already exists. This is an error.
        string errormsg = "redeclaration of symbol " + sym.name;
        yyerror(errormsg);
    }
}

int main(int argc, char **argv)
{

  yyparse();

  ofstream file(program_name.c_str());
  file << code.str();
  cout << code.str();

  return 0;
}
