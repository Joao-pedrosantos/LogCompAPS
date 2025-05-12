%{
  #include <stdio.h>
  #include <stdlib.h>

  int yylex(void);
  void yyerror(const char *s) { fprintf(stderr,"Erro: %s\n",s); }
%}

/* ── Tipos que o scanner envia ──────────── */
%union {
    int   intVal;
    char *strVal;
}

/* ── Tokens sem valor ───────────────────── */
%token TK_PENSO TK_EH TK_QUESTIONO TK_E TK_GUARDO TK_EM TK_DIGO
%token TK_CONSIDERO TK_ENTAO TK_TALVEZ TK_FIM TK_CONTINUO TK_ENQUANTO
%token TK_PLUS TK_MINUS TK_MUL TK_DIV
%token TK_GT TK_LT TK_GTE TK_LTE TK_EQ TK_NEQ

/* ── Tokens com valor ───────────────────── */
%token <intVal> TK_NUM
%token <strVal> TK_STR
%token <strVal> TK_ID

/* ── Precedência ───────────────────────── */
%left TK_PLUS TK_MINUS
%left TK_MUL  TK_DIV
%left TK_GT TK_LT TK_GTE TK_LTE TK_EQ TK_NEQ

%%  /* ─────────── Regras ─────────── */

programa
    : /* vazio */
    | programa pensamento
    ;

pensamento
    : atribuicao
    | pergunta
    | resposta
    | condicional
    | repeticao
    ;

atribuicao
    : TK_PENSO TK_ID TK_EH expressao
    ;

pergunta
    : TK_QUESTIONO TK_STR TK_E TK_GUARDO TK_EM TK_ID
    ;

resposta
    : TK_DIGO expressao
    ;

condicional
    : TK_CONSIDERO expressao TK_ENTAO bloco cond_opcional TK_FIM
    ;

cond_opcional
    : /* vazio */
    | TK_TALVEZ bloco
    ;

repeticao
    : TK_CONTINUO TK_ENQUANTO expressao bloco TK_FIM
    ;

bloco
    : pensamento
    | bloco pensamento
    ;

/* ── Expressões ────────────────────────── */
expressao
    : termo
    | expressao TK_PLUS  termo
    | expressao TK_MINUS termo
    | expressao TK_MUL   termo
    | expressao TK_DIV   termo
    | expressao TK_GT  termo
    | expressao TK_LT  termo
    | expressao TK_GTE termo
    | expressao TK_LTE termo
    | expressao TK_EQ  termo
    | expressao TK_NEQ termo
    ;

termo
    : TK_NUM
    | TK_STR
    | TK_ID
    | '(' expressao ')'
    ;

%%  /* ── Código de apoio ───────────────── */

int main(void){
    printf("Iniciando análise...\n");
    if(yyparse()==0)
        printf("Análise concluída com sucesso!\n");
    return 0;
}
