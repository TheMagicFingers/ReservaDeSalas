#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h" /** inclui o arquivo funcoes.h*/

int main()
{
    int a = 2, b = 5;
    printf("%d + %d = %d", a, b, soma(a,b)); // APENAS PARA TESTE
    printf("\n%d + %d = %d", a, b, sub(a,b)); // APENAS PARA UM OUTRO TESTE
    return 0;
}
