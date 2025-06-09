#include <stdio.h>
int main(void){
    /* variáveis auto-declaradas */
    long i, soma, limite;

limite = 0;
printf("Somar de 1 até quanto? "); fflush(stdout);
scanf(" %ld", &limite);
soma = 0;
i = 1;
while((i <= limite)){
}
printf("A soma de 1 até ");
printf("%ld", limite);
printf(" é ");
printf("%ld", soma);
printf("\n");
return 0;}
