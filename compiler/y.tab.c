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
#line 1 "grammar.y" /* yacc.c:339  */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <typeinfo>
#include "symtabold.h"
int GPUCODEFLAG=0;
int ERRPRINT;
extern int morph_size,TOT_GPU_GRAPH,MORPH_FLAG;//yes
extern int union_type,errflag,pdim_size;
extern FILE *FP,*FP1,*FPG,*fp1;
extern std::map<char *,int>newitr;
extern std::map<char *,int>newitrdtype;
extern  std::map<char *,statement *>fnames;//function definition
extern std::map<char *,statement *>fnamescond;//foreach call of function in char *with conditional
class statement *G1=NULL,*head=NULL,*temp=NULL,*temp1=NULL /*keeps track of second last statement parsed*/,*temp3=NULL /*keeps track of last statement parsed*/ ,*de1,*de2;
int nitr=11,STMTNO=0,macroflag=-1;
int KERNEL=0,PEER_ENABLE;
int FOREACH_FUN_FLAG;
int ariflag=0,LINENO=1,arglistflag=0;
globsymtable GLOBAL_TABLE;
int GALOIS_FLAG;
char *mainfunarr;
volatile int vartop;
extern void setparent();
extern char *union_string[2];
extern char *morphalloc_string[3];
extern FILE *yyin;
globsymtable *currsymtab=&GLOBAL_TABLE, *stemp;
char  *utflagarr[2][3]={{"3","+1","+2"},{"2","","+1"}};
int utflag=1;
int FUNCALL_FLAG=0,INNBRFLAG,OUTNBRFLAG;
char header[100],source[100],gheader[100],*tempitr=NULL;
struct funcall_list *fhead=NULL;//declared in tree.h
char *dtypenames[]={"int ","float ","short ","double ","char ","long ","void ","signed ","unsigned ","bool","...","struct ","struct_rec","enum","union ","typedef "};
char *libdtypenames[10]={"graph ","edge ","point ","set ","collection","g_p ","e_p ","g_p ","ITR","LINT"};
char *libdtypefields[5][8]={ { "npoints" ,"points","nedges","edges","directed","twod","isdel","XXXXX"},{"src","dst","weight","isdel","XXXXX","XXXXX","XXXXX","XXXXX"},{"minEdge","maxEdge","x","y","nbrs","inNbrs","outNbrs","isdel"},{"parent","size","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST"},{"size","PORST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST"}};
char *libdtypefunctions[5][19]={ { "addPoint" ,"read","addEdge","deledge","delpoint","getweight","addProperty","addPointProperty","addEdgeProperty","init","reset","getedge","readNodes","read2","read1","redmorph","OutDegree","InDegree","UpdatePartition"},
{"del","setweight","changesrc","changedst","reset","init","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST"},
{"getNeighbours","getInNeighbours","getOutNeighbours","del","addNeighbour","delNeighbour","reset","init","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST"},
{"makeset","merge","find","getSize","clear","Union","Merge","Findcompress","init","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST"},
{"add","del","merge","getSize","clear","reset","init","OrderByIntValue","empty","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST","PQRST"}};
char *exptypename[ ]={"+","-","*","/","%","&&","||","^","&","|","~","+","*","-","&","|","&","*","!","++","--","++","--","sizeof","align","[","<<",">>","<",">","<=",">=","==","!=","","","","","->","","","\(","",""};
char *libfunctions[]={"MIN","MAX","INCR","DECR","CAS","ADD","SUB","OR","AND","XOR","genericbarrier"};
char *libpartitionfunctions[]={">","<","+=1","-=1","CAS","+=","-=","||=","&&=","~=","genericbarrier"};
char *iternames[]={"points ", "edges ", "nbrs ", "innbrs ", "outnbrs ", "items "};
bool barrier=0;
#include "grammar.h"
tree_id *varname[100];
tree_expr *exprstack[25];
tree_decl_stmt *argstack[25];
int exprtop=0,argtop=0;
volatile int declared=0;
statement *foreach;
//#include "../include/tree.h"
extern int yylex();
extern void skipline();
void yyerror(const char *s);
int flag=0,fflag=0;
statement *sblock_begin[100],*s1;
int sbtop=0,arrtop=0;
proc_id *FDEF=NULL;
tree_typedecl *FTYPE,*DECLTYPE=NULL,*DECLTYPE1=NULL;
dir_decl *FNAME;
int param_count=0,vararg=0,argcount=0;


bool assflag;

// Variable declaration for FALCON extension
// #define DEBUGGING
int CONVERT_VERTEX_EDGE = 0;   // flag for different code generation (vertex & edge based)
extern std::set<statement*> foreach_list;
extern void convert_vertex_edge();
int level_of_foreach = 0;


#line 144 "y.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
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
    IDENTIFIER = 258,
    I_CONSTANT = 259,
    B_CONSTANT = 260,
    F_CONSTANT = 261,
    STRING_LITERAL = 262,
    FUNC_NAME = 263,
    SIZEOF = 264,
    GETTYPE = 265,
    WHITE_SPACE = 266,
    SECTION = 267,
    SECTIONS = 268,
    PARALLEL = 269,
    PTR_OP = 270,
    INC_OP = 271,
    DEC_OP = 272,
    LEFT_OP = 273,
    RIGHT_OP = 274,
    LE_OP = 275,
    GE_OP = 276,
    EQ_OP = 277,
    NE_OP = 278,
    AND_OP = 279,
    OR_OP = 280,
    MUL_ASSIGN = 281,
    DIV_ASSIGN = 282,
    MOD_ASSIGN = 283,
    ADD_ASSIGN = 284,
    RADD_ASSIGN = 285,
    RMUL_ASSIGN = 286,
    SUB_ASSIGN = 287,
    LEFT_ASSIGN = 288,
    RIGHT_ASSIGN = 289,
    AND_ASSIGN = 290,
    XOR_ASSIGN = 291,
    OR_ASSIGN = 292,
    TYPEDEF_NAME = 293,
    ENUMERATION_CONSTANT = 294,
    TYPEDEF = 295,
    EXTERN = 296,
    STATIC = 297,
    AUTO = 298,
    REGISTER = 299,
    INLINE = 300,
    CONST = 301,
    RESTRICT = 302,
    VOLATILE = 303,
    BOOL = 304,
    CHAR = 305,
    SHORT = 306,
    INT = 307,
    LONG = 308,
    SIGNED = 309,
    UNSIGNED = 310,
    FLOAT = 311,
    DOUBLE = 312,
    VOID = 313,
    SINGLE = 314,
    COMPLEX = 315,
    IMAGINARY = 316,
    STRUCT = 317,
    UNION = 318,
    ENUM = 319,
    ELLIPSIS = 320,
    STRUCT_REC = 321,
    CASE = 322,
    DEFAULT = 323,
    IF = 324,
    ELSE = 325,
    SWITCH = 326,
    WHILE = 327,
    DO = 328,
    FOR = 329,
    GOTO = 330,
    CONTINUE = 331,
    BREAK = 332,
    RETURN = 333,
    HASH_DEFINE = 334,
    ALIGNAS = 335,
    ALIGNOF = 336,
    ATOMIC = 337,
    GENERIC = 338,
    NORETURN = 339,
    STATIC_ASSERT = 340,
    THREAD_LOCAL = 341,
    GRAPH = 342,
    EDGE = 343,
    SET = 344,
    COLLECTION = 345,
    POINT = 346,
    E_P = 347,
    G_P = 348,
    P_P = 349,
    GPU = 350,
    POINTS = 351,
    EDGES = 352,
    NBRS = 353,
    INNBRS = 354,
    OUTNBRS = 355,
    ITEMS = 356,
    FOREACH = 357,
    INOLD = 358,
    ATOMIC1 = 359,
    EDGE1 = 360,
    POINT1 = 361,
    DIR_DECL = 362,
    MACRO1 = 363,
    GETTYPE1 = 364,
    PR_EXPR1 = 365,
    THEN = 366
  };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define I_CONSTANT 259
#define B_CONSTANT 260
#define F_CONSTANT 261
#define STRING_LITERAL 262
#define FUNC_NAME 263
#define SIZEOF 264
#define GETTYPE 265
#define WHITE_SPACE 266
#define SECTION 267
#define SECTIONS 268
#define PARALLEL 269
#define PTR_OP 270
#define INC_OP 271
#define DEC_OP 272
#define LEFT_OP 273
#define RIGHT_OP 274
#define LE_OP 275
#define GE_OP 276
#define EQ_OP 277
#define NE_OP 278
#define AND_OP 279
#define OR_OP 280
#define MUL_ASSIGN 281
#define DIV_ASSIGN 282
#define MOD_ASSIGN 283
#define ADD_ASSIGN 284
#define RADD_ASSIGN 285
#define RMUL_ASSIGN 286
#define SUB_ASSIGN 287
#define LEFT_ASSIGN 288
#define RIGHT_ASSIGN 289
#define AND_ASSIGN 290
#define XOR_ASSIGN 291
#define OR_ASSIGN 292
#define TYPEDEF_NAME 293
#define ENUMERATION_CONSTANT 294
#define TYPEDEF 295
#define EXTERN 296
#define STATIC 297
#define AUTO 298
#define REGISTER 299
#define INLINE 300
#define CONST 301
#define RESTRICT 302
#define VOLATILE 303
#define BOOL 304
#define CHAR 305
#define SHORT 306
#define INT 307
#define LONG 308
#define SIGNED 309
#define UNSIGNED 310
#define FLOAT 311
#define DOUBLE 312
#define VOID 313
#define SINGLE 314
#define COMPLEX 315
#define IMAGINARY 316
#define STRUCT 317
#define UNION 318
#define ENUM 319
#define ELLIPSIS 320
#define STRUCT_REC 321
#define CASE 322
#define DEFAULT 323
#define IF 324
#define ELSE 325
#define SWITCH 326
#define WHILE 327
#define DO 328
#define FOR 329
#define GOTO 330
#define CONTINUE 331
#define BREAK 332
#define RETURN 333
#define HASH_DEFINE 334
#define ALIGNAS 335
#define ALIGNOF 336
#define ATOMIC 337
#define GENERIC 338
#define NORETURN 339
#define STATIC_ASSERT 340
#define THREAD_LOCAL 341
#define GRAPH 342
#define EDGE 343
#define SET 344
#define COLLECTION 345
#define POINT 346
#define E_P 347
#define G_P 348
#define P_P 349
#define GPU 350
#define POINTS 351
#define EDGES 352
#define NBRS 353
#define INNBRS 354
#define OUTNBRS 355
#define ITEMS 356
#define FOREACH 357
#define INOLD 358
#define ATOMIC1 359
#define EDGE1 360
#define POINT1 361
#define DIR_DECL 362
#define MACRO1 363
#define GETTYPE1 364
#define PR_EXPR1 365
#define THEN 366

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 78 "grammar.y" /* yacc.c:355  */

    int  info;
    long ival;
    double fval;
    char* text;
    bool bval;
    class  tree_node* ptr;

#line 415 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 432 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  97
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3172

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  136
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  99
/* YYNRULES -- Number of rules.  */
#define YYNRULES  350
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  640

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   366

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   127,     2,     2,     2,   129,   115,     2,
     113,   114,   118,   116,   112,   117,   123,   128,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   120,   111,
     130,   135,   131,   134,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   121,     2,   122,   132,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   124,   133,   125,   126,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   119
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   130,   130,   136,   137,   138,   145,   149,   154,   158,
     162,   166,   172,   181,   185,   189,   190,   194,   195,   199,
     201,   243,   252,   281,   324,   330,   338,   339,   392,   393,
     400,   409,   411,   416,   420,   430,   433,   434,   435,   436,
     437,   442,   446,   447,   448,   449,   450,   451,   455,   456,
     462,   464,   465,   466,   470,   471,   472,   476,   477,   478,
     482,   483,   484,   485,   486,   490,   491,   492,   496,   497,
     501,   502,   506,   507,   511,   512,   516,   517,   521,   522,
     532,   536,   563,   564,   565,   566,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   579,   589,   599,   603,   618,
     635,   644,   648,   649,   653,   659,   665,   670,   673,   677,
     678,   682,   683,   690,   691,   695,   700,   705,   709,   716,
     717,   718,   719,   720,   721,   726,   727,   728,   729,   730,
     731,   732,   733,   734,   735,   738,   743,   744,   745,   746,
     747,   753,   757,   763,   771,   781,   782,   783,   787,   788,
     797,   801,   807,   811,   816,   819,   826,   834,   835,   844,
     845,   849,   853,   860,   867,   880,   891,   902,   903,   916,
     922,   935,   939,   942,   943,   944,   948,   949,   950,   951,
     952,   953,   954,   958,   959,   965,   966,   967,   971,   972,
     973,   974,   975,   976,   977,   978,   979,   980,   981,   988,
     996,  1007,  1012,  1020,  1021,  1025,  1030,  1034,  1038,  1041,
    1050,  1059,  1069,  1077,  1085,  1094,  1102,  1110,  1118,  1127,
    1148,  1150,  1156,  1167,  1177,  1185,  1198,  1207,  1208,  1212,
    1223,  1227,  1232,  1243,  1244,  1249,  1252,  1256,  1260,  1263,
    1275,  1276,  1280,  1286,  1294,  1299,  1304,  1308,  1314,  1319,
    1325,  1329,  1333,  1337,  1341,  1345,  1349,  1356,  1365,  1372,
    1379,  1386,  1393,  1400,  1407,  1412,  1418,  1426,  1439,  1444,
    1449,  1453,  1457,  1458,  1464,  1472,  1476,  1477,  1486,  1490,
    1497,  1501,  1506,  1512,  1518,  1523,  1528,  1534,  1539,  1544,
    1549,  1557,  1564,  1568,  1575,  1585,  1597,  1609,  1624,  1630,
    1640,  1667,  1677,  1686,  1701,  1711,  1716,  1724,  1725,  1737,
    1745,  1757,  1770,  1776,  1786,  1798,  1807,  1834,  1865,  1896,
    1927,  1926,  1971,  1970,  2011,  2023,  2024,  2029,  2032,  2040,
    2070,  2075,  2080,  2085,  2090,  2099,  2099,  2116,  2120,  2125,
    2133,  2145,  2150,  2158,  2158,  2179,  2261,  2261,  2289,  2321,
    2328
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "I_CONSTANT", "B_CONSTANT",
  "F_CONSTANT", "STRING_LITERAL", "FUNC_NAME", "SIZEOF", "GETTYPE",
  "WHITE_SPACE", "SECTION", "SECTIONS", "PARALLEL", "PTR_OP", "INC_OP",
  "DEC_OP", "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP",
  "AND_OP", "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN",
  "ADD_ASSIGN", "RADD_ASSIGN", "RMUL_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN",
  "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "TYPEDEF_NAME",
  "ENUMERATION_CONSTANT", "TYPEDEF", "EXTERN", "STATIC", "AUTO",
  "REGISTER", "INLINE", "CONST", "RESTRICT", "VOLATILE", "BOOL", "CHAR",
  "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE", "VOID",
  "SINGLE", "COMPLEX", "IMAGINARY", "STRUCT", "UNION", "ENUM", "ELLIPSIS",
  "STRUCT_REC", "CASE", "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE", "DO",
  "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "HASH_DEFINE", "ALIGNAS",
  "ALIGNOF", "ATOMIC", "GENERIC", "NORETURN", "STATIC_ASSERT",
  "THREAD_LOCAL", "GRAPH", "EDGE", "SET", "COLLECTION", "POINT", "E_P",
  "G_P", "P_P", "GPU", "POINTS", "EDGES", "NBRS", "INNBRS", "OUTNBRS",
  "ITEMS", "FOREACH", "INOLD", "ATOMIC1", "EDGE1", "POINT1", "DIR_DECL",
  "MACRO1", "GETTYPE1", "PR_EXPR1", "';'", "','", "'('", "')'", "'&'",
  "'+'", "'-'", "'*'", "THEN", "':'", "'['", "']'", "'.'", "'{'", "'}'",
  "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "'='",
  "$accept", "primary_expression", "constant", "enumeration_constant",
  "string", "generic_selection", "generic_assoc_list",
  "generic_association", "postfix_expression",
  "paraargument_expression_list", "argument_expression_list",
  "unary_expression", "unary_operator", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "atomic_type_specifier", "type_qualifier", "lib_type_specifier", "list1",
  "alltype", "function_specifier", "alignment_specifier", "declarator",
  "direct_declarator", "pointer", "type_qualifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "devno", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "designation", "designator_list", "designator",
  "static_assert_declaration", "statement", "parallel_statement",
  "sections", "macro_statement", "labeled_statement", "compound_statement",
  "compound_begin", "compound_end", "b_compound_begin", "block_item_list",
  "block_item", "expression_statement", "single_statement",
  "selection_statement", "iteration_statement", "$@1", "$@2", "IN", "IN1",
  "iterator", "jump_statement", "conditional_for", "$@3",
  "translation_unit", "external_declaration", "function_definition", "$@4",
  "$@5", "declaration_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,    59,    44,    40,    41,    38,    43,    45,    42,   366,
      58,    91,    93,    46,   123,   125,   126,    33,    47,    37,
      60,    62,    94,   124,    63,    61
};
# endif

#define YYPACT_NINF -466

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-466)))

#define YYTABLE_NINF -6

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    2410,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,
    -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,
    -466,  -466,  -466,  -466,  -466,  -466,    23,  -466,    58,   -67,
     -16,  -466,    21,  -466,  -466,    27,  -466,  -466,    56,    77,
     172,  -466,    53,  2942,  2942,  -466,    34,  -466,  -466,  2942,
    -466,  2942,  2942,  2643,     5,    39,  -466,  -466,  2239,  -466,
    -466,   -11,   169,   230,  1234,  3081,  2046,   198,   208,    74,
    -466,  -466,  -466,   172,  -466,    89,   120,   191,  -466,  2489,
    -466,  -466,   102,  2989,  -466,  -466,  -466,  -466,  -466,    53,
    -466,   882,  2834,   789,  1323,   219,     5,  -466,  -466,   169,
    -466,    95,   -59,  -466,  -466,  -466,  -466,  -466,  -466,  -466,
    -466,   130,  1234,  -466,  -466,  -466,  -466,   127,  2093,  2149,
    2149,   139,  1234,  -466,  -466,  -466,  -466,  -466,  -466,   212,
    -466,  2046,  -466,   -35,   188,    98,    94,   286,    15,   136,
     151,   268,    40,  -466,   182,  3081,   128,  3081,   186,   192,
     214,   216,   224,  -466,  -466,  -466,   227,   233,  -466,    64,
    1810,  -466,  2834,  2989,  2543,  -466,   103,  -466,   193,  -466,
     222,   333,   234,  2046,   229,   237,   238,   240,   973,   243,
     351,   248,   256,  1828,   255,  -466,  -466,   600,  -466,  -466,
     199,  -466,  -466,  -466,  -466,  -466,  -466,  -466,   882,  -466,
    -466,  -466,  -466,  -466,  -466,  -466,   245,  -466,  -466,   275,
      49,   262,   265,  -466,    79,  1661,  -466,  -466,  -466,  -466,
    -466,  -466,  -466,  -466,  -466,  -466,   376,   267,   271,   272,
     259,  1052,  -466,   269,   384,   270,  -466,  1412,   277,   -36,
    2046,    31,  -466,  2046,   144,   279,   230,   391,  -466,  -466,
    1867,  2046,   241,  1234,  -466,  -466,  -466,  3081,   281,  -466,
    2046,  2046,  2046,  2046,  2046,  2046,  2046,  2046,  2046,  2046,
    2046,  2046,  2046,  2046,  2046,  2046,  2046,  2046,  2046,  -466,
    -466,  2697,  1459,   -23,  -466,    20,  -466,  -466,  -466,   390,
    -466,  -466,    77,   395,   273,  -466,  1742,  -466,  -466,   245,
    2589,  -466,  -466,  -466,  2046,   203,  -466,   280,   973,   245,
    2046,   282,   973,  2046,  2046,  2046,   341,  1891,  2834,   294,
    -466,  -466,  -466,   206,  -466,   412,  -466,  -466,  -466,  -466,
    -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  2046,
    -466,  2046,  -466,  -466,  -466,   233,  2328,   322,  -466,    65,
    -466,  -466,  2888,   415,  -466,   297,  1661,  -466,   417,   418,
     419,  -466,   303,  -466,   313,  -466,  2046,   306,  -466,   308,
     430,    38,  -466,  -466,  -466,  -466,   323,  -466,   315,   212,
    -466,  -466,   159,     0,  -466,   324,   331,   332,  1953,  -466,
    -466,  -466,   -35,   -35,   188,   188,    98,    98,    98,    98,
      94,    94,   286,    15,   136,   151,   268,    17,  -466,   334,
     335,  1661,   325,  -466,   329,  1474,    20,  2779,  1599,   338,
     318,  -466,    77,  2046,   453,  -466,   -25,  1810,   -50,  -466,
    -466,  -466,  -466,  -466,    67,  2046,  -466,   445,   160,   973,
    -466,   164,   167,   168,   346,  1891,  1891,  -466,  -466,    22,
    -466,  -466,   340,   233,  -466,  -466,  -466,  -466,   342,   349,
     355,   362,  -466,   462,   363,  -466,  -466,   377,  -466,  3035,
    1742,  1144,  -466,  -466,   374,   315,  -466,  -466,  2046,  -466,
    -466,   368,  1661,  -466,  -466,  2046,  -466,   369,  -466,   378,
    1661,   371,  -466,   372,  1614,   385,  1810,   360,   375,  -466,
     357,  -466,  -466,  -466,  -466,  -466,  -466,   245,     7,   973,
    -466,   973,   973,   973,  2046,  2007,  2022,  -466,   205,   496,
     382,   499,   373,  -466,  -466,  -466,  -466,   389,  -466,  2942,
     388,   171,  -466,   393,   -24,   397,   402,  -466,  -466,    35,
    -466,  -466,   383,   396,  -466,  -466,   400,  1661,  -466,  -466,
    2046,  -466,   401,  -466,  -466,  1810,  -466,  -466,  -466,  1810,
    -466,   245,  -466,   454,   456,  -466,  -466,   174,   973,   177,
     973,   181,   512,   524,   -75,  -466,  -466,    77,  -466,   416,
    2046,  3035,  -466,  2046,  1685,  -466,  -466,  2046,   420,  -466,
    -466,  -466,   407,   409,  -466,  -466,  -466,  -466,   973,   973,
     422,  -466,   973,  -466,   973,   423,   424,  -466,   531,  -466,
    -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,
    -466,  -466,  -466,   433,   433,  1054,  -466,   425,   382,   382,
    1234,  -466,  -466,  -466,   185,  1054,   673,  -466,  -466,  -466
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   207,   140,   119,   120,   121,   123,   124,   201,   172,
     173,   174,   136,   126,   127,   128,   129,   132,   133,   130,
     131,   125,   137,   138,   145,   147,     0,   146,     0,     0,
     175,   202,     0,   122,   176,   177,   181,   182,   178,     0,
     226,   341,     0,   102,   104,   134,     0,   135,   139,   106,
     141,   108,   110,     0,   206,     0,   100,   342,     0,   338,
     340,   166,     0,     0,     0,     0,     0,     0,     0,     0,
     175,   227,   225,   224,    98,     0,     0,     0,   111,   114,
     101,   103,   144,     0,   105,   107,   109,   300,   349,     0,
     348,     0,   346,     0,     0,     0,   205,     1,   339,     0,
      11,   170,     0,   167,     2,     7,     9,     8,    12,    13,
      10,     0,     0,    19,     3,     4,     6,     0,     0,     0,
       0,     0,     0,    42,    44,    45,    43,    46,    47,    35,
      48,     0,    50,    54,    57,    60,    65,    68,    70,    72,
      74,    76,    78,    97,     0,   154,   243,   156,     0,     0,
       0,     0,     0,   209,   228,   223,   207,   240,    99,     0,
       0,   345,   343,     0,     0,   148,     0,   152,   114,   290,
       2,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   307,   301,    48,    80,    95,
       0,   305,   306,   288,   289,   281,   282,   298,     0,   303,
     283,   285,   284,   286,   287,   350,     0,   238,   221,     0,
     236,     0,   230,   231,     0,     0,   197,   189,   190,   191,
     192,   195,   196,   193,   194,   188,     0,     0,     0,     0,
      43,     0,   210,     0,     0,     0,   183,     0,     0,     0,
       0,     0,   162,     0,     0,     0,     0,     0,    26,    28,
       0,     0,     0,     0,    39,    36,    37,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   204,
     153,     0,     0,   245,   242,   246,   155,   203,   171,     0,
     179,   180,     0,     0,     0,   112,     0,   270,   113,     0,
       0,   142,   149,   150,     0,     0,   157,   161,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   302,     0,     0,
     331,   332,   333,     0,   302,     0,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    82,     0,
     308,     0,   299,   304,   347,   240,     0,     0,   233,   245,
     235,   219,     0,     0,   222,     0,     0,   200,     0,     0,
       0,   211,     0,   218,   198,   208,     0,    43,   217,     0,
       0,     0,   164,   169,   163,   168,     0,     5,     0,   294,
      24,    21,     0,     0,    25,     0,     0,     0,     0,    51,
      52,    53,    55,    56,    58,    59,    63,    64,    61,    62,
      66,    67,    69,    71,    73,    75,    77,     0,   264,     0,
       0,     0,    43,   248,     0,     0,   244,     0,     0,     0,
     117,   241,     0,     0,     0,   272,     0,     0,     0,   276,
     344,   143,   159,   151,     0,     0,   295,     0,     0,     0,
     297,     0,     0,     0,     0,     0,     0,   330,   334,     0,
      81,    96,     0,   240,   229,   232,   239,   213,     0,     0,
       0,     0,   184,     0,     0,   214,   216,     0,   165,     0,
       0,     0,    22,    20,     0,    40,    41,    49,     0,   265,
     247,     0,     0,   249,   255,     0,   254,     0,   266,     0,
       0,    43,   256,     0,     0,     0,     0,   116,     0,   279,
       0,   268,   271,   275,   277,   158,   160,     0,     0,     0,
     296,     0,     0,     0,     0,     0,     0,   327,     0,     0,
     326,     0,     0,   212,   186,   185,   187,     0,   215,     0,
       0,     0,    15,     0,     0,     0,    31,    33,    32,     0,
      79,   251,     0,     0,   253,   267,     0,     0,   257,   263,
       0,   262,     0,   280,   118,     0,   278,   269,   274,     0,
     292,     0,   291,   309,   312,   313,   314,     0,     0,     0,
       0,     0,     0,     0,     0,   328,   237,     0,   199,     0,
       0,     0,    14,     0,     0,    29,    23,     0,    27,   250,
     252,   259,     0,     0,   260,   115,   273,   293,     0,     0,
       0,   316,     0,   318,     0,     0,     0,   322,     0,   234,
     220,    18,    16,    17,    30,    34,   258,   261,   310,   311,
     315,   317,   319,     0,     0,     0,   329,     0,   324,   325,
       0,   337,   323,   320,     0,     0,     0,   321,   335,   336
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -466,  -466,  -466,  -466,  -466,  -466,  -466,   -41,   -47,  -466,
    -466,   348,  -466,  -111,    60,    66,    -5,    68,   276,   278,
     283,   266,   284,  -466,   -34,    16,  -466,  -105,   -37,   -17,
       6,  -466,   386,  -466,   -61,  -466,   -76,   380,  -143,   -68,
    -466,   110,  -466,   447,  -218,  -466,   -40,  -466,   319,  -466,
    -466,  -466,     2,   -42,   -26,   -84,   -88,  -466,   202,    18,
    -264,   -53,  -106,  -238,  -152,    85,  -465,  -466,   131,   -55,
     -51,  -466,  -466,    63,  -466,   -52,   247,  -189,   381,  -466,
     364,  -286,  -466,  -466,  -466,  -466,  -466,  -466,  -287,  -466,
    -466,   -71,  -466,  -466,   502,  -466,  -466,  -466,   488
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   113,   114,   101,   115,   116,   531,   532,   129,   535,
     536,   187,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   188,   189,   339,   190,   144,    41,
      89,    77,    78,    43,    44,    45,    46,   164,   165,   146,
     305,   306,    47,   102,   103,    48,    49,    50,   235,   236,
      51,    52,    69,    54,    55,    73,   409,   212,   213,   214,
     294,   258,   410,   285,   425,   426,   427,   428,   429,    56,
     192,   193,   508,   194,   195,   196,    91,   197,   318,   198,
     199,   200,   201,   202,   203,   635,   625,   519,   520,   627,
     204,   632,   639,    58,    59,    60,   299,   206,    92
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,    90,    53,   145,   145,   211,    42,   244,   298,   342,
     237,   148,   149,    96,    72,   166,   117,   244,   234,   561,
     259,   302,   145,   375,   147,   147,    61,   161,   167,   150,
     143,   445,   143,   154,   100,   559,    88,    82,   207,   607,
     284,   100,     1,   147,    79,   416,    64,   155,   608,    80,
      81,   145,     1,   241,    71,    84,     1,    85,    86,   245,
      53,   145,    88,    57,    42,   277,   242,     1,     1,    63,
       1,   423,   147,   424,   191,   205,   371,   280,   323,   286,
       1,   452,   147,   260,   145,   503,   145,   500,   584,   372,
     281,   168,   156,   261,   262,   166,   166,    65,   282,   210,
     501,   585,   145,   145,   350,   147,     1,   147,   167,   167,
     233,   416,   341,    99,   267,   268,   265,   266,    93,   559,
     283,    57,   473,   147,   147,   517,    94,   316,    95,   341,
     273,   356,   186,   417,    66,   518,   311,   478,   246,   143,
      67,   418,   247,   248,   249,   205,   383,    62,   244,   389,
     390,   391,    39,   375,   344,   234,   374,   302,    83,   515,
     516,   168,   346,   468,    74,   209,    75,    40,   307,    68,
     282,    40,   100,   407,   278,    71,   297,    75,   346,   347,
      39,   191,    40,    76,   349,    40,   282,   304,   153,   522,
      39,   353,   145,   354,    76,    40,   145,   154,   415,   379,
     386,   151,    39,   373,   387,   438,   143,    40,   441,   442,
     443,   152,   348,   147,   303,   157,    39,   147,     9,    10,
      11,    40,   238,   304,   269,   270,   163,   247,   248,   249,
     240,   355,   166,   104,   105,   106,   107,   108,   109,   145,
     250,   281,    71,   243,   384,   167,    40,   430,   251,   282,
     252,   385,   257,   369,    70,   283,   341,   436,   377,   376,
     147,   440,   396,   397,   398,   399,   382,   432,   274,   110,
     143,   471,   341,   472,   509,   502,   341,   477,   511,   341,
     341,   512,   513,   581,   275,   582,   341,   210,   600,   341,
      40,   602,   276,   341,   420,   604,   279,   341,   414,   636,
     287,   446,   158,   159,   263,   264,   288,    96,   271,   272,
     340,   341,   297,   111,   433,   434,   154,   448,   341,   562,
     349,   572,   573,   392,   393,   250,   289,   482,   160,   489,
     290,   394,   395,   251,   494,   252,   628,   629,   291,   400,
     401,   292,   308,   112,   554,   293,   309,   310,   558,   312,
     313,   314,   210,   315,   319,   450,   317,   451,   210,   320,
     104,   105,   106,   107,   108,   109,   118,   321,   324,    87,
     345,    71,   458,   119,   120,   154,   351,   352,    71,   357,
     358,   361,   464,   538,   359,   360,   498,   364,   510,   143,
     370,   363,   365,   378,   380,   388,   110,   419,   506,   421,
     435,   143,   439,   595,   422,   447,   547,   596,   145,   567,
     569,   571,   130,   444,   130,   449,   533,   453,   456,   457,
     459,   460,   461,   210,   497,   462,   463,   481,   465,   147,
     466,   487,   558,   467,   493,   469,   307,   474,   121,   470,
     111,   579,   154,   297,   540,   475,   476,   483,   479,   480,
      71,   484,   495,   496,   154,   560,   499,   507,   563,   514,
     564,   565,   566,   524,   523,   527,   254,   255,   256,   525,
     122,   521,   123,   124,   125,   126,   526,   210,   423,   130,
     424,   296,   557,   127,   128,   528,   297,   537,   539,   529,
     541,   544,   545,   548,   549,   555,   553,   556,   542,   574,
     575,   543,   576,   578,   577,   589,   546,   154,   580,   597,
     552,   586,   297,   583,   587,   605,   297,   601,   590,   603,
     145,   130,   591,   594,   598,   634,   599,   606,   533,   616,
     610,   617,   353,   620,   626,   210,   517,   623,   624,   633,
     612,   147,   405,   300,   505,   295,   239,   618,   619,   402,
     362,   621,   403,   622,   455,   534,   437,   588,   404,   504,
      98,   406,   343,   592,   637,   325,   593,   162,     0,   145,
       0,   297,     0,     0,   631,   297,     0,     0,     0,   609,
       0,     0,     0,     0,   631,   638,     0,     0,   130,     0,
     147,     0,     0,     0,     0,     0,   611,     0,     0,   613,
     297,     0,     0,   615,     0,     0,     0,     0,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   169,     0,   170,   105,   106,   107,
     108,   109,   118,     0,     0,     0,     0,   171,    -5,    -5,
      -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,     0,   110,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   172,     0,     0,   338,   130,     0,     0,     0,
     173,   174,   175,     0,   176,   177,   178,   179,   180,   181,
     182,   183,    28,     0,   121,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   130,     0,     0,     0,   184,     0,     0,     0,     0,
       0,     0,     0,   130,    -5,    -5,    -5,     0,   123,   124,
     125,   126,   207,     0,    -5,     0,    -5,    87,     0,   127,
     128,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   130,     2,     0,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,    22,
      23,    24,    25,    26,     0,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
       0,    30,     0,    31,     0,    33,    34,    35,    36,    37,
      38,     0,     0,   169,     0,   170,   105,   106,   107,   108,
     109,   118,     0,     0,     0,     0,   171,     0,   119,   120,
       0,     0,     0,   208,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   209,
       2,   110,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,   172,    22,    23,    24,    25,    26,     0,    27,   173,
     174,   175,     0,   176,   177,   178,   179,   180,   181,   182,
     183,    28,    29,   121,    30,   111,    31,    32,    33,    34,
      35,    36,    37,    38,   169,     0,   170,   105,   106,   107,
     108,   109,   118,     0,   184,     0,     0,   171,     0,   119,
     120,     0,     0,   185,     0,   122,     0,   123,   124,   125,
     126,     0,     0,     0,     0,     0,    87,   186,   127,   128,
       0,     0,   110,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   172,     0,     0,     0,     0,     0,     0,     0,
     173,   174,   175,     0,   176,   177,   178,   179,   180,   181,
     182,   183,    28,     0,   121,   169,   111,   170,   105,   106,
     107,   108,   109,   118,     0,     0,     0,     0,   171,     0,
     119,   120,     0,     0,     0,   184,     0,     0,     0,     0,
       0,     0,     0,     0,   185,     0,   122,     0,   123,   124,
     125,   126,     0,   110,     0,     0,     0,    87,     0,   127,
     128,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,     0,     0,   172,    24,    25,   226,     0,    27,     0,
       0,   173,   174,   175,     0,   176,   177,   178,   179,   180,
     181,   182,   183,    28,     0,   121,     0,   111,     0,   227,
     228,     0,     0,   229,     0,     0,     0,   104,   105,   106,
     107,   108,   109,   118,     0,     0,   184,     0,     0,     0,
     119,   120,     0,     0,     0,   185,     0,   630,     0,   123,
     124,   125,   126,   231,     0,     0,     0,     0,    87,     0,
     127,   128,     2,   110,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     0,    22,    23,    24,    25,    26,     0,
      27,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    29,   121,    30,   111,    31,     0,
      33,    34,    35,    36,    37,    38,     0,   104,   105,   106,
     107,   108,   109,   118,     0,     0,     0,     0,     0,     0,
     119,   120,     0,     0,     0,     0,     0,   122,     0,   123,
     124,   125,   126,     0,     0,     0,     0,     0,     0,     0,
     127,   128,     2,   110,     0,     0,     0,     0,     0,     0,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     0,    22,    23,    24,    25,    26,     0,
      27,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   121,    30,   111,     0,     0,
       0,    34,    35,    36,    37,    38,   104,   105,   106,   107,
     108,   109,   118,     0,     0,     0,     0,     0,     0,   119,
     120,     0,     0,     0,     0,     0,     0,   122,     0,   123,
     124,   125,   126,     0,     0,     0,     0,     0,     0,     0,
     127,   128,   110,     0,     0,   215,     0,     0,     0,     9,
      10,    11,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,     0,     0,     0,    24,    25,   226,     0,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,    70,   111,     0,     0,     0,
     227,   228,     0,     0,   229,   104,   105,   106,   107,   108,
     109,   118,     0,     0,     0,     0,     0,     0,   119,   120,
       0,     0,     0,     0,     0,     0,   122,     0,   123,   124,
     125,   230,     0,     0,   231,   232,     0,     0,     0,   127,
     128,   110,     0,     0,   366,     0,     0,     0,     9,    10,
      11,     0,   104,   105,   106,   107,   108,   109,   118,     0,
       0,     0,     0,     0,     0,   119,   120,   104,   105,   106,
     107,   108,   109,   118,     0,     0,     0,     0,     0,     0,
     119,   120,     0,   121,    70,   111,     0,     0,   110,     0,
       0,   411,     0,     0,     0,     9,    10,    11,     0,     0,
       0,     0,     0,   110,     0,     0,   485,     0,     0,     0,
       9,    10,    11,     0,     0,   122,     0,   123,   124,   125,
     367,     0,     0,     0,   368,     0,     0,     0,   127,   128,
     121,    70,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   121,    70,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   122,     0,   123,   124,   125,   412,     0,     0,
       0,   413,     0,     0,     0,   127,   128,   122,     0,   123,
     124,   125,   126,     0,     0,     0,   486,     0,     0,     0,
     127,   128,   104,   105,   106,   107,   108,   109,   118,     0,
       0,     0,     0,     0,     0,   119,   120,   104,   105,   106,
     107,   108,   109,   118,     0,     0,     0,     0,     0,     0,
     119,   120,     0,     0,     0,     0,     0,     0,   110,     0,
       0,   490,     0,     0,     0,     9,    10,    11,     0,     0,
       0,     0,     0,   110,     0,     0,   550,     0,     0,     0,
       9,    10,    11,     0,   104,   105,   106,   107,   108,   109,
     118,     0,     0,     0,     0,     0,     0,   119,   120,     0,
     121,    70,   111,     0,     0,     0,     0,     0,   104,   105,
     106,   107,   108,   109,   118,   121,    70,   111,     0,     0,
     110,   119,   120,     0,     0,     0,     0,     9,    10,    11,
       0,     0,   122,     0,   123,   124,   125,   491,     0,     0,
       0,   492,     0,     0,   110,   127,   128,   122,     0,   123,
     124,   125,   126,     0,     0,     0,   551,     0,     0,     0,
     127,   128,   121,    70,   111,   104,   105,   106,   107,   108,
     109,   118,     0,     0,     0,     0,     0,     0,   119,   120,
       0,     0,     0,     0,     0,     0,   121,     0,   111,     0,
       0,     0,     0,     0,   122,     0,   123,   124,   125,   126,
       0,   110,     0,     0,     0,     0,     0,   127,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   122,     0,
     123,   124,   125,   126,     0,     0,   423,     0,   424,   296,
     614,   127,   128,   104,   105,   106,   107,   108,   109,   118,
       0,     0,     0,   121,     0,   111,   119,   120,     0,     0,
       0,   104,   105,   106,   107,   108,   109,   118,     0,     0,
       0,     0,     0,     0,   119,   120,     0,     0,     0,   110,
       0,     0,     0,     0,     0,   122,     0,   123,   124,   125,
     126,     0,     0,   423,     0,   424,   296,   110,   127,   128,
     104,   105,   106,   107,   108,   109,   118,     0,     0,     0,
       0,     0,     0,   119,   120,     0,     0,     0,     0,     0,
       0,   121,     0,   111,   104,   105,   106,   107,   108,   109,
     118,     0,     0,     0,     0,     0,   110,   119,   120,   121,
       0,   111,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   122,     0,   123,   124,   125,   126,     0,
     110,     0,     0,     0,   296,     0,   127,   128,     0,   322,
       0,   122,     0,   123,   124,   125,   126,     0,   121,     0,
     111,     0,     0,     0,   127,   128,   104,   105,   106,   107,
     108,   109,   118,     0,     0,     0,     0,     0,     0,   119,
     120,     0,   121,     0,   111,     0,     0,     0,     0,     0,
     122,   381,   123,   124,   125,   126,     0,     0,     0,     0,
       0,     0,   110,   127,   128,     0,     0,     0,     0,     0,
       0,     0,   185,     0,   122,     0,   123,   124,   125,   126,
     104,   105,   106,   107,   108,   109,   118,   127,   128,     0,
       0,     0,     0,   119,   120,   104,   105,   106,   107,   108,
     109,   118,     0,     0,   121,     0,   111,     0,   119,   120,
       0,     0,     0,     0,     0,     0,   110,     0,     0,   104,
     105,   106,   107,   108,   109,   118,     0,     0,     0,     0,
       0,   110,   119,   120,     0,     0,   122,     0,   123,   124,
     125,   126,     0,     0,     0,     0,     0,   470,     0,   127,
     128,     0,     0,     0,     0,   110,     0,     0,   121,     0,
     111,     0,     0,     0,     0,     0,   104,   105,   106,   107,
     108,   109,   118,   121,     0,   111,     0,     0,     0,   119,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     122,   568,   123,   124,   125,   126,     0,   121,     0,   111,
       0,     0,   110,   127,   128,   122,   570,   123,   124,   125,
     126,     0,     0,     0,     0,     0,     0,     0,   127,   128,
       0,     0,   104,   105,   106,   107,   108,   109,   118,   122,
       0,   123,   124,   125,   126,   119,   120,     0,     0,     0,
       0,     0,   127,   128,   121,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   110,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   253,     0,   123,   124,
     125,   126,     0,     0,     0,     0,     0,     0,     0,   127,
     128,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     121,     0,   111,     0,     0,     0,     0,     0,     0,    97,
       0,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   112,     0,   123,   124,   125,   126,     0,     0,
       0,     0,     0,     0,     0,   127,   128,     2,     0,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,    22,
      23,    24,    25,    26,     0,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,    29,
       0,    30,     0,    31,    32,    33,    34,    35,    36,    37,
      38,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    39,     0,     0,     0,     0,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     0,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     0,    22,    23,
      24,    25,    26,     0,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,     0,
      30,     0,    31,     1,    33,    34,    35,    36,    37,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   346,   408,     0,     0,     0,    40,     0,     2,   282,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     0,
      22,    23,    24,    25,    26,     0,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
      29,     0,    30,     0,    31,    32,    33,    34,    35,    36,
      37,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,     0,     0,     0,     2,    40,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,    22,
      23,    24,    25,    26,     0,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
       0,    30,     0,    31,    32,    33,    34,    35,    36,    37,
      38,     2,     0,     0,     0,     0,     0,     0,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     0,    22,    23,    24,    25,    26,     0,    27,
       0,     0,     0,    87,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   160,    30,     0,     2,    32,     0,
      34,    35,    36,    37,    38,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,    22,
      23,    24,    25,    26,     0,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   301,     0,
       0,    30,     0,     0,    32,     0,    34,    35,    36,    37,
      38,     2,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     0,    22,    23,    24,    25,    26,     0,    27,
       0,     0,     0,     0,   431,     0,     0,     0,     0,     0,
       0,     0,     0,    29,     0,    30,     0,    31,    32,    33,
      34,    35,    36,    37,    38,     2,     0,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     0,    22,    23,    24,
      25,    26,     0,    27,     0,     0,     0,    87,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,    30,
       0,    31,     0,    33,    34,    35,    36,    37,    38,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     281,   408,     0,     0,     0,    40,     0,     2,   282,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,    22,
      23,    24,    25,    26,     0,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
       0,    30,     0,    31,     0,    33,    34,    35,    36,    37,
      38,     0,     2,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,   488,    22,    23,    24,    25,    26,     0,
      27,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    29,     0,    30,     0,    31,    32,
      33,    34,    35,    36,    37,    38,     2,     0,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     0,    22,    23,
      24,    25,    26,   454,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,     0,
      30,     0,    31,     0,    33,    34,    35,    36,    37,    38,
       2,     0,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     0,    22,    23,    24,    25,    26,     0,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,     0,    30,     0,    31,     2,    33,    34,
      35,    36,    37,    38,     0,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,    22,
      23,    24,    25,    26,     0,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    30,     0,     2,    32,     0,    34,    35,    36,    37,
      38,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     0,    22,    23,    24,    25,    26,
       0,    27,     0,   530,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    30,     0,     2,
       0,     0,    34,    35,    36,    37,    38,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,    22,    23,    24,    25,    26,     0,    27,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    30,     0,     0,     0,     0,    34,    35,
      36,    37,    38
};

static const yytype_int16 yycheck[] =
{
      40,    53,     0,    64,    65,    93,     0,   112,   160,   198,
      94,    64,    65,    55,    40,    83,    63,   122,    94,    12,
     131,   164,    83,   241,    64,    65,     3,    79,    83,    66,
      64,   317,    66,    73,     3,   500,    53,     3,     3,   114,
     146,     3,     3,    83,    42,   283,   113,    73,   123,    43,
      44,   112,     3,   112,    94,    49,     3,    51,    52,   112,
      58,   122,    79,     0,    58,    25,   125,     3,     3,    11,
       3,   121,   112,   123,    91,    92,   112,   145,   183,   147,
       3,   345,   122,   118,   145,   135,   147,   112,   112,   125,
     113,    89,     3,   128,   129,   163,   164,   113,   121,    93,
     125,   125,   163,   164,   210,   145,     3,   147,   163,   164,
      94,   349,   112,   124,    20,    21,    18,    19,   113,   584,
     146,    58,   122,   163,   164,   103,   121,   178,   123,   112,
     115,   215,   125,   113,   113,   113,   173,   120,    11,   173,
     113,   121,    15,    16,    17,   162,   251,   124,   253,   260,
     261,   262,   113,   371,   206,   231,   125,   300,   124,   445,
     446,   159,   113,   125,   111,   130,   113,   118,   166,   113,
     121,   118,     3,   278,   134,   215,   160,   113,   113,   130,
     113,   198,   118,   130,   210,   118,   121,   120,   114,   453,
     113,   112,   253,   114,   130,   118,   257,   237,   282,   246,
     253,     3,   113,   240,   257,   310,   240,   118,   313,   314,
     315,     3,   210,   253,   111,    95,   113,   257,    46,    47,
      48,   118,     3,   120,   130,   131,   124,    15,    16,    17,
     135,   215,   300,     3,     4,     5,     6,     7,     8,   300,
     113,   113,   282,   113,     3,   300,   118,   299,   121,   121,
     123,    10,   113,   237,    82,   281,   112,   308,   114,   243,
     300,   312,   267,   268,   269,   270,   250,   304,   132,    39,
     304,   112,   112,   114,   114,   427,   112,   388,   114,   112,
     112,   114,   114,   112,   133,   114,   112,   281,   114,   112,
     118,   114,    24,   112,   292,   114,   114,   112,   282,   114,
     114,   318,   111,   112,   116,   117,   114,   349,    22,    23,
     111,   112,   296,    83,   111,   112,   356,   111,   112,   508,
     346,   116,   117,   263,   264,   113,   112,   411,   135,   417,
     114,   265,   266,   121,   418,   123,   623,   624,   114,   271,
     272,   114,   120,   113,   496,   112,    13,   113,   500,   120,
     113,   113,   346,   113,     3,   339,   113,   341,   352,   111,
       3,     4,     5,     6,     7,     8,     9,   111,   113,   124,
      95,   411,   356,    16,    17,   415,   114,   112,   418,     3,
     113,   122,   366,   471,   113,   113,   423,     3,   439,   423,
     113,   122,   122,   114,     3,   114,    39,     7,   435,     4,
     120,   435,   120,   555,   131,   111,   490,   559,   469,   514,
     515,   516,    64,    72,    66,     3,   469,    95,     3,   122,
       3,     3,     3,   417,   422,   122,   113,   411,   122,   469,
     122,   415,   584,     3,   418,   112,   434,   113,    81,   124,
      83,   529,   482,   427,   478,   114,   114,   122,   114,   114,
     490,   122,   114,   135,   494,   507,     3,    12,   509,   113,
     511,   512,   513,   114,   122,     3,   118,   119,   120,   114,
     113,   131,   115,   116,   117,   118,   114,   471,   121,   131,
     123,   124,   125,   126,   127,   122,   470,   471,   114,   112,
     122,   122,   114,   122,   122,   135,   111,   122,   482,     3,
     118,   485,     3,   114,   131,   122,   490,   547,   120,   561,
     494,   114,   496,   120,   112,     3,   500,   568,   122,   570,
     581,   173,   122,   122,    70,   630,    70,     3,   581,   122,
     114,   122,   112,   111,     3,   529,   103,   114,   114,   114,
     581,   581,   276,   163,   434,   159,    99,   598,   599,   273,
     231,   602,   274,   604,   352,   470,   309,   539,   275,   428,
      58,   277,   198,   547,   635,   184,   550,    79,    -1,   630,
      -1,   555,    -1,    -1,   625,   559,    -1,    -1,    -1,   577,
      -1,    -1,    -1,    -1,   635,   636,    -1,    -1,   240,    -1,
     630,    -1,    -1,    -1,    -1,    -1,   580,    -1,    -1,   583,
     584,    -1,    -1,   587,    -1,    -1,    -1,    -1,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   304,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    -1,    -1,    -1,    -1,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    -1,    -1,   135,   388,    -1,    -1,    -1,
      67,    68,    69,    -1,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    -1,    81,    -1,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   423,    -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   435,   111,   112,   113,    -1,   115,   116,
     117,   118,     3,    -1,   121,    -1,   123,   124,    -1,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   478,    38,    -1,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    60,
      61,    62,    63,    64,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      -1,    82,    -1,    84,    -1,    86,    87,    88,    89,    90,
      91,    -1,    -1,     1,    -1,     3,     4,     5,     6,     7,
       8,     9,    -1,    -1,    -1,    -1,    14,    -1,    16,    17,
      -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   130,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    -1,    66,    67,
      68,    69,    -1,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    -1,   102,    -1,    -1,    14,    -1,    16,
      17,    -1,    -1,   111,    -1,   113,    -1,   115,   116,   117,
     118,    -1,    -1,    -1,    -1,    -1,   124,   125,   126,   127,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    -1,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    -1,    81,     1,    83,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,    -1,    -1,    14,    -1,
      16,    17,    -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   111,    -1,   113,    -1,   115,   116,
     117,   118,    -1,    39,    -1,    -1,    -1,   124,    -1,   126,
     127,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    -1,    -1,    59,    62,    63,    64,    -1,    66,    -1,
      -1,    67,    68,    69,    -1,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    -1,    81,    -1,    83,    -1,    87,
      88,    -1,    -1,    91,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,   102,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,   111,    -1,   113,    -1,   115,
     116,   117,   118,   121,    -1,    -1,    -1,    -1,   124,    -1,
     126,   127,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    60,    61,    62,    63,    64,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    81,    82,    83,    84,    -1,
      86,    87,    88,    89,    90,    91,    -1,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    -1,    -1,   113,    -1,   115,
     116,   117,   118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     126,   127,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    60,    61,    62,    63,    64,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    -1,    -1,
      -1,    87,    88,    89,    90,    91,     3,     4,     5,     6,
       7,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,   115,
     116,   117,   118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     126,   127,    39,    -1,    -1,    42,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    62,    63,    64,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    83,    -1,    -1,    -1,
      87,    88,    -1,    -1,    91,     3,     4,     5,     6,     7,
       8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,   115,   116,
     117,   118,    -1,    -1,   121,   122,    -1,    -1,    -1,   126,
     127,    39,    -1,    -1,    42,    -1,    -1,    -1,    46,    47,
      48,    -1,     3,     4,     5,     6,     7,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    16,    17,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    81,    82,    83,    -1,    -1,    39,    -1,
      -1,    42,    -1,    -1,    -1,    46,    47,    48,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    42,    -1,    -1,    -1,
      46,    47,    48,    -1,    -1,   113,    -1,   115,   116,   117,
     118,    -1,    -1,    -1,   122,    -1,    -1,    -1,   126,   127,
      81,    82,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   113,    -1,   115,   116,   117,   118,    -1,    -1,
      -1,   122,    -1,    -1,    -1,   126,   127,   113,    -1,   115,
     116,   117,   118,    -1,    -1,    -1,   122,    -1,    -1,    -1,
     126,   127,     3,     4,     5,     6,     7,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    16,    17,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    42,    -1,    -1,    -1,    46,    47,    48,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    42,    -1,    -1,    -1,
      46,    47,    48,    -1,     3,     4,     5,     6,     7,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      81,    82,    83,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    81,    82,    83,    -1,    -1,
      39,    16,    17,    -1,    -1,    -1,    -1,    46,    47,    48,
      -1,    -1,   113,    -1,   115,   116,   117,   118,    -1,    -1,
      -1,   122,    -1,    -1,    39,   126,   127,   113,    -1,   115,
     116,   117,   118,    -1,    -1,    -1,   122,    -1,    -1,    -1,
     126,   127,    81,    82,    83,     3,     4,     5,     6,     7,
       8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    83,    -1,
      -1,    -1,    -1,    -1,   113,    -1,   115,   116,   117,   118,
      -1,    39,    -1,    -1,    -1,    -1,    -1,   126,   127,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,
     115,   116,   117,   118,    -1,    -1,   121,    -1,   123,   124,
     125,   126,   127,     3,     4,     5,     6,     7,     8,     9,
      -1,    -1,    -1,    81,    -1,    83,    16,    17,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,   113,    -1,   115,   116,   117,
     118,    -1,    -1,   121,    -1,   123,   124,    39,   126,   127,
       3,     4,     5,     6,     7,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    83,     3,     4,     5,     6,     7,     8,
       9,    -1,    -1,    -1,    -1,    -1,    39,    16,    17,    81,
      -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,    -1,   115,   116,   117,   118,    -1,
      39,    -1,    -1,    -1,   124,    -1,   126,   127,    -1,   111,
      -1,   113,    -1,   115,   116,   117,   118,    -1,    81,    -1,
      83,    -1,    -1,    -1,   126,   127,     3,     4,     5,     6,
       7,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    81,    -1,    83,    -1,    -1,    -1,    -1,    -1,
     113,   114,   115,   116,   117,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    39,   126,   127,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   111,    -1,   113,    -1,   115,   116,   117,   118,
       3,     4,     5,     6,     7,     8,     9,   126,   127,    -1,
      -1,    -1,    -1,    16,    17,     3,     4,     5,     6,     7,
       8,     9,    -1,    -1,    81,    -1,    83,    -1,    16,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      -1,    39,    16,    17,    -1,    -1,   113,    -1,   115,   116,
     117,   118,    -1,    -1,    -1,    -1,    -1,   124,    -1,   126,
     127,    -1,    -1,    -1,    -1,    39,    -1,    -1,    81,    -1,
      83,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    81,    -1,    83,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     113,   114,   115,   116,   117,   118,    -1,    81,    -1,    83,
      -1,    -1,    39,   126,   127,   113,   114,   115,   116,   117,
     118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,   127,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,   113,
      -1,   115,   116,   117,   118,    16,    17,    -1,    -1,    -1,
      -1,    -1,   126,   127,    81,    -1,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,   115,   116,
     117,   118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,
     127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,     0,
      -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   113,    -1,   115,   116,   117,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   126,   127,    38,    -1,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    60,
      61,    62,    63,    64,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,
      -1,    82,    -1,    84,    85,    86,    87,    88,    89,    90,
      91,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   113,    -1,    -1,    -1,    -1,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    60,    61,
      62,    63,    64,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,
      82,    -1,    84,     3,    86,    87,    88,    89,    90,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   113,   114,    -1,    -1,    -1,   118,    -1,    38,   121,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    -1,
      60,    61,    62,    63,    64,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      80,    -1,    82,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,    -1,    -1,    -1,    38,   118,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    60,
      61,    62,    63,    64,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      -1,    82,    -1,    84,    85,    86,    87,    88,    89,    90,
      91,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    60,    61,    62,    63,    64,    -1,    66,
      -1,    -1,    -1,   124,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   135,    82,    -1,    38,    85,    -1,
      87,    88,    89,    90,    91,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    60,
      61,    62,    63,    64,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,    -1,
      -1,    82,    -1,    -1,    85,    -1,    87,    88,    89,    90,
      91,    38,    -1,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    60,    61,    62,    63,    64,    -1,    66,
      -1,    -1,    -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    -1,    82,    -1,    84,    85,    86,
      87,    88,    89,    90,    91,    38,    -1,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    60,    61,    62,
      63,    64,    -1,    66,    -1,    -1,    -1,   124,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    82,
      -1,    84,    -1,    86,    87,    88,    89,    90,    91,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     113,   114,    -1,    -1,    -1,   118,    -1,    38,   121,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    60,
      61,    62,    63,    64,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      -1,    82,    -1,    84,    -1,    86,    87,    88,    89,    90,
      91,    -1,    38,    -1,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,   114,    60,    61,    62,    63,    64,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    82,    -1,    84,    85,
      86,    87,    88,    89,    90,    91,    38,    -1,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,
      82,    -1,    84,    -1,    86,    87,    88,    89,    90,    91,
      38,    -1,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    -1,    60,    61,    62,    63,    64,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    82,    -1,    84,    38,    86,    87,
      88,    89,    90,    91,    -1,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    60,
      61,    62,    63,    64,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    38,    85,    -1,    87,    88,    89,    90,
      91,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    60,    61,    62,    63,    64,
      -1,    66,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    38,
      -1,    -1,    87,    88,    89,    90,    91,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    60,    61,    62,    63,    64,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    87,    88,
      89,    90,    91
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    38,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    60,    61,    62,    63,    64,    66,    79,    80,
      82,    84,    85,    86,    87,    88,    89,    90,    91,   113,
     118,   165,   166,   169,   170,   171,   172,   178,   181,   182,
     183,   186,   187,   188,   189,   190,   205,   209,   229,   230,
     231,     3,   124,    11,   113,   113,   113,   113,   113,   188,
      82,   182,   190,   191,   111,   113,   130,   167,   168,   188,
     166,   166,     3,   124,   166,   166,   166,   124,   165,   166,
     211,   212,   234,   113,   121,   123,   189,     0,   230,   124,
       3,   139,   179,   180,     3,     4,     5,     6,     7,     8,
      39,    83,   113,   137,   138,   140,   141,   144,     9,    16,
      17,    81,   113,   115,   116,   117,   118,   126,   127,   144,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   164,   170,   175,   182,   197,   197,
     164,     3,     3,   114,   182,   190,     3,    95,   111,   112,
     135,   211,   234,   124,   173,   174,   175,   205,   188,     1,
       3,    14,    59,    67,    68,    69,    71,    72,    73,    74,
      75,    76,    77,    78,   102,   111,   125,   147,   160,   161,
     163,   165,   206,   207,   209,   210,   211,   213,   215,   216,
     217,   218,   219,   220,   226,   165,   233,     3,   114,   130,
     166,   192,   193,   194,   195,    42,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    64,    87,    88,    91,
     118,   121,   122,   161,   172,   184,   185,   191,     3,   179,
     135,   112,   125,   113,   163,   197,    11,    15,    16,    17,
     113,   121,   123,   113,   147,   147,   147,   113,   197,   149,
     118,   128,   129,   116,   117,    18,    19,    20,    21,   130,
     131,    22,    23,   115,   132,   133,    24,    25,   134,   114,
     175,   113,   121,   190,   198,   199,   175,   114,   114,   112,
     114,   114,   114,   112,   196,   168,   124,   161,   200,   232,
     173,   125,   174,   111,   120,   176,   177,   188,   120,    13,
     113,   164,   120,   113,   113,   113,   206,   113,   214,     3,
     111,   111,   111,   163,   113,   214,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,   135,   162,
     111,   112,   213,   216,   211,    95,   113,   130,   188,   190,
     198,   114,   112,   112,   114,   161,   191,     3,   113,   113,
     113,   122,   184,   122,     3,   122,    42,   118,   122,   161,
     113,   112,   125,   164,   125,   180,   161,   114,   114,   144,
       3,   114,   161,   163,     3,    10,   197,   197,   114,   149,
     149,   149,   150,   150,   151,   151,   152,   152,   152,   152,
     153,   153,   154,   155,   156,   157,   158,   163,   114,   192,
     198,    42,   118,   122,   161,   191,   199,   113,   121,     7,
     188,     4,   131,   121,   123,   200,   201,   202,   203,   204,
     211,   125,   164,   111,   112,   120,   206,   212,   163,   120,
     206,   163,   163,   163,    72,   217,   165,   111,   111,     3,
     161,   161,   196,    95,    65,   194,     3,   122,   161,     3,
       3,     3,   122,   113,   161,   122,   122,     3,   125,   112,
     124,   112,   114,   122,   113,   114,   114,   149,   120,   114,
     114,   161,   191,   122,   122,    42,   122,   161,   114,   192,
      42,   118,   122,   161,   191,   114,   135,   188,   164,     3,
     112,   125,   200,   135,   204,   177,   164,    12,   208,   114,
     206,   114,   114,   114,   113,   217,   217,   103,   113,   223,
     224,   131,   196,   122,   114,   114,   114,     3,   122,   112,
      68,   142,   143,   197,   201,   145,   146,   161,   192,   114,
     160,   122,   161,   161,   122,   114,   161,   191,   122,   122,
      42,   122,   161,   111,   200,   135,   122,   125,   200,   202,
     211,    12,   213,   206,   206,   206,   206,   163,   114,   163,
     114,   163,   116,   117,     3,   118,     3,   131,   114,   192,
     120,   112,   114,   120,   112,   125,   114,   112,   195,   122,
     122,   122,   161,   161,   122,   200,   200,   211,    70,    70,
     114,   206,   114,   206,   114,     3,     3,   114,   123,   188,
     114,   161,   143,   161,   125,   161,   122,   122,   206,   206,
     111,   206,   206,   114,   114,   222,     3,   225,   224,   224,
     113,   206,   227,   114,   163,   221,   114,   227,   206,   228
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   136,   137,   137,   137,   137,   137,   138,   138,   138,
     138,   139,   140,   140,   141,   142,   142,   143,   143,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   145,   145,   146,   146,   147,   147,   147,   147,   147,
     147,   147,   148,   148,   148,   148,   148,   148,   149,   149,
     150,   150,   150,   150,   151,   151,   151,   152,   152,   152,
     153,   153,   153,   153,   153,   154,   154,   154,   155,   155,
     156,   156,   157,   157,   158,   158,   159,   159,   160,   160,
     161,   161,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   163,   163,   164,   165,   165,
     165,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   167,   167,   168,   168,   168,   168,   168,   168,   169,
     169,   169,   169,   169,   169,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   171,   171,   171,   172,   172,   172,   173,   173,
     174,   174,   174,   175,   175,   175,   175,   176,   176,   177,
     177,   177,   178,   178,   178,   178,   178,   179,   179,   180,
     180,   181,   182,   182,   182,   182,   183,   183,   183,   183,
     183,   183,   183,   184,   184,   184,   184,   184,   185,   185,
     185,   185,   185,   185,   185,   185,   185,   185,   185,   185,
     185,   186,   186,   187,   187,   188,   188,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   190,   190,   190,   190,   191,   191,   192,
     192,   193,   193,   194,   194,   194,   194,   195,   195,   195,
     196,   196,   197,   197,   198,   198,   198,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   200,   200,
     200,   201,   201,   201,   201,   202,   203,   203,   204,   204,
     205,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   207,   208,   208,   209,   210,   210,   210,   211,   211,
     212,   213,   214,   215,   215,   216,   216,   217,   217,   218,
     218,   219,   219,   219,   220,   220,   220,   220,   220,   220,
     221,   220,   222,   220,   223,   223,   223,   224,   224,   225,
     226,   226,   226,   226,   226,   228,   227,   227,   229,   229,
     230,   230,   230,   232,   231,   231,   233,   231,   231,   234,
     234
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     1,     3,     3,     3,     1,
       4,     3,     4,     6,     3,     3,     2,     6,     2,     6,
       7,     1,     1,     1,     3,     1,     2,     2,     2,     2,
       4,     4,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     5,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     2,     3,
       1,     2,     1,     2,     1,     2,     1,     2,     1,     2,
       1,     1,     3,     3,     1,     7,     5,     4,     6,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     5,     2,     1,     1,     1,     1,     2,
       2,     3,     1,     2,     1,     2,     1,     1,     3,     2,
       3,     1,     4,     5,     5,     6,     2,     1,     3,     3,
       1,     4,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     1,     1,     1,     3,     4,     4,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     5,
       2,     1,     1,     4,     4,     2,     1,     1,     4,     3,
       3,     4,     6,     5,     5,     6,     5,     4,     4,     4,
       8,     3,     4,     3,     2,     2,     1,     1,     2,     3,
       1,     1,     3,     2,     6,     2,     1,     5,     1,     3,
       0,     2,     2,     1,     2,     1,     1,     3,     2,     3,
       5,     4,     5,     4,     3,     3,     3,     4,     6,     5,
       5,     6,     4,     4,     2,     3,     3,     4,     3,     4,
       1,     2,     1,     4,     3,     2,     1,     2,     3,     2,
       7,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     2,     3,     5,     3,     4,     3,     2,     3,
       1,     1,     1,     1,     2,     1,     1,     1,     2,     5,
       7,     7,     5,     5,     5,     7,     6,     7,     6,     7,
       0,    10,     0,     8,     5,     5,     1,     1,     2,     1,
       3,     2,     2,     2,     3,     0,     5,     1,     1,     2,
       1,     1,     1,     0,     5,     3,     0,     4,     2,     1,
       2
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
        case 2:
#line 130 "grammar.y" /* yacc.c:1646  */
    {
      //	printf("XX\n");
      dir_decl *x=currsymtab->findsymbol((yyvsp[0].text));
    	(yyval.ptr)=new tree_expr(x);
    	((tree_expr *)(yyval.ptr))->name=(yyvsp[0].text);
    	((tree_expr *)(yyval.ptr))->nodetype=-1;	}
#line 2521 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 136 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 2527 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 137 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 2533 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 138 "grammar.y" /* yacc.c:1646  */
    {
      (yyval.ptr)=binaryopnode(NULL,NULL,EXPR,-1);
	    statement *t1=temp3; 
    	while(t1->comma==1)t1=t1->prev;
    	((tree_expr *)(yyval.ptr))->exprlist=t1;
      temp1=temp3=t1->prev;//printf("DDDDDDDDDDDDDDDDDDDD\n");
	  }
#line 2545 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 145 "grammar.y" /* yacc.c:1646  */
    { (yyval.ptr)=(yyvsp[0].ptr);}
#line 2551 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 149 "grammar.y" /* yacc.c:1646  */
    {
      (yyval.ptr)=binaryopnode(NULL,NULL,-1,TREE_INT);
    	((tree_expr *)(yyval.ptr))->ival=(yyvsp[0].ival);
    	((tree_expr *)(yyval.ptr))->dtype=0;
  	}
#line 2561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 154 "grammar.y" /* yacc.c:1646  */
    {
      (yyval.ptr)=binaryopnode(NULL,NULL,-1,TREE_FLOAT);
    	((tree_expr *)(yyval.ptr))->fval=(yyvsp[0].fval);
    	((tree_expr *)(yyval.ptr))->dtype=1;}
#line 2570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 158 "grammar.y" /* yacc.c:1646  */
    {
      (yyval.ptr)=binaryopnode(NULL,NULL,-1,TREE_BOOL);
    	((tree_expr *)(yyval.ptr))->ival=(yyvsp[0].ival);
    	((tree_expr *)(yyval.ptr))->dtype=9;}
#line 2579 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 162 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr); printf("%s\n", "test-155");}
#line 2585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 166 "grammar.y" /* yacc.c:1646  */
    {
      (yyval.ptr)=binaryopnode(NULL,NULL,-1,TREE_ENUMCONST);
	    ((tree_expr *)(yyval.ptr))->name=(yyvsp[0].text); }
#line 2593 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 172 "grammar.y" /* yacc.c:1646  */
    {
      char *tempstr=(char *)calloc(100,sizeof(char));
      strcpy(tempstr,(yyvsp[0].text));
      (yyval.ptr)=binaryopnode(NULL,NULL,-1,TREE_STRING);
	    ((tree_expr *)(yyval.ptr))->name=malloc(sizeof(char)*100);
      for(int i=0;i<100;i++) ((tree_expr *)(yyval.ptr))->name[i]='\0';
	    strcpy(((tree_expr *)(yyval.ptr))->name,tempstr);
	    if(strlen((yyvsp[0].text))<=3)((tree_expr *)(yyval.ptr))->dtype=4;
	  }
#line 2607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 181 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_expr();}
#line 2613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 185 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_node();}
#line 2619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 199 "grammar.y" /* yacc.c:1646  */
    {
    	(yyval.ptr)=(yyvsp[0].ptr); }
#line 2626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 201 "grammar.y" /* yacc.c:1646  */
    {
	    if(((tree_expr *)(yyvsp[-3].ptr))->expr_type!=ARRREF){
      	tree_expr *t1;
        t1=(yyvsp[-3].ptr); 
      	if(t1->expr_type!=STRUCTREF){
      		t1->expr_type=ARRREF;
      		(yyval.ptr)=t1;
      	} 
      	else {
      		t1=((tree_expr *)(yyvsp[-3].ptr))->rhs; 
      		t1->expr_type=ARRREF;
      	}
      	assign_stmt *y=t1->earr_list;
      	if(y==NULL){
      		t1->earr_list=((assign_stmt *)(yyvsp[-1].ptr));
      		t1->earr_list->next=NULL;
      	}	else{
      		while(y->next!=NULL){
      			y=y->next;
      		}
      		y->next=((assign_stmt *)(yyvsp[-1].ptr));
      		y->next->next=NULL;
      	}
      	(yyval.ptr)=(yyvsp[-3].ptr);
      } else {
        ((tree_expr *)(yyvsp[-3].ptr))->expr_type=ARRREF;
    	  assign_stmt *y=((tree_expr *)(yyvsp[-3].ptr))->earr_list;
    	  if(y==NULL){
      		((tree_expr *)(yyvsp[-3].ptr))->earr_list=((assign_stmt *)(yyvsp[-1].ptr));
      		((tree_expr *)(yyvsp[-3].ptr))->earr_list->next=NULL;
      	}	else{
      		while(y->next!=NULL){
      			y=y->next;
    		  }
      		y->next=((assign_stmt *)(yyvsp[-1].ptr));
      		y->next->next=NULL;
    	  }
    	  (yyval.ptr)=(yyvsp[-3].ptr);
    	}
    	temp1=temp3->prev; 
    	temp3->prev=NULL; 
    	temp1->next=NULL;}
#line 2673 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 243 "grammar.y" /* yacc.c:1646  */
    {
    	tree_expr *t1=(yyvsp[-2].ptr);
  	  if(t1->expr_type!=STRUCTREF){
        t1=funcallpostfix(t1,FUNCALL,KERNEL,NULL);
    	} else {
        t1=((tree_expr *)(yyvsp[-2].ptr))->rhs;
        t1=funcallpostfix(t1,FUNCALL,KERNEL,NULL);
	    }
	    (yyval.ptr)=(yyvsp[-2].ptr);}
#line 2687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 252 "grammar.y" /* yacc.c:1646  */
    {
  		tree_expr *t1=(yyvsp[-3].ptr);
  		if(t1->expr_type!=STRUCTREF){
        t1=funcallpostfix(t1,FUNCALL,KERNEL,(yyvsp[-1].ptr));
			  FUNCALL_FLAG=1;
        struct funcall_list *funtemp=malloc(sizeof(struct funcall_list));
        funtemp->name=malloc(sizeof(char)*100);
        if(t1->name!=NULL) strcpy(funtemp->name,t1->name);
        funtemp->call=t1;
        if(fhead!=NULL)funtemp->next=fhead;
        else funtemp->next=NULL;
        fhead=funtemp;
		  } else {
        t1=((tree_expr *)(yyvsp[-3].ptr))->rhs;
        t1=funcallpostfix(t1,FUNCALL,KERNEL,(yyvsp[-1].ptr));
      }
      t1=(yyvsp[-3].ptr);
      if(t1->expr_type==STRUCTREF&& t1->rhs && t1->rhs->name &&!(strcmp(t1->rhs->name,"updateFunction"))){
        tree_expr *tt1=t1->rhs;
        tree_expr *funname=tt1->arglist->rhs;
        for (std::map<char *,statement *>::iterator it1=fnames.begin(); it1!=fnames.end(); ++it1){
          if (!strcmp(funname->name, it1->first)&&(strlen(funname->name)==strlen(it1->first))){
            statement *update_decl= it1->second;
            update_decl->noprint=true;
            break;
          }
        }
      }
    }
#line 2721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 281 "grammar.y" /* yacc.c:1646  */
    {
      assign_stmt *pt1=createassignlhsrhs(-1,NULL,(yyvsp[-3].ptr)); 
      tree_expr *t1;
      t1=(yyvsp[-5].ptr);
      if(arglistflag==1){
        arglistflag=0;
        pt1->next=(yyvsp[-1].ptr);
      } else {
        if(t1->expr_type!=STRUCTREF)t1->params=(yyvsp[-1].ptr);
        else t1->rhs->params=(yyvsp[-1].ptr);
      }
      if(t1->expr_type!=STRUCTREF){
        t1->expr_type=FUNCALL;
        t1->kernel=KERNEL;
        t1->arglist=pt1;
        struct funcall_list *funtemp=malloc(sizeof(struct funcall_list));
        funtemp->name=malloc(sizeof(char)*100);
        if(t1->name!=NULL)strcpy(funtemp->name,t1->name); 
        funtemp->call=t1;
        if(fhead!=NULL)funtemp->next=fhead;
        else funtemp->next=NULL;
        fhead=funtemp;
        FUNCALL_FLAG=1;
  	  } else   {
  		  ((tree_expr *)(yyvsp[-5].ptr))->rhs->expr_type=FUNCALL;
  		  ((tree_expr *)(yyvsp[-5].ptr))->rhs->kernel=KERNEL;
  		  t1->rhs->arglist=pt1;
      }
	    (yyval.ptr)=(yyvsp[-5].ptr);
      if(t1->expr_type==STRUCTREF&&!(strcmp(t1->rhs->name,"addPointProperty"))){   
        adddynamicproperty(t1,P_P_TYPE,pt1);
      }
      if(t1->expr_type==STRUCTREF&&!(strcmp(t1->rhs->name,"addEdgeProperty"))){
        adddynamicproperty(t1,E_P_TYPE,pt1);
      }
      if(t1->expr_type==STRUCTREF&&!(strcmp(t1->rhs->name,"addProperty"))){
        addgraphproperty(t1,G_P_TYPE,pt1);
      }
      if(t1->expr_type==STRUCTREF&&!(strcmp(t1->rhs->name,"OrderByIntValue"))){
          dir_decl *d1=currsymtab->findsymbol(t1->lhs->name);
          d1->ordered=true;
      }
    }
#line 2769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 324 "grammar.y" /* yacc.c:1646  */
    {
      (yyval.ptr)= binaryopnode((yyvsp[-2].ptr),NULL,PTRREF,-1);
      ((tree_expr *)(yyval.ptr))->rhs=new tree_expr();
      ((tree_expr *)((tree_expr *)(yyval.ptr))->rhs)->name=(yyvsp[0].text);
      ((tree_expr *)((tree_expr *)(yyval.ptr))->rhs)->expr_type=VAR;
    }
#line 2780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 330 "grammar.y" /* yacc.c:1646  */
    {
      (yyval.ptr)= binaryopnode((yyvsp[-2].ptr),NULL,STRUCTREF,-1);
      ((tree_expr *)(yyval.ptr))->rhs=new tree_expr();
      ((tree_expr *)((tree_expr *)(yyval.ptr))->rhs)->name=(yyvsp[0].text);
      ((tree_expr *)((tree_expr *)(yyval.ptr))->rhs)->expr_type=VAR;
      ((tree_expr *)(yyval.ptr))->kernel=KERNEL;
      ((tree_expr *)((yyvsp[-2].ptr)))->nodetype=-10;
    }
#line 2793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 338 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)= binaryopnode((yyvsp[-1].ptr),NULL,POSTINC,-1);}
#line 2799 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 339 "grammar.y" /* yacc.c:1646  */
    { 
      (yyval.ptr)= binaryopnode((yyvsp[-5].ptr),NULL,GET_TYPE,-1);
      ((tree_expr *)(yyval.ptr))->rhs=new tree_expr();
      ((tree_expr *)((tree_expr *)(yyval.ptr))->rhs)->name=(yyvsp[-3].text);
      ((tree_expr *)((tree_expr *)(yyval.ptr))->rhs)->expr_type=VAR;
      ((tree_expr *)((tree_expr *)(yyval.ptr))->rhs)->nextv=(yyvsp[0].ptr);
      tree_expr *u1=(yyvsp[-5].ptr);
      if(u1->expr_type==VAR && ((dir_decl *)(u1->lhs))->libdtype==GRAPH_TYPE){
        dir_decl *dg=u1->lhs;
        tree_typedecl *tpold= dg->tp1;
        tree_typedecl *tp1;
        tp1=new tree_typedecl();
        tp1->libdatatype=GRAPH_TYPE; 
        tp1->name=malloc(sizeof(char)*100);
        strcpy(tp1->name,libdtypenames[tp1->libdatatype]);
        if(dg->ppts!=NULL){
          extra_ppts *newppts,*oldppts=dg->ppts,*head;
          newppts=malloc(sizeof(struct extra_ppts));
          newppts->parent=NULL;
          newppts->name=malloc(sizeof(char)*100);
          strncpy(newppts->name,oldppts->name,strlen(oldppts->name));
          newppts->libdtype=oldppts->libdtype;
          newppts->t1=oldppts->t1;//mutliple entries point to same type
          newppts->var2=oldppts->var2;
          newppts->var1=oldppts->var1;
          newppts->var3=oldppts->var3;
          newppts->val2=oldppts->val2;
          if(oldppts->var2!=NULL){
		      }
		      newppts->next=NULL;
		      newppts->parent=dg;
          head=newppts;
          oldppts=oldppts->next;
          while(oldppts){
            newppts->next=malloc(sizeof(struct extra_ppts));
            newppts=newppts->next;
            newppts->parent=NULL;
            newppts->name=malloc(sizeof(char)*100);
            strcpy(newppts->name,oldppts->name);
            newppts->libdtype=oldppts->libdtype;
            newppts->t1=oldppts->t1;
            newppts->var2=new dir_decl();
            newppts->val2=oldppts->val2;
            newppts->var2->name=malloc(sizeof(char)*100);
            if(oldppts->var2!=NULL)strncpy(newppts->var2->name,oldppts->var2->name,strlen(oldppts->var2->name));
            newppts->next=NULL;
            oldppts=oldppts->next;
          }
          tp1->ppts=head;
        }
        symtableentry *old=NULL;currsymtab->addsymbol((dir_decl *)(yyvsp[0].ptr),(tree_typedecl *)tp1);
      }
	  }
#line 2857 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 392 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)= binaryopnode((yyvsp[-1].ptr),NULL,POSTDEC,-1);}
#line 2863 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 393 "grammar.y" /* yacc.c:1646  */
    {
      (yyval.ptr)=new tree_expr();
      ((tree_expr *)(yyval.ptr))->expr_type=TYPE_INIT;
      ((tree_expr *)(yyval.ptr))->tpname=(yyvsp[-4].ptr);
      ((tree_expr *)(yyval.ptr))->rhs=new tree_expr();
      ((tree_expr*)(yyval.ptr))->rhs->expr_type=INITBLOCK;
      ((tree_expr*)(yyval.ptr))->rhs->rhs=(yyvsp[-1].ptr);}
#line 2875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 400 "grammar.y" /* yacc.c:1646  */
    {
      (yyval.ptr)=new tree_expr();
      ((tree_expr *)(yyval.ptr))->expr_type=TYPE_INIT;
      ((tree_expr *)(yyval.ptr))->tpname=(yyvsp[-5].ptr);
      ((tree_expr *)(yyval.ptr))->rhs=new tree_expr();
      ((tree_expr*)(yyval.ptr))->rhs->expr_type=INITBLOCK;
      ((tree_expr*)(yyval.ptr))->rhs->rhs=(yyvsp[-2].ptr);}
#line 2887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 409 "grammar.y" /* yacc.c:1646  */
    {
	    (yyval.ptr)=(yyvsp[0].ptr);arglistflag=1;}
#line 2894 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 411 "grammar.y" /* yacc.c:1646  */
    {
	    (yyval.ptr)=(yyvsp[0].ptr);}
#line 2901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 416 "grammar.y" /* yacc.c:1646  */
    {
      assign_stmt *t1=createassignlhsrhs(-1,NULL,(yyvsp[0].ptr)); 
      (yyval.ptr)=t1;
      argcount++;}
#line 2910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 420 "grammar.y" /* yacc.c:1646  */
    {
      assign_stmt *t1=(yyvsp[-2].ptr);
      while(t1->next!=NULL)t1=t1->next; 
      t1->next=createassignlhsrhs(-1,NULL,(yyvsp[0].ptr));
      t1=t1->next;
      (yyval.ptr)=(yyvsp[-2].ptr);
      argcount++;}
#line 2922 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 430 "grammar.y" /* yacc.c:1646  */
    {
    	//printf("xxXXX\n");
    	(yyval.ptr)=(yyvsp[0].ptr);}
#line 2930 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 433 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=binaryopnode((yyvsp[0].ptr),NULL,PREINC,-1);}
#line 2936 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 434 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=binaryopnode((yyvsp[0].ptr),NULL,PREDEC,-1);}
#line 2942 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 435 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=binaryopnode((yyvsp[0].ptr),NULL,((tree_expr *)((yyvsp[-1].ptr)))->expr_type,-1);}
#line 2948 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 436 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=binaryopnode(NULL,(yyvsp[0].ptr),TYPE_SIZEOF,-1);  }
#line 2954 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 437 "grammar.y" /* yacc.c:1646  */
    {
      (yyval.ptr)=new tree_expr();
      ((tree_expr *)(yyval.ptr))->tpname=(yyvsp[-1].ptr);
      ((tree_expr *)(yyval.ptr))->expr_type=TYPE_SIZEOF;
    }
#line 2964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 442 "grammar.y" /* yacc.c:1646  */
    {            (yyval.ptr)=new tree_id();}
#line 2970 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 446 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_expr(); ((tree_expr *)(yyval.ptr))->expr_type=UNARYAND;}
#line 2976 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 447 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_expr(); ((tree_expr *)(yyval.ptr))->expr_type=UNARYMUL;}
#line 2982 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 448 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_expr(); ((tree_expr *)(yyval.ptr))->expr_type=UNARYADD;}
#line 2988 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 449 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_expr(); ((tree_expr *)(yyval.ptr))->expr_type=UNARYSUB;}
#line 2994 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 450 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_expr(); ((tree_expr *)(yyval.ptr))->expr_type=COMP;}
#line 3000 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 451 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_expr(); ((tree_expr *)(yyval.ptr))->expr_type=NOT;}
#line 3006 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 455 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 456 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=binaryopnode(NULL,(yyvsp[0].ptr),CAST_EXPR,0);
  		((tree_expr *)(yyval.ptr))->tpname=(yyvsp[-2].ptr);}
#line 3020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 462 "grammar.y" /* yacc.c:1646  */
    {
	    (yyval.ptr)=(yyvsp[0].ptr);}
#line 3027 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 464 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)= binaryopnode((tree_expr *)(yyvsp[-2].ptr),(tree_expr *)(yyvsp[0].ptr),MUL,-1);}
#line 3033 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 465 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)= binaryopnode((tree_expr *)(yyvsp[-2].ptr),(tree_expr *)(yyvsp[0].ptr),DIV,-1);}
#line 3039 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 466 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=  binaryopnode((tree_expr *)(yyvsp[-2].ptr),(tree_expr *)(yyvsp[0].ptr),MOD,-1);}
#line 3045 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 470 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3051 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 471 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=  binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),ADD,-1);}
#line 3057 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 472 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)= binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),SUB,-1);}
#line 3063 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 476 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3069 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 477 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)= binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),LSHIFT,-1);}
#line 3075 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 478 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=  binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),RSHIFT,-1);}
#line 3081 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 482 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3087 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 483 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)= binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),LT,-1);}
#line 3093 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 484 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=  binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),GT,-1);}
#line 3099 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 485 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=  binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),LE,-1);}
#line 3105 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 486 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=  binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),GE,-1);}
#line 3111 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 490 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3117 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 491 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=  binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),EQ,-1);}
#line 3123 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 492 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=  binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),NEQ,-1);}
#line 3129 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 496 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3135 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 497 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=  binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),BAND,-1);}
#line 3141 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 501 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3147 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 502 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=  binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),XOR,-1);}
#line 3153 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 506 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3159 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 507 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=  binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),BOR,-1);}
#line 3165 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 511 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3171 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 512 "grammar.y" /* yacc.c:1646  */
    {  (yyval.ptr)=  binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),AND,-1);}
#line 3177 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 516 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3183 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 517 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=  binaryopnode((yyvsp[-2].ptr),(yyvsp[0].ptr),OR,-1);}
#line 3189 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 521 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3195 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 522 "grammar.y" /* yacc.c:1646  */
    {
      (yyval.ptr)=binaryopnode((yyvsp[-4].ptr),NULL,COND_OP,0);
      ((tree_expr *)(yyval.ptr))->rhs=binaryopnode(temp3->stassign->rhs,(yyvsp[0].ptr),-1,0);
      temp1=temp1->prev;
      temp1->next=NULL;
      temp3=temp1;
    }
#line 3207 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 532 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=(yyvsp[0].ptr);
  		assflag=0;
    }
#line 3216 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 536 "grammar.y" /* yacc.c:1646  */
    {
  		((assign_stmt *)(yyvsp[-1].ptr))->lhs=(tree_expr *)(yyvsp[-2].ptr);
  		((tree_expr *)(yyvsp[-2].ptr))->kernel=5;
  		((tree_expr *)(yyvsp[0].ptr))->kernel=5;
  		((assign_stmt *)(yyvsp[-1].ptr))->rhs=(tree_expr *)(yyvsp[0].ptr);
  		(yyval.ptr)=(yyvsp[-1].ptr);/*((assign_stmt *)$2)->print1(1);*/
  		temp3=createstmt(ASSIGN_STMT,NULL,NULL,LINENO); 
  		temp3->stmtno=STMTNO;
  		temp3->stassign=(yyval.ptr);
  		if(temp1==NULL){temp1=temp3;temp=G1=temp1; }
  		else {
  			if(temp1->sttype==ASSIGN_STMT  &&temp1->stmtno==STMTNO && temp1->stassign->lhs!=NULL){ 
  				temp1->prev->next=temp3; 
  				temp3->prev=temp1->prev;
  				temp1->prev=temp3;
  				temp3->next=temp1;
  				temp1=temp3;
  				((assign_stmt *)(yyvsp[-1].ptr))->rhs=NULL;
  			}
  			else {             linkstmt(&temp1,temp3);			}
  			assflag=1;
  		}
  		if(FUNCALL_FLAG==1 && fhead!=NULL)fhead->ass=(yyvsp[-1].ptr);
  		FUNCALL_FLAG=0;}
#line 3245 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 563 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createassign(AASSIGN);		arrtop=0;}
#line 3251 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 564 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createassign(AMUL_ASSIGN);}
#line 3257 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 565 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createassign(ADIV_ASSIGN);}
#line 3263 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 566 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createassign(AMOD_ASSIGN);}
#line 3269 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 567 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createassign(AADD_ASSIGN);}
#line 3275 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 568 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createassign(RRADD_ASSIGN);}
#line 3281 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 569 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createassign(RRMUL_ASSIGN);}
#line 3287 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 570 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createassign(ASUB_ASSIGN);}
#line 3293 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 571 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createassign(ALEFT_ASSIGN);}
#line 3299 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 572 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createassign(ARIGHT_ASSIGN);}
#line 3305 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 573 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createassign(AAND_ASSIGN);}
#line 3311 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 574 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createassign(AXOR_ASSIGN);}
#line 3317 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 575 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createassign(AOR_ASSIGN);}
#line 3323 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 579 "grammar.y" /* yacc.c:1646  */
    {
  		if(assflag==0  ){
  			temp3=createstmt(ASSIGN_STMT,NULL,NULL,LINENO);
  			temp3->stassign=createassignlhsrhs(-1,NULL,(yyvsp[0].ptr));
  			if(temp1)temp1->next=temp3;
  			temp3->prev=temp1;
  			temp1=temp3;
  			(yyval.ptr)=new assign_stmt();
  			((assign_stmt *)(yyval.ptr))->rhs=(yyvsp[0].ptr);
  		} else {(yyval.ptr)=(yyvsp[0].ptr);}}
#line 3338 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 589 "grammar.y" /* yacc.c:1646  */
    {
  		if(assflag==0){
  			temp3=createstmt(ASSIGN_STMT,NULL,NULL,LINENO);
  			temp3->stassign=createassignlhsrhs(-1,NULL,(yyvsp[0].ptr)); 
        linkstmt(&temp1,temp3);
  		}
      temp3->comma=1;}
#line 3350 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 599 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3356 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 603 "grammar.y" /* yacc.c:1646  */
    {
  		#ifdef DEBUGGING
        printf("%s\n", "declaration-1");
      #endif

      (yyval.ptr)=createdeclstmt((yyvsp[-1].ptr),NULL,NULL);
  		symtableentry *old=NULL;
  		if(((tree_typedecl *)(yyvsp[-1].ptr))->datatype>9)currsymtab->addsymbol((dir_decl *)NULL,(tree_typedecl *)(yyvsp[-1].ptr));
  		temp3=createstmt(DECL_STMT,NULL,NULL,LINENO);
  		temp3->stdecl=(yyval.ptr);
  		if(temp1==NULL){
  			temp1=temp3;
  		  temp=G1=temp1;
  		} else{ linkstmt(&temp1,temp3);}
		}
#line 3376 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 618 "grammar.y" /* yacc.c:1646  */
    {
  		#ifdef DEBUGGING
        printf("%s\n", "declaration-2");
      #endif

      symtableentry *old=NULL;
  		currsymtab->addsymbol((dir_decl *)(yyvsp[-1].ptr),(tree_typedecl *)(yyvsp[-2].ptr));
  		(yyval.ptr)=createdeclstmt((yyvsp[-2].ptr),NULL,(yyvsp[-1].ptr));
  		temp3=createstmt(DECL_STMT,NULL,NULL,LINENO);
  		temp3->stdecl=(yyval.ptr);
  		if(temp1==NULL){
  			temp1=temp3;
  			G1=temp=temp1;
  		} else{
        linkstmt(&temp1,temp3);
  		}
  	}
#line 3398 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 635 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "declaration-3");
      #endif

      (yyval.ptr)=new symtableentry();}
#line 3409 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 644 "grammar.y" /* yacc.c:1646  */
    {
  		tree_typedecl *t1=(yyvsp[-1].ptr); 
  		t1->next=(yyvsp[0].ptr);
  		(yyval.ptr)=(yyvsp[-1].ptr);}
#line 3418 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 648 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3424 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 649 "grammar.y" /* yacc.c:1646  */
    { 
  		tree_typedecl *t1=(yyvsp[-1].ptr);
  		t1->next=(yyvsp[0].ptr);
  		(yyval.ptr)=(yyvsp[-1].ptr);}
#line 3433 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 653 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "declaration_specifiers-4");
      #endif
		  (yyval.ptr)=(yyvsp[0].ptr);
    }
#line 3444 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 659 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=new tree_typedecl();
  		((tree_typedecl *)(yyval.ptr))->name=malloc(sizeof(char)*100); 
  		strcpy(((tree_typedecl *)(yyval.ptr))->name,((dir_decl *)(yyvsp[-1].ptr))->name);
  		((tree_typedecl *)(yyval.ptr))->next=(yyvsp[0].ptr);
  		(yyval.ptr)=(yyvsp[-1].ptr);}
#line 3455 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 665 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=new tree_typedecl();
  		((tree_typedecl *)(yyval.ptr))->datatype=-1;
  		((tree_typedecl *)(yyval.ptr))->name=malloc(sizeof(char)*100);
  		strcpy(((tree_typedecl *)(yyval.ptr))->name,((dir_decl *)(yyvsp[0].ptr))->name);}
#line 3465 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 670 "grammar.y" /* yacc.c:1646  */
    {
  		strcat(((tree_typedecl *)(yyvsp[0].ptr))->name,((dir_decl *)(yyvsp[-1].ptr))->name);
  		(yyval.ptr)=(yyvsp[0].ptr);}
#line 3473 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 673 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=new tree_typedecl();
  		((tree_typedecl *)(yyval.ptr))->name=malloc(sizeof(char)*100);
  		strcpy(((tree_typedecl *)(yyval.ptr))->name,((dir_decl *)(yyvsp[0].ptr))->name);}
#line 3482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 677 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_typedecl();}
#line 3488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 678 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_typedecl();}
#line 3494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 682 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3500 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 683 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-2].ptr); while(t1->nextv!=NULL)t1=t1->nextv;
  		t1->nextv=(yyvsp[0].ptr);
  		(yyval.ptr)=(yyvsp[-2].ptr);}
#line 3509 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 690 "grammar.y" /* yacc.c:1646  */
    {((dir_decl *)(yyvsp[-2].ptr))->rhs=(yyvsp[0].ptr);(yyval.ptr)=(yyvsp[-2].ptr);}
#line 3515 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 691 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=(yyvsp[0].ptr);
  		((dir_decl *)(yyvsp[0].ptr))->rhs=NULL;
  	}
#line 3524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 695 "grammar.y" /* yacc.c:1646  */
    {
  		((dir_decl *)(yyvsp[-2].ptr))->gpu=1;
  		((dir_decl *)(yyvsp[-2].ptr))->rhs=(yyvsp[0].ptr);
      GPUCODEFLAG=1;
  		(yyval.ptr)=(yyvsp[-2].ptr);}
#line 3534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 700 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=new tree_id();
  		((dir_decl *)(yyvsp[0].ptr))->gpu=1;
      GPUCODEFLAG=1;
  		(yyval.ptr)=(yyvsp[0].ptr);}
#line 3544 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 705 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=(yyvsp[0].ptr);
  		((dir_decl *)(yyvsp[0].ptr))->parent=currsymtab->findsymbol((yyvsp[-2].text));
  	}
#line 3553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 709 "grammar.y" /* yacc.c:1646  */
    {
  		((dir_decl *)(yyvsp[-2].ptr))->parent=currsymtab->findsymbol((yyvsp[-4].text));
  		((dir_decl *)(yyvsp[-2].ptr))->rhs=(yyvsp[0].ptr);
  		(yyval.ptr)=(yyvsp[-2].ptr);}
#line 3562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 716 "grammar.y" /* yacc.c:1646  */
    {	(yyval.ptr)= createstoragedef(TYPEDEF_TYPE,TYPEDEF_STR);	}
#line 3568 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 717 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)= createstoragedef(-1,EXTERN_STR);	}
#line 3574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 718 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)= createstoragedef(-1,STATIC_STR);		}
#line 3580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 719 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_typedecl();}
#line 3586 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 720 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)= createstoragedef(-1,AUTO_STR);		}
#line 3592 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 721 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)= createstoragedef(-1,REGISTER_STR);	
		  DECLTYPE=(yyval.ptr);	}
#line 3599 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 726 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createtypedef(VOID_TYPE); 	}
#line 3605 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 727 "grammar.y" /* yacc.c:1646  */
    { 		(yyval.ptr)= createtypedef(CHAR_TYPE); 	}
#line 3611 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 728 "grammar.y" /* yacc.c:1646  */
    { 		(yyval.ptr)= createtypedef(SHORT_TYPE); 		}
#line 3617 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 729 "grammar.y" /* yacc.c:1646  */
    { 		(yyval.ptr)= createtypedef(INT_TYPE); 	}
#line 3623 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 730 "grammar.y" /* yacc.c:1646  */
    { 		(yyval.ptr)= createtypedef(LONG_TYPE); 	}
#line 3629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 731 "grammar.y" /* yacc.c:1646  */
    { 		(yyval.ptr)= createtypedef(FLOAT_TYPE); 		}
#line 3635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 732 "grammar.y" /* yacc.c:1646  */
    { 		(yyval.ptr)= createtypedef(DOUBLE_TYPE); 		}
#line 3641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 733 "grammar.y" /* yacc.c:1646  */
    { 		(yyval.ptr)= createtypedef(SIGNED_TYPE); 		}
#line 3647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 734 "grammar.y" /* yacc.c:1646  */
    { 		(yyval.ptr)= createtypedef(UNSIGNED_TYPE); 		}
#line 3653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 735 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=(yyvsp[0].ptr);
  		if(((tree_typedecl *)(yyval.ptr))->datatype==STRUCTREC_TYPE)strcat(((tree_typedecl *)(yyval.ptr))->name," *");}
#line 3661 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 738 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "type_specifier-11");
      #endif
      (yyval.ptr)=(yyvsp[0].ptr);}
#line 3671 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 743 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createtypedef(BOOL_TYPE);	  }
#line 3677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 744 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_typedecl();}
#line 3683 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 745 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_typedecl();}
#line 3689 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 746 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_typedecl();}
#line 3695 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 747 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=new tree_typedecl();
  		((tree_typedecl *)(yyval.ptr))->datatype=TYPEDEF_TNAME;
  		((tree_typedecl *)(yyval.ptr))->name=malloc(sizeof(char)*100);
  		strcpy(((tree_typedecl *)(yyval.ptr))->name,(yyvsp[0].text));
  	}
#line 3706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 753 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 757 "grammar.y" /* yacc.c:1646  */
    {
  		((tree_typedecl *)(yyvsp[-3].ptr))->list=(yyvsp[-1].ptr);
  		(yyval.ptr)=(yyvsp[-3].ptr);
  		((tree_typedecl *)(yyval.ptr))->name=NULL;
  		((tree_typedecl *)(yyval.ptr))->def=1;
  	}
#line 3723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 763 "grammar.y" /* yacc.c:1646  */
    {
  		strcat(((tree_typedecl *)(yyvsp[-4].ptr))->name,(yyvsp[-3].text));
  		((tree_typedecl *)(yyvsp[-4].ptr))->list=(yyvsp[-1].ptr);
  		((tree_typedecl *)(yyvsp[-4].ptr))->def=1;
  		(yyval.ptr)=(yyvsp[-4].ptr);
  		((tree_typedecl *)(yyval.ptr))->vname=malloc(sizeof(char)*100);
  		strcpy(((tree_typedecl *)(yyval.ptr))->vname,(yyvsp[-3].text));
  	}
#line 3736 "y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 771 "grammar.y" /* yacc.c:1646  */
    {
  		strcat(((tree_typedecl *)(yyvsp[-1].ptr))->name,(yyvsp[0].text));
  		((tree_typedecl *)(yyvsp[-1].ptr))->def=0;
  		(yyval.ptr)=(yyvsp[-1].ptr);
  		((tree_typedecl *)(yyval.ptr))->vname=malloc(sizeof(char)*100);
  		strcpy(((tree_typedecl *)(yyval.ptr))->vname,(yyvsp[0].text));
  	}
#line 3748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 781 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)= createcompounddef(STRUCT_TYPE,"struct ");	}
#line 3754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 782 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)= createcompounddef(STRUCTREC_TYPE,"struct");	}
#line 3760 "y.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 783 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)= createcompounddef(UNION_TYPE,"union");	}
#line 3766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 787 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 788 "grammar.y" /* yacc.c:1646  */
    {
  		tree_decl_stmt *t1=(yyvsp[-1].ptr);
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=(yyvsp[0].ptr);
  		(yyval.ptr)=(yyvsp[-1].ptr);
  	}
#line 3783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 797 "grammar.y" /* yacc.c:1646  */
    {
		(yyval.ptr)=createdeclstmt((yyvsp[-1].ptr),NULL,NULL);
		symtableentry *old=NULL;
		if(((tree_typedecl *)(yyvsp[-1].ptr))->datatype!=STRUCTREC_TYPE)currsymtab->addsymbol((dir_decl *)NULL,(tree_typedecl *)(yyvsp[-1].ptr));}
#line 3792 "y.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 801 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=createdeclstmt((yyvsp[-2].ptr),NULL,(yyvsp[-1].ptr));
  		symtableentry *old=NULL;
  		if(((tree_typedecl *)(yyvsp[-2].ptr))->datatype==STRUCT_TYPE||((tree_typedecl *)(yyvsp[-2].ptr))->datatype==STRUCTREC_TYPE ||  ((tree_typedecl *)(yyvsp[-2].ptr))->datatype==ENUM_TYPE||((tree_typedecl *)(yyvsp[-2].ptr))->datatype==UNION_TYPE)
  			currsymtab->addsymbol((dir_decl *)(yyvsp[-1].ptr),(tree_typedecl *)(yyvsp[-2].ptr));
  	}
#line 3803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 807 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_id();}
#line 3809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 811 "grammar.y" /* yacc.c:1646  */
    {
  		tree_typedecl *t1=(yyvsp[-1].ptr); 
  		t1->next=(yyvsp[0].ptr);
  		(yyval.ptr)=(yyvsp[-1].ptr);
  	}
#line 3819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 816 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=(yyvsp[0].ptr);
  	}
#line 3827 "y.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 819 "grammar.y" /* yacc.c:1646  */
    {
  		tree_typedecl *t1=new tree_typedecl();
  		t1->name=malloc(sizeof(char)*100);
  		strcpy(t1->name,((dir_decl *)(yyvsp[-1].ptr))->name);
  		t1->next=(yyvsp[0].ptr);
  		(yyval.ptr)=t1;
  	}
#line 3839 "y.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 826 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=new tree_typedecl();
  		((tree_typedecl *)(yyval.ptr))->name=malloc(sizeof(char)*100);
  		strcpy(((tree_typedecl *)(yyval.ptr))->name,((dir_decl *)(yyvsp[0].ptr))->name);
  	}
#line 3849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 834 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 835 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-2].ptr); 
  		while(t1->nextv!=NULL)t1=t1->nextv;
  		t1->nextv=(yyvsp[0].ptr);
  		(yyval.ptr)=(yyvsp[-2].ptr);
  	}
#line 3866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 844 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_id();}
#line 3872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 845 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=(yyvsp[-2].ptr);
  		((dir_decl *)(yyval.ptr))->structexpr=(yyvsp[0].ptr);
  	}
#line 3881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 849 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 853 "grammar.y" /* yacc.c:1646  */
    { 
      tree_typedecl *S= createcompounddef(ENUM_TYPE,NULL);
  		S->def=1;
  		S->list=new tree_decl_stmt();
  		S->list->dirrhs=(yyvsp[-1].ptr);
  		(yyval.ptr)=S;
  	}
#line 3899 "y.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 860 "grammar.y" /* yacc.c:1646  */
    { 
      tree_typedecl *S= createcompounddef(ENUM_TYPE,NULL);
  		S->def=1;
  		S->list=new tree_decl_stmt();
  		S->list->dirrhs=(yyvsp[-2].ptr);
  		(yyval.ptr)=S;
  	}
#line 3911 "y.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 867 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "enum_specifier-3");
      #endif
      tree_typedecl *S= createcompounddef(ENUM_TYPE,"enum");
  		strcat(S->name, (yyvsp[-3].text));
  		S->vname=malloc(sizeof(char)*100);
  		strcpy(S->vname,(yyvsp[-3].text));
  		 S->def=1;
  		S->list=new tree_decl_stmt();
  		S->list->dirrhs=(yyvsp[-1].ptr);
  		(yyval.ptr)=S;
  	}
#line 3929 "y.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 880 "grammar.y" /* yacc.c:1646  */
    { 
      tree_typedecl *S= createcompounddef(ENUM_TYPE,"eunm");
  		strcat(S->name, (yyvsp[-4].text));
  		S->name=malloc(sizeof(char)*100);
  		S->vname=malloc(sizeof(char)*100);
  		strcpy(S->vname,(yyvsp[-4].text));
  		S->def=1;
  		S->list=new tree_decl_stmt();
  		S->list->dirrhs=(yyvsp[-2].ptr);
  		(yyval.ptr)=S;
  	}
#line 3945 "y.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 891 "grammar.y" /* yacc.c:1646  */
    { 
      tree_typedecl *S= createcompounddef(ENUM_TYPE,"enum");
  		strcat(S->name, (yyvsp[0].text));
  		S->vname=malloc(sizeof(char)*100);
  		strcpy(S->vname,(yyvsp[0].text));
  		S->def=0;
  		S->list=new tree_decl_stmt();
  	}
#line 3958 "y.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 902 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 903 "grammar.y" /* yacc.c:1646  */
    {
	    #ifdef DEBUGGING
        printf("%s\n", "enumerator_list-2");
      #endif
      
      dir_decl *t1=(yyvsp[-2].ptr);
		  while(t1->nextv!=NULL)t1=t1->nextv;
		  t1->nextv=(yyvsp[0].ptr);
		  (yyval.ptr)=(yyvsp[-2].ptr);
	  }
#line 3979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 916 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=new dir_decl();
  		((dir_decl *)(yyval.ptr))->name=((tree_expr *)(yyvsp[-2].ptr))->name;
  		((dir_decl *)(yyval.ptr))->idrhs=(yyvsp[0].ptr);
  		((dir_decl *)(yyval.ptr))->ctype=CENUM_TYPE;
  	}
#line 3990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 922 "grammar.y" /* yacc.c:1646  */
    {
		  #ifdef DEBUGGING
        printf("%s %s\n", "enumeration_constant-2", ((tree_expr *)(yyvsp[0].ptr))->name);
      #endif
      
      (yyval.ptr)=new dir_decl();
  		((dir_decl *)(yyval.ptr))->name=((tree_expr *)(yyvsp[0].ptr))->name;
  		((dir_decl *)(yyval.ptr))->idrhs=NULL;
  		((dir_decl *)(yyval.ptr))->ctype=CENUM_TYPE;
  	}
#line 4005 "y.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 939 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)=createdirdecl("const",0,NULL,0,0,0,0,NULL);
    /*	((dir_decl *)($$))->dtype=-1;((dir_decl *)($$))->libdtype=-1;*/
    }
#line 4013 "y.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 942 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)=createdirdecl("restrict",0,NULL,0,0,0,0,NULL);	}
#line 4019 "y.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 943 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)=createdirdecl("volatile",0,NULL,0,0,0,0,NULL);	}
#line 4025 "y.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 944 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)=createdirdecl("atomic",0,NULL,0,0,0,0,NULL);	}
#line 4031 "y.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 948 "grammar.y" /* yacc.c:1646  */
    {        (yyval.ptr)=createlibtypedef(GRAPH_TYPE,NULL);	}
#line 4037 "y.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 949 "grammar.y" /* yacc.c:1646  */
    {        (yyval.ptr)=createlibtypedef(EDGE_TYPE,NULL);	}
#line 4043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 950 "grammar.y" /* yacc.c:1646  */
    {        (yyval.ptr)=createlibtypedef(POINT_TYPE,NULL);	}
#line 4049 "y.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 951 "grammar.y" /* yacc.c:1646  */
    {     (yyval.ptr)=createlibtypedef(EDGE_TYPE,(yyvsp[-1].text));	}
#line 4055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 952 "grammar.y" /* yacc.c:1646  */
    {         (yyval.ptr)=createlibtypedef(POINT_TYPE,(yyvsp[-1].text));	}
#line 4061 "y.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 953 "grammar.y" /* yacc.c:1646  */
    {        (yyval.ptr)=createlibtypedef(SET_TYPE,NULL);	}
#line 4067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 954 "grammar.y" /* yacc.c:1646  */
    {        (yyval.ptr)=createlibtypedef(COLLECTION_TYPE,NULL);	}
#line 4073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 958 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 4079 "y.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 959 "grammar.y" /* yacc.c:1646  */
    {
  		tree_typedecl *t1=new tree_typedecl();
  		t1->next=(yyvsp[-1].ptr);
  		(yyval.ptr)=t1;
  		t1->d1=((tree_typedecl*)(yyvsp[-1].ptr))->d1;
  	}
#line 4090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 965 "grammar.y" /* yacc.c:1646  */
    { (yyval.ptr)=createlibtypedef(EDGE_TYPE,(yyvsp[-1].text));	((tree_typedecl *)(yyval.ptr))->ppts=NULL;}
#line 4096 "y.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 966 "grammar.y" /* yacc.c:1646  */
    { (yyval.ptr)=createlibtypedef(GRAPH_TYPE,(yyvsp[-1].text));	((tree_typedecl *)(yyval.ptr))->ppts=NULL;	}
#line 4102 "y.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 967 "grammar.y" /* yacc.c:1646  */
    { (yyval.ptr)=createlibtypedef(POINT_TYPE,(yyvsp[-1].text));	((tree_typedecl *)(yyval.ptr))->ppts=NULL;	}
#line 4108 "y.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 971 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createtypedef(VOID_TYPE);	 }
#line 4114 "y.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 972 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createtypedef(CHAR_TYPE);	}
#line 4120 "y.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 973 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createtypedef(SHORT_TYPE);	}
#line 4126 "y.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 974 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createtypedef(INT_TYPE);	}
#line 4132 "y.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 975 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createtypedef(LONG_TYPE);		}
#line 4138 "y.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 976 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createtypedef(FLOAT_TYPE);	}
#line 4144 "y.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 977 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createtypedef(DOUBLE_TYPE);	}
#line 4150 "y.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 978 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createtypedef(SIGNED_TYPE);	}
#line 4156 "y.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 979 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createtypedef(UNSIGNED_TYPE);	}
#line 4162 "y.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 980 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)= createtypedef(BOOL_TYPE);	}
#line 4168 "y.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 981 "grammar.y" /* yacc.c:1646  */
    {
  		strcat(((tree_typedecl *)(yyvsp[-1].ptr))->name,(yyvsp[0].text));
  		((tree_typedecl *)(yyvsp[-1].ptr))->def=0;
  		(yyval.ptr)=(yyvsp[-1].ptr);
  		((tree_typedecl *)(yyval.ptr))->vname=malloc(sizeof(char)*100);
  		strcpy(((tree_typedecl *)(yyval.ptr))->vname,(yyvsp[0].text));
  	}
#line 4180 "y.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 988 "grammar.y" /* yacc.c:1646  */
    {
  		strcat(((tree_typedecl *)(yyvsp[-4].ptr))->name,(yyvsp[-3].text));
  		((tree_typedecl *)(yyvsp[-4].ptr))->def=0;
  		(yyval.ptr)=(yyvsp[-4].ptr);
  		((tree_typedecl *)(yyval.ptr))->vname=malloc(sizeof(char)*100);
  		strcpy(((tree_typedecl *)(yyval.ptr))->vname,(yyvsp[-3].text));
  		((tree_typedecl *)(yyvsp[-4].ptr))->d1=currsymtab->findsymbol((yyvsp[-1].text));
  	}
#line 4193 "y.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 996 "grammar.y" /* yacc.c:1646  */
    { 
      tree_typedecl *S= createcompounddef(ENUM_TYPE,"enum");
  		strcat(S->name, (yyvsp[0].text));
  		S->vname=malloc(sizeof(char)*100);
  		strcpy(S->vname,(yyvsp[0].text));
  		S->def=0;
  		S->list=new tree_decl_stmt();
  	}
#line 4206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1007 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=new dir_decl();
  		((dir_decl *)(yyval.ptr))->name=malloc(sizeof(char)*100); 
  		strcpy(((dir_decl *)(yyval.ptr))->name," inline "); 
  	}
#line 4216 "y.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1012 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=new dir_decl();
  		((dir_decl *)(yyval.ptr))->name=malloc(sizeof(char)*100);
  		strcpy(((dir_decl *)(yyval.ptr))->name," noreturn ");
  	}
#line 4226 "y.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1025 "grammar.y" /* yacc.c:1646  */
    {
		  (yyval.ptr)= (yyvsp[0].ptr);
		  ((dir_decl *)(yyval.ptr))->ptrcnt=(yyvsp[-1].ptr)->ptrflag;
		  ((dir_decl *)(yyval.ptr))->ptrstring=((dir_decl *)(yyvsp[-1].ptr))->ptrstring;
	  }
#line 4236 "y.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1030 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 4242 "y.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1034 "grammar.y" /* yacc.c:1646  */
    {
		  (yyval.ptr)=new dir_decl();
		  ((dir_decl *)(yyval.ptr))->name=/*malloc(sizeof(char)*100); strcpy(((dir_decl *)$$)->name,*/(yyvsp[0].text);
	  }
#line 4251 "y.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1038 "grammar.y" /* yacc.c:1646  */
    {
		  ((dir_decl *)(yyvsp[-3].ptr))->tp1=(tree_typedecl *)(yyvsp[-1].ptr);
	  }
#line 4259 "y.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1041 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-1].ptr); 
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=new dir_decl();
  		t1=t1->next;
  		((dir_decl *)(yyvsp[-1].ptr))->open_brack=1;
  		t1->close_brack=1;
  		(yyval.ptr)=(yyvsp[-1].ptr);
  	}
#line 4273 "y.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1050 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-2].ptr);
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=new dir_decl();
  		t1=t1->next; 
  		t1->sbrack_flag=1;
  		(yyval.ptr)=(yyvsp[-2].ptr);
  		t1->ctype=CARR_TYPE;
  	}
#line 4287 "y.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1059 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-3].ptr); 
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=new dir_decl();
  		t1=t1->next; 
  		t1->sbrack_flag=1;
  		t1->ptrflag=1;
  		(yyval.ptr)=(yyvsp[-3].ptr);
  		t1->ctype=CARR_TYPE;
  	}
#line 4302 "y.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1069 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-5].ptr);	
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,1,(yyvsp[-2].ptr));
  		t1=t1->next; 
  		(yyval.ptr)=(yyvsp[-5].ptr);
  		t1->ctype=CARR_TYPE; 
  	}
#line 4315 "y.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1077 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-4].ptr);
  		while(t1->next!=NULL)t1=t1->next; 
  		t1->next=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,1,NULL);
  		t1=t1->next;
  		(yyval.ptr)=(yyvsp[-4].ptr); 
  		t1->ctype=CARR_TYPE;
  	}
#line 4328 "y.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1085 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-4].ptr);
  		while(t1->next!=NULL)t1=t1->next; 
  		t1->next=createdirdecl(NULL,0,NULL,0,1,0,0,(yyvsp[-2].ptr));
  		t1=t1->next;
  		t1->ptrflag=1;
  		(yyval.ptr)=(yyvsp[-4].ptr);
  		t1->ctype=CARR_TYPE;
  	}
#line 4342 "y.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1094 "grammar.y" /* yacc.c:1646  */
    { 
  		dir_decl *t1=(yyvsp[-5].ptr); 
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,1,(yyvsp[-3].ptr));
  		t1=t1->next;
  		(yyval.ptr)=(yyvsp[-5].ptr);
  		t1->ctype=CARR_TYPE;
  	}
#line 4355 "y.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1102 "grammar.y" /* yacc.c:1646  */
    { 
  		dir_decl *t1=(yyvsp[-4].ptr);
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,0,(yyvsp[-2].ptr));
  		t1=t1->next; 
  		(yyval.ptr)=(yyvsp[-4].ptr);
  		t1->ctype=CARR_TYPE;
  	}
#line 4368 "y.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1110 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-3].ptr);
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=createdirdecl(NULL,0,NULL,0,1,0,0,(yyvsp[-1].ptr));
  		t1=t1->next;
  		(yyval.ptr)=(yyvsp[-3].ptr);
  		t1->ctype=CARR_TYPE;
  	}
#line 4381 "y.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1118 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-3].ptr);
  		t1->ctype=CARR_TYPE;
  		while(t1->next!=NULL)t1=t1->next; 
  		t1->next=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,0,NULL);
  		t1=t1->next;
  		(yyval.ptr)=(yyvsp[-3].ptr);
  		t1->ctype=CARR_TYPE;
  	}
#line 4395 "y.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1127 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-3].ptr); 
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=new dir_decl();
  		t1=t1->next; 
  		((dir_decl *)(yyvsp[-3].ptr))->params=(yyvsp[-1].ptr);
  		proc_id *t2= new proc_id();
  		t2->name=((dir_decl *)(yyvsp[-3].ptr))->name;
  		FDEF=t2;
  		t2->params=(yyvsp[-1].ptr);
  		FNAME=new dir_decl();
  		FNAME->procd=1; 
  		FNAME->name=((dir_decl *)(yyvsp[-3].ptr))->name;
  		FNAME->ctype=CPROC_TYPE;
  		((dir_decl *)(yyvsp[-3].ptr))->brack_flag=2;
  		t2->param_count=param_count;
  		t2->vararg=vararg; 
  		param_count=vararg=0;
  		((dir_decl *)(yyvsp[-3].ptr))->procd=1;
  		(yyval.ptr)=(yyvsp[-3].ptr);
  	}
#line 4421 "y.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1148 "grammar.y" /* yacc.c:1646  */
    {
	  }
#line 4428 "y.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1150 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-2].ptr);
  		t1->brack_flag=2;
  		(yyval.ptr)=(yyvsp[-2].ptr);
  		((dir_decl *)(yyval.ptr))->procd=1;
  	}
#line 4439 "y.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1156 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-3].ptr);
  		t1->brack_flag=2;
  		t1->procd=1;
  		t1->parnames=new tree_decl_stmt();
  		t1->parnames->dirrhs=(yyvsp[-1].ptr);
  		(yyval.ptr)=t1;
  	}
#line 4452 "y.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1167 "grammar.y" /* yacc.c:1646  */
    {
  		if((yyvsp[0].ptr)->ptrstring!=NULL){
  			strcat(((dir_decl *)(yyvsp[-1].ptr))->name, (yyvsp[0].ptr)->ptrstring);
  		}
  		char *t1=((dir_decl *)(yyvsp[-1].ptr))->name;
  		int i=strlen(t1);
  		for(int j=i;j>=1;j--)t1[j]=t1[j-1];
  		t1[0]='*';
  		(yyval.ptr)=(yyvsp[0].ptr);
  		(yyval.ptr)->ptrstring=t1;}
#line 4467 "y.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1177 "grammar.y" /* yacc.c:1646  */
    {
  		char *t1=((dir_decl *)(yyvsp[0].ptr))->name; 
  		int i=strlen(t1);
  		for(int j=i;j>=1;j--)t1[j]=t1[j-1];
  		t1[0]='*';
  		(yyval.ptr)=new tree_node(); 
  		(yyval.ptr)->ptrstring=t1;
  	}
#line 4480 "y.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1185 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=(yyvsp[0].ptr);
  		(yyvsp[0].ptr)->ptrflag++;
  		if((yyvsp[0].ptr)->ptrstring!=NULL){
  			int i=strlen((yyvsp[0].ptr)->ptrstring);
  			int j;
  			i++;
  			for(j=i;j>=1;j--){
  				(yyvsp[0].ptr)->ptrstring[j]=(yyvsp[0].ptr)->ptrstring[j-1];
  			}
  			(yyvsp[0].ptr)->ptrstring[0]='*';
  		}
    }
#line 4498 "y.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1198 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=new tree_node(); 
  		(yyval.ptr)->ptrflag++;
  		(yyval.ptr)->ptrstring=(char *)malloc(sizeof(char)*25); 
  		strcpy((yyval.ptr)->ptrstring," *");
  	}
#line 4509 "y.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1207 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 4515 "y.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1208 "grammar.y" /* yacc.c:1646  */
    {		strcat(((dir_decl *)(yyvsp[-1].ptr))->name,((dir_decl *)(yyvsp[0].ptr))->name); 		(yyval.ptr)=(yyvsp[-1].ptr);	}
#line 4521 "y.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1212 "grammar.y" /* yacc.c:1646  */
    {
  		tree_decl_stmt *t1=(yyvsp[-2].ptr);
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=new tree_decl_stmt();
  		t1=t1->next;
  		t1->lhs=new tree_typedecl();
  		t1->lhs->datatype=ELLIPSIS_TYPE;
  		(yyval.ptr)=(yyvsp[-2].ptr);
  		 t1->lhs->name=malloc(sizeof(char)*100);
  		strcpy(t1->lhs->name,dtypenames[t1->lhs->datatype]);vararg=1;
  	}
#line 4537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1223 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 4543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1227 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=(yyvsp[0].ptr);
  		((tree_decl_stmt *)(yyval.ptr))->next=NULL;
  		param_count++;
  	}
#line 4553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1232 "grammar.y" /* yacc.c:1646  */
    {
  		tree_decl_stmt *t1=(yyvsp[-2].ptr); 
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=(tree_decl_stmt *)(yyvsp[0].ptr);
  		(yyval.ptr)=(yyvsp[-2].ptr);
  		param_count++;
  		(yyval.ptr)=(yyvsp[-2].ptr);
  	}
#line 4566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1243 "grammar.y" /* yacc.c:1646  */
    { 		(yyval.ptr)=createdeclstmt((yyvsp[-1].ptr),NULL,(yyvsp[0].ptr));	}
#line 4572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1244 "grammar.y" /* yacc.c:1646  */
    {		 (yyval.ptr)=createdeclstmt((yyvsp[-5].ptr),NULL,(yyvsp[0].ptr));
      ((dir_decl *)((yyvsp[0].ptr)))->gpu=1;
      GPUCODEFLAG=1;
      ((dir_decl *)((yyvsp[0].ptr)))->arg=1;
  	}
#line 4582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1249 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)=createdeclstmt((yyvsp[-1].ptr),NULL,(yyvsp[0].ptr));
      ((dir_decl *)((yyvsp[0].ptr)))->arg=1;
	  }
#line 4590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1252 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)=createdeclstmt((yyvsp[0].ptr),NULL,NULL);	}
#line 4596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1256 "grammar.y" /* yacc.c:1646  */
    {
		  (yyval.ptr)=createdirdecl((yyvsp[0].text),1,NULL,0,0,0,0,NULL);
      GPUCODEFLAG=1;
	  }
#line 4605 "y.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1260 "grammar.y" /* yacc.c:1646  */
    {
		  (yyval.ptr)=createdirdecl((yyvsp[0].text),0,NULL,0,0,0,0,NULL);
	  }
#line 4613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1263 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-2].ptr); 
  		while(t1->nextv!=NULL)t1=t1->nextv; 
  		t1->nextv=new dir_decl();
  		t1=t1->nextv;
  		t1->name=malloc(sizeof(char)*100);
  		strcpy(t1->name,(yyvsp[0].text));
  		(yyval.ptr)=(yyvsp[-2].ptr);
  		t1->nextv=NULL;
	  }
#line 4628 "y.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1275 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_expr();}
#line 4634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1276 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=new tree_expr();}
#line 4640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1280 "grammar.y" /* yacc.c:1646  */
    {
  		((dir_decl *)(yyvsp[0].ptr))->print();
  		(yyval.ptr)=new type_name();
  		((type_name *)(yyval.ptr))->typedecl=(yyvsp[-1].ptr);
  		((type_name *)(yyval.ptr))->decl=(yyvsp[0].ptr);
  	}
#line 4651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1286 "grammar.y" /* yacc.c:1646  */
    {
  		/*printf("TYPE_NAME= SQL=%s  ADCT=NULL",((tree_typedecl *)$1)->name);*/
  		(yyval.ptr)=new type_name();
  		((type_name *)(yyval.ptr))->typedecl=(yyvsp[0].ptr);
  	}
#line 4661 "y.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1294 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)= (yyvsp[0].ptr); 
  		((dir_decl *)(yyval.ptr))->ptrcnt=(yyvsp[-1].ptr)->ptrflag;
  		((dir_decl *)(yyval.ptr))->ptrstring=((dir_decl *)(yyvsp[-1].ptr))->ptrstring;
	  }
#line 4671 "y.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1299 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=new dir_decl(); 
  		((dir_decl *)(yyval.ptr))->ptrstring=(yyvsp[0].ptr)->ptrstring;
  		((dir_decl *)(yyval.ptr))->ptrcnt=1;
  	}
#line 4681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1304 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 4687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1308 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=new dir_decl();
  		t1->brack_flag=2;
  		t1->next=(yyvsp[-1].ptr);
  		(yyval.ptr)=t1; 
  	}
#line 4698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1314 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=new dir_decl();
  		t1->sbrack_flag=1;
  		(yyval.ptr)=t1;
  	}
#line 4708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1319 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=new dir_decl();
  		t1->sbrack_flag=1;
  		t1->ptrflag=1;
  		(yyval.ptr)=t1;
  	}
#line 4719 "y.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1325 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,1,(yyvsp[-2].ptr));
  		(yyval.ptr)=t1;
  	}
#line 4728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1329 "grammar.y" /* yacc.c:1646  */
    { 
  		dir_decl *t1=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,1,NULL);
  		(yyval.ptr)=t1;  
  	}
#line 4737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1333 "grammar.y" /* yacc.c:1646  */
    { 
  		dir_decl *t1=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,1,(yyvsp[-3].ptr));
  		(yyval.ptr)=t1;  
  	}
#line 4746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1337 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,0,(yyvsp[-2].ptr));
  		(yyval.ptr)=t1; 
  	}
#line 4755 "y.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1341 "grammar.y" /* yacc.c:1646  */
    { 
  		dir_decl *t1=createdirdecl(NULL,0,NULL,0,1,0,0,(yyvsp[-1].ptr));
  		(yyval.ptr)=t1;
  	}
#line 4764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1345 "grammar.y" /* yacc.c:1646  */
    { 
  		dir_decl *t1=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,0,NULL);
  		(yyval.ptr)=t1;
	  }
#line 4773 "y.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1349 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-2].ptr);
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=createdirdecl(NULL,0,NULL,0,1,0,0,NULL);
  		t1=t1->next;
  		(yyval.ptr)=(yyvsp[-2].ptr);
  	}
#line 4785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1356 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-3].ptr); 
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=new dir_decl();
  		t1->next=createdirdecl(NULL,0,NULL,0,1,0,0,NULL);
  		t1=t1->next; 
  		t1->ptrflag=1;
  		(yyval.ptr)=(yyvsp[-3].ptr);
  	}
#line 4799 "y.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1365 "grammar.y" /* yacc.c:1646  */
    { 
		  dir_decl *t1=(yyvsp[-5].ptr); 
		  while(t1->next!=NULL)t1=t1->next;
		  t1->next=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,1,(yyvsp[-2].ptr));
      t1=t1->next;
      (yyval.ptr)=(yyvsp[-5].ptr);
	  }
#line 4811 "y.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1372 "grammar.y" /* yacc.c:1646  */
    { 
  		dir_decl *t1=(yyvsp[-4].ptr);
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,1,NULL);
  		t1=t1->next;
  		(yyval.ptr)=(yyvsp[-4].ptr);
  	}
#line 4823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1379 "grammar.y" /* yacc.c:1646  */
    { 
  		dir_decl *t1=(yyvsp[-4].ptr);
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,0,(yyvsp[-2].ptr));
  		t1=t1->next; 
  		(yyval.ptr)=(yyvsp[-4].ptr);
  	}
#line 4835 "y.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1386 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-5].ptr); 
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,1,(yyvsp[-3].ptr));
  		t1=t1->next;
  		(yyval.ptr)=(yyvsp[-5].ptr);
  	}
#line 4847 "y.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1393 "grammar.y" /* yacc.c:1646  */
    { 
  		dir_decl *t1=(yyvsp[-3].ptr); 
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=createdirdecl(NULL,0,NULL,0,1,0,0,(yyvsp[-1].ptr));
  		t1=t1->next; 
  		(yyval.ptr)=(yyvsp[-3].ptr);
  	}
#line 4859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1400 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-3].ptr); 
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=createdirdecl(NULL,0,(yyvsp[-1].ptr),0,1,0,0,(yyvsp[-1].ptr));
  		t1=t1->next;
  		(yyval.ptr)=(yyvsp[-3].ptr);
  	}
#line 4871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1407 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=new dir_decl();
  		t1->brack_flag=2;
  		(yyval.ptr)=t1;
  	}
#line 4881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1412 "grammar.y" /* yacc.c:1646  */
    { 
  		dir_decl *t1=new dir_decl();
  		t1->params=(yyvsp[-1].ptr);
  		t1->brack_flag=2;
  		(yyval.ptr)=t1;
  	}
#line 4892 "y.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1418 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-2].ptr);
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=new dir_decl();
  		t1=t1->next;
  		t1->brack_flag==2;
  		(yyval.ptr)=(yyvsp[-2].ptr);
  	}
#line 4905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1426 "grammar.y" /* yacc.c:1646  */
    {
  		dir_decl *t1=(yyvsp[-3].ptr);
  		while(t1->next!=NULL)
  		t1=t1->next;
  		t1->next=new dir_decl();
  		t1=t1->next;
  		t1->params=(yyvsp[-1].ptr);
  		t1->brack_flag=2;
  		(yyval.ptr)=(yyvsp[-3].ptr);
  	}
#line 4920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1439 "grammar.y" /* yacc.c:1646  */
    {
		  (yyval.ptr)=new tree_expr();
		  ((tree_expr*)(yyval.ptr))->expr_type=INITBLOCK;
		  ((tree_expr*)(yyval.ptr))->rhs=(yyvsp[-1].ptr);
	  }
#line 4930 "y.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1444 "grammar.y" /* yacc.c:1646  */
    {
		  (yyval.ptr)=new tree_expr();
		  ((tree_expr*)(yyval.ptr))->expr_type=INITBLOCK;
		  ((tree_expr*)(yyval.ptr))->rhs=(yyvsp[-2].ptr);
	  }
#line 4940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1449 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 4946 "y.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1453 "grammar.y" /* yacc.c:1646  */
    {
  		((tree_expr *)(yyvsp[0].ptr))->desi=(yyvsp[-1].ptr);
  		(yyval.ptr)=(yyvsp[0].ptr);
  	}
#line 4955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1457 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 4961 "y.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1458 "grammar.y" /* yacc.c:1646  */
    {
  		((tree_expr *)(yyvsp[-3].ptr))->next=(yyvsp[0].ptr); 
  		((tree_expr *)(yyvsp[0].ptr))->prev=(yyvsp[-3].ptr);
  		(yyval.ptr)=(yyvsp[0].ptr);
  		((tree_expr *)(yyvsp[0].ptr))->desi=(yyvsp[-1].ptr);
  	}
#line 4972 "y.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1464 "grammar.y" /* yacc.c:1646  */
    { 
  		((tree_expr *)(yyvsp[-2].ptr))->next=(yyvsp[0].ptr); 
  		((tree_expr *)(yyvsp[0].ptr))->prev=(yyvsp[-2].ptr);
  		(yyval.ptr)=(yyvsp[0].ptr);
  	}
#line 4982 "y.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1476 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 4988 "y.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1477 "grammar.y" /* yacc.c:1646  */
    {
  		designator *t1=(yyvsp[-1].ptr);
  		while(t1->next!=NULL)t1=t1->next;
  		t1->next=(yyvsp[0].ptr);
  		(yyval.ptr)=(yyvsp[-1].ptr);
  	}
#line 4999 "y.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1486 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=new designator(); 
  		((designator *)(yyval.ptr))->expr=(yyvsp[-1].ptr);
  	}
#line 5008 "y.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1490 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=new designator();
  		((designator *)(yyval.ptr))->name=(yyvsp[0].text);
  	}
#line 5017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1501 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "statement-1");
      #endif
      (yyval.ptr)=new tree_node();}
#line 5027 "y.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1506 "grammar.y" /* yacc.c:1646  */
    {
		  #ifdef DEBUGGING
        printf("%s\n", "statement-2");
      #endif
      (yyval.ptr)=sblock_begin[sbtop];
	  }
#line 5038 "y.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1512 "grammar.y" /* yacc.c:1646  */
    {
		  #ifdef DEBUGGING
        printf("%s\n", "statement-3");
      #endif
      (yyval.ptr)=(yyvsp[0].ptr);
	  }
#line 5049 "y.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1518 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "statement-4");
      #endif
      (yyval.ptr)=new tree_node();((tree_node *)(yyval.ptr))->nodetype=TREE_IF;}
#line 5059 "y.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1523 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "statement-5");
      #endif
      (yyval.ptr)=new tree_node();}
#line 5069 "y.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1528 "grammar.y" /* yacc.c:1646  */
    {
		  #ifdef DEBUGGING
        printf("%s\n", "statement-6");
      #endif
      (yyval.ptr)=new tree_node() ;
	  }
#line 5080 "y.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1534 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "statement-7");
      #endif
      (yyval.ptr)=new tree_node();}
#line 5090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1539 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "statement-8");
      #endif      
    }
#line 5100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1544 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "statement-9");
      #endif
      (yyval.ptr)=(yyvsp[0].ptr);  }
#line 5110 "y.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1549 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "statement-10");
      #endif
      (yyval.ptr)=new tree_node();}
#line 5120 "y.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1557 "grammar.y" /* yacc.c:1646  */
    { 
  		(yyvsp[-2].ptr)=sblock_begin[sbtop];
  	  ((statement *)(yyvsp[-2].ptr))->sttype=SECTIONS_STMT;
    }
#line 5129 "y.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1564 "grammar.y" /* yacc.c:1646  */
    { 
  		(yyvsp[0].ptr)=sblock_begin[sbtop];
  		((statement *)(yyvsp[0].ptr))->sttype=SECTION_STMT;
    }
#line 5138 "y.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1568 "grammar.y" /* yacc.c:1646  */
    { 
  		(yyvsp[0].ptr)=sblock_begin[sbtop];
  		((statement *)(yyvsp[0].ptr))->sttype=SECTION_STMT;
    }
#line 5147 "y.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1575 "grammar.y" /* yacc.c:1646  */
    { 
  		temp3=createstmt(MACRO_STMT,(yyvsp[-2].ptr),NULL,LINENO); 
  		temp3->expr2=(yyvsp[0].ptr);
  		if(temp1)temp1->next=temp3;
  		temp1=temp3;
  		(yyval.ptr)=temp3;
  	}
#line 5159 "y.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 1585 "grammar.y" /* yacc.c:1646  */
    {
  		statement *t4=createstmt(LABELED_STMT,NULL,(yyvsp[-2].text),LINENO);
  		if(temp3->sttype==EBLOCK_STMT){
  			statement *t2=(yyvsp[0].ptr);
  			t2->prev->next=t4;
  			t4->next=t2;
  		} else {
  		  t4->next=temp3;
  			temp3->prev->next=t4;
  		}
  		temp3=t4;
  	}
#line 5176 "y.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1597 "grammar.y" /* yacc.c:1646  */
    {
  		statement *t4=createstmt(CASE_STMT,(yyvsp[-2].ptr),NULL,LINENO);
  		if(temp3->sttype==EBLOCK_STMT){
  			statement *t2=(yyvsp[0].ptr);
  			t2->prev->next=t4;
  			t4->next=t2;
  		} else {
  		  t4->next=temp3;; 
  			temp3->prev->next=t4;
  		}
  		temp3=t4;
  	}
#line 5193 "y.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1609 "grammar.y" /* yacc.c:1646  */
    {
  		statement *t4=createstmt(DEFAULT_STMT,NULL,NULL,LINENO);
  		if(temp3->sttype==EBLOCK_STMT){
  			statement *t2=(yyvsp[0].ptr); 
  			t4->next=t2;
  			t2->prev->next=t4;
  		} else {
  		  t4->next=temp3;
  			temp3->prev->next=t4;
  		}
  		temp3=t4;
  	}
#line 5210 "y.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1624 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "compound_statement-1");
      #endif
      (yyval.ptr)=new tree_node();
    }
#line 5221 "y.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1630 "grammar.y" /* yacc.c:1646  */
    {
		  #ifdef DEBUGGING
        printf("%s\n", "compound_statement-2");
      #endif
      
      (yyval.ptr)=new tree_node();
	  }
#line 5233 "y.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1640 "grammar.y" /* yacc.c:1646  */
    {
  		temp3=createstmt(SBLOCK_STMT,NULL,NULL,LINENO);
  		if(temp1!=NULL){linkstmt(&temp1,temp3);
  		} else {
  			temp1=temp=temp3;
  		}
  		stemp=new globsymtable();
  		stemp->parent=currsymtab;
  		stemp->sym->parent=currsymtab->sym;
  		currsymtab=stemp;
  		sblock_begin[sbtop++]=temp3;
  		
      if(FDEF!=NULL){
  			if(FDEF->params!=NULL){
  				FDEF->addsymbols(currsymtab);
  			}
  			FDEF=NULL;
  			symtableentry *old=NULL;
  			if(FTYPE==NULL){
  				FTYPE=new tree_typedecl();
  				FTYPE->datatype=VOID_TYPE;
  			}
  			currsymtab->parent->addsymbol(FNAME,FTYPE);
  		}
    }
#line 5263 "y.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1667 "grammar.y" /* yacc.c:1646  */
    {
  		temp3=createstmt(EBLOCK_STMT,NULL,NULL,LINENO);
  		if(temp1!=NULL) temp1->next=temp3;
  		temp3->prev=temp1;temp3->next=NULL;
  		temp1=temp3;
  		currsymtab=currsymtab->parent;sbtop--;
		}
#line 5275 "y.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1677 "grammar.y" /* yacc.c:1646  */
    {
  		stemp=new globsymtable();
  		stemp->parent=currsymtab;
  		stemp->sym->parent=currsymtab->sym;
  		currsymtab=stemp; 
	  }
#line 5286 "y.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1686 "grammar.y" /* yacc.c:1646  */
    {
  		#ifdef DEBUGGING
        printf("%s\n", "block_item_list-1");
      #endif
      
      if(temp==NULL){
  			G1=temp1;
  			flag=1;
  			temp=temp1;
  			temp->sttype=SBLOCK_STMT;
  			(yyval.ptr)=(yyvsp[0].ptr);
  		} else {
  		  (yyval.ptr)=(yyvsp[0].ptr);
      }
  	}
#line 5306 "y.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1701 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "block_item_list-2");
      #endif
      /*((statement *)$1)->next=$2;*/
      (yyval.ptr)=(yyvsp[0].ptr);
    }
#line 5318 "y.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1711 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "block-item-1");
      #endif
      (yyval.ptr)=(yyvsp[0].ptr);}
#line 5328 "y.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1716 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "block-item-2");
      #endif
      (yyval.ptr)=(yyvsp[0].ptr);}
#line 5338 "y.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1724 "grammar.y" /* yacc.c:1646  */
    {		(yyval.ptr)=createassign(EMPTY_ASSIGN);		}
#line 5344 "y.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1725 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=(yyvsp[-1].ptr);
  		while(temp1->next!=NULL&&temp1->sttype==ASSIGN_STMT&& temp1->stmtno==temp1->next->stmtno){
  		  temp1=temp1->next;
  		}
  		temp1->stassign->semi=1;
  		STMTNO++;
  		FUNCALL_FLAG=0;
  	}
#line 5358 "y.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1737 "grammar.y" /* yacc.c:1646  */
    {
  		statement *t4=createstmt(SINGLE_STMT,((assign_stmt *)(yyvsp[-2].ptr))->rhs,NULL,LINENO);
  		t4->stassign=(assign_stmt *)(yyvsp[-2].ptr);
  	  tree_expr *bar=t4->expr1;
  		if(bar->expr_type==VAR && bar->libdtype==COLLECTION_TYPE)barrier=1;
  		statement *t2=(statement *)(yyvsp[0].ptr); 
      createsinglestmt1(&t4,&t2,&temp3);
    }
#line 5371 "y.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 1745 "grammar.y" /* yacc.c:1646  */
    {
  		statement *t4=createstmt(SINGLE_STMT,((assign_stmt *)(yyvsp[-4].ptr))->rhs,NULL,LINENO);
  		t4->stassign=(assign_stmt *)(yyvsp[-4].ptr);
  	  tree_expr *bar=t4->expr1;
  		if(bar->expr_type==VAR && bar->libdtype==COLLECTION_TYPE)barrier=1;
  		statement *t2=(statement *)(yyvsp[-2].ptr); 
  		statement *t1=(statement *)(yyvsp[0].ptr); 
      createsinglestmt(&t4,&t1,&t2,&temp3);
    }
#line 5385 "y.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 1757 "grammar.y" /* yacc.c:1646  */
    {  
  		statement *t4=createstmt(IF_STMT,((assign_stmt *)((yyvsp[-4].ptr)))->rhs,NULL,LINENO);
      statement *t1=(yyvsp[0].ptr);
      statement *t2=(yyvsp[-2].ptr);
      //fprintf(FP1,"/*IFSTMT*/");
      //if(t1->nodetype==TREE_IF)
      //fprintf(FP1,"//if else if \n");
      createifstmt(&t4,&t1,&t2,&temp3,1);
      //if(temp1->sttype==IF_STMT)fprintf(FP1,"//IF ELSE IF \n");
      char arr[100];
      ((assign_stmt *)((yyvsp[-4].ptr)))->printcode1(arr,1);
      //fprintf(FP1,"%s \n",arr);
	  }
#line 5403 "y.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 1770 "grammar.y" /* yacc.c:1646  */
    {
  		statement *t4=createstmt(IF_STMT,((assign_stmt *)((yyvsp[-2].ptr)))->rhs,NULL,LINENO);
  		statement *t2=(statement *)(yyvsp[0].ptr);
      //fprintf(FP1,"//else sttype %d ",t2->sttype);
      createifstmt(&t4,NULL,&t2,&temp3,0);
  	}
#line 5414 "y.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 1776 "grammar.y" /* yacc.c:1646  */
    {
  		statement *t4=createstmt(SWITCH_STMT,((assign_stmt *)((yyvsp[-2].ptr)))->rhs,NULL,LINENO);
  		t4->f1=((statement *)(yyvsp[0].ptr));
  		((statement *)(yyvsp[0].ptr))->prev->prev->next=t4;
  		temp3=t4;/*statement *t2=(statement *)$5; t2->prev->next=temp3;((assign_stmt *)$3)->rhs->pflag=100;temp1=temp3;*/
      FUNCALL_FLAG=0;
  	}
#line 5426 "y.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 1786 "grammar.y" /* yacc.c:1646  */
    {
		  statement *t1;
  		if(temp3->sttype==EBLOCK_STMT){
  			t1=sblock_begin[sbtop];
  			t1->sttype=WHILE_STMT;
  			t1->expr1=((assign_stmt *)(yyvsp[-2].ptr))->rhs;
  		}else{
  			temp3->sttype=WHILE_STMT;
  			temp3->expr1=((assign_stmt *)(yyvsp[-2].ptr))->rhs;
  		}
  		((assign_stmt *)(yyvsp[-2].ptr))->rhs->pflag=100;
  	}
#line 5443 "y.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 1798 "grammar.y" /* yacc.c:1646  */
    {
  		(yyval.ptr)=new tree_node();
  		statement *t1=sblock_begin[sbtop];
  		t1->sttype=DOWHILE_STMT;
  		statement *t4=createstmt(DOWHILEEXPR_STMT,((assign_stmt *)((yyvsp[-2].ptr)))->rhs,NULL,LINENO);
      linkstmt(&temp1,temp3);
  		((assign_stmt *)(yyvsp[-2].ptr))->rhs->pflag=100;
  		FUNCALL_FLAG=0;
  	}
#line 5457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1807 "grammar.y" /* yacc.c:1646  */
    {
  		if(temp3->sttype==EBLOCK_STMT){
  			temp3->sttype=FOR_EBLOCK_STMT;
  			statement *t1=sblock_begin[sbtop];
        initforstmt1(&t1,(assign_stmt *)(yyvsp[-3].ptr),(assign_stmt *)(yyvsp[-2].ptr),(assign_stmt *)NULL);
  			/*t1->print();*/statement *t2=t1;
  			int i=0;int cnt=0; 
  			if(((assign_stmt *)(yyvsp[-3].ptr))->asstype!=EMPTY_ASSIGN)cnt++;
  			if(((assign_stmt *)(yyvsp[-2].ptr))->asstype!=EMPTY_ASSIGN)cnt++;
  			while(i<=cnt){
  				i++;
  				t2=t2->prev;
  			}
  			t2->next=t1; 
  			t1->prev=t2;
      } else {
        initforstmt1(&temp3,(assign_stmt *)(yyvsp[-3].ptr),(assign_stmt *)(yyvsp[-2].ptr),(assign_stmt *)NULL);
  			statement *t2=temp3;
  			int i=0; int cnt=0;
  			if(((assign_stmt *)(yyvsp[-3].ptr))->asstype!=EMPTY_ASSIGN)cnt++;
  			if(((assign_stmt *)(yyvsp[-2].ptr))->asstype!=EMPTY_ASSIGN)cnt++;
  			while(i<=cnt){i++;t2=t2->prev;}
			  t2->next=temp3; 
			  temp3->prev=t2;
  		}
  		FUNCALL_FLAG=0;
    }
#line 5489 "y.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 1834 "grammar.y" /* yacc.c:1646  */
    {
  		if(temp3->sttype==EBLOCK_STMT){
  			temp3->sttype=FOR_EBLOCK_STMT;
  			statement *t1=sblock_begin[sbtop];
        initforstmt1(&t1,(assign_stmt *)(yyvsp[-4].ptr),(assign_stmt *)(yyvsp[-3].ptr),(assign_stmt *)(yyvsp[-2].ptr));
  			/*t1->print();*/
  			statement *t2=t1; 
  			int i=0; int cnt=0; 
  			if(((assign_stmt *)(yyvsp[-4].ptr))->asstype!=EMPTY_ASSIGN)cnt++;
  			if(((assign_stmt *)(yyvsp[-3].ptr))->asstype!=EMPTY_ASSIGN)cnt++;
  			while(i<=cnt+1){
  				i++;
  				t2=t2->prev;
  			}
  			t2->next=t1;
  			t1->prev=t2;
      } else {
        initforstmt1(&temp3,(assign_stmt *)(yyvsp[-4].ptr),(assign_stmt *)(yyvsp[-3].ptr),(assign_stmt *)(yyvsp[-2].ptr));
  		  statement *t2=temp3;
  		  int i=0; int cnt=0; 
  		  if(((assign_stmt *)(yyvsp[-4].ptr))->asstype!=EMPTY_ASSIGN)cnt++;
  		  if(((assign_stmt *)(yyvsp[-3].ptr))->asstype!=EMPTY_ASSIGN)cnt++;
  		  while(i<=cnt+1){
  				i++;
  				t2=t2->prev;
  		  }
  			t2->next=temp3;
  			temp3->prev=t2;
  		}
  		FUNCALL_FLAG=0;
  	}
#line 5525 "y.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1865 "grammar.y" /* yacc.c:1646  */
    {
  		if(temp3->sttype==EBLOCK_STMT){ 
  			temp3->sttype=FOR_EBLOCK_STMT;
  			statement *t1=sblock_begin[sbtop];
        initforstmt(&t1,(tree_decl_stmt *)(yyvsp[-3].ptr),(assign_stmt *)(yyvsp[-2].ptr),(assign_stmt *)NULL);
  			statement *t2=t1;
  			int i=0;
  			int cnt=0; 
  			if(((assign_stmt *)(yyvsp[-2].ptr))->asstype!=EMPTY_ASSIGN)cnt++;
  			while(i<=cnt+1){
  				i++;
  				t2=t2->prev;
  			}
  			t2->next=t1;
  			t1->prev=t2;
  		} else {
        initforstmt(&temp3,(tree_decl_stmt *)(yyvsp[-3].ptr),(assign_stmt *)(yyvsp[-2].ptr),(assign_stmt *)NULL);
  			statement *t2=temp3;
  			int i=0; 
  			int cnt=0;
  			if(((assign_stmt *)(yyvsp[-2].ptr))->asstype!=EMPTY_ASSIGN)cnt++;
  			while(i<=cnt+1){
  				i++;
  				t2=t2->prev;
  			}
  			t2->next=temp3;
  			temp3->prev=t2;
  		}
  		currsymtab=currsymtab->parent;
  		FUNCALL_FLAG=0;
    }
#line 5561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 1896 "grammar.y" /* yacc.c:1646  */
    {
  		if(temp3->sttype==EBLOCK_STMT){
  			temp3->sttype=FOR_EBLOCK_STMT;
  			statement *t1=sblock_begin[sbtop];
        initforstmt(&t1,(tree_decl_stmt *)(yyvsp[-4].ptr),(assign_stmt *)(yyvsp[-3].ptr),(assign_stmt *)(yyvsp[-2].ptr));
  			statement *t2=t1;
  			int i=0; int cnt=0;
  			if(((assign_stmt *)(yyvsp[-3].ptr))->asstype!=EMPTY_ASSIGN)cnt++;
  			while(i<=cnt+2){
  				i++;
  				t2=t2->prev;
  			}
  			t2->next=t1;
  			t1->prev=t2;
  	  } else { 
        initforstmt(&temp3,(tree_decl_stmt *)(yyvsp[-4].ptr),(assign_stmt *)(yyvsp[-3].ptr),(assign_stmt *)(yyvsp[-2].ptr));
  			statement *t2=temp3;
  			int i=0;
  			int cnt=0; 
  			if(((assign_stmt *)(yyvsp[-3].ptr))->asstype!=EMPTY_ASSIGN)cnt++;
  			while(i<=cnt+2){
  				i++;
  				t2=t2->prev;
  			}
  			t2->next=temp3;
  			temp3->prev=t2;
      }
    	currsymtab=currsymtab->parent;
    	FUNCALL_FLAG=0;
    }
#line 5596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 1927 "grammar.y" /* yacc.c:1646  */
    {
      level_of_foreach++;
      // put variable into symbol table
		  dir_decl *d1=createdirdeclforeach((char *)(yyvsp[-5].text),(char *)(yyvsp[-3].text),ITERATOR_TYPE,-1,-1,(int)(yyvsp[-1].ival));
		}
#line 5606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 1934 "grammar.y" /* yacc.c:1646  */
    {	if(temp3->sttype==EBLOCK_STMT){
        statement *t1=sblock_begin[sbtop];
        if(temp3->expr4!=NULL){
				  temp3->expr4->print(temp3->expr4);      
				  fnamescond[t1->next->stassign->rhs->name]=temp1;
        }
        temp3->sttype=FOREACH_EBLOCK_STMT;
        t1->expr4=temp3->expr4;
        t1->expr5=(yyvsp[-6].ptr);  
		    t1->sttype=FOREACH_STMT;
        FOREACH_FUN_FLAG=1;
        t1->feb=1;
        initforeach1(&t1,(char *)(yyvsp[-7].text),(char *)(yyvsp[-5].text),(int)(yyvsp[-3].ival));
        t1->end_stmt = temp3;
		  } else {
        // printf("%s %d\n", "grammar.y-1813", temp1->prev->sttype);
        if(temp1->expr4!=NULL){
				  fnamescond[temp1->stassign->rhs->name]=temp1;
        }
        temp3=createstmt(FOREACH_STMT,NULL,NULL,LINENO);
        FOREACH_FUN_FLAG=1;
        temp3->expr5=(yyvsp[-6].ptr);
        initforeach1(&temp3,(char *)(yyvsp[-7].text),(char *)(yyvsp[-5].text),(int)(yyvsp[-3].ival));
			  temp3->prev=temp1->prev;
        temp3->expr4=temp1->expr4;
        temp3->stassign=temp1->stassign;
        fnamescond[temp1->stassign->rhs->name]=temp3;
        temp3->prev->next=temp3;temp1=temp3;
        
        if(level_of_foreach == 1) foreach_list.insert(temp3);
      }
    	currsymtab=currsymtab->parent;
      KERNEL=0;
      FUNCALL_FLAG=0;
      level_of_foreach--;
    }
#line 5647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 1971 "grammar.y" /* yacc.c:1646  */
    {
      level_of_foreach++;
		  dir_decl *d1=createdirdeclforeach((char *)(yyvsp[-3].text),(char *)(yyvsp[-1].text),ITERATOR_TYPE,-1,-1,(int)5);
		}
#line 5656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 1976 "grammar.y" /* yacc.c:1646  */
    { 
      if(temp3->sttype==EBLOCK_STMT){
        statement *t1=sblock_begin[sbtop];
        if(temp3->expr4!=NULL){
				  temp3->expr4->print(temp3->expr4);      
				  fnamescond[t1->next->stassign->rhs->name]=temp1;
        }
        temp3->sttype=FOREACH_EBLOCK_STMT;
        t1->expr5=(yyvsp[-4].ptr);
			  t1->feb=1;
        FOREACH_FUN_FLAG=1;
        t1->sttype=FOREACH_STMT;
        initforeach(&t1,&temp3,(char *)(yyvsp[-5].text),(char *)(yyvsp[-3].text),5);
		  } else {
        if(temp3->expr4!=NULL){
				  fnamescond[temp1->stassign->rhs->name]=temp1;
			  }
        temp3=createstmt(FOREACH_STMT,NULL,NULL,LINENO);
        FOREACH_FUN_FLAG=1;
			  temp3->expr5=(yyvsp[-4].ptr); 
        initforeach(&temp3,&temp3,(char *)(yyvsp[-5].text),(char *)(yyvsp[-3].text),5);
		    temp3->prev=temp1->prev; 
			  temp3->stassign=temp1->stassign;
			  temp3->prev->next=temp3;
			  temp1=temp3;

        if(level_of_foreach == 1) foreach_list.insert(temp3);
	    }
	    currsymtab=currsymtab->parent;
	    KERNEL=0;
      FUNCALL_FLAG=0;
      level_of_foreach--;
    }
#line 5694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 2011 "grammar.y" /* yacc.c:1646  */
    { 
		  (yyval.ptr)=new tree_expr(); 
      dir_decl *d1=new dir_decl();
      d1->name=malloc(sizeof(char)*30);
      strcpy(d1->name,(yyvsp[-2].text));
      tree_typedecl *tt1=new tree_typedecl();
	    tt1->datatype=INT_TYPE;tt1->name=malloc(sizeof(char)*100);strcpy(tt1->name,dtypenames[tt1->datatype]);
      currsymtab->addsymbol(d1,tt1);
		  dir_decl *x1=currsymtab->findsymbol((yyvsp[-2].text));
		  ((tree_expr *)(yyval.ptr))->rhs=new tree_expr(x1);
		  ((tree_expr *)((yyval.ptr)))->expr_type=VAR;
	  }
#line 5711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 2023 "grammar.y" /* yacc.c:1646  */
    { (yyval.ptr)=(yyvsp[0].ptr);}
#line 5717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 2024 "grammar.y" /* yacc.c:1646  */
    {
		  (yyval.ptr)=(yyvsp[0].ptr);
	  }
#line 5725 "y.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 2029 "grammar.y" /* yacc.c:1646  */
    {
		  (yyval.ptr)=NULL;
    }
#line 5733 "y.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 2032 "grammar.y" /* yacc.c:1646  */
    { 
  		(yyvsp[-1].ptr)=new tree_expr(); 
  		((tree_expr *)((yyvsp[-1].ptr)))->name=malloc(sizeof(char)*10);
  		strcpy(((tree_expr *)(yyvsp[-1].ptr))->name,"In");
  		((tree_expr *)((yyvsp[-1].ptr)))->ptrflag++;(yyval.ptr)=(yyvsp[-1].ptr);
  	}
#line 5744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 2040 "grammar.y" /* yacc.c:1646  */
    { 
    	if((!strcmp((yyvsp[0].text),"points"))&&(strlen((yyvsp[0].text))==strlen("points")))(yyval.ival)=0;
		  else if((!strcmp((yyvsp[0].text),"edges"))&&(strlen((yyvsp[0].text))==strlen("edges")))(yyval.ival)=1;
      else if((!strcmp((yyvsp[0].text),"nbrs"))&&(strlen((yyvsp[0].text))==strlen("nbrs"))){
		    (yyval.ival)=2;
		    OUTNBRFLAG=INNBRFLAG=1;
      }
      else if((!strcmp((yyvsp[0].text),"innbrs"))&&(strlen((yyvsp[0].text))==strlen("innbrs"))){
				(yyval.ival)=3;
				INNBRFLAG=1;
      }
      else if((!strcmp((yyvsp[0].text),"outnbrs"))&&(strlen((yyvsp[0].text))==strlen("outnbrs"))){
  			(yyval.ival)=4;
  			OUTNBRFLAG=1;
      }
      else if((!strcmp((yyvsp[0].text),"items"))&&(strlen((yyvsp[0].text))==strlen("items"))){
        (yyval.ival)=5;
      }
	      else {
        int flag=0;
        for (std::map<char *,int>::iterator it=newitr.begin(); it!=newitr.end(); ++it){
		      if(!strcmp(it->first,(yyvsp[0].text))){(yyval.ival)=it->second;flag=1;}
        }
        tempitr=malloc(sizeof(char)*100);
        strcpy(tempitr,(yyvsp[0].text));
      }
    }
#line 5776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 2070 "grammar.y" /* yacc.c:1646  */
    {
      temp3=createstmt(GOTO_STMT,NULL,(yyvsp[-1].text),LINENO);
      linkstmt(&temp1,temp3);
			(yyval.ptr)=new tree_node();
	  }
#line 5786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2075 "grammar.y" /* yacc.c:1646  */
    {
      temp3=createstmt(CONTINUE_STMT,NULL,NULL,LINENO);
      linkstmt(&temp1,temp3);
		  (yyval.ptr)=new tree_node();
	  }
#line 5796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 2080 "grammar.y" /* yacc.c:1646  */
    {
   		temp3=createstmt(BREAK_STMT,NULL,NULL,LINENO);
      linkstmt(&temp1,temp3);
		  (yyval.ptr)=new tree_node();
	  }
#line 5806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 2085 "grammar.y" /* yacc.c:1646  */
    {
  		temp3=createstmt(RETURN_STMT,NULL,NULL,LINENO);
      linkstmt(&temp1,temp3);
		  (yyval.ptr)=new tree_node();
	  }
#line 5816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 2090 "grammar.y" /* yacc.c:1646  */
    {
   		temp3=createstmt(RETURN_STMT,((assign_stmt *)(yyvsp[-1].ptr))->rhs,NULL,LINENO);
		  temp1->prev->next=temp3;
		  temp3->prev=temp1->prev;
		  temp1=temp3;
		  (yyval.ptr)=new tree_node();
	  }
#line 5828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 2099 "grammar.y" /* yacc.c:1646  */
    {  }
#line 5834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 2100 "grammar.y" /* yacc.c:1646  */
    {	if(temp3->sttype==EBLOCK_STMT){ 
        temp3->expr4=((assign_stmt *)(yyvsp[-3].ptr))->rhs;
			  statement *t1=sblock_begin[sbtop]; 
        statement * t4=t1->prev;
        t4->prev->next=t1;
        t1->prev=t4->prev;
        t4->next=NULL;
      } else {
        temp3->expr4=((assign_stmt *)(yyvsp[-3].ptr))->rhs;
        temp3->prev=temp3->prev->prev;
        temp3->expr4=((assign_stmt *)(yyvsp[-3].ptr))->rhs;
        temp3->prev->next->next=NULL;
        temp3->prev->next=temp3; 
        temp1=temp3;  
		  }
    }
#line 5855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 2120 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr); 
      #ifdef DEBUGGING
        printf("%s\n", "translation_unit-1");
      #endif
    }
#line 5865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 2125 "grammar.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);
      #ifdef DEBUGGING
        printf("%s\n", "translation_unit-2");
      #endif
    }
#line 5875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 2133 "grammar.y" /* yacc.c:1646  */
    {
  		currsymtab=&GLOBAL_TABLE;
  		(yyval.ptr)=new tree_node();  
  		statement *t1=sblock_begin[sbtop]; 
  		fnames[t1->prev->stdecl->dirrhs->name]=t1->prev;
      t1->prev->foreachflag=FOREACH_FUN_FLAG;
      FOREACH_FUN_FLAG=0;
  
      #ifdef DEBUGGING
        printf("%s\n", "external_declaration-1");
      #endif
	  }
#line 5892 "y.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 2145 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "external_declaration-2");
      #endif
    }
#line 5902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2150 "grammar.y" /* yacc.c:1646  */
    { 
      #ifdef DEBUGGING
        printf("%s\n", "external_declaration-3");
      #endif
    }
#line 5912 "y.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2158 "grammar.y" /* yacc.c:1646  */
    {de2=temp3;}
#line 5918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 2158 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "function_definition-1");
      #endif

		  if(temp3->sttype==EBLOCK_STMT)
  		  temp3->sttype=FUNCTION_EBLOCK_STMT;
  		statement *t1=new statement();
  		t1->stdecl=createdeclstmt((yyvsp[-4].ptr),NULL,(yyvsp[-3].ptr));
  		((dir_decl *)(yyvsp[-3].ptr))->procd=1;
  		t1->sttype=DECL_STMT;
  		t1->flist=fhead; fhead=NULL;
  		statement *t2=sblock_begin[sbtop]; 
  		t1->next=de1; 
  		if(de1->prev!=NULL)de1->prev->next=t1;
  		else temp=t1;
  		de1->prev=t1; 
  		de2->next=t2; 
  		t2->prev=de2;
  		t1->lineno=LINENO;
    }
#line 5944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 2179 "grammar.y" /* yacc.c:1646  */
    {
  		#ifdef DEBUGGING
        printf("%s\n", "function_definition-2");
      #endif

      statement *t1=new statement();

  		temp3->sttype=FUNCTION_EBLOCK_STMT;
  		if(barrier==1){
  			t1->barrier=1;
  			barrier=0;
  			dir_decl *dd=(yyvsp[-1].ptr);
  			if(dd->params!=NULL &&  dd->params->dirrhs && dd->params->dirrhs->gpu) {
  				tree_decl_stmt *dd1=dd->params;
  				while(dd1->next!=NULL)dd1=dd1->next;
  				dd1->next=new tree_decl_stmt();
  				dd1=dd1->next;
  				dd1->lhs=new tree_typedecl(); 
  				dd1->lhs->datatype=INT_TYPE;
  				dd1->lhs->name=malloc(sizeof(char)*100);
  				strcpy(dd1->lhs->name,dtypenames[dd1->lhs->datatype]);
  				dd1->dirrhs=new dir_decl();
  				dd1->dirrhs->name=malloc(sizeof(char)*100); 
  				strcpy(dd1->dirrhs->name,"nblocks");
  				dd1->next=new tree_decl_stmt();
  				dd1=dd1->next;
  				dd1->lhs=new tree_typedecl();
  				dd1->lhs->datatype=INT_TYPE;
  				dd1->lhs->name=malloc(sizeof(char)*100);
  				strcpy(dd1->lhs->name,dtypenames[dd1->lhs->datatype]);
  				dd1->dirrhs=new dir_decl();
  				dd1->dirrhs->name=malloc(sizeof(char)*100);
  			  strcpy(dd1->dirrhs->name,"size");
  			  dd1->next=NULL;
  			  dd1->next=new tree_decl_stmt();
  				dd1=dd1->next;
  				dd1->lhs=new tree_typedecl();
  				dd1->lhs->datatype=INT_TYPE;
  				dd1->lhs->name=malloc(sizeof(char)*100);
  				strcpy(dd1->lhs->name,"int ");
  				dd1->dirrhs=new dir_decl();
  				dd1->dirrhs->name=malloc(sizeof(char)*100);
  				strcpy(dd1->dirrhs->name,"goal");
  				dd1->next=new tree_decl_stmt();
  				dd1=dd1->next;
  				dd1->lhs=new tree_typedecl();
  				dd1->lhs->datatype=INT_TYPE;
  				dd1->lhs->name=malloc(sizeof(char)*100);
  				strcpy(dd1->lhs->name,"unsigned volatile int * ");
  				dd1->dirrhs=new dir_decl();
  				dd1->dirrhs->name=malloc(sizeof(char)*100); 
  				strcpy(dd1->dirrhs->name,"arrayin");
  				dd1->next=new tree_decl_stmt();
  				dd1=dd1->next;
  				dd1->lhs=new tree_typedecl();
  				dd1->lhs->datatype=INT_TYPE;
  				dd1->lhs->name=malloc(sizeof(char)*100);
  				strcpy(dd1->lhs->name,"unsigned volatile int * ");
  				dd1->dirrhs=new dir_decl();
  				dd1->dirrhs->name=malloc(sizeof(char)*100);
  				strcpy(dd1->dirrhs->name,"arrayout");
  				dd1->next=NULL;		
  		  }
  	  }
    	t1->stdecl=new tree_decl_stmt();
    	t1->stdecl->lhs=(yyvsp[-2].ptr);
    	t1->sttype=DECL_STMT;
    	t1->flist=fhead;
  	  fhead=NULL;
    	t1->stdecl->dirrhs=(yyvsp[-1].ptr);
    	statement *t2=sblock_begin[sbtop]; 
    	if(t2->prev==NULL){
    		temp=t1;
    	}
    	if(t2!=NULL){
    		t1->prev=t2->prev;
    		t2->prev=t1;
    		t1->next=t2;
    		if(t1->prev!=NULL)t1->prev->next=t1;
    	}
    	t1->lineno=LINENO;
    }
#line 6031 "y.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 2261 "grammar.y" /* yacc.c:1646  */
    {de2=temp3;}
#line 6037 "y.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 2261 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "function_definition-3");
      #endif

  		temp3->sttype=FUNCTION_EBLOCK_STMT;
  		((dir_decl *)(yyvsp[-3].ptr))->procd=1;
  		statement *t1=new statement();
  		t1->stdecl=new tree_decl_stmt();
  		t1->stdecl->dirrhs=((dir_decl *)(yyvsp[-3].ptr));
  		t1->stdecl->lhs=new tree_typedecl();
  		t1->stdecl->lhs->datatype=VOID_TYPE;
  		t1->sttype=DECL_STMT;
  		t1->flist=fhead;
		  fhead=NULL;
		  statement *t2=sblock_begin[sbtop];
  		t1->next=de1;
  		if(de1->prev!=NULL)de1->prev->next=t1; 
  		else temp=t1; 
  		de1->prev=t1;
  		de2->next=t2; 
  		t2->prev=de2;
  		t1->lineno=LINENO;
      #ifdef DEBUGGING
        printf("%s\n", "function_definition-3");
      #endif

  	}
#line 6070 "y.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 2289 "grammar.y" /* yacc.c:1646  */
    {
      #ifdef DEBUGGING
        printf("%s\n", "function_definition-4");
      #endif

  		statement *t1=new statement();
  		temp3->sttype=FUNCTION_EBLOCK_STMT;
  		if(barrier==1){
  		  t1->barrier=1;barrier=0;
  	  }
    	t1->stdecl=new tree_decl_stmt();
    	t1->stdecl->dirrhs=((dir_decl *)(yyvsp[-1].ptr));
    	t1->stdecl->lhs=new tree_typedecl();
    	t1->stdecl->lhs->datatype=VOID_TYPE;
    	t1->sttype=DECL_STMT;
    	t1->flist=fhead;
    	fhead=NULL;
    	statement *t2=sblock_begin[sbtop]; 
    	if(t2->prev==NULL){
    		temp=t1;
    	}
    	if(t2!=NULL){
    		t1->prev=t2->prev;
    		t2->prev=t1;
    		t1->next=t2;
    		if(t1->prev!=NULL)t1->prev->next=t1;
    	}
    	t1->lineno=LINENO;
    }
#line 6104 "y.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 2321 "grammar.y" /* yacc.c:1646  */
    {
      de1=temp3;
      (yyval.ptr)=(yyvsp[0].ptr);
      #ifdef DEBUGGING
        printf("%s\n", "declaration_list-1");
      #endif
    }
#line 6116 "y.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 2328 "grammar.y" /* yacc.c:1646  */
    {
      (yyval.ptr)=(yyvsp[-1].ptr);
      #ifdef DEBUGGING
        printf("%s\n", "declaration_list-1");
      #endif
    }
#line 6127 "y.tab.c" /* yacc.c:1646  */
    break;


#line 6131 "y.tab.c" /* yacc.c:1646  */
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
#line 2336 "grammar.y" /* yacc.c:1906  */

#include <stdio.h>

void yyerror(const char *s)
{
	fflush(stdout);
	fprintf(stderr, "%d*** %s\n",LINENO, s);
}

printlibdtypes(){
  for(int k=0;k<5;k++){
    for(int i=0;i<7;i++){
    }
  }
  for(int k=0;k<3;k++){
    for(int i=0;i<8;i++){
    }
  }
}

main(int argc, char *argv[]){
  if(argc<2){
    printf("LEss number of arguments\n");
    return;
  }
  yyin=fopen(argv[1],"r");
  int t1=0;
  mainfunarr=(char *)malloc(sizeof(char)*500);
  for(int i=0;i<500;i++)mainfunarr[i]='\0';
  while(argv[1][t1]!='.')t1++;
  strncpy(header,argv[1],t1+1);
  strncpy(gheader,argv[1],t1);
  strncpy(source,argv[1],t1+1);
  if(argc >2 ){
    //for all extra command line argument. option for partition size on cpu gpu has to be added.
    int temp=2;
    while(argc>temp){
      if(!strcmp(argv[temp],"-ptype"))union_type=atoi(argv[temp+1]);//if point is float give command line -ptype 1
      else if(!strcmp(argv[temp],"-pdim"))pdim_size=atoi(argv[temp+1]);//if points have dim==2 or dim==3 give that value. default is 1.
      else if(!strcmp(argv[temp],"-mtype")){
        morph_size=atoi(argv[temp+1]);//if algo is morph give allocation size -mtype size
        MORPH_FLAG=1;
      }
      else if (!strcmp(argv[temp], "-convert")) {
        CONVERT_VERTEX_EDGE = atoi(argv[temp+1]);
      }
      temp=temp+2;
    }
  }
  dir_decl *d1=new dir_decl();
  d1->name=malloc(sizeof(char)*30);
  tree_typedecl *tt1=new tree_typedecl();
  tt1->datatype=INT_TYPE;tt1->name=malloc(sizeof(char)*100);strcpy(tt1->name,dtypenames[tt1->datatype]);
  strcpy(d1->name,"MAX_INT");
  GLOBAL_TABLE.addsymbol(d1,tt1);
  if(GPUCODEFLAG==1)strcat(source,"cu");
  if(GPUCODEFLAG==0)strcat(source,"cpp");
  FP1=fopen(source,"w+");
  int parserr;

  parserr=yyparse();
  if(parserr!=0)exit(0);
  strcat(header,"h");
  strcat(gheader,"global.h");
  FP=fopen(header,"w+");
  FPG=fopen(gheader,"w+");
  if(FPG==NULL){printf("FOPEN FAILED\n");return;}
  fprintf(FPG,"int FALC_THREADS;\n");
  fprintf(FP1,"\n #include \"%s\"\n",header);
  fprintf(FP,"\n#include \"%s\"\n",gheader);
  system("rm -f global.h");
  if(GALOIS_FLAG==0){
    for(int ii=0;ii<TOT_GPU_GRAPH;ii++)fprintf(FP1,"cudaDeviceProp prop%d;\n",ii);
    if(GPUCODEFLAG){
      fprintf(FP," #include \"HGraph.h\"\n #include \"GGraph.cu\"\n#include \"thrust.cu\"\n #include \"HSetOPT.h\"\n #include<sys/time.h>\n#include </usr/local/cuda/include/cuda.h>\n #include </usr/local/cuda/include/cuda_runtime_api.h>\n#include<unistd.h>\n");
    }else {
      fprintf(FP," #include \"../include/HGraph.h\"\n  #include \"../include/HSetOPT.h\"\n #include<sys/time.h>\n#include<unistd.h>\n");

    }
  }
  else{

    fprintf(FP,"#include \"../include/HGraph.h\"\n");
    fprintf(FP,"#include \"../include/HSet.h\"\n");
  }

  temp->print();
  setparent();
  ERRPRINT=1;
  temp->print();
  if(errflag!=0){
    printf("skipping codegeneration\n");
    exit(0);
  }


 // falcon extension code
  convert_vertex_edge();

  #ifdef DEBUGGING
    printf("%s\n", "\n***********************\n****parse completed****\n***********************\n");
  #endif

  temp->codeGen1();
  for(int ii=1;ii<TOT_GPU_GRAPH;ii++)fprintf(FP,"cudaDeviceProp prop%d;\n",ii);
  printf("codegeneration done\n output files \n 1)%s\n %s\n %s \n",source,header,gheader);
}

