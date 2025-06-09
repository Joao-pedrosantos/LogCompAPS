#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ───────── utilidade: lista encadeada de strings únicas ─────────── */
typedef struct IdNode {
    char            *name;
    struct IdNode   *next;
} IdNode;

static int id_exists(IdNode *h, const char *s)
{
    for(; h; h=h->next) if(strcmp(h->name,s)==0) return 1;
    return 0;
}
static void id_add(IdNode **h, const char *s)
{
    if(id_exists(*h,s)) return;
    IdNode *n = malloc(sizeof(IdNode));
    n->name = strdup(s);
    n->next = *h;
    *h = n;
}
static void idlist_free(IdNode *h)
{
    while(h){ IdNode *t=h->next; free(h->name); free(h); h=t; }
}

/* ───────── coleta identificadores em expr ───────────────────────── */
static void collect_expr_ids(Node *n, IdNode **ids);

static void collect_stmt_ids(Node *s, IdNode **ids)
{
    if(!s) return;
    switch(s->type){
    case N_ASSIGN:
        id_add(ids, s->text);
        collect_expr_ids(s->left, ids);
        break;
    case N_PLIST: {
        Node *cur=s;
        while(cur){ collect_expr_ids(cur->left, ids); cur=cur->next; }
        break;
    }
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
    default: break;
    }
}

static void collect_block_ids(Node *blk, IdNode **ids)
{
    for(Node *n=blk; n; n=n->next)
        collect_stmt_ids(n->left ? n->left : n, ids);
}

static void collect_expr_ids(Node *n, IdNode **ids)
{
    if(!n) return;
    switch(n->type){
    case N_ID: id_add(ids, n->text); break;
    case N_BINOP: collect_expr_ids(n->left, ids);
                  collect_expr_ids(n->right, ids); break;
    default: break;
    }
}

/* ───────── emissor de código (expressões & blocos) ───────────────── */
static void emit_expr(Node *n, FILE *f);

static void emit_stmt(Node *s, FILE *f)
{
    if(!s) return;
    switch(s->type){
    case N_ASSIGN:
        fprintf(f,"%s = ",s->text); emit_expr(s->left,f); fprintf(f,";\n");
        break;

    case N_PLIST: {                     /* lista “digo” */
        Node *cur=s;
        while(cur){
            Node *item=cur->left;
            if(item->type==N_STR)
                fprintf(f,"printf(\"%s\");\n", item->text);
            else{
                fprintf(f,"printf(\"%%ld\", "); emit_expr(item,f); fprintf(f,");\n");
            }
            cur=cur->next;
        }
        fprintf(f,"printf(\"\\n\");\n");
        break;
    }

    case N_SCAN:
        fprintf(f, "printf(\"%s \"); fflush(stdout);\n", (char*)s->right);
        /* CORREÇÃO: Adicionado um espaço antes de "%ld" para consumir quebras de linha
           ou espaços em branco que sobraram no buffer de entrada. */
        fprintf(f, "scanf(\" %%ld\", &%s);\n", s->text);
        break;

    case N_IF:
        fprintf(f,"if("); emit_expr(s->left,f); fprintf(f,"){\n");
        emit_stmt(s->right,f);
        fprintf(f,"}");
        if(s->next){ fprintf(f,"else{\n"); emit_stmt(s->next,f); fprintf(f,"}"); }
        fprintf(f,"\n");
        break;

    case N_WHILE:
        fprintf(f,"while("); emit_expr(s->left,f); fprintf(f,"){\n");
        emit_stmt(s->right,f); fprintf(f,"}\n");
        break;

    default: break;
    }
}

static void emit_block(Node *blk, FILE *f)
{
    for(Node *n=blk; n; n=n->next)
        emit_stmt(n->left ? n->left : n, f);
}

static void emit_expr(Node *n, FILE *f)
{
    switch(n->type){
    case N_NUM: fprintf(f,"%ld",(long)n->left); break;
    case N_ID:  fprintf(f,"%s",n->text); break;
    case N_BINOP:
        fprintf(f,"("); emit_expr(n->left,f); fprintf(f," %s ",n->text);
        emit_expr(n->right,f); fprintf(f,")"); break;
    default: break;
    }
}

/* ───────── API principal ─────────────────────────────────────────── */
void emit_c(Node *root, const char *outname)
{
    /* 1. coleta variáveis */
    IdNode *ids=NULL;
    collect_block_ids(root, &ids);

    /* 2. gera arquivo C */
    FILE *f = fopen(outname,"w");
    if(!f){ perror(outname); return; }

    fprintf(f,"#include <stdio.h>\nint main(void){\n");

    /* declarações */
    if(ids){
        fprintf(f,"    /* variáveis auto-declaradas */\n    long ");
        for(IdNode*p=ids; p; p=p->next){
            fprintf(f,"%s", p->name);
            if(p->next) fprintf(f,", ");
        }
        fprintf(f,";\n\n");
    }

    /* corpo do programa */
    emit_block(root,f);

    fprintf(f,"return 0;}\n");
    fclose(f);

    idlist_free(ids);
}