/* Allows use of yylineno */
%option yylineno
%option noyywrap

%{
#include <unistd.h>
#include "y.tab.h"
#include <string.h>
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
{PROGRAM} {return PROGRAM;}
{BEGIN_PROGRAM} return BEGIN_PROGRAM;
{END_PROGRAM} return END_PROGRAM;
{INTEGER} return INTEGER;
{ARRAY} return ARRAY;
{OF} return OF;
{IF} return IF;
{THEN} return THEN;
{ENDIF} return ENDIF;
{ELSE} return ELSE;
{ELSEIF} return ELSEIF;
{WHILE} return WHILE;
{DO} return DO;
{BEGINLOOP} return BEGINLOOP;
{ENDLOOP} return ENDLOOP;
{BREAK} return BREAK;
{CONTINUE} return CONTINUE;
{EXIT} return EXIT;
{READ} return READ;
{WRITE} return WRITE;
{AND} return AND;
{OR} return OR;
{NOT} return NOT;
{TRUE} return TRUE;
{FALSE} return FALSE;

{ADD} return ADD;
{SUB} return SUB;
{MULT} return MULT;
{DIV} return DIV;
{MOD} return MOD;

{EQ} return EQ;
{NEQ} return NEQ;
{LT} return LT;
{GT} return GT;
{LTE} return LTE;
{GTE} return GTE;

{NUMBER} yylval.int_val = atoi(yytext);return NUMBER;
{IDENTIFIER} yylval.string_val = strdup(yytext); return IDENT;
{INVALID_IDEN_START}  printf("Error at line %d, column %d: identifier \"", yylineno, col); ECHO; printf("\" must begin with a letter\n"); exit(1);
{INVALID_IDEN_END}  printf("Error at line %d, column %d: identifier \"", yylineno, col); ECHO; printf("\" cannot end with an underscore\n"); exit(1);


{SEMICOLON} return SEMICOLON;
{COLON} return COLON;
{COMMA} return COMMA;
{QUESTION} return QUESTION;
{L_BRACKET} return L_BRACKET;
{R_BRACKET} return R_BRACKET;
{L_PAREN} return L_PAREN;
{R_PAREN} return R_PAREN;
{ASSIGN} return ASSIGN;

{COMMENT}
{WHITESPACE}
{NEWLINE} col = 0;

. printf("Error at line %d, column %d: unrecognized symbol \"", yylineno, col); ECHO; printf("\"\n"); exit(1);
%%
