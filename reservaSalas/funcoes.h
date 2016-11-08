/** Cabecalhos das funcoes implementadas no modulo funcoes.c */

typedef struct
{
   int id;
   int numSala;
   char bloco;
   int caraterSala;  // Lab, Anfiteatro, sala comum, audit�rio, etc
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

/* Respons�vel pela fun��o: Lucas Vieira
   Compara o CPF e senha do t�cnico, caso os dados estejam
   corretos o usu�rio � redirecionado para o menu, caso contr�rio
   ele � redirecionado para a tela inicial/login.
*/
int login(char cpf, char senha);

/* Respons�vel pela fun��o: Alan Pires
   A fun��o "menu" imprime as op��es do sistema
*/
void menu();

/* Respons�vel pela fun��o: Gustavo Soares
   Chama os "DBs" necess�rios para exibir
   detalhes sobre salas que foram reservadas
*/
void relatorio();

/* Respons�vel pela fun��o: Lucas Vieira
   Verifica o tipo de opera��o desejada
   (cadastro de salas/docentes) e solicita
   ao usu�rio as info. necess�rias e chama
   o DB correspondente ao tipo do par�metro.
*/
void cadastrar(int op);

/* Respons�vel pela fun��o: Gustavo Soares
   Cadastra uma sala armazenando-a em um arquivo
   txt
*/
int dbSala(TipoSala sala);

/* Respons�vel pela fun��o: Alan Pires
   Chama um arquivo txt que cont�m
   info sobre as datas e hor�rios em que
   as salas est�o cadastradas
*/
void consultaReser();

/* Respons�vel pela fun��o: Lucas Vieira
   A fun��o pede as info necess�rias para
   cadastrar uma reserva
*/
int reserva();
