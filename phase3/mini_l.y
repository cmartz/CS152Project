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

void add_temp(stack<string> &temps);
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

stack<string> temps;
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
%token ADD
%left SUB
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
%type<string_val> Var_prime
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
  if(sym_table.find($1) == sym_table.end())
  {
    string errormsg = "Undefined variable";
    errormsg = errormsg + $1;
    yyerror(errormsg);
  }
  else
  {
    sym_table.find($1)->second.val = $3;
    code << "= " << $1 << ", " << temps.top() << endl;
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
  /*string cntxt = get_context();
  code << "." << cntxt << " " << $1 << endl;*/
  temps.push($1);
}
     | IDENT L_BRACKET Expr R_BRACKET {     temps.push(to_string($3));
                                            temps.push($1);
}
     | SUB IDENT {

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
  if(!temps.empty())
  {
    string rhs = temps.top();
    add_temp(temps);
    code << "+ " << temps.top() << ", " << $1 << ", " << rhs << endl;
  }
  else
  {
    add_temp(temps);
    code << "+ " << temps.top() << ", " << $1 << ", " << $3 << endl;
  }
}
      | Term SUB Expr {

  $$ = $1 - $3;
  if(!temps.empty())
  {
    string rhs = temps.top();
    add_temp(temps);
    code << "- " << temps.top() << ", " << $1 << ", " << rhs << endl;
  }
  else
  {
    add_temp(temps);
    code << "- " << temps.top() << ", " << $1 << ", " << $3 << endl;
  }
}
      | Term MULT Expr {
  $$ = $1 * $3;
}
      | Term DIV Expr {
  $$ = $1 / $3;
}
      | Term {
}
      | Var ADD Expr {
  if(!temps.empty())
  {
    string rhs = temps.top();
    add_temp(temps);
    code << "+ " << temps.top() << ", " << $1 << ", " << rhs << endl;
  }
  else
  {
    add_temp(temps);
    code << "+ " << temps.top() << ", " << $1 << ", " << $3 << endl;
  }

}
      | Var SUB Expr {
  if(!temps.empty())
  {
    string rhs = temps.top();
    add_temp(temps);
    code << "- " << temps.top() << ", " << $1 << ", " << rhs << endl;
  }
  else
  {
    add_temp(temps);
    code << "- " << temps.top() << ", " << $1 << ", " << $3 << endl;
  }
}
      | Var MULT Expr {
  if(!temps.empty())
  {
    string rhs = temps.top();
    add_temp(temps);
    code << "* " << temps.top() << ", " << $1 << ", " << rhs << endl;
  }
  else
  {
    add_temp(temps);
    code << "* " << temps.top() << ", " << $1 << ", " << $3 << endl;
  }
}
      | Var DIV Expr {
  if(!temps.empty())
  {
    string rhs = temps.top();
    add_temp(temps);
    code << "/ " << temps.top() << ", " << $1 << ", " << rhs << endl;
  }
  else
  {
    add_temp(temps);
    code << "/ " << temps.top() << ", " << $1 << ", " << $3 << endl;
  }
}
      | Var MOD Expr {
  if(!temps.empty())
  {
    string rhs = temps.top();
    add_temp(temps);
    code << "% " << temps.top() << ", " << $1 << ", " << rhs << endl;
  }
  else
  {
    add_temp(temps);
    code << "% " << temps.top() << ", " << $1 << ", " << $3 << endl;
  }
}
      | Var {
  add_temp(temps);
  code << "= " << temps.top() << ", " << $1 << endl;
}


Term: NUMBER {
  $$ = $1;
}
      | L_PAREN Expr R_PAREN {
  $$ = $2;
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

void verify_sym(string name)
{
    if(sym_table.find(name) == sym_table.end())
    {
        //Symbol does not exist. Throw error
        string errormsg = "use of undeclared symbol " + name;
        yyerror(errormsg);
    }
}

void add_temp(stack<string> &temps)
{
  string vname = "t" + to_string(temps.size() + 1);
  temps.push(vname);

  Sym sym;
  sym.name = vname;
  sym.type = INTARR;
  add_sym(sym);

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
  file << code.str();
  cout << code.str();

  return 0;
}
