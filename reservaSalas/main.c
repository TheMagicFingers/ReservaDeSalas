#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h" /** inclui o arquivo funcoes.h*/

int main()
{
    char *user = entrada_char("Usuario: ");
    char *senha = entrada_char("Senha: ");
    login(user,senha);
    return 0;
}
