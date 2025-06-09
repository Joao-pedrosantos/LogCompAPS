#ifndef DRAFT_AST_H
#define DRAFT_AST_H
#include <stddef.h>

/* ── Tipos de nó ───────────────────────────────────────────────────── */
typedef enum {
    N_NUM,       /* número inteiro                          */
    N_ID,        /* identificador                           */
    N_STR,       /* string literal                          */
    N_BINOP,     /* exp binária (+, -, *, /, >, < …)        */

    N_ASSIGN,    /* atribuição id = expr  OU  penso …       */
    N_PLIST,     /* lista de itens do “digo …”              */
    N_SCAN,      /* questiono "prompt" guardo em var        */

    N_IF,        /* if / else                               */
    N_WHILE,     /* while                                   */
    N_SEQ        /* sequência genérica de statements        */
} NodeType;

/* ── Estrutura principal ──────────────────────────────────────────── */
typedef struct Node {
    NodeType      type;
    char         *text;     /* lexema, operador ou string      */
    struct Node  *left;     /* 1º filho / valor / condição     */
    struct Node  *right;    /* 2º filho / corpo / prompt ptr   */
    struct Node  *next;     /* encadeia statements ou itens    */
} Node;

/* ── Construtores ─────────────────────────────────────────────────── */
Node *num_node(long v);
Node *id_node (const char *s);
Node *str_node(const char *s);

Node *binop_node(const char *op, Node *l, Node *r);

Node *assign_node(const char *name, Node *expr);
Node *plist_append(Node *list, Node *item);      /* “digo” list */
Node *scan_node(const char *var, const char *prompt);

Node *if_node   (Node *cond, Node *thenBlk, Node *elseBlk);
Node *while_node(Node *cond, Node *body);

Node *seq_append(Node *seq,  Node *stmt);        /* sequência */

void  free_tree(Node *n);

#endif
