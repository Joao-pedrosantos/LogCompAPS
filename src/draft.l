%{
#include "draft.tab.h"   /* tokens do Bison */
#include <stdlib.h>
#include <string.h>
%}

%option noyywrap

DIGIT   [0-9]
ID      [a-zA-Z][a-zA-Z0-9_]*

%%

"penso"             { return TK_PENSO; }
"é"                 { return TK_EH; }
"questiono"         { return TK_QUESTIONO; }
"e"                 { return TK_E; }
"guardo"            { return TK_GUARDO; }
"em"                { return TK_EM; }
"digo"              { return TK_DIGO; }
"considero"         { return TK_CONSIDERO; }
"então"             { return TK_ENTAO; }
"talvez"            { return TK_TALVEZ; }
"fim"               { return TK_FIM; }
"continuo"          { return TK_CONTINUO; }
"enquanto"          { return TK_ENQUANTO; }
"=="                { return TK_EQ; }
"!="                { return TK_NEQ; }
">="                { return TK_GTE; }
"<="                { return TK_LTE; }
">"                 { return TK_GT; }
"<"                 { return TK_LT; }
"+"                 { return TK_PLUS; }
"-"                 { return TK_MINUS; }
"*"                 { return TK_MUL; }
"/"                 { return TK_DIV; }
{DIGIT}+            { yylval.intVal = atoi(yytext); return TK_NUM; }
\"([^\\\n\"]|\\.)*\" { yylval.strVal = strdup(yytext); return TK_STR; }
{ID}                { yylval.strVal = strdup(yytext); return TK_ID; }
[ \t\r\n]+          { /* ignora */ }
"//".*              { /* ignora */ }
.                   { fprintf(stderr,"Caractere inesperado: %s\n",yytext); }

%%