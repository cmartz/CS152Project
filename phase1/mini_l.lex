/* Allows use of yylineno */
%option yylineno

%{

#include <unistd.h>

/* Increment column number after every rule */
int col = 0;
#define YY_USER_ACTION { col += yyleng; }

%}

/* Reserved Words */
PROGRAM program
BEGIN_PROGRAM beginprogram
END_PROGRAM endprogram
INTEGER integer
ARRAY array
OF of
IF if
THEN then
ENDIF endif
ELSE else
ELSEIF elseif
WHILE while
DO do
BEGINLOOP beginloop
ENDLOOP endloop
BREAK break
CONTINUE continue
EXIT exit
READ read
WRITE write
AND and
OR or
NOT not
TRUE true
FALSE false

/* Arithmetic Operators */
ADD "+"
SUB "-"
MULT "*"
DIV "/"
MOD "%"

/* Comparison Operators */
EQ "=="
NEQ "<>"
LT "<"
GT ">"
LTE "<="
GTE ">="

/* Identifiers and Numbers */

DIGIT [0-9]
NUMBER {DIGIT}+
IDENTIFIER [a-zA-Z](_[a-zA-Z0-9]|[a-zA-Z0-9])*
INVALID_IDEN_START [_0-9](_[a-zA-Z0-9]|[a-zA-Z0-9])*
INVALID_IDEN_END [a-zA-Z](_[a-zA-Z0-9]|[a-zA-Z0-9])*_

/* Other Special Symbols */
SEMICOLON ";"
COLON ":"
COMMA ","
QUESTION "?"
L_BRACKET "["
R_BRACKET "]"
L_PAREN "("
R_PAREN ")"
ASSIGN ":="

/* Other */
COMMENT ##.*\n
WHITESPACE [ \t]
NEWLINE \n

%%
{PROGRAM} printf("PROGRAM\n");
{BEGIN_PROGRAM} printf("BEGIN_PROGRAM\n");
{END_PROGRAM} printf("END_PROGRAM\n");
{INTEGER} printf("INTEGER\n");
{ARRAY} printf("ARRAY\n");
{OF} printf("OF\n");
{IF} printf("IF\n");
{THEN} printf("THEN\n");
{ENDIF} printf("ENDIF\n");
{ELSE} printf("ELSE\n");
{ELSEIF} printf("ELSEIF\n");
{WHILE} printf("WHILE\n");
{DO} printf("DO\n");
{BEGINLOOP} printf("BEGINLOOP\n");
{ENDLOOP} printf("ENDLOOP\n");
{BREAK} printf("BREAK\n");
{CONTINUE} printf("CONTINUE\n");
{EXIT} printf("EXIT\n");
{READ} printf("READ\n");
{WRITE} printf("WRITE\n");
{AND} printf("AND\n");
{OR} printf("OR\n");
{NOT} printf("NOT\n");
{TRUE} printf("TRUE\n");
{FALSE} printf("FALSE\n");

{ADD} printf("ADD\n");
{SUB} printf("SUB\n");
{MULT} printf("MULT\n");
{DIV} printf("DIV\n");
{MOD} printf("MOD\n");

{EQ} printf("EQ\n");
{NEQ} printf("NEQ\n");
{LT} printf("LT\n");
{GT} printf("GT\n");
{LTE} printf("LTE\n");
{GTE} printf("GTE\n");

{NUMBER} printf("NUMBER "); ECHO; printf("\n");
{IDENTIFIER} printf("IDENT "); ECHO; printf("\n");
{INVALID_IDEN_START}  printf("Error at line %d, column %d: identifier \"", yylineno, col); ECHO; printf("\" must begin with a letter\n"); exit(1);
{INVALID_IDEN_END}  printf("Error at line %d, column %d: identifier \"", yylineno, col); ECHO; printf("\" cannot end with an underscore\n"); exit(1);


{SEMICOLON} printf("SEMICOLON\n");
{COLON} printf("COLON\n");
{COMMA} printf("COMMA\n");
{QUESTION} printf("QUESTION\n");
{L_BRACKET} printf("L_BRACKET\n");
{R_BRACKET} printf("R_BRACKET\n");
{L_PAREN} printf("L_PAREN\n");
{R_PAREN} printf("R_PAREN\n");
{ASSIGN} printf("ASSIGN\n");

{COMMENT}
{WHITESPACE}
{NEWLINE} col = 0;

. printf("Error at line %d, column %d: unrecognized symbol \"", yylineno, col); ECHO; printf("\"\n"); exit(1);
%%

main(int argc, char * argv[])
{
  // Invoke the lexer as follows: 'cat primes.min | lexer'
  yylex();
}
