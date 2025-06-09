%option noyywrap
%{
#include "ast.h"
#include "draft.tab.h"
#include <string.h>
%}

%%

[\r\n]+                  { return ';'; }
[ \t]+                   { /* ignora espaços e tabs */ }
"penso"                  { return KW_PENSO; }
"é"                      { return KW_EH;    }
"digo"                   { return KW_DIGO;  }
"questiono"              { return KW_QST;   }
"guardo"                 { return KW_GUARDO;}
"em"                     { return KW_EM;    }
"e"                      { return KW_E;     } /* REGRA ADICIONADA */
"considero"              { return KW_CONS;  }
"então"                  { return KW_ENTAO; }
"talvez"                 { return KW_TALVEZ;}
"fim"                    { return KW_FIM;   }
"continuo"               { return KW_CONT;  }
"enquanto"               { return KW_ENQ;   }
">="                     { return GE; }
"<="                     { return LE; }
"!="                     { return NE; }
"=="                     { return EQ; }
">"                      { return GT; }
"<"                      { return LT; }

\"([^\\\"]|\\.)*\"       {
                           yylval.sval=strdup(yytext+1);
                           yylval.sval[strlen(yylval.sval)-1]='\0';
                           return STR;
                         }

[0-9]+                   { yylval.ival = atol(yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.sval = strdup(yytext); return ID; }
"="                      { return '='; }
"+"                      { return '+'; }
"-"                      { return '-'; }
"*"                      { return '*'; }
"/"                      { return '/'; }
"("                      { return '('; }
")"                      { return ')'; }
";"                      { return ';'; }
.                        { fprintf(stderr,"caractere inválido: %s\n", yytext); }

%%