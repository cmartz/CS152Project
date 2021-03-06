    %{
#define YY_NO_UNPUT
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <string>
#include <stack>
#include <sstream>
#include <map>
using namespace std;

int yyerror(char *s);
int yyerror(string s);
extern int yylex(void);
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

string add_label();
string add_while_label();
string add_if_label();
string add_temp();
void add_sym(Sym sym);
void verify_sym(string name);

map <string, Sym> sym_table;
stack<Context> context;
stack<string> temps;
stack<string> labels;
int while_labels_size;
stack<string> while_labels;
stack<string> if_labels;

string program_name;
stringstream output;
stringstream code;
stringstream vars;
vector<string> errors;
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
Program: PROGRAM IDENT SEMICOLON {program_name = $2;}Block END_PROGRAM {
  code << ": " << "EndLabel" << endl;
}
         ;

Block: Dec SEMICOLON Dec_prime BEGIN_PROGRAM Stmt SEMICOLON Stmt_prime {}
       ;

Dec_prime: Dec SEMICOLON Dec_prime {}
      | {}
      ;

Dec: IDENT Ident_seq COLON ARRAY L_BRACKET NUMBER R_BRACKET OF INTEGER {
  if($1 == program_name)
  {
    string error = "Variable cannot have same name as program";
    yyerror(error);
  }
  else if($6 <= 0)
  {
    string error = "Array size must be >= 0";
    yyerror(error);
  }
  Sym sym;
  sym.name = $1;
  sym.size = $6;
  sym.type = INTARR;
  add_sym(sym);
}
      | IDENT Ident_seq COLON INTEGER {
  if($1 == program_name)
  {
    string error = "Variable cannot have same name as program";
    yyerror(error);
  }
  Sym sym;
  sym.name = $1;
  sym.size = -1;
  sym.type = INT;
  add_sym(sym);
}
;

Ident_seq: COMMA IDENT {
  if($2 == program_name)
  {
    string error = "Variable cannot have same name as program";
    yyerror(error);
  }
  Sym sym;
  sym.name = $2;
  sym.type = INT;
  add_sym(sym);
} Ident_seq
           |
           ;

Stmt: Var ASSIGN Expr{
  if(sym_table[$1].type == INTARR)
  {
    string source = temps.top();
    temps.pop();
    temps.pop();

    if(sym_table[$3].type == INTARR)
       temps.pop();

    string index = temps.top();
    code << "[]= " << $1 << ", " << index << ", " << source << endl;
  }
  else
  {
    if(sym_table[$3].type == INTARR)
    {
      string source = temps.top();
      code << "= " << $1 << ", " << source << endl;
    }
    else
    {
      code << "= " << $1 << ", " << temps.top() << endl;
    }
  }
}
      | Var ASSIGN Bool_exp QUESTION Expr COLON Expr {

  string lhs_label = add_label();
  string rhs_label = add_label();
  string end_label = add_label();
  string t3 = temps.top();
  temps.pop();
  string t2 = temps.top();
  temps.pop();
  if(sym_table[$1].type == INTARR)
  {

    code << "?:= " << lhs_label << ", " << temps.top() << endl;
    code << ": " << rhs_label << endl;
    temps.pop();
    temps.pop();
    string index = temps.top();
    code << "[]= " << $1 << ", " << index << ", " << t3 << endl;
    code << ":= " << end_label << endl;
    code << ": " << lhs_label << endl;

    code << "[]= " << $1 << ", " << index << ", " << t2 << endl;
    code << ": " << end_label << endl;
  }
  else
  {
    code << "?:= " << lhs_label << ", " << temps.top() << endl;
    code << ": " << rhs_label << endl;

    code << "= " << $1 << ", " << t3 << endl;
    code << ":= " << end_label << endl;
    code << ": " << lhs_label << endl;

    code << "= " << $1 << ", " << t2 << endl;
    code << ": " << end_label << endl;
  }
}
      | IF Bool_exp {
  string end_label = add_if_label();
  string next_cond_label = add_if_label();
  string cond = temps.top();
  string neg_cond = add_temp();
  code << "! " << neg_cond << ", " << cond << endl;
  code << "?:= " << next_cond_label << ", " << neg_cond << endl;
} THEN Stmt SEMICOLON Stmt_prime {
  string next_cond_label = if_labels.top();
  if_labels.pop();
  string end_label = if_labels.top();
  code << ":= " << end_label << endl;
  code << ": " << next_cond_label << endl;
}Cond_tail {
    string end_label = if_labels.top();
    if_labels.pop();
    code << ": " << end_label << endl;
}

      | WHILE {
  string begin_label = add_while_label();
  code << ": " << begin_label << endl;

}Bool_exp {
  string end_label = add_while_label();
  string cond = temps.top();
  string neg_cond = add_temp();
  code << "! " << neg_cond << ", " << cond << endl;
  code << "?:= " << end_label << ", " << neg_cond << endl;

}BEGINLOOP Stmt SEMICOLON Stmt_prime ENDLOOP {
  string end_label = while_labels.top();
  while_labels.pop();
  string begin_label = while_labels.top();
  while_labels.pop();

  code << ":= " << begin_label << endl;
  code << ": " << end_label << endl;
}

      | DO BEGINLOOP {
  string begin_label = add_while_label();
  string end_label = add_while_label();
  code << ": " << begin_label << endl;

}Stmt SEMICOLON Stmt_prime ENDLOOP WHILE Bool_exp {
  string end_label = while_labels.top();
  while_labels.pop();
  string begin_label = while_labels.top();
  while_labels.pop();
  code << "?:= " << begin_label << ", " << temps.top() << endl;
  code << ": " << end_label << endl;
}
      | READ Var {
  if(sym_table[$2].type == INTARR)
  {
    //string dst = temps.top();
    temps.pop();
    string expr = temps.top();
    code << ".[]< " << $2 << ", " << expr << endl;
  }
  else
  {
    code << ".< " << temps.top() << endl;
  }
}Read_var_prime

      | WRITE Var{
  if(sym_table[$2].type == INTARR)
  {
    //string dst = temps.top();
    temps.pop();
    string expr = temps.top();
    code << ".[]> " << $2 << ", " << expr << endl;
  }
  else
  {
    code << ".> " << temps.top() << endl;
  }
}Write_var_prime

      | BREAK {
  // break statement found outside of while loop
  if(while_labels.size() == 0)
  {
    yyerror("break statement not within a loop");
  }
  else
  {
    string end_label = while_labels.top();
    code << ":= " << end_label << endl;
  }
}
      | CONTINUE {
  // continue statement found outside of while loop
  if(while_labels.size() == 0)
  {
    yyerror("continue statement not within a loop");
  }
  else
  {
    string end_label = while_labels.top();
    while_labels.pop();
    string begin_label = while_labels.top();
    while_labels.push(end_label);

    code << ":= " << begin_label << endl;
  }
}
      | EXIT {
  code << ":= " << "EndLabel" << endl;
}
      ;

Read_var_prime: COMMA Var {
  if(sym_table[$2].type == INTARR)
  {
    //string dst = temps.top();
    temps.pop();
    string expr = temps.top();
    code << ".[]< " << $2 << ", " << expr << endl;
  }
  else
  {
    code << ".< " << temps.top() << endl;
  }
}Read_var_prime
           | {}
           ;

Write_var_prime: COMMA Var{
  if(sym_table[$2].type == INTARR)
  {
    //string dst = temps.top();
    temps.pop();
    string expr = temps.top();
    code << ".[]> " << $2 << ", " << expr << endl;
  }
  else
  {
    code << ".> " << temps.top() << endl;
  }
}Write_var_prime
           | {}
           ;

Stmt_prime: Stmt SEMICOLON Stmt_prime {}
            | {}
            ;

Bool_exp: Relation_and_exp Or_seq {} //TODO
          ;

Or_seq: OR Relation_and_exp Or_seq {
    string t2 = temps.top();
    temps.pop();
    string t3 = temps.top();
    temps.pop();
    string tname = add_temp();
    string t1 = temps.top();
    code << "|| " << t1 << ", " << t3 << ", " << t2 << endl;
}//TODO
          | {}
          ;

Relation_and_exp: Relation_exp And_seq {}//TODO
                  ;

And_seq: AND Relation_exp And_seq {
    string t2 = temps.top();
    temps.pop();
    string t3 = temps.top();
    temps.pop();
    string tname = add_temp();
    string t1 = temps.top();
    code << "&& " << t1 << ", " << t3 << ", " << t2 << endl;
}
         | {}
         ;

Relation_exp: NOT Expr Comp Expr {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << $3 << t1 << ", " << t3 << ", " << t2 << endl;
  code << "! " << t1 << ", " << t1 << endl;
}
              | NOT FALSE {
  string tname = add_temp();
  code << "= " << tname << ", " << 1 << endl;
}
              | NOT TRUE {
  string tname = add_temp();
  code << "= " << tname << ", " << 0 << endl;
}
              | NOT L_PAREN Bool_exp R_PAREN {
                  string t1 = temps.top();
                  code << "! " << t1 << ", " << t1 << endl;
}
              | Expr Comp Expr {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << $2 << t1 << ", " << t3 << ", " << t2 << endl;
}
              | FALSE {
  string tname = add_temp();
  code << "= " << tname << ", " << 0 << endl;
}
              | TRUE {
  string tname = add_temp();
  code << "= " << tname << ", " << 1 << endl;
}
              | L_PAREN Bool_exp R_PAREN {

}
              ;

Comp: EQ {
  $$ = (char *)"== ";
}
      | NEQ {
  $$ = (char *)"!= ";
}
      | LT {
  $$ = (char *)"< ";
}
      | GT {
  $$ = (char *)"> ";
}
      | LTE {
  $$ = (char *)"<= ";
}
      | GTE {
  $$ = (char *)">= ";
}
      ;

Var: IDENT {
  verify_sym($1);
  if(sym_table[$1].type == INTARR)
  {
    yyerror("Cannot access array as scalar variable. Must use index");
  }
  $$ = $1;
  temps.push($1);
}
     | IDENT L_BRACKET Expr R_BRACKET {
  verify_sym($1);
  if(sym_table[$1].type != INTARR)
  {
    yyerror("Cannot access scalar variable as array.");
  }
  else
  {
    sym_table[$1].type = INTARR;
    $$ = const_cast<char*>($1);
    string index = temps.top();
    string tname = add_temp();
    code << "=[] " << tname << ", " << $1 << ", " << index << endl;
    //temps.push($1);
  }
}

Cond_tail: ELSE Stmt SEMICOLON Stmt_prime ENDIF {}
           | Else_if Else_if_prime ENDIF {}
           | Else_if Else_if_prime ELSE Stmt SEMICOLON Stmt_prime ENDIF {}
           | ENDIF
           ;

Else_if: ELSEIF Bool_exp {
  string next_cond_label = add_if_label();
  string cond = temps.top();
  string neg_cond = add_temp();
  code << "! " << neg_cond << ", " << cond << endl;
  code << "?:= " << next_cond_label << ", " << neg_cond << endl;
} Stmt SEMICOLON Stmt_prime {
  string next_cond_label = if_labels.top();
  if_labels.pop();
  string end_label = if_labels.top();
  code << ":= " << end_label << endl;
  code << ": " << next_cond_label << endl;
}
              ;

Else_if_prime: Else_if Else_if_prime |
                                     {};

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
}
          | SUB Mult_expr Expr_seq {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << "- " << t1 << ", " << t3 << ", " << t2 << endl;
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
}
               | DIV Term Mult_expr_seq {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << "/ " << t1 << ", " << t3 << ", " << t2 << endl;
}
               | MOD Term Mult_expr_seq {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << "% " << t1 << ", " << t3 << ", " << t2 << endl;
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
  stringstream error;
  error << "ERROR: " << s << " at symbol \"" << yytext;
  error << "\" on line " << yylineno << endl;
  errors.push_back(error.str());
  return 1;
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
  stringstream ss;
  ss << sym_table.size() + 1;
  string vname = "t" + ss.str();
  Sym sym;
  sym.name = vname;
  sym.type = INT;
  add_sym(sym);
  temps.push(vname);

  return vname;
}

string add_label()
{
  static int id = 0;
  stringstream ss;
  ss << ++id;
  string lname = "L" + ss.str();
  labels.push(lname);
  return lname;
}

string add_while_label()
{
  stringstream ss;
  ss << ++while_labels_size;
  string lname = "WL" + ss.str();
  while_labels.push(lname);
  return lname;
}

string add_if_label()
{
    static int id = 0;
    stringstream ss;
    ss << ++id;
    string lname = "IL" + ss.str();
    if_labels.push(lname);
    return lname;
}

void gen_variables()
{
  map<string, Sym>::iterator it;
  for(it = sym_table.begin(); it != sym_table.end(); ++it)
  {
      if(it->second.type == INTARR)
      {
          vars << ".[] " << it->second.name << "," << it->second.size << endl;
      }
      else
      {
          vars << ". " << it->second.name << endl;
      }

  }
  output << vars.str();
  //cout << vars.str();
}

int main(int argc, char **argv)
{

  yyparse();
  if(errors.size() != 0)
  {
    for(int i = 0; i < errors.size(); ++i)
    {
      printf("%s", errors[i].c_str());
    }
    exit(1);
  }
  else
  {
    cout << "Compilation successful!" << endl;
    gen_variables();
    output << code.str();
    //cout << code.str();
    ofstream FILE((program_name + ".mil").c_str());
    FILE << output.rdbuf();
  }
  return 0;
}
