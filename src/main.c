#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

// Protótipos
int  yyparse(void);
extern Node *ast_root;
void emit_c(Node *root, const char *outfile);
extern FILE *yyin; // Necessário para apontar o yyin para um arquivo

int main(int argc, char *argv[])
{
    // Verifica se um nome de arquivo foi passado como argumento
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo.dft>\n", argv[0]);
        return 1;
    }

    // Abre o arquivo de entrada fornecido no argumento
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror(argv[1]); // Reporta erro se não conseguir abrir o arquivo
        return 1;
    }

    // 1. Roda o parser. Se a sintaxe estiver correta, yyparse() retorna 0.
    if (yyparse() == 0) {
        // 2. Gera o código C intermediário em "temp.c"
        emit_c(ast_root, "temp.c");
        
        // 3. Compila "temp.c" para um executável "temp.out".
        if (system("gcc temp.c -o temp.out -Wall -Wextra")) {
            fprintf(stderr, "Erro na compilação do código C gerado.\n");
            fclose(yyin);
            return 1; // Retorna erro se o GCC falhar
        }
        
        fclose(yyin); // Fecha o arquivo de entrada
        return 0; // Sucesso
    }
    
    fclose(yyin); // Fecha o arquivo de entrada em caso de erro de parse
    return 1; // Retorna erro se o parser falhar
}
