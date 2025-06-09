/* codegen.c — gerador C para a linguagem Draft                        */
/* corrigido: evita recursão infinita em N_SEQ com left == NULL        */

#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ───────── utilidade: lista encadeada de identificadores únicos ──── */
typedef struct IdNode { char *name; struct IdNode *next; } IdNode;

static int  id_exists(IdNode *h, const char *s)
{ for (; h; h = h->next) if (!strcmp(h->name, s)) return 1; return 0; }

static void id_add(IdNode **h, const char *s)
{
    if (id_exists(*h, s)) return;
    IdNode *n = malloc(sizeof *n);
    n->name   = strdup(s);
    n->next   = *h;
    *h        = n;
}

static void idlist_free(IdNode *h)
{ while (h) { IdNode *t = h->next; free(h->name); free(h); h = t; } }

/* ───────── coleta de variáveis ───────────────────────────────────── */
static void collect_expr_ids(Node *n, IdNode **ids);

static void collect_stmt_ids(Node *s, IdNode **ids)
{
    if (!s) return;
    switch (s->type) {
    case N_ASSIGN:
        id_add(ids, s->text);
        collect_expr_ids(s->left, ids);
        break;

    case N_PLIST:
        for (Node *p = s; p; p = p->next) collect_expr_ids(p->left, ids);
        break;

    case N_SCAN:
        id_add(ids, s->text);
        break;

    case N_IF:
        collect_expr_ids(s->left, ids);
        collect_stmt_ids(s->right, ids);
        collect_stmt_ids(s->next , ids);
        break;

    case N_WHILE:
        collect_expr_ids(s->left, ids);
        collect_stmt_ids(s->right, ids);
        break;

    case N_SEQ:
        for (Node *p = s; p; p = p->next)
            if (p->left) collect_stmt_ids(p->left, ids);
        break;

    default: break;
    }
}

static void collect_expr_ids(Node *n, IdNode **ids)
{
    if (!n) return;
    switch (n->type) {
    case N_ID:    id_add(ids, n->text); break;
    case N_BINOP: collect_expr_ids(n->left , ids);
                  collect_expr_ids(n->right, ids); break;
    default: break;
    }
}

/* ───────── geração de código ─────────────────────────────────────── */
static void emit_expr (Node *n, FILE *f);      /* fwd           */
static void emit_stmt (Node *s, FILE *f);      /* declaração    */

static void emit_block(Node *blk, FILE *f)     /* seq encadeada */
{
    for (Node *p = blk; p; p = p->next)
        if (p->left)                           /* pula linhas vazias */
            emit_stmt(p->left, f);
}

static void emit_stmt(Node *s, FILE *f)
{
    switch (s->type) {

    case N_ASSIGN:
        fprintf(f, "%s = ", s->text);
        emit_expr(s->left, f);
        fprintf(f, ";\n");
        break;

    case N_PLIST: {
        Node *cur = s;
        while (cur) {
            Node *item = cur->left;
            if (item->type == N_STR)
                fprintf(f, "printf(\"%s\");\n", item->text);
            else {
                fprintf(f, "printf(\"%%ld\", ");
                emit_expr(item, f);
                fprintf(f, ");\n");
            }
            cur = cur->next;
        }
        fprintf(f, "printf(\"\\n\");\n");
        break;
    }

    case N_SCAN:
        fprintf(f, "printf(\"%s \"); fflush(stdout);\n", (char*)s->right);
        fprintf(f, "scanf(\" %%ld\", &%s);\n", s->text);
        break;

    case N_IF:
        fprintf(f, "if (");           emit_expr(s->left,  f); fprintf(f, ") {\n");
        emit_block(s->right, f);      fprintf(f, "}");
        if (s->next) {                fprintf(f, " else {\n");
            emit_block(s->next, f);   fprintf(f, "}"); }
        fprintf(f, "\n");
        break;

    case N_WHILE:
        fprintf(f, "while (");        emit_expr(s->left, f); fprintf(f, ") {\n");
        emit_block(s->right, f);      fprintf(f, "}\n");
        break;

    default: break;   /* os demais nós não geram stmt isolado */
    }
}

static void emit_expr(Node *n, FILE *f)
{
    switch (n->type) {
    case N_NUM:   fprintf(f, "%ld", (long)n->left); break;
    case N_ID:    fprintf(f, "%s", n->text);        break;
    case N_BINOP: fprintf(f, "("); emit_expr(n->left, f);
                  fprintf(f, " %s ", n->text);
                  emit_expr(n->right, f); fprintf(f, ")"); break;
    default: break;
    }
}

/* ───────── API principal ─────────────────────────────────────────── */
void emit_c(Node *root, const char *outname)
{
    IdNode *ids = NULL;
    collect_stmt_ids(root, &ids);

    FILE *f = fopen(outname, "w");
    if (!f) { perror(outname); return; }

    fprintf(f, "#include <stdio.h>\nint main(void) {\n");

    if (ids) {
        fprintf(f, "    long ");
        for (IdNode *p = ids; p; p = p->next)
            fprintf(f, "%s%s", p->name, p->next ? ", " : "");
        fprintf(f, ";\n\n");
    }

    emit_block(root, f);

    fprintf(f, "    return 0;\n}\n");
    fclose(f);
    idlist_free(ids);
}
