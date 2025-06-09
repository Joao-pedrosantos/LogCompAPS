#include "ast.h"
#include <stdlib.h>

int  yyparse(void);
extern Node *ast_root;

void emit_c(Node *root, const char *outfile);

int main(void)
{
    if(yyparse()==0){
        emit_c(ast_root,"temp.c");
        if(system("gcc temp.c -o temp.out -Wall -Wextra")) return 1;
        return system("./temp.out");
    }
    return 1;
}
