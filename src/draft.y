%{
#include "ast.h"
#include <stdio.h>
Node *ast_root;
int yylex(void);
void yyerror(const char *s){ fprintf(stderr,"Erro sintático: %s\n",s); }
%}

%union{
    long  ival;
    char *sval;
    Node *nptr;
}

%token <ival> NUM
%token <sval> ID STR
%token KW_PENSO KW_EH KW_DIGO KW_QST KW_GUARDO KW_EM
%token KW_CONS KW_ENTAO KW_TALVEZ KW_FIM
%token KW_CONT KW_ENQ
%token KW_E
%token GE LE EQ NE GT LT

%left GE LE GT LT EQ NE
%left '+' '-'
%left '*' '/'

%type <nptr> program seq stmt plist cond expr

%%

program : seq                                     { ast_root = $1; }
        ;

seq     :                                          { $$ = NULL; }
        | seq stmt                                { $$ = seq_append($1,$2); }
        ;

opt_e   :                                          { }
        | KW_E                                    { }
        ;

opt_eol :                                         { }
        | ';'                                    { }

stmt    : KW_PENSO ID KW_EH expr                  { $$ = assign_node($2,$4); }
        | KW_DIGO plist                           { $$ = $2; }
        | KW_QST STR opt_e KW_GUARDO KW_EM ID     { $$ = scan_node($6,$2); }
        | KW_CONS cond KW_ENTAO opt_eol seq KW_FIM
                                                { $$ = if_node($2,$5,NULL); }
        | KW_CONS cond KW_ENTAO opt_eol seq KW_TALVEZ opt_eol seq KW_FIM
                                                { $$ = if_node($2,$5,$8); }
        | KW_CONT KW_ENQ cond opt_eol seq KW_FIM  { $$ = while_node($3,$5); }
        | ';'                                     { $$ = NULL; }
        ;

plist   : expr                                    { $$ = plist_append(NULL,$1); }
        | STR                                     { $$ = plist_append(NULL,str_node($1)); }
        | plist '+' expr                          { $$ = plist_append($1,$3); }
        | plist '+' STR                           { $$ = plist_append($1,str_node($3)); }
        ;

cond    : expr                                    { $$ = $1; }
        | expr GT expr                            { $$ = binop_node(">", $1,$3); }
        | expr GE expr                            { $$ = binop_node(">=",$1,$3); }
        | expr LT expr                            { $$ = binop_node("<", $1,$3); }
        | expr LE expr                            { $$ = binop_node("<=",$1,$3); }
        | expr EQ expr                            { $$ = binop_node("==",$1,$3); }
        | expr NE expr                            { $$ = binop_node("!=", $1,$3); }
        ;

expr    : NUM                                     { $$ = num_node($1); }
        | ID                                      { $$ = id_node($1); }
        | '(' expr ')'                            { $$ = $2; }
        | expr '+' expr                           { $$ = binop_node("+",$1,$3); }
        | expr '-' expr                           { $$ = binop_node("-",$1,$3); }
        | expr '*' expr                           { $$ = binop_node("*",$1,$3); }
        | expr '/' expr                           { $$ = binop_node("/",$1,$3); }
        ;

%%
