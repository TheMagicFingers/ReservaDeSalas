#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

/** Arquivo onde serão inseridas as funções */

void menu(){

    printf("Menu\n");
/*
    ~[1] - Realizar um novo cadastro
        +[1] - Sala
        +[2] - Docente
    ~[2] - Realizar uma consulta ao sistema
    ~[3] - Reservar uma sala
    ~[4] - Elaborar um relatorio
    ~[5] - Sair
*/
}


void cadastrar(int op){
}

void consultaReser(){

}

int dbSala(TipoSala tipoSala){

    int flg = 1;
    FILE *arq;//ponteiro para o tipo arquivo
    arq = fopen("db/dbSala.txt", "a");//abro o arquivo no modo a -> append

    //falta implementar
    verifica_registro(tipoSala.numSala);

    if(arq != NULL){//caso a variavel n esteja nula posso operar sobre ela.
        fprintf(arq,"%d ", 1);//id temporariamente 1 e escrevo no txt
        fputc(strupr(tipoSala.bloco), arq);//escrevo o bloco em letra maiuscula no arq
        fprintf(arq, " %d %d\n",tipoSala.numSala, tipoSala.caraterSala);//escrevo os outros dados da struct e dou um \n
    }else{
        printf("Erro ao abrir banco de dados!\n");
        flg = 0;
    }

    fclose(arq);//fecho o arquivo txt
    return flg;//flg = 1 -> op bem sucedida | flg = 0 -> ocorreu algum erro de leitura.
}

int verifica_registro(int numSala){

    FILE *arq;//ponteiro de tipo arquivo
    arq = fopen("db/dbSala.txt", "r");//aponto o arq para o dbSala
    int linhas = 0;//variavel para contar quantas linhas o txt tem

    while(!feof(arq)){//enquanto arq != do feof (end of file)
        if(fgetc(arq) == '\n'){
            linhas++;//dou um ++ quando encontro uma quebra de linha
        }            //oq significa q tenho mais uma linha
    }

    printf("Registros: %d\n",linhas);

    printf("\nFalta implementrar a verificacao de duplicidade.\n");
    return 0;
}

int dbDocente(Docentes docente){
    printf("OK!\n");
    system("pause && cls");
    menu();
    return 0;
}

void relatorio(){
}

int reserva(){
    return 0;
}

int entrada_num(char texto[50]) {
    int numEntrada;
    printf("\nDigite %s: ", texto);
    scanf("%d", &numEntrada);
    return numEntrada;
}

int login(int cpf, int senha)
{
    int TrueCpf = 123456789;
    int TrueSenha = 1234;
    if((cpf == TrueCpf) && senha == TrueSenha){
        return 1;
    }else{
        return 0;
    }
}


