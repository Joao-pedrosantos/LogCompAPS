#include "ast.h"
#include <stdlib.h>
#include <string.h>

/* ── Helpers ───────────────────────────────────────────────────────── */
static Node *new(NodeType t)
{
    Node *n = calloc(1,sizeof(Node));
    n->type = t;
    return n;
}
static char *dupstr(const char *s) { return s ? strdup(s) : NULL; }

/* ── Expressões ────────────────────────────────────────────────────── */
Node *num_node(long v)            { Node*n=new(N_NUM); n->left=(void*)v; return n; }
Node *id_node (const char *s)     { Node*n=new(N_ID);  n->text=dupstr(s); return n; }
Node *str_node(const char *s)     { Node*n=new(N_STR); n->text=dupstr(s); return n; }
Node *binop_node(const char*op,Node*l,Node*r)
{ Node*n=new(N_BINOP); n->text=dupstr(op); n->left=l; n->right=r; return n; }

/* ── Statements ───────────────────────────────────────────────────── */
Node *assign_node(const char *name, Node *expr)
{ Node*n=new(N_ASSIGN); n->text=dupstr(name); n->left=expr; return n; }

Node *plist_append(Node *list, Node *item)       /* lista de “digo” */
{
    if(!list) { Node *h=new(N_PLIST); h->left=item; return h; }
    Node *p=list; while(p->next) p=p->next;
    p->next=new(N_PLIST); p->next->left=item; return list;
}

Node *scan_node(const char *var, const char *prompt)
{
    Node*n=new(N_SCAN);
    n->text = dupstr(var);            /* variável destino */
    n->right = (Node*)dupstr(prompt); /* prompt salva em right (cast) */
    return n;
}

Node *if_node(Node*c,Node*t,Node*e){Node*n=new(N_IF);n->left=c;n->right=t;n->next=e;return n;}
Node *while_node(Node*c,Node*b){Node*n=new(N_WHILE);n->left=c;n->right=b;return n;}

Node *seq_append(Node *seq, Node *stmt)
{
    if(!seq){ Node *h=new(N_SEQ); h->left=stmt; return h; }
    Node *p=seq; while(p->next) p=p->next;
    p->next=new(N_SEQ); p->next->left=stmt; return seq;
}

/* ── Free ──────────────────────────────────────────────────────────── */
void free_tree(Node *n)
{
    if(!n) return;
    free_tree(n->left);
    free_tree(n->right);
    free_tree(n->next);
    free(n->text);
    free(n);
}
