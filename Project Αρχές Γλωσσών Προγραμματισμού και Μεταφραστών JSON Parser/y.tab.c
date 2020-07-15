/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "test.y" /* yacc.c:339  */

#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


void yyerror(char const *S);
extern int yylineno;
extern char* yytext;
extern FILE *yyin;
extern FILE *yyout;
int yylex(void);
char* months[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
char* days[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
int tweet_id_array_size = 0;
int tweet_id_array_max_size = 10;
int *tweet_id;
int counter;
long long int id_string;
long long int *tweet_id_string;
int tweet_id_string_array_size = 0;
int tweet_id_string_array_max_size = 10;
char* input_string;
char* split_string;
char* retweeted_tweet_text;
char* retweeted_tweet_name;
int extended = 1;
int extended_tweet_length;
int hashtag_counter = 0;
char* full_text;
char* indice_text;
int indice_tuple_start;
int indice_tuple_end;
int hashtag_parsed = 0;

#line 104 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    STRING = 258,
    SIGN = 259,
    UNSIGN = 260,
    REAL = 261,
    true = 262,
    false = 263,
    null = 264
  };
#endif
/* Tokens.  */
#define STRING 258
#define SIGN 259
#define UNSIGN 260
#define REAL 261
#define true 262
#define false 263
#define null 264

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 41 "test.y" /* yacc.c:355  */

    float real;
	int number;
    char *string;
	double scien;

#line 169 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 186 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   170

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  17
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  188

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   264

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    16,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    10,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    12,     2,    13,     2,     2,     2,     2,     2,     2,
       2,    11,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    14,     2,    15,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   106,   106,   107,   110,   111,   112,   113,   130,   133,
     136,   139,   142,   145,   148,   151,   152,   155,   158,   159,
     162,   163,   164,   165,   168,   210,   216,   232,   247,   258,
     270,   279,   290,   296,   318,   329,   343,   353,   362,   373,
     394,   395,   403,   428,   444,   459,   498,   537,   548,   566,
     577,   588,   599,   612,   623,   635,   646,   769,   780,   786,
     815,   826,   837,   848,   884,   885,   886,   887,   890,   891,
     892
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "STRING", "SIGN", "UNSIGN", "REAL",
  "true", "false", "null", "':'", "'e'", "'['", "']'", "'{'", "'}'", "','",
  "$accept", "program", "json_attributes", "double_dot", "epsilon",
  "left_bracket", "right_bracket", "left_curly_bracket",
  "right_curly_bracket", "comma", "boolean", "generic_array",
  "generic_elements", "generic_values", "extended_tweet_object",
  "extended_tweet_attributes", "extended_tweet_text_field",
  "truncated_field", "display_text_field", "unsign_tuple",
  "extended_tweet", "extended_tweet_fields", "full_text_field",
  "extended_tweet_display_text_range", "extended_tweet_unsign_tuple",
  "entities", "entities_field", "hashtags", "indice_array", "indice",
  "indice_text_field", "indice_tuple", "tweet_object", "retweet_object",
  "retweeted_tweet_object", "retweeted_tweet_text_field",
  "retweeted_tweet_user_field", "retweet_user_screen_name_field",
  "retweeted_status_object", "retweeted_status_text_field",
  "retweeted_status_user_field", "retweeted_status_screen_name_field",
  "tweet_text_field", "tweet_created_at_field", "tweet_user_field",
  "user_attributes", "user_id_field", "user_name_field",
  "user_screen_name_field", "user_location_field", "tweet_id_string_field",
  "number", "scientific", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
      58,   101,    91,    93,   123,   125,    44
};
# endif

#define YYPACT_NINF -152

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-152)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,  -152,  -152,     5,  -152,   161,    -1,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,    -4,    -4,    -4,  -152,  -152,  -152,
    -152,    -3,     8,  -152,  -152,    18,    26,     8,    28,  -152,
      29,    32,    33,  -152,  -152,  -152,   161,  -152,    -2,    18,
      17,    39,    18,    42,  -152,  -152,  -152,  -152,     8,    44,
      35,  -152,  -152,    18,    17,    47,    18,    48,    51,  -152,
      18,    52,    54,    35,  -152,     8,     1,    18,  -152,    18,
      17,    57,    18,    17,    18,    60,    61,    63,  -152,     8,
       8,    65,    35,  -152,  -152,    35,  -152,    66,    18,    17,
    -152,    18,  -152,    18,    68,  -152,    69,     8,    71,    73,
       8,    35,  -152,    70,    75,    18,    17,    18,  -152,  -152,
      18,    17,    77,    18,    17,  -152,    82,    81,     8,  -152,
      35,  -152,    70,    83,  -152,    18,    86,    87,  -152,    18,
      17,     8,  -152,    90,    89,     8,     8,    92,    18,    95,
    -152,    70,  -152,    96,    18,    17,     8,  -152,  -152,     8,
      99,    18,  -152,    35,    -3,   102,  -152,   101,  -152,     8,
     104,   107,    -3,     8,  -152,  -152,    -3,  -152,     8,    18,
     108,  -152,    35,  -152,  -152,   110,    18,    17,  -152,     8,
      70,  -152,  -152,   109,     8,   112,    -3,  -152
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    10,    12,     0,     2,     0,     0,     7,     4,     6,
       5,     1,     3,    21,    64,    65,    66,    15,    16,    22,
      23,     0,    18,    20,    67,     0,     0,     0,     0,     9,
       0,     0,     0,    11,    17,    14,     0,     8,     0,     0,
       0,     0,     0,     0,    68,    69,    70,    19,     0,     0,
       0,    13,    24,     0,     0,     0,     0,     0,     0,    56,
       0,     0,     0,     0,    46,     0,     0,     0,    25,     0,
       0,     0,     0,     0,     0,    37,     0,     0,    63,     0,
       0,     0,     0,    45,    52,     0,    51,     0,     0,     0,
      36,     0,    32,     0,     0,    55,     0,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,     0,    27,    26,
       0,     0,     0,     0,     0,    33,     0,     0,     0,    48,
       0,    47,    30,     0,    57,     0,     0,     0,    53,     0,
       0,     0,    34,     0,     0,     0,     0,     0,     0,     0,
      54,     0,    38,     0,     0,     0,     0,    28,    59,     0,
       0,     0,    58,     0,     0,     0,    49,     0,    60,     0,
       0,     0,     0,    40,    35,    50,     0,    61,     0,     0,
       0,    39,     0,    29,    62,     0,     0,     0,    41,     0,
       0,    42,    43,     0,     0,     0,     0,    44
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -152,  -152,   117,   -26,     7,   -97,  -151,   -24,   -14,   -27,
      49,  -152,    85,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,   -49,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
    -152,  -152,  -152
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    38,    30,     5,    34,     6,    52,    36,
      20,     7,    21,    22,     8,    26,    68,    57,   108,   135,
      40,    75,    76,    92,   118,    89,    90,   130,   162,   163,
     170,   177,     9,    10,    54,    94,   106,   145,    27,    61,
      73,   114,    58,    28,    70,   111,   112,   126,   139,   152,
      43,    23,    24
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      41,    48,    25,   164,    79,    11,   117,    29,    17,    18,
      33,   171,     2,    50,    49,   173,    55,     1,     1,     2,
       2,    59,    31,    32,    35,   134,    62,    63,    37,    39,
      66,    42,    51,    44,    71,   187,    45,    46,    78,    77,
      64,    81,    53,    82,   153,    56,    85,    60,    87,     2,
      65,    67,    95,    96,    69,    72,    83,    74,    98,    86,
      84,    99,   101,    88,    91,   103,    93,   104,    97,   100,
     109,   105,   107,   115,   110,   102,   113,   116,   119,   120,
     125,   122,     1,   183,   123,   129,   131,   127,   136,   138,
     140,   132,   121,   144,   146,   149,   133,   124,   151,   137,
     128,   154,   159,   141,   143,   165,   166,   168,   147,   148,
     169,   176,   150,   179,   184,    80,   142,   186,   155,   157,
      12,    47,   158,   178,     0,   160,     0,     0,     0,   161,
       0,   156,   167,     0,     0,     0,   172,     0,     0,     0,
       0,   174,     0,   175,     0,     0,     0,     0,   161,     0,
     180,     0,   182,     0,     0,     0,     0,   185,     0,     0,
       0,     0,     0,   181,    13,    14,    15,    16,    17,    18,
      19
};

static const yytype_int16 yycheck[] =
{
      27,     3,     3,   154,     3,     0,   103,    11,     7,     8,
      13,   162,    14,    39,    38,   166,    42,    12,    12,    14,
      14,    48,    15,    16,    16,   122,    50,    53,    10,     3,
      56,     3,    15,     4,    60,   186,     4,     4,    65,    63,
      54,    67,     3,    69,   141,     3,    72,     3,    74,    14,
       3,     3,    79,    80,     3,     3,    70,     3,    82,    73,
       3,    85,    88,     3,     3,    91,     3,    93,     3,     3,
      97,     3,     3,   100,     3,    89,     3,   101,     3,   105,
       3,   107,    12,   180,   110,     3,     5,   113,     5,     3,
       3,   118,   106,     3,     5,     3,   120,   111,     3,   125,
     114,     5,     3,   129,   131,     3,     5,     3,   135,   136,
       3,     3,   138,     3,     5,    66,   130,     5,   144,   146,
       3,    36,   149,   172,    -1,   151,    -1,    -1,    -1,   153,
      -1,   145,   159,    -1,    -1,    -1,   163,    -1,    -1,    -1,
      -1,   168,    -1,   169,    -1,    -1,    -1,    -1,   172,    -1,
     176,    -1,   179,    -1,    -1,    -1,    -1,   184,    -1,    -1,
      -1,    -1,    -1,   177,     3,     4,     5,     6,     7,     8,
       9
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    12,    14,    18,    19,    22,    24,    28,    31,    49,
      50,     0,    19,     3,     4,     5,     6,     7,     8,     9,
      27,    29,    30,    68,    69,     3,    32,    55,    60,    11,
      21,    21,    21,    13,    23,    16,    26,    10,    20,     3,
      37,    26,     3,    67,     4,     4,     4,    29,     3,    24,
      20,    15,    25,     3,    51,    20,     3,    34,    59,    26,
       3,    56,    24,    20,    25,     3,    20,     3,    33,     3,
      61,    20,     3,    57,     3,    38,    39,    24,    26,     3,
      27,    20,    20,    25,     3,    20,    25,    20,     3,    42,
      43,     3,    40,     3,    52,    26,    26,     3,    24,    24,
       3,    20,    25,    20,    20,     3,    53,     3,    35,    26,
       3,    62,    63,     3,    58,    26,    24,    22,    41,     3,
      20,    25,    20,    20,    25,     3,    64,    20,    25,     3,
      44,     5,    26,    24,    22,    36,     5,    20,     3,    65,
       3,    20,    25,    26,     3,    54,     5,    26,    26,     3,
      20,     3,    66,    22,     5,    20,    25,    26,    26,     3,
      20,    24,    45,    46,    23,     3,     5,    26,     3,     3,
      47,    23,    26,    23,    26,    20,     3,    48,    45,     3,
      20,    25,    26,    22,     5,    26,     5,    23
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    17,    18,    18,    19,    19,    19,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    27,    28,    29,    29,
      30,    30,    30,    30,    31,    32,    33,    34,    35,    36,
      36,    37,    38,    39,    40,    41,    42,    42,    43,    44,
      45,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    68,    68,    68,    69,    69,
      69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     3,
       1,     1,     1,     1,     4,     4,     4,     5,     4,     5,
       0,     6,     2,     4,     4,     5,     1,     0,     5,     5,
       1,     3,     4,     4,     7,     6,     5,     6,     3,     5,
       3,     6,     3,     5,     3,     4,     4,     5,     4,     4,
       4,     4,     4,     4,     1,     1,     1,     1,     3,     3,
       3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 110 "test.y" /* yacc.c:1646  */
    { fprintf(yyout,"%s", "\n");}
#line 1390 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 111 "test.y" /* yacc.c:1646  */
    { fprintf(yyout,"%s", "\n");}
#line 1396 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 112 "test.y" /* yacc.c:1646  */
    { fprintf(yyout,"%s", "\n");}
#line 1402 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 113 "test.y" /* yacc.c:1646  */
    { fprintf(yyout,"%s", "\n");}
#line 1408 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 130 "test.y" /* yacc.c:1646  */
    { (yyval.string) = ":"; }
#line 1414 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 133 "test.y" /* yacc.c:1646  */
    { (yyval.string) = "e"; }
#line 1420 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 136 "test.y" /* yacc.c:1646  */
    { (yyval.string) = "["; }
#line 1426 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 139 "test.y" /* yacc.c:1646  */
    { (yyval.string) = "]"; }
#line 1432 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 142 "test.y" /* yacc.c:1646  */
    { (yyval.string) = "{\n"; }
#line 1438 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 145 "test.y" /* yacc.c:1646  */
    { (yyval.string) = "\n}"; }
#line 1444 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 148 "test.y" /* yacc.c:1646  */
    { (yyval.string) = ","; }
#line 1450 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 151 "test.y" /* yacc.c:1646  */
    { (yyval.string) = strdup("true");  }
#line 1456 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 152 "test.y" /* yacc.c:1646  */
    { (yyval.string) = strdup("false");  }
#line 1462 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 155 "test.y" /* yacc.c:1646  */
    { fprintf(yyout,"%s%s%s", (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string)); }
#line 1468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 158 "test.y" /* yacc.c:1646  */
    { sprintf((yyval.string),"%s", (yyvsp[0].string)); }
#line 1474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 159 "test.y" /* yacc.c:1646  */
    { sprintf((yyval.string),"%s%s%s", (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string)); }
#line 1480 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 162 "test.y" /* yacc.c:1646  */
    { sprintf((yyval.string),"%s", (yyvsp[0].string)); }
#line 1486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 163 "test.y" /* yacc.c:1646  */
    { sprintf((yyval.string),"%s", (yyvsp[0].string)); }
#line 1492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 164 "test.y" /* yacc.c:1646  */
    { (yyval.string) = strdup("null"); }
#line 1498 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 165 "test.y" /* yacc.c:1646  */
    { sprintf((yyval.string),"%s", (yyvsp[0].string)); }
#line 1504 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 169 "test.y" /* yacc.c:1646  */
    {
															extended = 1;
															hashtag_counter = 0;
															hashtag_parsed = 0;
															char* printf_string;
															asprintf(&printf_string,"%s%s\n%s%s\n", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
															int left_bracket_counter = 0;
															int right_bracket_counter = 0;
															for(int i = 0; i < strlen(printf_string); i++)
															{
																if(printf_string[i] == '{')
																{
																	left_bracket_counter++;
																}
																if(printf_string[i] == '}')
																{
																	right_bracket_counter++;
																}
																printf("%c",printf_string[i]);
																if(printf_string[i] == '\n')
																{
																	int j;
																if(i+1 < strlen(printf_string) && printf_string[i+1] == '}')
																{
																	for(j = 0; j < left_bracket_counter - right_bracket_counter - 1; j++)
																	{
																		printf("\t");
																	}
																}
																else
																{
																	for(j = 0; j < left_bracket_counter - right_bracket_counter; j++)
																	{
																		printf("\t");
																	}
																}
															}
														}		
													}
#line 1548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 211 "test.y" /* yacc.c:1646  */
    {
															sprintf((yyval.string),"%s\n%s\n%s\n%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
														}
#line 1556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 217 "test.y" /* yacc.c:1646  */
    { 
									if(strcmp("\"text\"",(yyvsp[-3].string)) != 0)
									{
										fprintf(stderr,"Error in line: %d\nInvalid extended tweet text field.\n", yylineno);
										exit(1);
									}
									if((strlen((yyvsp[-1].string))>140))
									{
										fprintf(stderr,"Error in line: %d\nExtended tweet text field must have maximum 140 characters.\n", yylineno);
										exit(1);
									}
									sprintf((yyval.string), "%s %s %s%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
								}
#line 1574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 233 "test.y" /* yacc.c:1646  */
    {
										if(strcmp("\"truncated\"", (yyvsp[-4].string)) != 0)
										{
											fprintf(stderr,"Error in line: %d\nInvalid extended tweet truncated field.\n", yylineno);
											exit(1);
										}
										if(strcmp("false",(yyvsp[-2].string)) == 0)
										{
											extended = 0;
										}
										sprintf((yyval.string),"%s %s %s%s\n%s", (yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
									}
#line 1591 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 248 "test.y" /* yacc.c:1646  */
    {
															if(strcmp("\"display_text_range\"", (yyvsp[-3].string)) != 0)
															{
																fprintf(stderr,"Error in line: %d\nInvalid extended tweet display text range field.\n", yylineno);
																exit(1);
															}
															sprintf((yyval.string),"%s %s %s%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
														}
#line 1604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 259 "test.y" /* yacc.c:1646  */
    { 
													if(((yyvsp[-3].number) != 0) || ((yyvsp[-1].number)>140) || (extended == 0))
													{
														fprintf(stderr,"Error in line: %d\nInvalid extended tweet display text range tuple field.\n", yylineno);
														exit(1);
													}
													char tuple[9];
													sprintf(tuple,"%s%d%s%d%s", (yyvsp[-4].string), (yyvsp[-3].number), (yyvsp[-2].string), (yyvsp[-1].number), (yyvsp[0].string));
													(yyval.string) = strdup(tuple); 
												}
#line 1619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 270 "test.y" /* yacc.c:1646  */
    {
					if(extended == 1)
					{
						fprintf(stderr,"Error in line: %d\nInvalid extended tweet format.\n", yylineno);
						exit(1);
					}
				}
#line 1631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 280 "test.y" /* yacc.c:1646  */
    {
															if(strcmp("\"extended_tweet\"", (yyvsp[-5].string)) != 0)
															{
																fprintf(stderr,"Error in line: %d\nInvalid extended tweet field.\n", yylineno);
																exit(1);
															}
															sprintf((yyval.string),"%s %s\n%s%s\n%s%s", (yyvsp[-5].string), (yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
														}
#line 1644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 291 "test.y" /* yacc.c:1646  */
    {
													sprintf((yyval.string),"%s\n%s", (yyvsp[-1].string), (yyvsp[0].string));
												}
#line 1652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 297 "test.y" /* yacc.c:1646  */
    {
										if(strcmp("\"full_text\"", (yyvsp[-3].string)) != 0)
										{
											fprintf(stderr,"Error in line: %d\nInvalid extended tweet full text field.\n", yylineno);
											exit(1);
										}
										full_text = strdup((yyvsp[-1].string));
										int index = 0;
										while(full_text[index]!='\0')
										{
											if(full_text[index] == '#')
											{
												hashtag_counter++;
											}
											index++;
										}
										extended_tweet_length = strlen((yyvsp[-1].string));
										sprintf((yyval.string),"%s %s %s%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
									}
#line 1676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 319 "test.y" /* yacc.c:1646  */
    {
															if(strcmp("\"display_text_range\"", (yyvsp[-3].string)) != 0)
															{
																fprintf(stderr,"Error in line: %d\nInvalid extended tweet display text range field.\n", yylineno);
																exit(1);
															}
															sprintf((yyval.string),"%s %s %s%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
														}
#line 1689 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 330 "test.y" /* yacc.c:1646  */
    { 
												
													if(((yyvsp[-3].number) != 0) || ((yyvsp[-1].number) != extended_tweet_length))
													{
														fprintf(stderr,"Error in line: %d\nInvalid extended tweet display text range tuple field.\n", yylineno);
														exit(1);
													}
													char tuple[9];
													sprintf(tuple,"%s%d%s%d%s", (yyvsp[-4].string), (yyvsp[-3].number), (yyvsp[-2].string), (yyvsp[-1].number), (yyvsp[0].string));
													(yyval.string) = strdup(tuple);
												}
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 344 "test.y" /* yacc.c:1646  */
    {
					if(hashtag_counter == 0)
					{
						fprintf(stderr,"Error in line: %d\nInvalid extended tweet hashtags field.\n", yylineno);
						exit(1);
					}
					sprintf((yyval.string),"%s", (yyvsp[0].string));
				}
#line 1718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 353 "test.y" /* yacc.c:1646  */
    {
					if(hashtag_counter > 0)
					{
						fprintf(stderr,"Error in line: %d\nMissing extended tweet hashtags field.\n", yylineno);
						exit(1);
					}
				}
#line 1730 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 363 "test.y" /* yacc.c:1646  */
    {
													if(strcmp("\"entities\"", (yyvsp[-4].string)) != 0)
													{
														fprintf(stderr,"Error in line: %d\nInvalid extended tweet entities field.\n", yylineno);
														exit(1);
													}
													sprintf((yyval.string),"%s %s\n%s%s%s", (yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
												}
#line 1743 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 374 "test.y" /* yacc.c:1646  */
    {
													if(hashtag_counter > hashtag_parsed)
													{
														fprintf(stderr,"Error in line: %d\nMissing extended tweet hashtag.\n", yylineno);
														exit(1);
													}
													if(hashtag_counter < hashtag_parsed)
													{
														fprintf(stderr,"Error in line: %d\nInvalid extended tweet hashtag.\n", yylineno);
														exit(1);
													}
													if(strcmp("\"hashtags\"", (yyvsp[-4].string)) != 0)
													{
														fprintf(stderr,"Error in line: %d\nInvalid extended tweet hashtags field.\n", yylineno);
														exit(1);
													}
													sprintf((yyval.string),"%s %s\n%s\n%s\n%s", (yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
												}
#line 1766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 394 "test.y" /* yacc.c:1646  */
    {	(yyval.string) = strdup((yyvsp[0].string)); }
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 396 "test.y" /* yacc.c:1646  */
    {
				char* text;
				text = strdup((yyvsp[0].string));
				sprintf((yyval.string),"%s%s\n%s", (yyvsp[-2].string), (yyvsp[-1].string), text);
			}
#line 1782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 404 "test.y" /* yacc.c:1646  */
    {
										char* hashtag_text = (char*)malloc(sizeof(char) * (strlen(indice_text) + 1));
										strcat(hashtag_text, "#");
										indice_text[strlen(indice_text) - 1] = 0;
										strcat(hashtag_text, &indice_text[1]);
										char* hashtag_pointer = strstr(full_text, hashtag_text);
										if(hashtag_pointer == NULL)
										{
											fprintf(stderr,"Error in line: %d\nInvalid extended tweet indice field.\n", yylineno);
											exit(1);
										}
										int position = (int)(hashtag_pointer - full_text);
										if((indice_tuple_start != position) || (indice_tuple_end != (strlen(hashtag_text) + position)))
										{
											fprintf(stderr,"Error in line: %d\nInvalid extended tweet indice field.\n", yylineno);
											exit(1);
										}
										char* text = (char*)malloc(sizeof(char) * (strlen((yyvsp[-3].string)) + strlen((yyvsp[-2].string)) + strlen((yyvsp[-1].string)) + strlen((yyvsp[0].string))));	
										sprintf(text,"%s%s\n%s%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
										(yyval.string) = strdup(text);
										hashtag_parsed++;
									}
#line 1809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 429 "test.y" /* yacc.c:1646  */
    { 
									if(strcmp("\"text\"",(yyvsp[-3].string)) != 0)
									{
										fprintf(stderr,"Error in line: %d\nInvalid extended tweet text field.\n", yylineno);
										exit(1);
									}
									if((strlen((yyvsp[-1].string))>140))
									{
										fprintf(stderr,"Error in line: %d\nExtended tweet text field must have maximum 140 characters.\n", yylineno);
										exit(1);
									}
									indice_text = strdup((yyvsp[-1].string));
									sprintf((yyval.string), "%s %s %s%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
								}
#line 1828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 445 "test.y" /* yacc.c:1646  */
    {
											if(strcmp("\"indices\"", (yyvsp[-6].string)) != 0)
											{
												fprintf(stderr,"Error in line: %d\nInvalid extended tweet indice tuple field.\n", yylineno);
												exit(1);
											}
											char tuple[9];
											indice_tuple_start = (yyvsp[-3].number);
											indice_tuple_end = (yyvsp[-1].number);
											sprintf(tuple,"%s%d%s%d%s", (yyvsp[-4].string), (yyvsp[-3].number), (yyvsp[-2].string), (yyvsp[-1].number), (yyvsp[0].string));
											sprintf((yyval.string),"%s %s %s", (yyvsp[-6].string), (yyvsp[-5].string), tuple);
										}
#line 1845 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 460 "test.y" /* yacc.c:1646  */
    {
																				char* printf_string;
																				asprintf(&printf_string,"%s\n%s\n%s\n%s\n%s\n%s", (yyvsp[-5].string), (yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
																				int left_bracket_counter = 0;
																				int right_bracket_counter = 0;
																				for(int i = 0; i < strlen(printf_string); i++)
																				{
																					if(printf_string[i] == '{')
																					{
																						left_bracket_counter++;
																					}
																					if(printf_string[i] == '}')
																					{
																						right_bracket_counter++;
																					}
																					printf("%c",printf_string[i]);
																					if(printf_string[i] == '\n')
																					{
																						int j;
																						if(i+1 < strlen(printf_string) && printf_string[i+1] == '}')
																						{
																							for(j = 0; j < left_bracket_counter - right_bracket_counter - 1; j++)
																							{
																								printf("\t");
																							}
																						}
																						else
																						{
																							for(j = 0; j < left_bracket_counter - right_bracket_counter; j++)
																							{
																								printf("\t");
																							}
																						}
																					}
																				}
																			}
#line 1886 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 499 "test.y" /* yacc.c:1646  */
    {
																				char* printf_string;
																				asprintf(&printf_string,"%s%s%s%s%s", (yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
																				int left_bracket_counter = 0;
																				int right_bracket_counter = 0;
																				for(int i = 0; i < strlen(printf_string); i++)
																				{
																					if(printf_string[i] == '{')
																					{
																						left_bracket_counter++;
																					}
																					if(printf_string[i] == '}')
																					{
																						right_bracket_counter++;
																					}
																					printf("%c",printf_string[i]);
																					if(printf_string[i] == '\n')
																					{
																						int j;
																						if(i+1 < strlen(printf_string) && printf_string[i+1] == '}')
																						{
																							for(j = 0; j < left_bracket_counter - right_bracket_counter - 1; j++)
																							{
																								printf("\t");
																							}
																						}
																						else
																						{
																							for(j = 0; j < left_bracket_counter - right_bracket_counter; j++)
																							{
																								printf("\t");
																							}
																						}
																					}																				
																				}
																			}
#line 1927 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 538 "test.y" /* yacc.c:1646  */
    {
		if(strcmp("\"tweet\"",(yyvsp[-5].string)) != 0)
		{
			fprintf(stderr,"Error in line: %d\nInvalid retweet field.\n", yylineno);
			exit(1);
		}
		sprintf((yyval.string),"%s %s\n%s\n%s\n%s\n%s", (yyvsp[-5].string), (yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));	
	}
#line 1940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 549 "test.y" /* yacc.c:1646  */
    {
										char* retweeted_text = (char*)malloc(sizeof(char) * (strlen(retweeted_tweet_name) + strlen(retweeted_tweet_text) + 8));
										strcat(retweeted_text, "\"RT @");
										retweeted_tweet_name[strlen(retweeted_tweet_name) - 1] = ' ';
										strcat(retweeted_text, &retweeted_tweet_name[1]);
										retweeted_tweet_text[strlen(retweeted_tweet_text) - 1] = 0;
										strcat(retweeted_text, &retweeted_tweet_text[1]);
										strcat(retweeted_text, "\"");
										if((strcmp("\"text\"",(yyvsp[-2].string)) != 0) || (strlen((yyvsp[0].string))>140) || (strcmp(retweeted_text,(yyvsp[0].string)) != 0))
										{
											fprintf(stderr,"Error in line: %d\nInvalid retweet text field.\n", yylineno);
											exit(1);
										}
										sprintf((yyval.string), "%s %s %s", (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
									}
#line 1960 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 567 "test.y" /* yacc.c:1646  */
    {
		if(strcmp("\"user\"",(yyvsp[-4].string)) != 0)
		{
			fprintf(stderr,"Error in line: %d\nInvalid retweet user field.\n", yylineno);
			exit(1);
		}
		sprintf((yyval.string), "%s %s\n%s%s%s", (yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
	}
#line 1973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 578 "test.y" /* yacc.c:1646  */
    {
													if(strcmp("\"screen_name\"", (yyvsp[-2].string)) != 0)
													{
														fprintf(stderr,"Error in line: %d\nInvalid retweet screen name field.\n", yylineno);
														exit(1);
													}
													sprintf((yyval.string), "%s %s %s", (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
												}
#line 1986 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 589 "test.y" /* yacc.c:1646  */
    {
		if(strcmp("\"retweeted_status\"",(yyvsp[-5].string)) != 0)
		{
			fprintf(stderr,"Error in line: %d\nInvalid retweet status field.\n", yylineno);
			exit(1);
		}
		sprintf((yyval.string), "%s %s\n%s%s%s%s\n", (yyvsp[-5].string), (yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
	}
#line 1999 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 600 "test.y" /* yacc.c:1646  */
    {
										printf("\n");
										if((strcmp("\"text\"",(yyvsp[-2].string)) != 0) || (strlen((yyvsp[0].string))>140))
										{
											fprintf(stderr,"Error in line: %d\nInvalid retweet status text field.\n", yylineno);
											exit(1);
										}
										retweeted_tweet_text = strdup((yyvsp[0].string));
										sprintf((yyval.string), "%s %s %s\n", (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
									}
#line 2014 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 613 "test.y" /* yacc.c:1646  */
    {
		if(strcmp("\"user\"",(yyvsp[-4].string)) != 0)
		{
			fprintf(stderr,"Error in line: %d\nInvalid retweet status user field.\n", yylineno);
			exit(1);
		}
		sprintf((yyval.string), "%s %s\n%s%s%s", (yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
	}
#line 2027 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 624 "test.y" /* yacc.c:1646  */
    {
													if(strcmp("\"screen_name\"", (yyvsp[-2].string)) != 0)
													{
														fprintf(stderr,"Error in line: %d\nInvalid retweet status screen name field.\n", yylineno);
														exit(1);
													}
													retweeted_tweet_name = strdup((yyvsp[0].string));
													sprintf((yyval.string), "%s %s %s", (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
												}
#line 2041 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 636 "test.y" /* yacc.c:1646  */
    { 
									if((strcmp("\"text\"",(yyvsp[-3].string)) == 0) && (strlen((yyvsp[-1].string))>=140))
									{
										fprintf(stderr,"Error in line: %d\nInvalid tweet text field.\n", yylineno);
										exit(1);
									}
									sprintf((yyval.string), "%s %s %s%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
								}
#line 2054 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 647 "test.y" /* yacc.c:1646  */
    { 
									if(strcmp("\"created_at\"",(yyvsp[-3].string)) == 0)
									{
										split_string = strdup((yyvsp[-1].string));
										char* token = strtok(split_string, " "); 
										int index = 0;
										int flag = 0;
										while (token != NULL && index < 6) 
										{ 
											switch(index)
											{
												case 0: 
												for (counter = 0; counter < 7; counter++) 
												{ 														
													if(strcmp(days[counter], &token[1]) == 0)
													{
														flag = 1;
														break;
													}
												}
												if(flag == 0)
												{
													fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
													exit(1);
												}													
												break;
												case 1: 
												flag = 0;
												for (counter = 0; counter < 12; counter++) 
												{ 														
													if(strcmp(months[counter], token) == 0)
													{
														flag = 1;
														break;
													}
												}
												if(flag == 0)
												{
													fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
													exit(1);
												}													
												break;
												case 2: 
												{
													int day = atoi(token);
													if(day < 1 || day > 32)
													{
														fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
														exit(1);
													}
												}
												break;
												case 3: 
												{
													int time_counter = 0;
													int time_value;
													char* timestamp;
													char* timestamp_token;
													timestamp = strdup(token);
													timestamp_token = strtok(timestamp, ":");												
													while (timestamp_token != NULL && time_counter < 3) 
													{
														time_value = atoi(timestamp_token);
														if (time_counter == 0 )
														{
															if(time_value < 0 || time_value > 24)
															{
																fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
																exit(1);
															}
														}
														if(time_counter == 1)
														{
															if(time_value < 0 || time_value > 59)
															{
																fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
																exit(1);
															}
														}
														if(time_counter == 2)
														{	
															if(time_value < 0 || time_value > 59)
															{
																fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
																exit(1);
															}
														}
														timestamp_token = strtok(NULL, ":");
														time_counter++;
													}
												}
												break;
												case 4: 
												{
													int timezone = atoi(token);
													if(timezone < -13 || timezone > 13)
													{
														fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
														exit(1);
													}
												}
												break;
												case 5: 
												{
													token[4] = ' ';
													int year = atoi(token);
													if(year < 1900)
													{
														fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
														exit(1);
													}
												}
												break;
											}
											token = strtok(NULL, " ");
											index++;
										}
										sprintf((yyval.string),"%s %s %s%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
									}
								}
#line 2179 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 770 "test.y" /* yacc.c:1646  */
    { 
									if(strcmp("\"user\"",(yyvsp[-4].string)) != 0)
									{
										fprintf(stderr,"Error in line: %d\nInvalid tweet user field.\n", yylineno);
										exit(1);
									}
									sprintf((yyval.string),"%s %s\n%s%s%s", (yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
								}
#line 2192 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 781 "test.y" /* yacc.c:1646  */
    {
											sprintf((yyval.string),"%s\n%s\n%s\n%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
										}
#line 2200 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 787 "test.y" /* yacc.c:1646  */
    {																								
												if(strcmp("\"id\"", (yyvsp[-3].string)) == 0)
												{												
													for(counter = 0; counter < tweet_id_array_size; counter++)
													{
														if(tweet_id[counter] == (yyvsp[-1].number))
														{
															fprintf(stderr,"Error in line: %d\nDuplicate user id: %d.\n", yylineno, tweet_id[counter]);
															exit(1);
														}
													}
													if(tweet_id_array_size == tweet_id_array_max_size)
													{
														tweet_id_array_max_size = tweet_id_array_max_size + 10;
														tweet_id = (int*)realloc(tweet_id, sizeof(int)*tweet_id_array_max_size);
														tweet_id[tweet_id_array_size] = (yyvsp[-1].number);
														tweet_id_array_size++;
													}
													else
													{
														tweet_id[tweet_id_array_size] = (yyvsp[-1].number);
														tweet_id_array_size++;
													}
													sprintf((yyval.string),"%s %s %d%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].number), (yyvsp[0].string));
												}
											}
#line 2231 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 816 "test.y" /* yacc.c:1646  */
    {
													if(strcmp("\"name\"", (yyvsp[-3].string)) != 0)
													{
														fprintf(stderr,"Error in line: %d\nInvalid tweet name field.\n", yylineno);
														exit(1);
													}
													sprintf((yyval.string),"%s %s %s%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
												}
#line 2244 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 827 "test.y" /* yacc.c:1646  */
    {
													if(strcmp("\"screen_name\"", (yyvsp[-3].string)) != 0)
													{
														fprintf(stderr,"Error in line: %d\nInvalid tweet screen name field.\n", yylineno);
														exit(1);
													}
													sprintf((yyval.string), "%s %s %s%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string),(yyvsp[0].string));
												}
#line 2257 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 838 "test.y" /* yacc.c:1646  */
    {
													if(strcmp("\"location\"", (yyvsp[-3].string)) != 0)
													{
														fprintf(stderr,"Error in line: %d\nInvalid tweet location field.\n", yylineno);
														exit(1);
													}
													sprintf((yyval.string),"%s %s %s%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
												}
#line 2270 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 849 "test.y" /* yacc.c:1646  */
    {
														if(strcmp("\"id_str\"", (yyvsp[-3].string)) == 0)
														{
															input_string = strdup((yyvsp[-1].string));
															id_string = strtoll(&input_string[1],NULL,10);
															if(id_string < 0)
															{
																fprintf(stderr,"Error in line: %d\nNegative id string.\n", yylineno);
																exit(1);
															}
															for(counter = 0; counter < tweet_id_string_array_size; counter++)
															{
																if(tweet_id_string[counter] == id_string)
																{
																	fprintf(stderr,"Error in line: %d\nDuplicate id string: %d.\n", yylineno, tweet_id[counter]);
																	exit(1);
																}
															}
															if(tweet_id_string_array_size == tweet_id_string_array_max_size)
															{
																tweet_id_string_array_max_size = tweet_id_string_array_max_size + 10;
																tweet_id_string = (long long int *)realloc(tweet_id_string, sizeof(long long int) * tweet_id_string_array_max_size);
																tweet_id_string[tweet_id_string_array_size] = id_string;
																tweet_id_string_array_size++;
															}
															else
															{
																tweet_id_string[tweet_id_string_array_size] = id_string;
																tweet_id_string_array_size++;
															}
															sprintf((yyval.string),"%s %s %s%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[0].string));
														}
													}
#line 2308 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 884 "test.y" /* yacc.c:1646  */
    { asprintf(&(yyval.string),"%d", (yyvsp[0].number)); }
#line 2314 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 885 "test.y" /* yacc.c:1646  */
    { asprintf(&(yyval.string),"%d", (yyvsp[0].number)); }
#line 2320 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 886 "test.y" /* yacc.c:1646  */
    { asprintf(&(yyval.string),"%g", (yyvsp[0].real)); }
#line 2326 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 887 "test.y" /* yacc.c:1646  */
    { sprintf((yyval.string),"%s", (yyvsp[0].string)); }
#line 2332 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 890 "test.y" /* yacc.c:1646  */
    { asprintf(&(yyval.string),"%d%s%+d", (yyvsp[-2].number), (yyvsp[-1].string), (yyvsp[0].number)); }
#line 2338 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 891 "test.y" /* yacc.c:1646  */
    { asprintf(&(yyval.string),"%d%s%+d", (yyvsp[-2].number), (yyvsp[-1].string), (yyvsp[0].number)); }
#line 2344 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 892 "test.y" /* yacc.c:1646  */
    { asprintf(&(yyval.string),"%g%s%+d", (yyvsp[-2].real), (yyvsp[-1].string), (yyvsp[0].number)); }
#line 2350 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2354 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 894 "test.y" /* yacc.c:1906  */


void yyerror(char const *s) 
{
    fprintf(stderr,"\nError: %s\nLine: %d\nToken: %s\n", s, yylineno, yytext);
	exit(1);
}									


int main ( int argc, char **argv  ) 
{
	tweet_id = (int*)malloc(sizeof(int) * tweet_id_array_max_size);
	tweet_id_string = (long long int*)malloc(sizeof(long long int) * tweet_id_string_array_max_size);
	++argv; --argc;
	if ( argc > 0 )
		yyin = fopen( argv[0], "r" );
	else
		yyin = stdin;
	yyparse ();
	fprintf(stderr, "%s", "\n\nParsing was completed successfully\n");
	return 0;
}   
