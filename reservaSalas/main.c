#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h" /** inclui o arquivo funcoes.h*/

int main()
{
    if(login(entrada_num("CPF"), entrada_num("Senha") == 1){
        menu();
    }else{
        printf("CPF ou senha incorretos, por favor tente novamente: \n");
        login(entrada_num("CPF"), entrada_num("Senha"));
    }
    return 0;
}
