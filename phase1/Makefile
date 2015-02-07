all: lexer

lexer: lex.yy.c
	gcc lex.yy.c -ll -o lexer

lex.yy.c: mini_l.lex
	flex mini_l.lex

clean:
	rm lexer lex.yy.c
