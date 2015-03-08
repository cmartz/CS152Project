    %{
#define YY_NO_UNPUT
using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <string>
#include <stack>
#include <sstream>
#include <map>

int yyerror(char *s);
int yyerror(string s);
int yylex(void);
extern char * yytext;

enum Symtype { INT, INTARR };

enum Context { READING, WRITING };

struct Sym
{
    int val;
    int size; //for arrays only; -1 otherwise
    string name;
    Symtype type;
};

stack<Context> context;
string get_context();
void pop_context();

stack<string> labels;
string add_label();

stack<string> temps;
string add_temp();
map <string, Sym> sym_table;
void add_sym(Sym sym);
void verify_sym(string name);

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
%left MULT DIV MOD
%left ADD SUB


/* Comparison Operators */
%token <string_val> EQ
%token <string_val> NEQ
%token <string_val> LT
%token <string_val> GT
%token <string_val> LTE
%token <string_val> GTE

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

%type<string_val> Expr_seq
%type<string_val> Mult_expr_seq
%type<string_val> Mult_expr
%type<string_val> Expr
%type<string_val> Var
%type<string_val> Term

%type<string_val> Comp


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
  sym.size = $6;
  sym.type = INTARR;
  add_sym(sym);
}
      | IDENT Ident_seq COLON INTEGER {
  Sym sym;
  sym.name = $1;
  sym.size = -1;
  sym.type = INT;
  add_sym(sym);
}
;

Ident_seq: COMMA IDENT {
  Sym sym;
  sym.name = $2;
  sym.type = INT;
  add_sym(sym);
} Ident_seq
           |
           ;

Stmt: Var ASSIGN Expr {
  code << "= " << $1 << ", " << temps.top() << endl;
}
      | Var ASSIGN Bool_exp QUESTION Expr COLON Expr {
  string lhs_label = add_label();
  string rhs_label = add_label();
  string end_label = add_label();
  string t3 = temps.top();
  temps.pop();
  string t2 = temps.top();
  temps.pop();

  code << "?:= " << lhs_label << ", " << temps.top() << endl;
  code << ": " << rhs_label << endl;

  code << "= " << $1 << ", " << t3 << endl;
  code << ":= " << end_label << endl;
  code << ": " << lhs_label << endl;

  code << "= " << $1 << ", " << t2 << endl;
  code << ": " << end_label << endl;
}
      | IF Bool_exp THEN Stmt SEMICOLON Stmt_prime Cond_tail {}
      | WHILE Bool_exp BEGINLOOP Stmt SEMICOLON Stmt_prime ENDLOOP {}
      | BEGINLOOP Stmt SEMICOLON Stmt_prime ENDLOOP WHILE Bool_exp {}
      | READ Var Var_prime {
  verify_sym($2);
  while(!(temps.empty()))
  {
      string sym = temps.top();
      if( sym_table[sym].type == INTARR )
      {
          temps.pop();
          code << ".[]< " << sym << "," << temps.top() << endl;
      }
      else
      {
          code << ".< " << temps.top() << endl;
      }

      temps.pop();
  }
}
      | WRITE Var Var_prime {
  verify_sym($2);
  while(!(temps.empty()))
  {
      string sym = temps.top();
      if( sym_table[sym].type == INTARR )
      {
          temps.pop();
          code << ".[]> " << sym << "," << temps.top() << endl;
      }
      else
      {
          code << ".> " << temps.top() << endl;
      }

      temps.pop();
  }
}
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
          | {
}
        | {
}
          ;

Relation_and_exp: Relation_exp And_seq {}
                  ;

And_seq: AND Relation_exp And_seq {}
         | {}
         ;

Relation_exp: NOT Expr Comp Expr {
}
              | NOT FALSE {}
              | NOT TRUE {}
              | NOT L_PAREN Bool_exp R_PAREN {}
              | Expr Comp Expr {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << $2 << t1 << ", " << t3 << ", " << t2 << endl;
  //$$ = const_cast<char*>(tname.c_str());
}
              | FALSE {}
              | TRUE {}
              | L_PAREN Bool_exp R_PAREN {}
              |
              ;

Comp: EQ {
  $$ = "== ";
}
      | NEQ {
  $$ = "!= ";
}
      | LT {
  $$ = "< ";
}
      | GT {
  $$ = "> ";
}
      | LTE {
  $$ = "<= ";
}
      | GTE {
  $$ = ">= ";
}
      ;

Var: IDENT {
  $$ = $1;
  temps.push($1);
}
     | IDENT L_BRACKET Expr R_BRACKET {
  string tname = add_temp();
  $$ = const_cast<char*>(tname.c_str());
  code << "= " << tname << ", " << $1 << endl;
  temps.push($3);
  temps.push($1);
}
     ;

Var_prime: COMMA Var Var_prime {}
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

Expr: Mult_expr Expr_seq {

}
;

Expr_seq: ADD Mult_expr Expr_seq {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << "+ " << t1 << ", " << t3 << ", " << t2 << endl;
  $$ = const_cast<char*>(tname.c_str());
}
          | SUB Mult_expr Expr_seq {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << "- " << t1 << ", " << t3 << ", " << t2 << endl;
  $$ = const_cast<char*>(tname.c_str());
}
          | {

}
          ;

Mult_expr: Term Mult_expr_seq {
  $$ = $1;
}
            ;

Mult_expr_seq: MULT Term Mult_expr_seq {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << "* " << t1 << ", " << t3 << ", " << t2 << endl;
  $$ = const_cast<char*>(tname.c_str());
}
               | DIV Term Mult_expr_seq {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << "/ " << t1 << ", " << t3 << ", " << t2 << endl;
  $$ = const_cast<char*>(tname.c_str());
}
               | MOD Term Mult_expr_seq {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << "% " << t1 << ", " << t3 << ", " << t2 << endl;
  $$ = const_cast<char*>(tname.c_str());
}
               | {

}
               ;


Term: Var {
  $$ = $1;
}
      | SUB Var {
  string tname = add_temp();
  code << "= " << tname << ", " << $2 << endl;
  code << "* " << tname << ", " << tname << ", " << -1 << endl;
}
      | L_PAREN Expr R_PAREN {
  $$ = $2;
}
      | SUB L_PAREN Expr R_PAREN{
  code << "* " << $3 << ", " << $3 << ", " << -1 << endl;
}
      | NUMBER {
  string tname = add_temp();
  code << "= " << tname << ", " << $1 << endl;
  $$ = const_cast<char*>(tname.c_str());
}
      | SUB NUMBER {
  string tname = add_temp();
  code << "= " << tname << ", " << $2 << endl;
  code << "* " << tname << ", " << tname  << ", " << -1 << endl;
  $$ = const_cast<char*>(tname.c_str());
}
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


void verify_sym(string name)
{
    if(sym_table.find(name) == sym_table.end())
    {
        //Symbol does not exist. Throw error
        string errormsg = "use of undeclared symbol " + name;
        yyerror(errormsg);
    }
}

string add_temp()
{
  string vname = "t" + to_string(sym_table.size() + 1);

  Sym sym;
  sym.name = vname;
  sym.type = INT;
  add_sym(sym);
  temps.push(vname);

  return vname;
}

string add_label()
{
  string lname = "L" + to_string(labels.size() + 1);

  labels.push(lname);

  return lname;
}

void gen_variables()
{
  map<string, Sym>::iterator it;
  for(it = sym_table.begin(); it != sym_table.end(); ++it)
  {
      if(it->second.type == INTARR)
      {
          cout << ".[] " << it->second.name << "," << it->second.size << endl;
      }
      else
      {
          cout << ". " << it->second.name << endl;
      }

  }

}

string get_context()
{
    if(context.empty())
    {
       return "";
    }

    Context cntxt = context.top();

    string ret_val;

    switch(cntxt)
    {
        case READING:
        ret_val = "<";
        break;

        case WRITING:
        ret_val =  ">";
        break;

        default:
        ret_val =  "";
        break;
    }

    return ret_val;
}

void pop_context()
{
    context.pop();
}

int main(int argc, char **argv)
{

  yyparse();

  ofstream file(program_name.c_str());
  gen_variables();
  // Not yet..
  //file << code.str();
  cout << code.str();

  return 0;
}
