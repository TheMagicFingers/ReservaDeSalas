#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

/** Arquivo onde serão inseridas as funções */

void menu(){
    int op, op_cad, op_res, op_ed, op_ex;
    system("cls");
    printf("SISTEMA DE CADASTRO DE SALAS\n");

    printf("[1] - Realizar um novo cadastro\n");
    printf("[2] - Realizar uma consulta ao sistema\n");
    printf("[3] - Reservar uma sala\n");
    printf("[4] - Editar dados\n");
    printf("[5] - Excluir dados\n");
    printf("[6] - Elaborar um relatorio\n");
    printf("[7] - Sair\n");
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
        system("cls");
        printf("\t\t---Tela de Edicao---\n");
        printf("[1] - Editar Sala\n");
        printf("[2] - Editar Docente\n");
        printf("[3] - Editar Reserva\n");
        printf("[4] - Voltar\n");

        scanf("%d", &op_ed);
        switch(op_ed){
        case 1:
            editarSala();
            break;
        case 2:
            editarDocente();
            break;
        case 3:
            printf("Falta implementar edicao de reservas!\n");
            break;
        case 4:
            menu();
            break;
        default:
            printf("Opcao invalida!\n");
            system("pause");
        }
        break;
    case 5:
        system("cls");
        printf("\t\t---Modulo de Exclusao de registros---\n");
        printf("[1] - Excluir Sala\n");
        printf("[2] - Excluir Docente\n");
        printf("[3] - Excluir Reserva\n");
        printf("[4] - Voltar\n");
        scanf("%d", &op_ex);

        switch(op_ex){
        case 1:
            excluirSala();
            break;
        case 2:
            excluirDocente();
        case 3:
            printf("Falta implementar!\n");
            break;
        case 4:
            menu();
        default:
            printf("Opcao invalida!\n");
            system("pause");
            menu();
        }
        break;
    case 6:
        relatorio();
        break;
    case 7:
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
                case 1: ;
                    TipoSala tipoSala;
                    printf("Informe o numero da sala: ");
                    scanf("%d", &tipoSala.numSala);
                    printf("Informe o bloco da sala: ");
                    fflush(stdin);
                    tipoSala.bloco = getchar();
                    printf("[1] Laboratorio\n[2] Sala Comum\n");
                    scanf("%d", &tipoSala.caraterSala);
                    //tipoSala.id = 1;
                    tipoSala.id = getId_tipoSala();//o id da sala atual vai ser o id anterior incrementado em 1
                    if(dbSala(tipoSala)){
                        printf("Sala salva com sucesso!\n");
                    }
                    system("pause");
                    menu();
                case 2: ; // NÃO APAGUE O ; Ler observação 1 no final do arquivo
                    Docentes docente;
                    docente.id = getId_docente();
                    printf("Digite a matricula: ");
                    scanf("%d", &docente.mat);
                    fflush(stdin);
                    printf("Digite o nome: ");
                    gets(docente.nome);

                    if(dbDocente(docente)){
                        printf("Docente cadastrado com sucesso!\n");
                    }
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
}

void consultaReser(int op_res){
//alterei a funcao consulta reserva para que ela fique mais generica da seguinte forma:
//no menu peco para o usuario informar qual objeto ele quer consultar:
//1 - Salas
//2 - Docentes
//3 - Reservas
//e com isso faço o tratamento para listar os dados corretamente.
    FILE *arq;

    if(op_res == 1){//caso a op_res seja 1 -> consulta de salas
        arq = fopen("db/dbSala.bin", "rb");
        system("cls");
        TipoSala tipoSala;
        printf("Lista de Salas cadastradas\n");
        printf("ID\tSala\tTipo\n");
        while (fread(&tipoSala, sizeof tipoSala, 1, arq)){//abro o dbSala.bin e listo os registros contido nele
            printf("%d\t",tipoSala.id);
            printf("%c%-6d\t",tipoSala.bloco,tipoSala.numSala);
            if(tipoSala.caraterSala == 1){
                printf("Laboratorio\n");
            }else if(tipoSala.caraterSala){
                printf("Comum\n");
            }else{
                printf("Desconhecido\n");
            }
        }
    }else if(op_res == 2){//caso a op_res seja 2 -> consulta de docentes
        Docentes docente;
        arq = fopen("db/dbDocente.bin", "rb");
        printf("Docentes cadastrados\n");
        printf("ID\tMatricula\tNome\n");
        while(fread(&docente, sizeof docente, 1, arq)){
            printf("%d\t%d\t\t%s\n", docente.id, docente.mat, docente.nome);
        }
    }else if(op_res == 3){//caso a op_res seja 3 -> consulta de reservas
        Reserva reserva;
        arq = fopen("db/dbReserva.bin", "rb");
        printf("Lista de reservas\n");
        while(fread(&reserva, sizeof(reserva), 1, arq)){
            printf("Reserva %d\n", reserva.id);
            printf("Data: %s\n", reserva.data);
            printf("De %s as %s\n", reserva.horaEntrada, reserva.horaSaida);
            printf("Professor responsavel: %d\n", reserva.id_Docente);
            printf("Sala: %d\n", reserva.id_TipoSala);
            if(reserva.reserProjetor == 1){
                printf("O projetor tambem foi reservado!\n");
            }
            printf("\n");
        }
    }

    fclose(arq);
    printf("\n");
    system("pause");
    menu();
}

int dbSala(TipoSala tipoSala){

    int flg = 1;
    FILE *arq;//ponteiro para o tipo arquivo
    arq = fopen("db/dbSala.bin", "a");//abro o arquivo no modo a -> append

    //falta implementar

    if(arq != NULL){//caso a variavel n esteja nula posso operar sobre ela.
        if(registro_duplicado_sala(tipoSala.numSala, tipoSala.bloco)){
            fwrite(&tipoSala, sizeof(tipoSala), 1, arq);
        }else{
            flg = 0;
            printf("Erro: Informacao duplicado!\n");
        }
    }else{
        printf("Erro ao abrir banco de dados <SALA>!\n");
        flg = 0;
    }

    fclose(arq);//fecho o arquivo txt
    return flg;//flg = 1 -> op bem sucedida | flg = 0 -> ocorreu algum erro de leitura.
}

int registro_duplicado_sala(int numSala, char bloco){

    TipoSala ts;
    FILE *arq;//ponteiro de tipo arquivo
    arq = fopen("db/dbSala.bin", "rb");//aponto o arq para o dbSala
    int flg = 1;

    if(arq != NULL){
        while (fread(&ts, sizeof ts, 1, arq)){
            if(ts.bloco == bloco && ts.numSala == numSala){
                //caso o dado informado ja esteja no arquivo, flg = 0 e n salvo os dados atuais.
                flg = 0;
                break;
            }
        }
    }
    fclose(arq);
    return flg;
}

int getId_tipoSala(){

    FILE *arq;
    arq = fopen("db/dbSala.bin", "rb");

    TipoSala tipoSala;
    int last_id, maior, i=0;

    if(arq != NULL){
        while(fread(&tipoSala, sizeof tipoSala, 1, arq)){
            last_id = tipoSala.id;
            if(i==0){
                maior = last_id;
            }else if(last_id > maior){
                maior = last_id;
            }
            i++;
        }
    }

    fclose(arq);

    if(i == 0){//significa que o arquivo esta vazio e nao existe id para fazer o incremento
        maior = 0;
    }
    //retorno o last_id incrementado para ser id do novo objeto.
    return maior + 1;
}

int dbDocente(Docentes docente){
    int flg = 1;
    FILE *arq;
    arq = fopen("db/dbDocente.bin", "a");

    if(arq != NULL){
            if(registro_duplicado_docente(docente.mat)){
                fwrite(&docente, sizeof(docente), 1, arq);
            }else{
                flg = 0;
                printf("Erro: Matricula duplicada!\n");
            }
    }else{
        printf("Erro ao abrir bando de dados dbDocente.bin\n");
        flg = 0;
    }
    fclose(arq);
    return flg;
}

int registro_duplicado_docente(int matricula){
    Docentes docente;
    int flg = 1;
    FILE *arq;
    arq = fopen("db/dbDocente.bin", "rb");
    if(arq != NULL){
        while(fread(&docente, sizeof(docente), 1, arq)){
            if(matricula == docente.mat){
                flg = 0;
                break;
            }
        }
    }else{
        printf("Arquivo errado!\n");
    }

    fclose(arq);
    return flg;
}

int getId_docente(){
    Docentes docente;
    int last_id, maior,i=0;
    FILE *arq;
    arq = fopen("db/dbDocente.bin", "rb");

    if(arq != NULL){
        while(fread(&docente, sizeof(docente), 1, arq)){
            last_id = docente.id;
            if(i==0){
                maior = last_id;
            }else if(last_id > maior){
                maior = last_id;
            }
            i++;
        }
    }else{
        printf("Erro ao abrir dbDocente.bin!\n");
    }

    if(i == 0){
        maior = 0;
    }

    fclose(arq);
    return maior+1;
}

void relatorio(){
    printf("Falta implementar!\n");
}

void reserva(){
    system("cls");
    printf("\t\t--- Reserva de Sala ---\n");
    Reserva reserva;
    printf("Data e hora da reserva\n");

    printf("Informe a data (dd/mm/aaaa)\n");
    fflush(stdin);
    gets(reserva.data);

    printf("Hora de entrada (hh:mm)\n");
    fflush(stdin);
    gets(reserva.horaEntrada);

    printf("Hora de saida (hh:mm)\n");
    fflush(stdin);
    gets(reserva.horaSaida);

    printf("Sala e responsavel\n");
    printf("Informe o id da sala: ");//funcao para encontrar o nome da sala
    scanf("%d", &reserva.id_TipoSala);

    printf("Informe o id do professor responsavel: ");//funcao para encontrar a mat do prof
    scanf("%d", &reserva.id_Docente);

    printf("Reserva de projetor\n[1] - Sim\n[2] - Nao\n");
    scanf("%d", &reserva.reserProjetor);
    //reserva.id = getId_reserva();
    reserva.id = 1;

    if(dbReserva(reserva)){
        printf("Reserva Cadastrada com sucesso!\n");
    }

    system("pause");
    menu();
}

int dbReserva(Reserva reserva){

    int flg = 1;
    FILE *arq;
    arq = fopen("db/dbReserva.bin", "a");

    if(arq != NULL){
        fwrite(&reserva, sizeof(reserva), 1, arq);
    }else{
        flg = 0;
        printf("Erro ao abrir dbReserva.bin");
    }

    fclose(arq);
    return flg;
}

int getId_reserva(){
    Reserva reserva;
    int last_id, maior, i=0;
    FILE *arq;
    arq = fopen("db/dbReserva.bin", "rb");

    if(arq != NULL){
        while(fread(&reserva, sizeof(reserva), 1, arq)){
            last_id = reserva.id;
            if(i ==0){
                maior = last_id;
            }else if(last_id > maior){
                maior = last_id;
            }
            i++;
        }
    }else{
        printf("Erro ao abrir dbReserva.bin!\n");
    }

    if(i == 0){
        maior = 0;
    }

    fclose(arq);
    return last_id+1;
}

char* entrada_char(char *texto)
{
    char *entrada = (char*) malloc(sizeof(char) * 50);
    printf("\nDigite %s", texto);
    gets(entrada);
    return entrada;
}

void login(char* user, char* senha){
    char *TrueUser = "Luquinhas";
    char * TrueSenha = "22k";

    if(strcmp(user,TrueUser) == 0 && strcmp(senha,TrueSenha) == 0){
        menu();
    }else{
        printf("O cpf ou a senha estao incorretos. Tente novamente.\n");
        system("pause && cls");
        char *user = entrada_char("Usuario: ");
        char *senha = entrada_char("Senha: ");
        login(user,senha);
    }
}

void editarSala(){

    int id_sala , flg = 0;
    printf("Informe o id da sala para edicao: ");
    scanf("%d", &id_sala);

    TipoSala edicaoSala, tipoSala;
    FILE *arq, *arq_tmp;
    arq = fopen("db/dbSala.bin", "r");

    while(fread(&tipoSala, sizeof(tipoSala), 1, arq)){
        if(id_sala == tipoSala.id){
            flg = 1;
        }
    }

    fclose(arq);

    if(flg){
        arq = fopen("db/dbSala.bin", "r");
        arq_tmp = fopen("db/tmpSala.bin", "a");
        while(fread(&tipoSala, sizeof(tipoSala), 1, arq)){
            if(!(id_sala == tipoSala.id)){//caso o id nao seja o id informado, o registro é salvo no .bin
                fwrite(&tipoSala, sizeof(tipoSala), 1, arq_tmp);
            }
        }
        fclose(arq);
        fclose(arq_tmp);

        edicaoSala.id = id_sala;
        printf("Informe o numero da sala: ");
        scanf("%d", &edicaoSala.numSala);
        printf("Informe o bloco da sala: ");
        fflush(stdin);
        edicaoSala.bloco = getchar();
        printf("[1] - Sala Comum\n[2] - Laboratorio\n");
        scanf("%d", &edicaoSala.caraterSala);

        arq_tmp = fopen("db/tmpSala.bin", "a");
        if(registro_duplicado_sala(edicaoSala.numSala, edicaoSala.bloco)){
            fwrite(&edicaoSala, sizeof(edicaoSala), 1, arq_tmp);
            printf("Sala editada com sucesso!\n");
            system("pause");
        }else{
            printf("Sala ja cadastrada!\n");
        }
        fclose(arq_tmp);
    }else{
        printf("Id nao encontrado!\n");
        system("pause");
    }

    remove("db/dbSala.bin");
    rename("db/tmpSala.bin", "db/dbSala.bin");
    menu();
}

void excluirSala(){
    int id_sala, flg = 0;
    printf("Informe o id da sala: ");
    scanf("%d", &id_sala);

    TipoSala tipoSala;
    FILE *arq;
    FILE *arq_tmp;

    arq = fopen("db/dbSala.bin", "r");
    arq_tmp=fopen("db/tmpSala.bin", "w+");

    while(fread(&tipoSala, sizeof(tipoSala), 1, arq)){
        if(tipoSala.id == id_sala){
            printf("Sala excluida com sucesso!\n");
            flg = 1;
            system("pause");
        }else{
            fwrite(&tipoSala, sizeof(tipoSala), 1, arq_tmp);
        }
    }

    if(!flg){
        printf("Sala nao encontrada!\n");
        system("pause");
    }

    fclose(arq);
    fclose(arq_tmp);

    remove("db/dbSala.bin");
    rename("db/tmpSala.bin", "db/dbSala.bin");

    menu();
}

void editarDocente(){
    Docentes docente;
    int id_docente, flg = 0;

    FILE *arq, *arq_tmp;
    arq = fopen("db/dbDocente.bin", "r");

    printf("Informe o id do docente: ");
    scanf("%d", &id_docente);
    while(fread(&docente, sizeof(docente), 1, arq)){
        if(id_docente == docente.id){
            flg = 1;
        }
    }
    fclose(arq);

    if(flg){
        arq = fopen("db/dbDocente.bin", "r");
        arq_tmp = fopen("db/tmpDocente.bin", "a");
        while(fread(&docente, sizeof(docente), 1,arq)){
            if(!(id_docente == docente.id)){
                fwrite(&docente, sizeof(docente), 1,arq_tmp);
            }
        }
        fclose(arq);
        fclose(arq_tmp);

        Docentes editaDocente;
        editaDocente.id = id_docente;
        printf("Informe a matricula: ");
        scanf("%d", &editaDocente.mat);
        printf("Informe o nome: ");
        fflush(stdin);
        gets(editaDocente.nome);

        arq_tmp = fopen("db/tmpDocente.bin", "a");

        if(registro_duplicado_docente(editaDocente.mat)){
            fwrite(&editaDocente, sizeof(editaDocente), 1,arq_tmp);
            printf("Docente editado com sucesso!\n");
            system("pause");
        }else{
            printf("Registro duplicado!\n");
        }
        fclose(arq_tmp);
    }else{
        printf("Id nao encontrado!\n");
    }

    remove("db/dbDocente.bin");
    rename("db/tmpDocente.bin", "db/dbDocente.bin");
    menu();
}

void excluirDocente(){
    int id_docente, flg = 0;
    printf("Informe o id do docente: ");
    scanf("%d", &id_docente);

    Docentes docente;
    FILE *arq;
    FILE *arq_tmp;

    arq = fopen("db/dbDocente.bin", "r");
    arq_tmp=fopen("db/tmpDocente.bin", "w+");

    while(fread(&docente, sizeof(docente), 1, arq)){
        printf("%d\n",docente.id);
        if(docente.id == id_docente){
            printf("Docente excluido com sucesso!\n");
            flg = 1;
            system("pause");
        }else{
            fwrite(&docente, sizeof(docente), 1, arq_tmp);
        }
    }

    if(!flg){
        printf("Docente nao encontrado!\n");
        system("pause");
    }

    fclose(arq);
    fclose(arq_tmp);

    remove("db/dbDocente.bin");
    rename("db/tmpDocente.bin", "db/dbDocente.bin");

    menu();
}

/** OBS 1:
This is a quirk of the C grammar. A label (Cleanup:) is not allowed to appear immediately before a declaration
(such as char *str ...;), only before a statement (printf(...);). In C89 this was no great difficulty because
declarations could only appear at the very beginning of a block, so you could always move the label down a bit and
avoid the issue. In C99 you can mix declarations and code, but you still can't put a label immediately before a declaration.
You can put a semicolon immediately after the label's colon to make there be an empty statement (https://goo.gl/6SwXRB)
**/
