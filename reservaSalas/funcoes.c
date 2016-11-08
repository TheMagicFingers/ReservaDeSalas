/** Arquivo onde serão inseridas as funções */

void menu(){
    int op, op_cad;

    printf("\t\tInforme a opcao desejada\n");
    printf("[1] - Realizar um novo cadastro.\n");
    printf("[2] - Realizar uma consulta ao sistema.\n");
    printf("[3] - Reservar uma sala.\n");
    printf("[4] - Elaborar um relatorio.\n");

    scanf("%d", &op);

    switch(op){
    case 1:
        system("cls");
        printf("Cadastros\n");
        printf("[1] - Realizar Cadastro de Sala.\n");
        printf("[2] - Realizar Cadastro de Docente.\n");
        scanf("%d", &op_cad);
        cadastrar(op_cad);
        break;
    case 2:
        consultaReser();
        break;
    case 3:
        reserva();
        break;
    case 4:
        relatorio();
        break;
    default:
        printf("Opcao Invalida!\n");
    }
}


void cadastrar(int op){
    printf("Operacao desejada: %d\n", op);
}

void consultaReser(){

}

void relatorio(){
}

int reserva(){
    return 0;
}
int entrada_num(char texto[50]) {
    int numEntrada;
    printf("\nDigite %s", texto);
    scanf("%d", &numEntrada);
    return numEntrada;
}

