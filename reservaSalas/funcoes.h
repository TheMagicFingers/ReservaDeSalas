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
   int id;
   int id_TipoSala;
   int id_Docente;
   char data[10];
   char horaEntrada[5];
   char horaSaida[5];
   int reserProjetor;
}Reserva;

/* Responsável pela função: Lucas Vieira
   Compara o CPF e senha do técnico, caso os dados estejam
   corretos o usuário é redirecionado para o menu, caso contrário
   ele é redirecionado para a tela inicial/login.
*/
int login(char cpf, char senha);

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

/* Responsável pela função: Alan Pires
   Chama um arquivo txt que contém
   info sobre as datas e horários em que
   as salas estão cadastradas
*/
void consultaReser();

/* Responsável pela função: Lucas Vieira
   A função pede as info necessárias para
   cadastrar uma reserva
*/
int reserva();
