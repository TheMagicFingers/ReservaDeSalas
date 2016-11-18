/** Cabecalhos das funcoes implementadas no modulo funcoes.c */

typedef struct
{
   int id;
   int numSala;
   char bloco;
   int caraterSala;  // Lab, Anfiteatro, sala comum, auditório, etc
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

/* Responsável pela função: Lucas Vieira
   Compara o CPF e senha do técnico, caso os dados estejam
   corretos o usuário é redirecionado para o menu, caso contrário
   ele é redirecionado para a tela inicial/login.
*/
void login(char *user, char *senha);

/* Responsável pela função: Alan Pires
   A função "menu" imprime as opções do sistema
*/
void menu();

/* Responsável pela função: Gustavo Soares
   Chama os "DBs" necessários para exibir
   detalhes sobre salas que foram reservadas
*/
void relatorio();

/* Responsável pela função: Lucas Vieira
   Verifica o tipo de operação desejada
   (cadastro de salas/docentes) e solicita
   ao usuário as info. necessárias e chama
   o DB correspondente ao tipo do parâmetro.
*/
void cadastrar(int op);

/* Responsável pela função: Gustavo Soares
   Cadastra uma sala armazenando-a em um arquivo
   txt
*/
int dbSala(TipoSala sala);

/* Responsável pela função: Gustavo Soares
   Cadastra um docente armazenando-o em um arquivo
   dat
*/
int dbDocente(Docentes docente);

/* Responsável pela função: Gustavo Soares
   Cadastra uma reserva armazenando-a em um arquivo
   dat
*/
int dbReserva(Reserva reserva);

/* Responsável pela função: Alan Pires
   Chama um arquivo txt que contém
   info sobre as datas e horários em que
   as salas estão cadastradas
*/

void consultaReser(int op_res);

/* Responsável pela função: Lucas Vieira
   A função pede as info necessárias para
   cadastrar uma reserva
*/
void reserva();

/*  Responsável pela função: Alan Pires
    A função recebe um texto como parâmetro
    e pede ao usuário que digite algo referente
    ao texto que foi recebido pela função
*/
char* entrada_char(char *texto);

/*
    Responsavel pela função: Gustavo Soares
    Caso o número e o bloco da sala informado ja esteja no
    arquivo texto a funcao retorna 0 para informar
    a duplicidade da informação
*/
int registro_duplicado_sala(int numSala, char bloco);

/*
    Responsavel pela função: Gustavo Soares
    retorna o id da ultima sala cadastrada
*/
int getId_tipoSala();

/*
    Responsavel pela função: Gustavo Soares
    retorna o id da ultima reserva
*/
int getId_reserva();

/*
    Responsavel pela função: Gustavo Soares
    Caso a matricula informada ja esteja no
    arquivo texto a funcao retorna 0 para informar
    a duplicidade da informação
*/
int registro_duplicado_docente(int matricula);

/*
    Responsavel pela função: Gustavo Soares
    retorna o id do ultimo docente cadastrado
*/
int getId_docente();

void editarSala();

void excluirSala();

void editarDocente();

void excluirDocente();

void editarReserva();

void menu2();

/*Recebe um id de reserva, verifica se ele 
  existe e o exluir
*/
void excluirReserva ();

void calendar();
