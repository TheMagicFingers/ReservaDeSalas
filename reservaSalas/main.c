#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h" /** inclui o arquivo funcoes.h*/
#include "BibConio.h"

int main()
{
    login(entrada_num("Senha"), entrada_num("CPF")); // Primeiro recebe a senha e depois o cpf devido à ordem de precedêcia do C.
    return 0;
}
