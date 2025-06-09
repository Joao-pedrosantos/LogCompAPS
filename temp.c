#include <stdio.h>
int main(void) {
    long i, soma, limite;

limite = 0;
printf("Somar de 1 até quanto? "); fflush(stdout);
scanf(" %ld", &limite);
soma = 0;
i = 1;
while ((i <= limite)) {
soma = (soma + i);
i = (i + 1);
}
printf("A soma de 1 até ");
printf("%ld", limite);
printf(" é ");
printf("%ld", soma);
printf("\n");
    return 0;
}
