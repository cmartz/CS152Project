/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROGRAM = 258,
     BEGIN_PROGRAM = 259,
     END_PROGRAM = 260,
     INTEGER = 261,
     ARRAY = 262,
     OF = 263,
     IF = 264,
     THEN = 265,
     ENDIF = 266,
     ELSE = 267,
     ELSEIF = 268,
     WHILE = 269,
     DO = 270,
     BEGINLOOP = 271,
     ENDLOOP = 272,
     BREAK = 273,
     CONTINUE = 274,
     EXIT = 275,
     READ = 276,
     WRITE = 277,
     AND = 278,
     OR = 279,
     NOT = 280,
     TRUE = 281,
     FALSE = 282,
     MOD = 283,
     DIV = 284,
     MULT = 285,
     SUB = 286,
     ADD = 287,
     EQ = 288,
     NEQ = 289,
     LT = 290,
     GT = 291,
     LTE = 292,
     GTE = 293,
     NUMBER = 294,
     IDENT = 295,
     SEMICOLON = 296,
     COLON = 297,
     COMMA = 298,
     QUESTION = 299,
     L_BRACKET = 300,
     R_BRACKET = 301,
     L_PAREN = 302,
     R_PAREN = 303,
     ASSIGN = 304
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define BEGIN_PROGRAM 259
#define END_PROGRAM 260
#define INTEGER 261
#define ARRAY 262
#define OF 263
#define IF 264
#define THEN 265
#define ENDIF 266
#define ELSE 267
#define ELSEIF 268
#define WHILE 269
#define DO 270
#define BEGINLOOP 271
#define ENDLOOP 272
#define BREAK 273
#define CONTINUE 274
#define EXIT 275
#define READ 276
#define WRITE 277
#define AND 278
#define OR 279
#define NOT 280
#define TRUE 281
#define FALSE 282
#define MOD 283
#define DIV 284
#define MULT 285
#define SUB 286
#define ADD 287
#define EQ 288
#define NEQ 289
#define LT 290
#define GT 291
#define LTE 292
#define GTE 293
#define NUMBER 294
#define IDENT 295
#define SEMICOLON 296
#define COLON 297
#define COMMA 298
#define QUESTION 299
#define L_BRACKET 300
#define R_BRACKET 301
#define L_PAREN 302
#define R_PAREN 303
#define ASSIGN 304




/* Copy the first part of user declarations.  */
#line 1 "mini_l.y"

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
stringstream code;
stringstream vars;
vector<string> errors;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 52 "mini_l.y"
{
  int		int_val;
  char* string_val;
}
/* Line 193 of yacc.c.  */
#line 249 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 262 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   170

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNRULES -- Number of states.  */
#define YYNSTATES  176

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    11,    19,    23,    24,    34,    39,
      40,    45,    46,    50,    58,    59,    60,    71,    72,    73,
      83,    84,    94,    95,   100,   101,   106,   108,   110,   112,
     113,   118,   119,   120,   125,   126,   130,   131,   134,   138,
     139,   142,   146,   147,   152,   155,   158,   163,   167,   169,
     171,   175,   176,   178,   180,   182,   184,   186,   188,   190,
     195,   200,   202,   208,   209,   210,   219,   220,   223,   227,
     231,   232,   235,   239,   243,   247,   248,   250,   253,   257,
     262,   264
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      51,     0,    -1,    -1,     3,    40,    41,    52,    53,     5,
      -1,    55,    41,    54,     4,    58,    41,    70,    -1,    55,
      41,    54,    -1,    -1,    40,    56,    42,     7,    45,    39,
      46,     8,     6,    -1,    40,    56,    42,     6,    -1,    -1,
      43,    40,    57,    56,    -1,    -1,    77,    49,    82,    -1,
      77,    49,    71,    44,    82,    42,    82,    -1,    -1,    -1,
       9,    71,    59,    10,    58,    41,    70,    60,    78,    11,
      -1,    -1,    -1,    14,    61,    71,    62,    16,    58,    41,
      70,    17,    -1,    -1,    15,    16,    63,    58,    41,    70,
      17,    14,    71,    -1,    -1,    21,    77,    64,    66,    -1,
      -1,    22,    77,    65,    68,    -1,    18,    -1,    19,    -1,
      20,    -1,    -1,    43,    77,    67,    66,    -1,    -1,    -1,
      43,    77,    69,    68,    -1,    -1,    58,    41,    70,    -1,
      -1,    73,    72,    -1,    24,    73,    72,    -1,    -1,    75,
      74,    -1,    23,    75,    74,    -1,    -1,    25,    82,    76,
      82,    -1,    25,    27,    -1,    25,    26,    -1,    25,    47,
      71,    48,    -1,    82,    76,    82,    -1,    27,    -1,    26,
      -1,    47,    71,    48,    -1,    -1,    33,    -1,    34,    -1,
      35,    -1,    36,    -1,    37,    -1,    38,    -1,    40,    -1,
      40,    45,    82,    46,    -1,    12,    58,    41,    70,    -1,
      79,    -1,    79,    12,    58,    41,    70,    -1,    -1,    -1,
      13,    71,    80,    58,    41,    70,    81,    79,    -1,    -1,
      84,    83,    -1,    32,    84,    83,    -1,    31,    84,    83,
      -1,    -1,    86,    85,    -1,    30,    86,    85,    -1,    29,
      86,    85,    -1,    28,    86,    85,    -1,    -1,    77,    -1,
      31,    77,    -1,    47,    82,    48,    -1,    31,    47,    82,
      48,    -1,    39,    -1,    31,    39,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   125,   125,   125,   130,   133,   134,   137,   149,   163,
     163,   174,   177,   180,   199,   206,   199,   218,   222,   218,
     239,   239,   252,   252,   266,   266,   280,   292,   308,   313,
     313,   326,   329,   329,   342,   345,   346,   349,   352,   353,
     358,   361,   362,   365,   375,   379,   383,   384,   393,   394,
     395,   396,   399,   402,   405,   408,   411,   414,   419,   428,
     442,   443,   444,   447,   453,   447,   460,   463,   468,   477,
     486,   491,   496,   505,   514,   523,   529,   532,   537,   540,
     543,   548
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "BEGIN_PROGRAM",
  "END_PROGRAM", "INTEGER", "ARRAY", "OF", "IF", "THEN", "ENDIF", "ELSE",
  "ELSEIF", "WHILE", "DO", "BEGINLOOP", "ENDLOOP", "BREAK", "CONTINUE",
  "EXIT", "READ", "WRITE", "AND", "OR", "NOT", "TRUE", "FALSE", "MOD",
  "DIV", "MULT", "SUB", "ADD", "EQ", "NEQ", "LT", "GT", "LTE", "GTE",
  "NUMBER", "IDENT", "SEMICOLON", "COLON", "COMMA", "QUESTION",
  "L_BRACKET", "R_BRACKET", "L_PAREN", "R_PAREN", "ASSIGN", "$accept",
  "Program", "@1", "Block", "Dec_prime", "Dec", "Ident_seq", "@2", "Stmt",
  "@3", "@4", "@5", "@6", "@7", "@8", "@9", "Read_var_prime", "@10",
  "Write_var_prime", "@11", "Stmt_prime", "Bool_exp", "Or_seq",
  "Relation_and_exp", "And_seq", "Relation_exp", "Comp", "Var",
  "Cond_tail", "Else_if_seq", "@12", "@13", "Expr", "Expr_seq",
  "Mult_expr", "Mult_expr_seq", "Term", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    52,    51,    53,    54,    54,    55,    55,    57,
      56,    56,    58,    58,    59,    60,    58,    61,    62,    58,
      63,    58,    64,    58,    65,    58,    58,    58,    58,    67,
      66,    66,    69,    68,    68,    70,    70,    71,    72,    72,
      73,    74,    74,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    76,    76,    76,    76,    76,    76,    77,    77,
      78,    78,    78,    80,    81,    79,    79,    82,    83,    83,
      83,    84,    85,    85,    85,    85,    86,    86,    86,    86,
      86,    86
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     6,     7,     3,     0,     9,     4,     0,
       4,     0,     3,     7,     0,     0,    10,     0,     0,     9,
       0,     9,     0,     4,     0,     4,     1,     1,     1,     0,
       4,     0,     0,     4,     0,     3,     0,     2,     3,     0,
       2,     3,     0,     4,     2,     2,     4,     3,     1,     1,
       3,     0,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     1,     5,     0,     0,     8,     0,     2,     3,     3,
       0,     2,     3,     3,     3,     0,     1,     2,     3,     4,
       1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     2,     0,    11,     0,     0,
       0,     0,     3,     6,     9,     0,     0,     0,    11,     8,
       0,     0,     6,    10,     0,    51,    17,     0,    26,    27,
      28,     0,     0,    58,     0,     0,     5,     0,     0,    49,
      48,     0,    80,    51,    14,    39,    42,    76,     0,    70,
      75,    51,    20,    22,    24,     0,    36,    51,     0,    45,
      44,    51,     0,    81,     0,    77,     0,     0,     0,    51,
      37,    51,    40,    52,    53,    54,    55,    56,    57,     0,
       0,     0,    67,     0,     0,     0,    71,    18,     0,    31,
      34,     0,     0,     0,     4,     0,    12,     0,     0,     0,
       0,    50,    78,     0,    39,    42,    47,    70,    70,    75,
      75,    75,     0,     0,     0,    23,     0,    25,     0,    59,
      36,     0,     7,    46,    43,    79,     0,    38,    41,    69,
      68,    74,    73,    72,     0,    36,    29,    32,    35,     0,
      36,     0,     0,    31,    34,     0,    15,    36,     0,    30,
      33,    13,    66,     0,    51,     0,    51,     0,    61,    19,
      21,     0,    63,    16,     0,    36,     0,     0,    60,     0,
      36,    36,    62,    64,    66,    65
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     8,    16,    17,    11,    18,    93,    68,
     152,    51,   112,    88,    89,    90,   115,   143,   117,   144,
      94,    44,    70,    45,    72,    46,    79,    47,   157,   158,
     166,   174,    48,    82,    49,    86,    50
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -115
static const yytype_int16 yypact[] =
{
       2,   -33,    19,   -16,  -115,  -115,   -13,   -14,    36,    -7,
       3,     8,  -115,   -13,  -115,    41,    58,    34,   -14,  -115,
      33,    82,   -13,  -115,    38,     5,  -115,    64,  -115,  -115,
    -115,    43,    43,    42,    40,    37,  -115,    44,    32,  -115,
    -115,   -38,  -115,     5,  -115,    65,    69,  -115,    74,    29,
       9,     5,  -115,  -115,  -115,   -23,    82,     5,    80,  -115,
    -115,     5,    74,  -115,   -23,  -115,    46,   118,    88,     5,
    -115,     5,  -115,  -115,  -115,  -115,  -115,  -115,  -115,   -23,
     -23,   -23,  -115,   -23,   -23,   -23,  -115,  -115,    82,    62,
      75,   -23,    77,    79,  -115,    81,    74,   115,    76,   -23,
      83,  -115,  -115,    82,    65,    69,  -115,    29,    29,     9,
       9,     9,   111,    87,    43,  -115,    43,  -115,    84,  -115,
      82,   -23,  -115,  -115,  -115,  -115,    92,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,    82,    82,  -115,  -115,  -115,    93,
      82,    95,   112,    62,    75,   -23,  -115,    82,   124,  -115,
    -115,  -115,    53,   122,     5,    82,     5,   129,   130,  -115,
    -115,   100,  -115,  -115,    82,    82,    82,   106,  -115,   116,
      82,    82,  -115,  -115,   145,  -115
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -115,  -115,  -115,  -115,   137,   154,   143,  -115,   -18,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,    20,  -115,    18,  -115,
    -114,   -39,    60,    96,    63,    98,   105,   -21,  -115,    -4,
    -115,  -115,   -15,   -34,   -12,   -96,   -30
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      35,    63,    33,    34,    66,     1,   138,     3,    41,    64,
      53,    54,    87,   131,   132,   133,    42,    33,    95,     4,
      65,   142,    98,    62,    91,     5,   146,     7,    67,    10,
      38,    39,    40,   153,    13,    35,    41,    83,    84,    85,
      92,    12,    96,    14,    42,    33,    67,    19,    20,   100,
      15,   168,    43,   109,   110,   111,   172,   173,    59,    60,
      80,    81,    21,    41,   106,   155,   156,    35,   107,   108,
     113,    42,    33,   129,   130,    22,   118,    37,    24,    61,
      52,    56,    35,    33,   124,   126,    57,    55,    97,    69,
      58,    25,    71,   136,   101,   137,    26,    27,   103,    35,
      28,    29,    30,    31,    32,   114,   139,    73,    74,    75,
      76,    77,    78,    35,    35,   160,   141,   162,   116,    35,
     120,   122,    33,   119,   123,   121,    35,   134,   135,   148,
     151,   125,   102,   140,    35,   145,   147,   161,   154,   159,
     163,   165,   164,    35,    35,    35,   167,   170,   169,    35,
      35,    73,    74,    75,    76,    77,    78,   171,   156,    36,
       9,    23,   150,   149,   127,   104,   102,    99,   128,   105,
     175
};

static const yytype_uint8 yycheck[] =
{
      21,    39,    40,    21,    43,     3,   120,    40,    31,    47,
      31,    32,    51,   109,   110,   111,    39,    40,    57,     0,
      41,   135,    61,    38,    47,    41,   140,    40,    43,    43,
      25,    26,    27,   147,    41,    56,    31,    28,    29,    30,
      55,     5,    57,    40,    39,    40,    61,     6,     7,    64,
      42,   165,    47,    83,    84,    85,   170,   171,    26,    27,
      31,    32,     4,    31,    79,    12,    13,    88,    80,    81,
      88,    39,    40,   107,   108,    41,    91,    39,    45,    47,
      16,    41,   103,    40,    99,   103,    49,    45,     8,    24,
      46,     9,    23,   114,    48,   116,    14,    15,    10,   120,
      18,    19,    20,    21,    22,    43,   121,    33,    34,    35,
      36,    37,    38,   134,   135,   154,   134,   156,    43,   140,
      41,     6,    40,    46,    48,    44,   147,    16,    41,    17,
     145,    48,    48,    41,   155,    42,    41,   155,    14,    17,
      11,    41,    12,   164,   165,   166,   164,    41,   166,   170,
     171,    33,    34,    35,    36,    37,    38,    41,    13,    22,
       6,    18,   144,   143,   104,    69,    48,    62,   105,    71,
     174
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    51,    40,     0,    41,    52,    40,    53,    55,
      43,    56,     5,    41,    40,    42,    54,    55,    57,     6,
       7,     4,    41,    56,    45,     9,    14,    15,    18,    19,
      20,    21,    22,    40,    58,    77,    54,    39,    25,    26,
      27,    31,    39,    47,    71,    73,    75,    77,    82,    84,
      86,    61,    16,    77,    77,    45,    41,    49,    46,    26,
      27,    47,    82,    39,    47,    77,    71,    82,    59,    24,
      72,    23,    74,    33,    34,    35,    36,    37,    38,    76,
      31,    32,    83,    28,    29,    30,    85,    71,    63,    64,
      65,    47,    82,    58,    70,    71,    82,     8,    71,    76,
      82,    48,    48,    10,    73,    75,    82,    84,    84,    86,
      86,    86,    62,    58,    43,    66,    43,    68,    82,    46,
      41,    44,     6,    48,    82,    48,    58,    72,    74,    83,
      83,    85,    85,    85,    16,    41,    77,    77,    70,    82,
      41,    58,    70,    67,    69,    42,    70,    41,    17,    66,
      68,    82,    60,    70,    14,    12,    13,    78,    79,    17,
      71,    58,    71,    11,    12,    41,    80,    58,    70,    58,
      41,    41,    70,    70,    81,    79
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 125 "mini_l.y"
    {program_name = (yyvsp[(2) - (3)].string_val);;}
    break;

  case 3:
#line 125 "mini_l.y"
    {
  code << ": " << "EndLabel" << endl;
;}
    break;

  case 4:
#line 130 "mini_l.y"
    {;}
    break;

  case 5:
#line 133 "mini_l.y"
    {;}
    break;

  case 6:
#line 134 "mini_l.y"
    {;}
    break;

  case 7:
#line 137 "mini_l.y"
    {
  if((yyvsp[(1) - (9)].string_val) == program_name)
  {
    string error = "Variable cannot have same name as program";
    yyerror(error);
  }
  Sym sym;
  sym.name = (yyvsp[(1) - (9)].string_val);
  sym.size = (yyvsp[(6) - (9)].int_val);
  sym.type = INTARR;
  add_sym(sym);
;}
    break;

  case 8:
#line 149 "mini_l.y"
    {
  if((yyvsp[(1) - (4)].string_val) == program_name)
  {
    string error = "Variable cannot have same name as program";
    yyerror(error);
  }
  Sym sym;
  sym.name = (yyvsp[(1) - (4)].string_val);
  sym.size = -1;
  sym.type = INT;
  add_sym(sym);
;}
    break;

  case 9:
#line 163 "mini_l.y"
    {
  if((yyvsp[(2) - (2)].string_val) == program_name)
  {
    string error = "Variable cannot have same name as program";
    yyerror(error);
  }
  Sym sym;
  sym.name = (yyvsp[(2) - (2)].string_val);
  sym.type = INT;
  add_sym(sym);
;}
    break;

  case 12:
#line 177 "mini_l.y"
    {
  code << "= " << (yyvsp[(1) - (3)].string_val) << ", " << temps.top() << endl;
;}
    break;

  case 13:
#line 180 "mini_l.y"
    {
  string lhs_label = add_label();
  string rhs_label = add_label();
  string end_label = add_label();
  string t3 = temps.top();
  temps.pop();
  string t2 = temps.top();
  temps.pop();

  code << "?:= " << lhs_label << ", " << temps.top() << endl;
  code << ": " << rhs_label << endl;

  code << "= " << (yyvsp[(1) - (7)].string_val) << ", " << t3 << endl;
  code << ":= " << end_label << endl;
  code << ": " << lhs_label << endl;

  code << "= " << (yyvsp[(1) - (7)].string_val) << ", " << t2 << endl;
  code << ": " << end_label << endl;
;}
    break;

  case 14:
#line 199 "mini_l.y"
    {
  string end_label = add_if_label();
  string next_cond_label = add_if_label();
  string cond = temps.top();
  string neg_cond = add_temp();
  code << "! " << neg_cond << ", " << cond << endl;
  code << "?:= " << next_cond_label << ", " << neg_cond << endl;
;}
    break;

  case 15:
#line 206 "mini_l.y"
    {
  string next_cond_label = if_labels.top();
  if_labels.pop();
  string end_label = if_labels.top();
  code << ":= " << end_label << endl;
  code << ": " << next_cond_label << endl;
;}
    break;

  case 16:
#line 212 "mini_l.y"
    {
    string end_label = if_labels.top();
    if_labels.pop();
    code << ": " << end_label << endl;
;}
    break;

  case 17:
#line 218 "mini_l.y"
    {
  string begin_label = add_while_label();
  code << ": " << begin_label << endl;

;}
    break;

  case 18:
#line 222 "mini_l.y"
    {
  string end_label = add_while_label();
  string cond = temps.top();
  string neg_cond = add_temp();
  code << "! " << neg_cond << ", " << cond << endl;
  code << "?:= " << end_label << ", " << neg_cond << endl;

;}
    break;

  case 19:
#line 229 "mini_l.y"
    {
  string end_label = while_labels.top();
  while_labels.pop();
  string begin_label = while_labels.top();
  while_labels.pop();

  code << ":= " << begin_label << endl;
  code << ": " << end_label << endl;
;}
    break;

  case 20:
#line 239 "mini_l.y"
    {
  string begin_label = add_while_label();
  string end_label = add_while_label();
  code << ": " << begin_label << endl;

;}
    break;

  case 21:
#line 244 "mini_l.y"
    {
  string end_label = while_labels.top();
  while_labels.pop();
  string begin_label = while_labels.top();
  while_labels.pop();
  code << "?:= " << begin_label << ", " << temps.top() << endl;
  code << ": " << end_label << endl;
;}
    break;

  case 22:
#line 252 "mini_l.y"
    {
  if(sym_table[temps.top()].type == INTARR)
  {
    string dst = temps.top();
    temps.pop();
    string expr = temps.top();
    code << ".[]< " << dst << ", " << expr << endl;
  }
  else
  {
    code << ".< " << temps.top() << endl;
  }
;}
    break;

  case 24:
#line 266 "mini_l.y"
    {
  if(sym_table[temps.top()].type == INTARR)
  {
    string dst = temps.top();
    temps.pop();
    string expr = temps.top();
    code << ".[]> " << dst << ", " << expr << endl;
  }
  else
  {
    code << ".> " << temps.top() << endl;
  }
;}
    break;

  case 26:
#line 280 "mini_l.y"
    {
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
;}
    break;

  case 27:
#line 292 "mini_l.y"
    {
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
;}
    break;

  case 28:
#line 308 "mini_l.y"
    {
  code << ":= " << "EndLabel" << endl;
;}
    break;

  case 29:
#line 313 "mini_l.y"
    {
  if(sym_table[temps.top()].type == INTARR)
  {
    string dst = temps.top();
    temps.pop();
    string expr = temps.top();
    code << ".[]< " << dst << ", " << expr << endl;
  }
  else
  {
    code << ".< " << temps.top() << endl;
  }
;}
    break;

  case 31:
#line 326 "mini_l.y"
    {;}
    break;

  case 32:
#line 329 "mini_l.y"
    {
  if(sym_table[temps.top()].type == INTARR)
  {
    string dst = temps.top();
    temps.pop();
    string expr = temps.top();
    code << ".[]> " << dst << ", " << expr << endl;
  }
  else
  {
    code << ".> " << temps.top() << endl;
  }
;}
    break;

  case 34:
#line 342 "mini_l.y"
    {;}
    break;

  case 35:
#line 345 "mini_l.y"
    {;}
    break;

  case 36:
#line 346 "mini_l.y"
    {;}
    break;

  case 37:
#line 349 "mini_l.y"
    {;}
    break;

  case 38:
#line 352 "mini_l.y"
    {;}
    break;

  case 39:
#line 353 "mini_l.y"
    {

;}
    break;

  case 40:
#line 358 "mini_l.y"
    {;}
    break;

  case 41:
#line 361 "mini_l.y"
    {;}
    break;

  case 42:
#line 362 "mini_l.y"
    {;}
    break;

  case 43:
#line 365 "mini_l.y"
    {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << "! " << t1 << ", " << t1 << endl;
  code << (yyvsp[(3) - (4)].string_val) << t1 << ", " << t3 << ", " << t2 << endl;
;}
    break;

  case 44:
#line 375 "mini_l.y"
    {
  string tname = add_temp();
  code << "= " << tname << ", " << 1 << endl;
;}
    break;

  case 45:
#line 379 "mini_l.y"
    {
  string tname = add_temp();
  code << "= " << tname << ", " << 0 << endl;
;}
    break;

  case 46:
#line 383 "mini_l.y"
    {;}
    break;

  case 47:
#line 384 "mini_l.y"
    {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << (yyvsp[(2) - (3)].string_val) << t1 << ", " << t3 << ", " << t2 << endl;
;}
    break;

  case 48:
#line 393 "mini_l.y"
    {;}
    break;

  case 49:
#line 394 "mini_l.y"
    {;}
    break;

  case 50:
#line 395 "mini_l.y"
    {;}
    break;

  case 52:
#line 399 "mini_l.y"
    {
  (yyval.string_val) = (char *)"== ";
;}
    break;

  case 53:
#line 402 "mini_l.y"
    {
  (yyval.string_val) = (char *)"!= ";
;}
    break;

  case 54:
#line 405 "mini_l.y"
    {
  (yyval.string_val) = (char *)"< ";
;}
    break;

  case 55:
#line 408 "mini_l.y"
    {
  (yyval.string_val) = (char *)"> ";
;}
    break;

  case 56:
#line 411 "mini_l.y"
    {
  (yyval.string_val) = (char *)"<= ";
;}
    break;

  case 57:
#line 414 "mini_l.y"
    {
  (yyval.string_val) = (char *)">= ";
;}
    break;

  case 58:
#line 419 "mini_l.y"
    {
  verify_sym((yyvsp[(1) - (1)].string_val));
  if(sym_table[(yyvsp[(1) - (1)].string_val)].type == INTARR)
  {
    yyerror("Cannot access array as scalar variable. Must use index");
  }
  (yyval.string_val) = (yyvsp[(1) - (1)].string_val);
  temps.push((yyvsp[(1) - (1)].string_val));
;}
    break;

  case 59:
#line 428 "mini_l.y"
    {
  verify_sym((yyvsp[(1) - (4)].string_val));
  if(sym_table[(yyvsp[(1) - (4)].string_val)].type != INTARR)
  {
    yyerror("Cannot access scalar variable as array.");
  }
  string tname = add_temp();
  sym_table[(yyvsp[(1) - (4)].string_val)].type = INTARR;
  (yyval.string_val) = const_cast<char*>(tname.c_str());
  code << "= " << tname << ", " << (yyvsp[(1) - (4)].string_val) << endl;
  temps.push((yyvsp[(3) - (4)].string_val));
  temps.push((yyvsp[(1) - (4)].string_val));
;}
    break;

  case 60:
#line 442 "mini_l.y"
    {;}
    break;

  case 61:
#line 443 "mini_l.y"
    {;}
    break;

  case 62:
#line 444 "mini_l.y"
    {;}
    break;

  case 63:
#line 447 "mini_l.y"
    {
  string next_cond_label = add_if_label();
  string cond = temps.top();
  string neg_cond = add_temp();
  code << "! " << neg_cond << ", " << cond << endl;
  code << "?:= " << next_cond_label << ", " << neg_cond << endl;
;}
    break;

  case 64:
#line 453 "mini_l.y"
    {
  string next_cond_label = if_labels.top();
  if_labels.pop();
  string end_label = if_labels.top();
  code << ":= " << end_label << endl;
  code << ": " << next_cond_label << endl;
;}
    break;

  case 65:
#line 459 "mini_l.y"
    {;}
    break;

  case 67:
#line 463 "mini_l.y"
    {

;}
    break;

  case 68:
#line 468 "mini_l.y"
    {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << "+ " << t1 << ", " << t3 << ", " << t2 << endl;
;}
    break;

  case 69:
#line 477 "mini_l.y"
    {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << "- " << t1 << ", " << t3 << ", " << t2 << endl;
;}
    break;

  case 70:
#line 486 "mini_l.y"
    {

;}
    break;

  case 71:
#line 491 "mini_l.y"
    {
  (yyval.string_val) = (yyvsp[(1) - (2)].string_val);
;}
    break;

  case 72:
#line 496 "mini_l.y"
    {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << "* " << t1 << ", " << t3 << ", " << t2 << endl;
;}
    break;

  case 73:
#line 505 "mini_l.y"
    {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << "/ " << t1 << ", " << t3 << ", " << t2 << endl;
;}
    break;

  case 74:
#line 514 "mini_l.y"
    {
  string t2 = temps.top();
  temps.pop();
  string t3 = temps.top();
  temps.pop();
  string tname = add_temp();
  string t1 = temps.top();
  code << "% " << t1 << ", " << t3 << ", " << t2 << endl;
;}
    break;

  case 75:
#line 523 "mini_l.y"
    {

;}
    break;

  case 76:
#line 529 "mini_l.y"
    {
  (yyval.string_val) = (yyvsp[(1) - (1)].string_val);
;}
    break;

  case 77:
#line 532 "mini_l.y"
    {
  string tname = add_temp();
  code << "= " << tname << ", " << (yyvsp[(2) - (2)].string_val) << endl;
  code << "* " << tname << ", " << tname << ", " << -1 << endl;
;}
    break;

  case 78:
#line 537 "mini_l.y"
    {
  (yyval.string_val) = (yyvsp[(2) - (3)].string_val);
;}
    break;

  case 79:
#line 540 "mini_l.y"
    {
  code << "* " << (yyvsp[(3) - (4)].string_val) << ", " << (yyvsp[(3) - (4)].string_val) << ", " << -1 << endl;
;}
    break;

  case 80:
#line 543 "mini_l.y"
    {
  string tname = add_temp();
  code << "= " << tname << ", " << (yyvsp[(1) - (1)].int_val) << endl;
  (yyval.string_val) = const_cast<char*>(tname.c_str());
;}
    break;

  case 81:
#line 548 "mini_l.y"
    {
  string tname = add_temp();
  code << "= " << tname << ", " << (yyvsp[(2) - (2)].int_val) << endl;
  code << "* " << tname << ", " << tname  << ", " << -1 << endl;
  (yyval.string_val) = const_cast<char*>(tname.c_str());
;}
    break;


/* Line 1267 of yacc.c.  */
#line 2284 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 556 "mini_l.y"


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
        errors.push_back(errormsg);
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

string add_while_label()
{
  string lname = "WL" + to_string(++while_labels_size);
  while_labels.push(lname);
  return lname;
}

string add_if_label()
{
    static int id = 0;
    
    string lname = "IL" + to_string(++id);
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
  // Not yet..
  //file << vars.str();
  cout << vars.str();
}

int main(int argc, char **argv)
{

  yyparse();

  ofstream file(program_name.c_str());
  if(errors.size() != 0)
  {
    for(int i = 0; i < errors.size(); ++i)
    {
      printf("%s", errors[i].c_str());
    }
    //exit(1);
  }
  //else
  {
    gen_variables();
    // Not yet..
    //file << code.str();
    cout << code.str();
  }
  return 0;
}

