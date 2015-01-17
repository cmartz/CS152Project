all: lexer

lexer: lex.yy.c
	gcc lex.yy.c -ll -o lexer

lex.yy.c: lexer.lex
	flex lexer.lex

clean:
	rm lexer lex.yy.c
