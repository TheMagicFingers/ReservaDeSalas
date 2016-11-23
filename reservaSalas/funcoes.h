/** CABECALHO DAS FUNCOES IMPLEMENTADAS NO MODULO FUNCOES.c */

/*-----Structs------*/

typedef struct
{
   int id;
   int numSala;
   char bloco;
   int caraterSala;  // Lab e sala comum
}TipoSala;

typedef struct
{
   int id;
   int mat;
   char nome[100];
}Docentes;

typedef struct
{
   int id;
   int mat;
   int cpf;
   char nome[100];
}Tecnico;

typedef struct
{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct
{
    int id;
    int id_TipoSala;
    int id_Docente;
    Data data;
}Reserva;

/*-----Funções------*/

void menu();
/* Responsável pela função: Alan Pires
   A função "menu" imprime as opções do sistema
*/

void cadastrar(int op);
/* Responsável pela função: Lucas Vieira
   Entrada: Recebe a operação digitada pelo usuário e
   verifica qual o tipo de cadastro a ser realizado (salas/docentes)
   e solicita ao usuário as informações necessárias;
   Saída: chama o DB correspondente ao tipo do parâmetro passando
   a struct correspondente.
*/

int dbSala(TipoSala sala);
/* Responsável pela função: Gustavo Soares
   Entrada: recebe uma struct TipoSala com as informações
   digitadas pelo usuário;
   Saída: retorna 1 se o cadastro foi realizado com sucesso
   e 0 se não.
*/

int getId_tipoSala();
/*
    Responsavel pela função: Gustavo Soares
    Retorna o id da ultima sala cadastrada.
*/

int registro_duplicado_sala(int numSala, char bloco);
/*
    Responsavel pela função: Gustavo Soares
    Caso o número e o bloco da sala informado ja esteja no
    arquivo a funcao retorna 0 para informar
    a duplicidade da informação.
*/

void editarSala();
/*
    Responsavel pela função: Lucas Vieira
    Pede o id da sala para o usuário e verifica se ele existe; 
    caso exista, recebe as atulizações referentes aquela sala, se não existir,
    imprime que a sala informada não foi encontrada.
*/

void excluirSala();
/*
    Responsavel pela função: Alan Pires
    Pede o id da sala para o usuário e verifica se ele existe; 
    caso exista, exclui o registro do arquivo, se não existir,
    imprime que a sala informada não foi encontrada.
*/

int dbDocente(Docentes docente);
/* Responsável pela função: Gustavo Soares
   Entrada: recebe uma struct Docentes com as informações
   digitadas pelo usuário;
   Saída: retorna 1 se o cadastro foi realizado com sucesso
   e 0 se não.
*/

int getId_docente();
/*
    Responsavel pela função: Gustavo Soares
    Retorna o id do ultimo docente cadastrado.
*/

int registro_duplicado_docente(int matricula);
/*
    Responsavel pela função: Gustavo Soares
    Entrada: recebe uma matricula como parametro;
    Saída: retorna 0 se for duplicado e 1 se não.
*/

void editarDocente();
/*
    Responsavel pela função: Lucas Vieira
    Pede o id do docente para o usuário e verifica se ele existe; 
    caso exista, recebe as atulizações referentes aquele docente, se não existir,
    imprime que o docente informado não foi encontrado.
*/

void excluirDocente();
/*
    Responsavel pela função: Alan Pires
    Pede o id do docente para o usuário e verifica se ele existe; 
    caso exista, exclui o registro do arquivo, se não existir,
    imprime que o docente informado não foi encontrado.
*/

char* select_docente(int id_docente);
/*
    Responsavel pela função: Gustavo Soares
    Entrada: recebe o id de um docente;
    Saída: retorna o nome do docente equivalente ao parametro.
*/

int dbReserva(Reserva reserva);
/* Responsável pela função: Gustavo Soares
   Entrada: recebe uma struct Reserva com as informações
   digitadas pelo usuário;
   Saída: retorna 1 se o cadastro foi realizado com sucesso
   e 0 se não.
*/

int getId_reserva();
/*
    Responsavel pela função: Gustavo Soares
    retorna o id da ultima reserva.
*/

void excluirReserva ();
/*
    Responsavel pela função: Alan Pires
    Pede o id da reserva para o usuário e verifica se ele existe; 
    caso exista, exclui o registro do arquivo, se não existir,
    imprime que a reserva informada não foi encontrada.
*/

void editarReserva();
/*
    Responsavel pela função: Lucas Vieira
    Pede o id da reserva para o usuário e verifica se ele existe; 
    caso exista, recebe as atulizações referentes aquela reserva, se não existir,
    imprime que a resrva informada não foi encontrada.
*/

void reserva();
/* Responsável pela função: Lucas Vieira
   Coleta os dados necessários para a reserva de uma sala,
   verifica a integridade das data digitada para a reserva e a
   salva em um arquivo.
*/

void consulta(int op_res);
/* Responsável pela função: Gustavo Soares
   Entrada: recebe o operado digitado pelo usuário e
   verifica qual a sua correspondêecia (salas/docentes/reservas);
   Saída: imprime na tela a lista com todos os cadastros realizados
   de acordo com o operado digitado.
*/

int verificaMES(int mes, int dia);
/*  Responsável pela função: Lucas Vieira
    Entrada: dois int referente aos mes e dia digitado pelo usuario
    no momento da reserva;
    Saída: retorna um int de acordo com a integridade da data.
*/

int bissexto(int ano);
/*  Responsável pela função: Lucas Vieira
    Entrada: recebe um int referente ao ano digitado pelo usuario
    no momento da reserva;
    Saída: retorna 1 caso o ano seja bissexto e 0 caso contrario.
*/

void calendar();
/*
    Responsavel pela função: Lucas Vieira
    Imprime todas as reservas que estão registradas a partir
    da data atual.
*/

void relatorio();
/* Responsável pela função: Alan Pires
   Cria um arquivo de texto com as informações sobre
   as salas e docentes cadastrados e com as resrvas realizadas
*/

char* entrada_char(char *texto);
/*  Responsável pela função: Alan Pires
    Entrada: recebe uma string como parametro que será o comando 
    a se seguido pelo usuário e a imprime;
    Saída: retorna uma string com a informação referente ao parametro.
*/

void login(char *user, char *senha);
/* Responsável pela função: Lucas Vieira
   Entrada: Recebe dois char, user e senha;
   Saída: Chama a função menu se os parametros recebidos
   estiverem iguais aos cadastrados no sistema;se não, 
   permanece na tela de login.
*/

void logo();
/*
    Responsavel pela função: Gustavo Soares
    Imprime o logo do IFB e chama a função login.
*/

void molde(char *str);
/*
    Responsavel pela função: Gustavo Soares
    Entrada: recebe um texto;
    Saída: retorna o texto recebido em um molde.
*/
