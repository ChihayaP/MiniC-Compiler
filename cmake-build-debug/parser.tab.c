/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "../parser.y"



#include <string.h>
#include "../ast.h"
#include <stdio.h>
#include <stdlib.h>
extern int yylineno;
extern char *yytext;

void yyerror(const char *msg);
int yylex();


#line 86 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_VOID = 4,                       /* VOID  */
  YYSYMBOL_RETURN = 5,                     /* RETURN  */
  YYSYMBOL_EQ = 6,                         /* EQ  */
  YYSYMBOL_NEQ = 7,                        /* NEQ  */
  YYSYMBOL_AND = 8,                        /* AND  */
  YYSYMBOL_OR = 9,                         /* OR  */
  YYSYMBOL_GTE = 10,                       /* GTE  */
  YYSYMBOL_LTE = 11,                       /* LTE  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_BREAK = 15,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 16,                  /* CONTINUE  */
  YYSYMBOL_IDENT = 17,                     /* IDENT  */
  YYSYMBOL_INT_CONST = 18,                 /* INT_CONST  */
  YYSYMBOL_LT_ELSE = 19,                   /* LT_ELSE  */
  YYSYMBOL_20_ = 20,                       /* '('  */
  YYSYMBOL_21_ = 21,                       /* ')'  */
  YYSYMBOL_22_ = 22,                       /* ','  */
  YYSYMBOL_23_ = 23,                       /* '['  */
  YYSYMBOL_24_ = 24,                       /* ']'  */
  YYSYMBOL_25_ = 25,                       /* '{'  */
  YYSYMBOL_26_ = 26,                       /* '}'  */
  YYSYMBOL_27_ = 27,                       /* ';'  */
  YYSYMBOL_28_ = 28,                       /* '='  */
  YYSYMBOL_29_ = 29,                       /* '<'  */
  YYSYMBOL_30_ = 30,                       /* '>'  */
  YYSYMBOL_31_ = 31,                       /* '+'  */
  YYSYMBOL_32_ = 32,                       /* '-'  */
  YYSYMBOL_33_ = 33,                       /* '*'  */
  YYSYMBOL_34_ = 34,                       /* '/'  */
  YYSYMBOL_35_ = 35,                       /* '%'  */
  YYSYMBOL_36_ = 36,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_program = 38,                   /* program  */
  YYSYMBOL_CompUnit = 39,                  /* CompUnit  */
  YYSYMBOL_FuncDef = 40,                   /* FuncDef  */
  YYSYMBOL_FuncFParams = 41,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 42,                /* FuncFParam  */
  YYSYMBOL_FuncType = 43,                  /* FuncType  */
  YYSYMBOL_Block = 44,                     /* Block  */
  YYSYMBOL_BlockItem = 45,                 /* BlockItem  */
  YYSYMBOL_Decl = 46,                      /* Decl  */
  YYSYMBOL_VarDecl = 47,                   /* VarDecl  */
  YYSYMBOL_VarArray = 48,                  /* VarArray  */
  YYSYMBOL_BType = 49,                     /* BType  */
  YYSYMBOL_Stmt = 50,                      /* Stmt  */
  YYSYMBOL_Cond = 51,                      /* Cond  */
  YYSYMBOL_Exp = 52,                       /* Exp  */
  YYSYMBOL_LOrExp = 53,                    /* LOrExp  */
  YYSYMBOL_LAndExp = 54,                   /* LAndExp  */
  YYSYMBOL_LVal = 55,                      /* LVal  */
  YYSYMBOL_Array = 56,                     /* Array  */
  YYSYMBOL_EqExp = 57,                     /* EqExp  */
  YYSYMBOL_RelExp = 58,                    /* RelExp  */
  YYSYMBOL_AddExp = 59,                    /* AddExp  */
  YYSYMBOL_MulExp = 60,                    /* MulExp  */
  YYSYMBOL_UnaryExp = 61,                  /* UnaryExp  */
  YYSYMBOL_PrimaryExp = 62,                /* PrimaryExp  */
  YYSYMBOL_Number = 63                     /* Number  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   156

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   274


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,     2,     2,    35,     2,     2,
      20,    21,    33,    31,    22,    32,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    27,
      29,    28,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    23,     2,    24,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,    26,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    41,    41,    45,    46,    47,    48,    52,    53,    57,
      58,    62,    63,    64,    68,    69,    73,    74,    78,    79,
      80,    81,    85,    89,    90,    91,    92,    96,    97,   101,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   119,   123,   127,   128,   132,   133,   137,   138,   142,
     143,   147,   148,   149,   153,   154,   155,   156,   157,   161,
     162,   163,   167,   168,   169,   170,   174,   175,   176,   177,
     181,   182,   183,   187
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "VOID",
  "RETURN", "EQ", "NEQ", "AND", "OR", "GTE", "LTE", "IF", "ELSE", "WHILE",
  "BREAK", "CONTINUE", "IDENT", "INT_CONST", "LT_ELSE", "'('", "')'",
  "','", "'['", "']'", "'{'", "'}'", "';'", "'='", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'!'", "$accept", "program", "CompUnit",
  "FuncDef", "FuncFParams", "FuncFParam", "FuncType", "Block", "BlockItem",
  "Decl", "VarDecl", "VarArray", "BType", "Stmt", "Cond", "Exp", "LOrExp",
  "LAndExp", "LVal", "Array", "EqExp", "RelExp", "AddExp", "MulExp",
  "UnaryExp", "PrimaryExp", "Number", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-82)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      73,   -82,   -82,    10,   -82,    73,    -1,    73,    14,   -82,
     -82,     1,   -82,    58,     8,     4,    14,    24,    31,   -82,
     -82,    32,    28,    38,    56,   -82,    65,    14,    12,   -82,
      32,    63,    80,    99,   -82,    87,    76,   110,   109,   111,
     114,   -82,    95,   -82,   -82,    95,    95,    95,   -82,   113,
      47,    47,   115,   131,   133,   116,    92,    81,    77,    36,
     -82,   -82,   -82,   -82,   -82,    27,   -82,   -82,   -82,   118,
     -82,    95,    95,   -82,   -82,    95,   -82,   122,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    99,
     -82,   125,   131,   126,   124,   -82,   133,    92,   123,    81,
      81,    77,    77,    77,    77,    36,    36,   -82,   -82,   -82,
     -82,    70,    70,   114,   -82,   136,   -82,   -82,    70,   -82
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    14,    15,     0,     2,     3,     0,     4,     0,     1,
       5,     0,     6,    23,     0,     0,     0,     0,    25,    22,
      29,     0,     0,     9,     0,    24,     0,     0,     0,     7,
       0,     0,    11,    27,    26,     0,     0,     0,     0,     0,
      47,    73,     0,    17,    32,     0,     0,     0,    30,     0,
      18,    19,     0,    42,    43,    72,    45,    51,    54,    59,
      62,    66,    71,     8,    10,     0,    12,    28,    36,     0,
      72,     0,     0,    33,    34,     0,    48,     0,    67,    68,
      69,    16,    20,    21,    31,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,     0,    41,     0,     0,    70,    44,    46,     0,    52,
      53,    58,    57,    55,    56,    60,    61,    63,    64,    65,
      13,     0,     0,    49,    37,    40,    38,    50,     0,    39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -82,   -82,     7,   -82,   120,   -82,   -82,   -12,    66,   -17,
      -8,   -31,     5,   -81,    82,   -29,    49,    67,   -28,    33,
      69,    40,    42,    30,   -42,   -82,   -82
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,    22,    23,     6,    48,    49,     7,
      14,    18,     8,    51,   101,    52,    53,    54,    70,    76,
      56,    57,    58,    59,    60,    61,    62
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      55,    66,    67,    78,    79,    80,    69,    20,    25,    29,
       9,    50,    10,    77,    12,    20,    11,    35,    63,    34,
      24,    15,    55,    55,    36,    21,    37,    38,    39,    40,
      41,    13,    42,    50,    50,    19,    24,    28,    43,    44,
     125,   126,    26,    45,    46,    26,   104,   129,    47,    30,
      20,    99,    35,    27,   117,   118,   119,    28,   108,    36,
      31,    37,    38,    39,    40,    41,    20,    42,   120,    96,
      97,    98,    28,    32,    44,    35,     1,     2,    45,    46,
      16,    17,    36,    47,    37,    38,    39,    40,    41,    33,
      42,    90,    91,    55,    55,    28,    71,    44,    88,    89,
      55,    45,    46,    65,    40,    41,    47,    42,    94,    95,
      92,    93,    40,    41,    68,    42,    82,    83,    45,    46,
     102,   102,    17,    47,   115,   116,    45,    46,   109,   110,
      72,    47,   111,   112,   113,   114,    73,    75,    74,    81,
      85,    86,    84,   105,    87,   100,   121,   122,   123,   128,
     124,    64,   106,     0,   103,   107,   127
};

static const yytype_int16 yycheck[] =
{
      28,    32,    33,    45,    46,    47,    35,     3,    16,    21,
       0,    28,     5,    42,     7,     3,    17,     5,    30,    27,
      15,    20,    50,    51,    12,    21,    14,    15,    16,    17,
      18,    17,    20,    50,    51,    27,    31,    25,    26,    27,
     121,   122,    18,    31,    32,    18,    75,   128,    36,    21,
       3,    24,     5,    22,    96,    97,    98,    25,    87,    12,
      22,    14,    15,    16,    17,    18,     3,    20,    99,    33,
      34,    35,    25,    17,    27,     5,     3,     4,    31,    32,
      22,    23,    12,    36,    14,    15,    16,    17,    18,    24,
      20,    10,    11,   121,   122,    25,    20,    27,     6,     7,
     128,    31,    32,    23,    17,    18,    36,    20,    31,    32,
      29,    30,    17,    18,    27,    20,    50,    51,    31,    32,
      71,    72,    23,    36,    94,    95,    31,    32,    88,    89,
      20,    36,    90,    91,    92,    93,    27,    23,    27,    26,
       9,     8,    27,    21,    28,    27,    21,    21,    24,    13,
      27,    31,    85,    -1,    72,    86,   123
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,    38,    39,    40,    43,    46,    49,     0,
      39,    17,    39,    17,    47,    20,    22,    23,    48,    27,
       3,    21,    41,    42,    49,    47,    18,    22,    25,    44,
      21,    22,    17,    24,    47,     5,    12,    14,    15,    16,
      17,    18,    20,    26,    27,    31,    32,    36,    44,    45,
      46,    50,    52,    53,    54,    55,    57,    58,    59,    60,
      61,    62,    63,    44,    41,    23,    48,    48,    27,    52,
      55,    20,    20,    27,    27,    23,    56,    52,    61,    61,
      61,    26,    45,    45,    27,     9,     8,    28,     6,     7,
      10,    11,    29,    30,    31,    32,    33,    34,    35,    24,
      27,    51,    53,    51,    52,    21,    54,    57,    52,    58,
      58,    59,    59,    59,    59,    60,    60,    61,    61,    61,
      48,    21,    21,    24,    27,    50,    50,    56,    13,    50
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    39,    39,    39,    39,    40,    40,    41,
      41,    42,    42,    42,    43,    43,    44,    44,    45,    45,
      45,    45,    46,    47,    47,    47,    47,    48,    48,    49,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    51,    52,    53,    53,    54,    54,    55,    55,    56,
      56,    57,    57,    57,    58,    58,    58,    58,    58,    59,
      59,    59,    60,    60,    60,    60,    61,    61,    61,    61,
      62,    62,    62,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     2,     5,     6,     1,
       3,     2,     3,     5,     1,     1,     3,     2,     1,     1,
       2,     2,     3,     1,     3,     2,     4,     3,     4,     1,
       1,     2,     1,     2,     2,     3,     2,     4,     5,     7,
       5,     1,     1,     1,     3,     1,     3,     1,     2,     3,
       4,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     2,
       3,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* program: CompUnit  */
#line 41 "../parser.y"
              {storeAstRoot((yyvsp[0].ptr));}
#line 1222 "parser.tab.c"
    break;

  case 3: /* CompUnit: FuncDef  */
#line 45 "../parser.y"
                      {(yyval.ptr)=mknode(_COMP_FUNCDEF,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1228 "parser.tab.c"
    break;

  case 4: /* CompUnit: Decl  */
#line 46 "../parser.y"
                      {(yyval.ptr)=mknode(_GLO_DECL,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1234 "parser.tab.c"
    break;

  case 5: /* CompUnit: FuncDef CompUnit  */
#line 47 "../parser.y"
                      {(yyval.ptr)=mknode(_COMP_FUNCDEF_COMP,(yyvsp[-1].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"compUnit");}
#line 1240 "parser.tab.c"
    break;

  case 6: /* CompUnit: Decl CompUnit  */
#line 48 "../parser.y"
                      {(yyval.ptr)=mknode(_GLO_DECL_COMP,(yyvsp[-1].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"compUnit");}
#line 1246 "parser.tab.c"
    break;

  case 7: /* FuncDef: FuncType IDENT '(' ')' Block  */
#line 52 "../parser.y"
                                 {(yyval.ptr)=mknode(_FUNCDEF,(yyvsp[-4].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[-3].type_id));}
#line 1252 "parser.tab.c"
    break;

  case 8: /* FuncDef: FuncType IDENT '(' FuncFParams ')' Block  */
#line 53 "../parser.y"
                                             {(yyval.ptr)=mknode(_FUNCDEF,(yyvsp[-5].ptr),(yyvsp[-2].ptr),(yyvsp[0].ptr),yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[-4].type_id));}
#line 1258 "parser.tab.c"
    break;

  case 9: /* FuncFParams: FuncFParam  */
#line 57 "../parser.y"
                                {(yyval.ptr)=mknode(_FUNCFPARAM,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1264 "parser.tab.c"
    break;

  case 10: /* FuncFParams: FuncFParam ',' FuncFParams  */
#line 58 "../parser.y"
                                {(yyval.ptr)=mknode(_FUNCFPARAM_COMMA,(yyvsp[-2].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,",");}
#line 1270 "parser.tab.c"
    break;

  case 11: /* FuncFParam: BType IDENT  */
#line 62 "../parser.y"
                                  {(yyval.ptr)=mknode(_PARAM,(yyvsp[-1].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));}
#line 1276 "parser.tab.c"
    break;

  case 12: /* FuncFParam: BType IDENT VarArray  */
#line 63 "../parser.y"
                                  {(yyval.ptr)=mknode(_PARAM_VARARR,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[-1].type_id));}
#line 1282 "parser.tab.c"
    break;

  case 13: /* FuncFParam: BType IDENT '[' ']' VarArray  */
#line 64 "../parser.y"
                                  {(yyval.ptr)=mknode(_PARAM_NULL,(yyvsp[-4].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[-3].type_id));}
#line 1288 "parser.tab.c"
    break;

  case 14: /* FuncType: INT  */
#line 68 "../parser.y"
          {(yyval.ptr)=mknode(_INT,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"int");}
#line 1294 "parser.tab.c"
    break;

  case 15: /* FuncType: VOID  */
#line 69 "../parser.y"
          {(yyval.ptr)=mknode(_VOID,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"void");}
#line 1300 "parser.tab.c"
    break;

  case 16: /* Block: '{' BlockItem '}'  */
#line 73 "../parser.y"
                      {(yyval.ptr)=mknode(_BLOCKITEM,(yyvsp[-1].ptr),NULL,NULL,yylineno);}
#line 1306 "parser.tab.c"
    break;

  case 17: /* Block: '{' '}'  */
#line 74 "../parser.y"
                      {(yyval.ptr)=mknode(_BLOCKITEMNULL,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"\\{\\}");}
#line 1312 "parser.tab.c"
    break;

  case 18: /* BlockItem: Decl  */
#line 78 "../parser.y"
                      {(yyval.ptr)=mknode(_DECL,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1318 "parser.tab.c"
    break;

  case 19: /* BlockItem: Stmt  */
#line 79 "../parser.y"
                      {(yyval.ptr)=mknode(_STMT,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1324 "parser.tab.c"
    break;

  case 20: /* BlockItem: Decl BlockItem  */
#line 80 "../parser.y"
                      {(yyval.ptr)=mknode(_DECL_BLOCKITEM,(yyvsp[-1].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"blockItem");}
#line 1330 "parser.tab.c"
    break;

  case 21: /* BlockItem: Stmt BlockItem  */
#line 81 "../parser.y"
                      {(yyval.ptr)=mknode(_STMT_BLOCKITEM,(yyvsp[-1].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"blockItem");}
#line 1336 "parser.tab.c"
    break;

  case 22: /* Decl: BType VarDecl ';'  */
#line 85 "../parser.y"
                      {(yyval.ptr)=mknode(_VARDECL,(yyvsp[-2].ptr),(yyvsp[-1].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"varDecl");}
#line 1342 "parser.tab.c"
    break;

  case 23: /* VarDecl: IDENT  */
#line 89 "../parser.y"
                      {(yyval.ptr)=mknode(_IDENT_ONLY_DECL,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));}
#line 1348 "parser.tab.c"
    break;

  case 24: /* VarDecl: IDENT ',' VarDecl  */
#line 90 "../parser.y"
                      {(yyval.ptr)=mknode(_IDENT_COMMA,(yyvsp[0].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,strcat((yyvsp[-2].type_id),","));}
#line 1354 "parser.tab.c"
    break;

  case 25: /* VarDecl: IDENT VarArray  */
#line 91 "../parser.y"
                      {(yyval.ptr)=mknode(_IDENT_VARARR,(yyvsp[0].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[-1].type_id));}
#line 1360 "parser.tab.c"
    break;

  case 26: /* VarDecl: IDENT VarArray ',' VarDecl  */
#line 92 "../parser.y"
                               {(yyval.ptr)=mknode(_IDENT_VARARR_COMMA,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,strcat((yyvsp[-3].type_id),","));}
#line 1366 "parser.tab.c"
    break;

  case 27: /* VarArray: '[' INT_CONST ']'  */
#line 96 "../parser.y"
                                {(yyval.ptr)=mknode(_VARARR_ONLY,NULL,NULL,NULL,yylineno);(yyval.ptr)->type_int,(yyvsp[-1].type_int);}
#line 1372 "parser.tab.c"
    break;

  case 28: /* VarArray: '[' INT_CONST ']' VarArray  */
#line 97 "../parser.y"
                                {(yyval.ptr)=mknode(_VARARR_WITH,(yyvsp[0].ptr),NULL,NULL,yylineno);(yyval.ptr)->type_int,(yyvsp[-2].type_int);}
#line 1378 "parser.tab.c"
    break;

  case 29: /* BType: INT  */
#line 101 "../parser.y"
        {(yyval.ptr)=mknode(_INT,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"int");}
#line 1384 "parser.tab.c"
    break;

  case 30: /* Stmt: Block  */
#line 105 "../parser.y"
                      {(yyval.ptr)=mknode(_BLOCK,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1390 "parser.tab.c"
    break;

  case 31: /* Stmt: Exp ';'  */
#line 106 "../parser.y"
                      {(yyval.ptr)=mknode(_EXP_SEMI,(yyvsp[-1].ptr),NULL,NULL,yylineno);}
#line 1396 "parser.tab.c"
    break;

  case 32: /* Stmt: ';'  */
#line 107 "../parser.y"
                      {(yyval.ptr)=mknode(_SEMI,NULL,NULL,NULL,yylineno);}
#line 1402 "parser.tab.c"
    break;

  case 33: /* Stmt: BREAK ';'  */
#line 108 "../parser.y"
                      {(yyval.ptr)=mknode(_BREAK,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"break");}
#line 1408 "parser.tab.c"
    break;

  case 34: /* Stmt: CONTINUE ';'  */
#line 109 "../parser.y"
                      {(yyval.ptr)=mknode(_CONTINUE,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"continue");}
#line 1414 "parser.tab.c"
    break;

  case 35: /* Stmt: RETURN Exp ';'  */
#line 110 "../parser.y"
                      {(yyval.ptr)=mknode(_RETURN,(yyvsp[-1].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"return");}
#line 1420 "parser.tab.c"
    break;

  case 36: /* Stmt: RETURN ';'  */
#line 111 "../parser.y"
                      {(yyval.ptr)=mknode(_RETURN_SEMI,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"return;");}
#line 1426 "parser.tab.c"
    break;

  case 37: /* Stmt: LVal '=' Exp ';'  */
#line 112 "../parser.y"
                      {(yyval.ptr)=mknode(_LVAL_ASSIGN,(yyvsp[-3].ptr),(yyvsp[-1].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"=");}
#line 1432 "parser.tab.c"
    break;

  case 38: /* Stmt: WHILE '(' Cond ')' Stmt  */
#line 113 "../parser.y"
                                       {(yyval.ptr)=mknode(_WHILE,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"while");}
#line 1438 "parser.tab.c"
    break;

  case 39: /* Stmt: IF '(' Cond ')' Stmt ELSE Stmt  */
#line 114 "../parser.y"
                                       {(yyval.ptr)=mknode(_IF_ELSE,(yyvsp[-4].ptr),(yyvsp[-2].ptr),(yyvsp[0].ptr),yylineno);strcpy((yyval.ptr)->type_id,"if");}
#line 1444 "parser.tab.c"
    break;

  case 40: /* Stmt: IF '(' Cond ')' Stmt  */
#line 115 "../parser.y"
                                       {(yyval.ptr)=mknode(_IF,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"if");}
#line 1450 "parser.tab.c"
    break;

  case 41: /* Cond: LOrExp  */
#line 119 "../parser.y"
            {(yyval.ptr)=mknode(_COND,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1456 "parser.tab.c"
    break;

  case 42: /* Exp: LOrExp  */
#line 123 "../parser.y"
            {(yyval.ptr)=mknode(_LOREXP,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1462 "parser.tab.c"
    break;

  case 43: /* LOrExp: LAndExp  */
#line 127 "../parser.y"
                      {(yyval.ptr)=mknode(_LANDEXP,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1468 "parser.tab.c"
    break;

  case 44: /* LOrExp: LOrExp OR LAndExp  */
#line 128 "../parser.y"
                      {(yyval.ptr)=mknode(_OR,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"||");}
#line 1474 "parser.tab.c"
    break;

  case 45: /* LAndExp: EqExp  */
#line 132 "../parser.y"
                      {(yyval.ptr)=mknode(_EQEXP,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1480 "parser.tab.c"
    break;

  case 46: /* LAndExp: LAndExp AND EqExp  */
#line 133 "../parser.y"
                      {(yyval.ptr)=mknode(_AND,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"&&");}
#line 1486 "parser.tab.c"
    break;

  case 47: /* LVal: IDENT  */
#line 137 "../parser.y"
                      {(yyval.ptr)=mknode(_IDENT_ONLY,NULL,NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));}
#line 1492 "parser.tab.c"
    break;

  case 48: /* LVal: IDENT Array  */
#line 138 "../parser.y"
                      {(yyval.ptr)=mknode(_IDENT_ARR,(yyvsp[0].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[-1].type_id));}
#line 1498 "parser.tab.c"
    break;

  case 49: /* Array: '[' Exp ']'  */
#line 142 "../parser.y"
                      {(yyval.ptr)=mknode(_ARR_ONLY,(yyvsp[-1].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"[]");}
#line 1504 "parser.tab.c"
    break;

  case 50: /* Array: '[' Exp ']' Array  */
#line 143 "../parser.y"
                      {(yyval.ptr)=mknode(_ARR_WITH,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"[]");}
#line 1510 "parser.tab.c"
    break;

  case 51: /* EqExp: RelExp  */
#line 147 "../parser.y"
                      {(yyval.ptr)=mknode(_RELEXP,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1516 "parser.tab.c"
    break;

  case 52: /* EqExp: EqExp EQ RelExp  */
#line 148 "../parser.y"
                      {(yyval.ptr)=mknode(_EQ,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"==");}
#line 1522 "parser.tab.c"
    break;

  case 53: /* EqExp: EqExp NEQ RelExp  */
#line 149 "../parser.y"
                      {(yyval.ptr)=mknode(_NEQ,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"!=");}
#line 1528 "parser.tab.c"
    break;

  case 54: /* RelExp: AddExp  */
#line 153 "../parser.y"
                      {(yyval.ptr)=mknode(_ADDEXP,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1534 "parser.tab.c"
    break;

  case 55: /* RelExp: RelExp '<' AddExp  */
#line 154 "../parser.y"
                      {(yyval.ptr)=mknode(_LT,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"\\<");}
#line 1540 "parser.tab.c"
    break;

  case 56: /* RelExp: RelExp '>' AddExp  */
#line 155 "../parser.y"
                      {(yyval.ptr)=mknode(_GT,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"\\>");}
#line 1546 "parser.tab.c"
    break;

  case 57: /* RelExp: RelExp LTE AddExp  */
#line 156 "../parser.y"
                      {(yyval.ptr)=mknode(_LTE,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"\\<=");}
#line 1552 "parser.tab.c"
    break;

  case 58: /* RelExp: RelExp GTE AddExp  */
#line 157 "../parser.y"
                      {(yyval.ptr)=mknode(_GTE,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"\\>=");}
#line 1558 "parser.tab.c"
    break;

  case 59: /* AddExp: MulExp  */
#line 161 "../parser.y"
                      {(yyval.ptr)=mknode(_MULEXP,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1564 "parser.tab.c"
    break;

  case 60: /* AddExp: AddExp '+' MulExp  */
#line 162 "../parser.y"
                      {(yyval.ptr)=mknode(_PLUS,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"+");}
#line 1570 "parser.tab.c"
    break;

  case 61: /* AddExp: AddExp '-' MulExp  */
#line 163 "../parser.y"
                      {(yyval.ptr)=mknode(_MINUS,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"-");}
#line 1576 "parser.tab.c"
    break;

  case 62: /* MulExp: UnaryExp  */
#line 167 "../parser.y"
                        {(yyval.ptr)=mknode(_UNARYEXP,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1582 "parser.tab.c"
    break;

  case 63: /* MulExp: MulExp '*' UnaryExp  */
#line 168 "../parser.y"
                        {(yyval.ptr)=mknode(_MUL,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"*");}
#line 1588 "parser.tab.c"
    break;

  case 64: /* MulExp: MulExp '/' UnaryExp  */
#line 169 "../parser.y"
                        {(yyval.ptr)=mknode(_DIV,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"/");}
#line 1594 "parser.tab.c"
    break;

  case 65: /* MulExp: MulExp '%' UnaryExp  */
#line 170 "../parser.y"
                        {(yyval.ptr)=mknode(_MOD,(yyvsp[-2].ptr),(yyvsp[0].ptr),NULL,yylineno);strcpy((yyval.ptr)->type_id,"%");}
#line 1600 "parser.tab.c"
    break;

  case 66: /* UnaryExp: PrimaryExp  */
#line 174 "../parser.y"
                  {(yyval.ptr)=mknode(_PRIMARYEXP,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1606 "parser.tab.c"
    break;

  case 67: /* UnaryExp: '+' UnaryExp  */
#line 175 "../parser.y"
                  {(yyval.ptr)=mknode(_POSI,(yyvsp[0].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"+");}
#line 1612 "parser.tab.c"
    break;

  case 68: /* UnaryExp: '-' UnaryExp  */
#line 176 "../parser.y"
                  {(yyval.ptr)=mknode(_NEGA,(yyvsp[0].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"-");}
#line 1618 "parser.tab.c"
    break;

  case 69: /* UnaryExp: '!' UnaryExp  */
#line 177 "../parser.y"
                  {(yyval.ptr)=mknode(_NOT,(yyvsp[0].ptr),NULL,NULL,yylineno);strcpy((yyval.ptr)->type_id,"!");}
#line 1624 "parser.tab.c"
    break;

  case 70: /* PrimaryExp: '(' Exp ')'  */
#line 181 "../parser.y"
                {(yyval.ptr)=mknode(_EXP,(yyvsp[-1].ptr),NULL,NULL,yylineno);}
#line 1630 "parser.tab.c"
    break;

  case 71: /* PrimaryExp: Number  */
#line 182 "../parser.y"
                {(yyval.ptr)=mknode(_NUMBER,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1636 "parser.tab.c"
    break;

  case 72: /* PrimaryExp: LVal  */
#line 183 "../parser.y"
                {(yyval.ptr)=mknode(_LVAL,(yyvsp[0].ptr),NULL,NULL,yylineno);}
#line 1642 "parser.tab.c"
    break;

  case 73: /* Number: INT_CONST  */
#line 187 "../parser.y"
              {(yyval.ptr)=mknode(_INT_CONST,NULL,NULL,NULL,yylineno);(yyval.ptr)->type_int=(yyvsp[0].type_int);}
#line 1648 "parser.tab.c"
    break;


#line 1652 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 190 "../parser.y"



void yyerror(const char *msg)
{
    printf("%d:  %s  at  '%s'  \n",yylineno,msg,yytext);
}
