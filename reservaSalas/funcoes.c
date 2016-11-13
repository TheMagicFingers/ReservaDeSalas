#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

/** Arquivo onde serão inseridas as funções */

void menu(){
    int op, op_cad, op_res;
    system("cls");
    printf("SISTEMA DE CADASTRO DE SALAS\n");

    printf("[1] - Realizar um novo cadastro\n");
    printf("[2] - Realizar uma consulta ao sistema\n");
    printf("[3] - Reservar uma sala\n");
    printf("[4] - Elaborar um relatorio\n");
    printf("[5] - Sair\n");
    scanf("%d", &op);

    switch(op){
    case 1:
        system("cls");
        printf("Informe o tipo de Cadastro\n");
        printf("[1] - Sala\n");
        printf("[2] - Docente\n");
        printf("[3] - Voltar\n");
        scanf("%d", &op_cad);

        switch(op_cad){
        case 1:
        case 2:
            cadastrar(op_cad);
            break;
        case 3:
            menu();
            break;
        }
        break;
    case 2:
        system("cls");
        printf("Consulta de registros\n");
        printf("[1] - Salas Cadastradas\n");
        printf("[2] - Docentes Cadastrados\n");
        printf("[3] - Reservas de Salas\n");
        printf("[4] - Voltar\n");
        scanf("%d", &op_res);
        switch(op_res){
            case 1:
            case 2:
            case 3:
                consultaReser(op_res);
                break;
            case 4:
                menu();
                break;
            default:
                printf("Opcao invalida!\n");
                system("pause");
        }
        break;
    case 3:
        reserva();
        break;
    case 4:
        relatorio();
        break;
    case 5:
        exit(0);
        break;
    default:
        printf("Opcao invalida!\n");
        system("pause && cls");
        menu();
        break;
    }
}

void cadastrar(int op){
    system("cls");
    int sair;
    printf("Deseja Continuar? \n");
    printf("[1] - Sim\n");
    printf("[2] - Nao\n");
    scanf("%d", &sair);
    switch(sair){
        case 2:
            menu();
            break;
        case 1:
            switch(op){
                case 2: ; // NÃO APAGUE O ; Ler observação 1 no final do arquivo
                    Docentes docente;
                    docente.id = 1;
                    printf("Digite a matricula: ");
                    scanf("%d", &docente.mat);
                    fflush(stdin);
                    printf("Digite o nome: ");
                    gets(docente.nome);

                    printf("ID: %d  ", docente.id);
                    printf("Nome: %s  ", docente.nome);
                    printf("Matricula: %d  ", docente.mat);
                    system("pause");
                    menu();
                    break;
                default:
                    printf("Opcao invalida\n");
                    break;
            }
        default:
            printf("Opção invalida\n");
            break;
    }
    //fiz so a parte da sala para testar
    //nao levei em conta o op que esta chegando como paramentro
    /*TipoSala tipoSala;
    printf("Numero: ");
    scanf("%d", &tipoSala.numSala);
    printf("Bloco: ");
    fflush(stdin);
    tipoSala.bloco = getchar();
    printf("[1] Laboratorio\n[2] Sala Comum\n");
    scanf("%d", &tipoSala.caraterSala);
    tipoSala.id = getId_tipoSala();//o id da sala atual vai ser o id anterior incrementado em 1
    dbSala(tipoSala);
    system("pause");
    menu();*/
}

//alterei a funcao consulta reserva para que ela fique mais generica da seguinte forma:
//no menu peco para o usuario informar qual objeto ele quer consultar:
//1 - Salas
//2 - Docentes
//3 - Reservas
//e com isso faço o tratamento para listar os dados corretamente.
void consultaReser(int op_res){

    FILE *arq;

    if(op_res == 1){//caso a op_res seja 1 -> consulta de salas
        arq = fopen("db/dbSala.dat", "rb");
        TipoSala tipoSala;
        printf("Lista de Salas cadastradas\n");
        while (fread(&tipoSala, sizeof tipoSala, 1, arq)){//abro o dbSala.dat e listo os registros contido nele
            printf("ID: %d ",tipoSala.id);
            printf("Sala: %c%-6dTipo: ",tipoSala.bloco,tipoSala.numSala);
            if(tipoSala.caraterSala == 1){
                printf("Laboratorio\n");
            }else if(tipoSala.caraterSala){
                printf("Comum\n");
            }else{
                printf("Desconhecido\n");
            }
        }
    }else if(op_res == 2){//caso a op_res seja 2 -> consulta de docentes
        printf("Lista de Docentes cadastrados\n");
    }else if(op_res == 3){//caso a op_res seja 3 -> consulta de reservas
        printf("Lista de reservas\n");
    }

    fclose(arq);
    system("pause");
    menu();
}

int dbSala(TipoSala tipoSala){

    int flg = 1;
    FILE *arq;//ponteiro para o tipo arquivo
    arq = fopen("db/dbSala.dat", "a");//abro o arquivo no modo a -> append

    //falta implementar

    if(arq != NULL){//caso a variavel n esteja nula posso operar sobre ela.
        if(registro_duplicado(tipoSala.numSala, tipoSala.bloco)){
            fwrite(&tipoSala, sizeof(tipoSala), 1, arq);
            printf("Sala cadastrada com sucesso!\n");
        }else{
            printf("Erro: Informacao duplicado!\n");
        }
    }else{
        printf("Erro ao abrir banco de dados!\n");
        flg = 0;
    }

    fclose(arq);//fecho o arquivo txt
    return flg;//flg = 1 -> op bem sucedida | flg = 0 -> ocorreu algum erro de leitura.
}

int registro_duplicado(int numSala, char bloco){

    TipoSala ts;
    FILE *arq;//ponteiro de tipo arquivo
    arq = fopen("db/dbSala.dat", "rb");//aponto o arq para o dbSala
    int flg = 1;

    if(arq != NULL){
        while (fread(&ts, sizeof ts, 1, arq)){
            if(ts.bloco == bloco && ts.numSala == numSala){
                //caso o dado informado ja esteja no arquivo, flg = 0 e n salvo os dados atuais.
                flg = 0;
            }
        }
    }
    fclose(arq);
    return flg;
}

int getId_tipoSala(){

    FILE *arq;
    arq = fopen("db/dbSala.dat", "rb");

    TipoSala ts;
    int last_id;

    if(arq != NULL){
        while(fread(&ts, sizeof ts, 1, arq)){
            last_id = ts.id;
            //listo todos os ids e quando sair do while a var last_id vai conter o ultimo id
        }
    }

    fclose(arq);
    //retorno o last_id incrementado para ser id do novo objeto.
    return last_id + 1;
}

int dbDocente(Docentes docente){
    printf("OK!\n");
    system("pause && cls");
    menu();
    return 0;
}

void relatorio(){
    printf("Falta implementar!\n");
}

int reserva(){
    printf("Falta implementar!\n");
    return 0;
}

int entrada_num(char texto[50]){
    int numEntrada;
    printf("\nDigite %s: ", texto);
    scanf("%d", &numEntrada);
    return numEntrada;
}

int login(int senha, int cpf){ // Primeiro recebe a senha e depois o cpf devido à ordem de precedêcia do C.
    int TrueCpf = 123456;
    int TrueSenha = 1234;
    if((cpf == TrueCpf) && senha == TrueSenha){
        menu();
    }else{
        printf("O cpf ou a senha estao incorretos. Tente novamente.\n");
        login(entrada_num("Senha"), entrada_num("CPF")); //chama funcao login novamente até que o usuário acerte o login.
    }
}
/** OBS 1:
This is a quirk of the C grammar. A label (Cleanup:) is not allowed to appear immediately before a declaration
(such as char *str ...;), only before a statement (printf(...);). In C89 this was no great difficulty because
declarations could only appear at the very beginning of a block, so you could always move the label down a bit and
avoid the issue. In C99 you can mix declarations and code, but you still can't put a label immediately before a declaration.
You can put a semicolon immediately after the label's colon to make there be an empty statement (https://goo.gl/6SwXRB) **/
