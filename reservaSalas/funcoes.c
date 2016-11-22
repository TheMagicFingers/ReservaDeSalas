#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"
#include "BibConio.h"

/** Arquivo onde serão inseridas as funções */

void menu(){
    int op, op_salas, op_doce, op_reser;
    system("cls");
    molde("SISTEMA DE CADASTRO E RESERVA DE SALAS");

    printf("[1] - Datas ja reservadas\n");
    printf("[2] - Salas\n");
    printf("[3] - Docentes\n");
    printf("[4] - Reservas\n");
    printf("[5] - Relatorios\n");
    printf("[6] - Sair\n");
    scanf("%d", &op);

    switch(op){
    case 1:
        system("cls");
        calendar();
        break;
    case 2:
        system("cls");
        molde("MODULO DE SALAS");
        printf("[1] - Cadastrar\n");
        printf("[2] - Editar\n");
        printf("[3] - Excluir\n");
        printf("[4] - Lista de cadastros\n");
        printf("[5] - Voltar\n");
        scanf("%d", &op_salas);

        switch(op_salas){
        case 1:
            cadastrar(op);
        case 2:
            editarSala();
            break;
        case 3:
            excluirSala();
            break;
        case 4:
            consultaReser(op);
            break;
        case 5:
            menu();
            break;
        }
        break;

    case 3:
        system("cls");
        molde("MODULO DE DOCENTES");
        printf("[1] - Cadastrar\n");
        printf("[2] - Editar\n");
        printf("[3] - Excluir\n");
        printf("[4] - Lista de cadastros\n");
        printf("[5] - Voltar\n");
        scanf("%d", &op_doce);

        switch(op_doce){
        case 1:
            cadastrar(op);
            break;
        case 2:
            editarDocente();
            break;
        case 3:
            excluirDocente();
            break;
        case 4:
            consultaReser(op);
            break;
        case 5:
            menu();
            break;
        }
        break;

    case 4:
        system("cls");
        molde("MODULO DE RESERVAS");
        printf("[1] - Cadastrar\n");
        printf("[2] - Editar\n");
        printf("[3] - Excluir\n");
        printf("[4] - Lista de reservas\n");
        printf("[5] - Dias reservados\n");
        printf("[6] - Voltar\n");
        scanf("%d", &op_reser);

        switch(op_reser){
        case 1:
            reserva();
        case 2:
            printf("Falta implementar a funcao para editar!\n");
            system("pause && cls");
            menu();
            break;
        case 3:
            excluirReserva();
            break;
        case 4:
            consultaReser(op);
        case 5:
            menu();
        }
        break;

    case 5:
        system("cls");
        relatorio();
        break;

    case 6:
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
                case 2: ;
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
                case 3: ; // NÃO APAGUE O ; Ler observação 1 no final do arquivo
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

    if(op_res == 2){//caso a op_res seja 1 -> consulta de salas
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
            }else if(tipoSala.caraterSala == 2){
                printf("Comum\n");
            }else{
                printf("Desconhecido\n");
            }
        }
    }else if(op_res == 3){//caso a op_res seja 2 -> consulta de docentes
        Docentes docente;
        arq = fopen("db/dbDocente.bin", "rb");
        printf("Docentes cadastrados\n");
        printf("ID\tMatricula\tNome\n");
        while(fread(&docente, sizeof docente, 1, arq)){
            printf("%d\t%d\t\t%s\n", docente.id, docente.mat, docente.nome);
        }
    }else if(op_res == 4){//caso a op_res seja 3 -> consulta de reservas
        Reserva reserva;
        arq = fopen("db/dbReserva.bin", "rb");
        printf("Lista de reservas\n");
        while(fread(&reserva, sizeof(reserva), 1, arq)){
            printf("ID da Reserva %d\n", reserva.id);
            printf("Data da reserva: %d/%d/%d\n", reserva.data.dia, reserva.data.mes, reserva.data.ano);
            printf("Professor responsavel: %d\n", reserva.id_Docente);
            printf("Sala: %d\n\n", reserva.id_TipoSala);
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

    printf("%d - %d - %s\n", docente.id, docente.mat, docente.nome);

    system("pause");
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
    arq = fopen("db/dbDocente.bin", "r");

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
    molde("Relatorio gerado com sucesso!");
    FILE *arq, *arqR;
    arq = fopen("db/dbSala.bin", "r");
    arqR = fopen("Relatorio/relatorio.txt", "w");
    if(arq != NULL){
        TipoSala sala;
        fprintf(arqR, "SALAS CADASTRADAS\n");
        fprintf(arqR, "ID\tNUM/SALA\tTIPO\n");
        fprintf(arqR, "\n");
        while(fread(&sala, sizeof(sala), 1, arq)){
            fprintf(arqR, "%d\t",sala.id);
            fprintf(arqR,"%c%-6d\t",sala.bloco, sala.numSala);
            if(sala.caraterSala == 1){
                fprintf(arqR, "Laboratorio\n");
            }else if(sala.caraterSala == 2){
                fprintf(arqR, "Comum\n");
            }else{
                fprintf(arqR, "Desconhecido\n");
            }
        }


    }else {
        printf("Nao achou");
    }
    fclose(arq);
    fclose(arqR);

    arq = fopen("db/dbDocente.bin", "r");
    arqR = fopen("Relatorio/relatorio.txt", "a");
    if(arq != NULL){
            Docentes docente;
            fprintf(arqR, "DOCENTES CADASTRADOS\n");
            fprintf(arqR, "ID\tMatricula\tNome\n");
            while (fread(&docente, sizeof (docente), 1, arq)) {
                    fprintf(arqR, "%d\t%d\t\t%s\n", docente.id, docente.mat, docente.nome);
        }
    } else {
    printf("Nao achou");
}
    fclose(arq);
    fclose(arqR);

    arq = fopen("db/dbReserva.bin", "r");
    arqR = fopen("Relatorio/relatorio.txt", "a");
    if (arq != NULL) {
        Reserva reserva;
        fprintf(arqR, "RESERVAS REALIZADAS\n");
        fprintf(arqR, "ID\tData da reserva\tSala\tProfessor\n");
        while (fread(&reserva, sizeof(reserva), 1, arq)) {
                fprintf(arqR, "%d\t", reserva.id);
                fprintf(arqR, "%d/%d/%d\t", reserva.data.dia, reserva.data.mes, reserva.data.ano);
                fprintf(arqR, "%d\t", reserva.id_TipoSala);
                fprintf(arqR, "%s\t\n", select_docente(reserva.id_Docente));


        }
    }
    else {
        printf("Nao achou!");
    }
    fclose(arq);
    fclose(arqR);
    system("pause");
    menu();
}

void reserva(){
    TipoSala idSala;
    Docentes idProf;
    int flg = 0;
    system("cls");
    printf("\t\t--- Reserva de Sala ---\n");
    Reserva reserva;

    printf("Informe o dia: ");
    scanf("%d", &reserva.data.dia);

    printf("Informe o mes: ");
    scanf("%d", &reserva.data.mes);

    printf("Informe o ano: ");
    scanf("%d", &reserva.data.ano);

    printf("\nSala e responsavel\n");
    printf("Informe o id da sala: ");//funcao para encontrar o nome da sala
    scanf("%d", &reserva.id_TipoSala);

    printf("%d", reserva.id_TipoSala);

    FILE *arq;

    arq = fopen("db/dbSala.bin", "r");
    while(fread(&idSala, sizeof(idSala), 1, arq))
    {
        if(reserva.id_TipoSala == idSala.id){
            flg = 1;
            break;
        }
    }// AQUI ACABA O WHILE
    fclose(arq);

    if(flg == 1){
        flg = 0;
        printf("Informe o id do professor responsavel: ");//funcao para encontrar a mat do prof
        scanf("%d", &reserva.id_Docente);

        arq = fopen("db/dbDocente.bin", "r");
        while(fread(&idProf, sizeof(idProf), 1, arq)){
            if(reserva.id_Docente == idProf.id){
                flg = 1;
                break;
            }
        }

        if(flg == 1)
        {
            fclose(arq);
            reserva.id = getId_reserva();
            if(dbReserva(reserva)){
                printf("Reserva Cadastrada com sucesso!\n"); // Retorna 1 caso cadastro com success
            }
            system("pause");
            menu();
        }else{
            printf("O professor informado nao esta cadastrado\n");
            system("pause");
            menu();
        }
    }else{
        printf("A sala informada nao existe\n");
        system("pause");
        menu();
    }
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

char* entrada_char(char *texto){
    char *entrada = (char*) malloc(sizeof(char) * 50);
    printf("%s", texto);
    gets(entrada);
    return entrada;
}

void login(char *user, char *senha){
    char *TrueUser = "Luquinhas";
    char *TrueSenha = "22k";

    if(strcmp(user,TrueUser) == 0 && strcmp(senha,TrueSenha) == 0){
        menu();
    }else{
        backcolor(4);
        gotoxy(5,15);
        printf(" O usuario ou a senha estao incorretos. Tente novamente.\n");
        backcolor(0);
        gotoxy(8,16);
        system("pause && cls");
        logo();
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

void excluirReserva (){
    int id_reserva, flg=0;

    printf("Informe o id da reserva:");
    scanf("%d", &id_reserva);

    Reserva reserva;
    FILE *arq;
    FILE *arq_temp;

    arq = fopen("db/dbReserva.bin", "r");
    arq_temp = fopen ("db/tempReserva.bin", "w+");

    while (fread(&reserva, sizeof(reserva), 1, arq)  == 1) {
        if (reserva.id == id_reserva) {
            printf("Registro excluido com sucesso!\n");
            flg=1;
            system("pause");
            menu();
        }
        else {
            fwrite(&reserva, sizeof(reserva), 1, arq_temp);
        }
    }
    if (flg==0) {
        printf("Registro não localizado!\n");
        system("pause");
        menu();
    }
    fclose(arq);
    fclose(arq_temp);

    remove("db/dbReserva.bin");
    rename("db/tempReserva.bin", "db/dbReserva.bin");
}

void editarReserva(){
    int id_reserva, flg = 0;
    printf("Digite o id da reserva para edicao: ");
    scanf("%d", &id_reserva);

    Reserva reserva, editaReserva;
    FILE *arq, *arq_temp;
    arq = fopen("db/dbReserva.bin", "r");

    while(fread(&reserva, sizeof(reserva), 1, arq)){
        if(id_reserva == reserva.id){
            flg = 1;
        }
    }
    fclose(arq);

    if(flg){
        arq = fopen("db/dbReserva.bin", "r");
        arq_temp = fopen("db/tmpReserva.bin", "a");
        while(fread(&reserva, sizeof(reserva), 1, arq)){
            if(id_reserva != reserva.id){
                printf("Salvo %d\n", reserva.id);
                fwrite(&reserva, sizeof(reserva), 1, arq_temp);
            }
        }
        fclose(arq);
        fclose(arq_temp);

        editaReserva.id = id_reserva;

        printf("\t\t--- Editar Reserva de Sala ---\n");

        printf("Informe o dia: ");
        scanf("%d", &editaReserva.data.dia);

        printf("Informe o mes: ");
        scanf("%d", &editaReserva.data.mes);

        printf("Informe o ano: ");
        scanf("%d", &editaReserva.data.ano);

        printf("\nSala e responsavel\n");
        printf("Informe o id da sala: ");  //funcao para encontrar o nome da sala
        scanf("%d", &editaReserva.id_TipoSala);

        printf("Informe o id do professor responsavel: ");//funcao para encontrar a mat do prof
        scanf("%d", &editaReserva.id_Docente);

        arq_temp = fopen("db/tmpReserva.bin", "a");
        if(fwrite(&editaReserva, sizeof(editaReserva), 1, arq_temp)){
            printf("Reserva editada!\n");
        }else{

            printf("nao foi possible");
        }

        fclose(arq_temp);

        remove("db/dbReserva.bin");
        rename("db/tmpReserva.bin", "db/dbReserva.bin");

        system("pause");
        menu();

    }else{
        printf("O id nao foi encontrado\n");
    }
}

void calendar(){
    Reserva reserva;
    int flg = 0;
    FILE *arq;
    arq = fopen("db/dbReserva.bin", "r");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    while(fread(&reserva, sizeof(reserva), 1, arq)){
        if(reserva.data.ano >= tm.tm_year+1900 && reserva.data.mes >= tm.tm_mon+1 && reserva.data.dia >= tm.tm_mday){
                flg = 1;
                printf("id: %d \nSala: %d\nDocente: %s\n", reserva.id, reserva.id_TipoSala, select_docente(reserva.id_Docente));
                printf("Data da reserva: %d/%d/%d\n", reserva.data.dia, reserva.data.mes, reserva.data.ano);
                printf("\n");
        }
    }
    if(flg == 0){
        printf("Nao ha reservas!\n");
    }
    system("pause");
    menu();
}

char* select_docente(int id_docente){
    Docentes docente;
    FILE *arq;
    arq = fopen("db/dbDocente.bin", "r");

    while(fread(&docente, sizeof(docente), 1, arq)){
        if(docente.id == id_docente){
            break;
        }
    }

    fclose(arq);
    return docente.nome;
}

void logo(){
    backcolor(2);
    char letra[20], l = 219; //caracter da tabela ascii
    int logo[8][19];
    //8x19
    int i,j,k=20;

    strcpy(&logo[0],"0000000000000000000");
    strcpy(&logo[1],"0888800888880888800");
    strcpy(&logo[2],"0088000800000800080");
    strcpy(&logo[3],"0088000888800888880");
    strcpy(&logo[4],"0088000888800800080");
    strcpy(&logo[5],"0088000800000800080");
    strcpy(&logo[6],"0888800800000888800");
    strcpy(&logo[7],"0000000000000000000");

    printf("\n\n");
    for(i=0;i<8;i++){
        strcpy(&letra,logo[i]);
        gotoxy(k,i+3);
        for(j=0;j<19;j++){
            //printf("%c-",letra[j]);
            switch(letra[j]){
            case '0':
                backcolor(2);
                textcolor(2);
                printf("%c",l);
                break;
            case '8':
                backcolor(7);
                textcolor(7);
                printf("%c",l);
                break;
            }
        }
        backcolor(2);
        printf("\n");
    }

    gotoxy(k-10,i+3);
    textcolor(7);
    printf(" SISTEMA DE CADASTRO E RESERVA DE SALAS \n");
    backcolor(6);
    textcolor(7);
    gotoxy(k-5,i+4);
    printf("                               \n");
    gotoxy(15,12);
    char *user = entrada_char("Usuario: ");
    gotoxy(k-5,i+5);
    printf("                               \n");
    gotoxy(15,13);
    char *senha = entrada_char("Senha: ");

    backcolor(0);
    textcolor(7);

    login(user, senha);
}

void molde(char *str){
    int i, k = strlen(str) + 2;
    for(i=0;i<k;i++){
        if(i==0){
            printf("%c", 201);
        }else if(i==(k-1)){
            printf("%c",187);
        }else{
            printf("%c", 205);
        }
    }
    printf("\n%c%s%c\n", 186,str,186);

    for(i=0;i<k;i++){
        if(i==0){
            printf("%c", 200);
        }else if(i==(k-1)){
            printf("%c",188);
        }else{
            printf("%c", 205);
        }
    }
    printf("\n");
}
/** OBS 1:
This is a quirk of the C grammar. A label (Cleanup:) is not allowed to appear immediately before a declaration
(such as char *str ...;), only before a statement (printf(...);). In C89 this was no great difficulty because
declarations could only appear at the very beginning of a block, so you could always move the label down a bit and
avoid the issue. In C99 you can mix declarations and code, but you still can't put a label immediately before a declaration.
You can put a semicolon immediately after the label's colon to make there be an empty statement (https://goo.gl/6SwXRB)
**/
