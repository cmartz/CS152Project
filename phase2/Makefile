

OBJS = bison.o lex.o main.o
CC = g++
CFLAGS = -g -Wall -pedantic -ll


parser: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o parser

# Lexical Analyzer
lex.o: lex.c
	$(CC) $(CFLAGS) -c lex.c -o lex.o

lex.c: mini_l.lex
	flex mini_l.lex
	mv lex.yy.c lex.c

# Parser
bison.o: bison.c
	$(CC) $(CFLAGS) -c bison.c -o bison.o

bison.c: mini_l.y
	bison -d -v --file-prefix=y mini_l.y
	mv y.tab.c bison.c

main.o:	main.cc
	$(CC) $(CFLAGS) -c main.cc -o main.o

clean:
	rm parser *.o lex.c bison.c mini_l.output mini_l.tab.h y.output y.tab.c y.tab.h
