#include <dirent.h> // Biblioteca DIR
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h> // Sleep
#include <time.h>
#include <signal.h>  //kill

// ---------- Parte 4 ---------- //
int enviar_sinal (int pid, int sinal) {
        int processo;
        if(sinal == 1) {
            processo = kill(pid,SIGHUP);
            printf("processo : %d\n",processo);
        }
        else if (sinal == 2) {
            processo = kill(pid,SIGINT);
            printf("processo : %d\n",processo);
        }
        else if (sinal == 15) {
            processo = kill(pid,SIGTERM);
            printf("processo : %d\n",processo);
        }
        else if (sinal == 9) {
            processo = kill(pid,SIGKILL);
            printf("processo : %d\n",processo);
        }
        else if (sinal == 20) {
            processo = kill(pid,SIGTSTP);
            printf("processo : %d\n",processo);
        }
        else {
            printf("Sinal invalido\n");
        }
}

// ---------- Parte 3 ---------- //
// Imprime o cacecalho do top
void imprimeCabecalho( ) {
  printf("PID    | USER       | PROCNAME             | Estado |\n");
  printf("-------|------------|----------------------|--------|\n");
}

int imprimeAutorProc(int idProc) {
  struct stat sb;
  char file[200];
  sprintf(file, "/proc/%d/stat", idProc);

  stat(file, &sb);
  struct passwd *pw = getpwuid(sb.st_uid);

  printf(" %s", pw->pw_name);

  return strlen(pw->pw_name);

}

// Manipula arquivos da pasta PROC
void leProcessos(int cont)
{
  char path[50];
	char string[100];
	int i, j = 0;
    int idProc, tamString, quantEspaco;
	char temp;
	FILE *arq;

  struct timespec t = {1/*seconds*/, 0/*nanoseconds*/};
  while(1)
  {

    imprimeCabecalho();

    cont = 20;

    for(i = 1; i <= cont; i++)
    {
      sprintf(path, "/proc/%d/stat", i);
      arq = fopen(path, "r");

      if (arq == NULL)
        cont += 1;

      if (arq != NULL)
      {
        fscanf(arq, "%s", string);
        while(strcmp(string, "") != 0)
        {
          if(feof(arq)) break;
          if(j == 0)
          {
            printf("%s", string); // Le o PID
            tamString = strlen(string);
            quantEspaco = 7 - tamString;
            for(int k = 0; k < quantEspaco; k++)
              printf(" ");
            printf("|");
            j++;

            // Uma vez que o PID eh lido, precisamos ler o user
            idProc = atoi(string);
            tamString = imprimeAutorProc(idProc);
            quantEspaco = 11 - tamString;
            for(int k = 0; k < quantEspaco; k++)
              printf(" ");
            printf("| ");
          }
          else if(j == 1)
          {
            printf(" %s", string); // Le o Proc_Name
            j++;

            idProc = atoi(string);
            tamString = strlen(string);
            quantEspaco = 20 - tamString;
            for(int k = 0; k < quantEspaco; k++)
              printf(" ");
            printf("| ");
          }
          else if(j == 2)
          {
            printf(" %s", string); // Le o Estado
            j++;

            idProc = atoi(string);
            tamString = strlen(string);
            quantEspaco = 6 - tamString;
            for(int k = 0; k < quantEspaco; k++)
              printf(" ");
            printf("|");
          }
          else
          {
            j = 0;
            break;
          }
          fscanf(arq, "%c", &temp);
          fscanf(arq, "%s", string);
        }
        printf("\n");
      }
    }
    nanosleep(&t,NULL);
    fflush(stdout); //see below
    system("clear");
  }

}

// Manipula arquivos da pasta PROC
void leProcessosMandaSinais(int cont)
{
  char path[50];
	char string[100];
	int i, j = 0;
    int idProc, tamString, quantEspaco;
	char temp;
	FILE *arq;

    imprimeCabecalho();
    // zera a variavel cont
    cont = 20;

    for(i = 1; i <= cont; i++)
    {
      sprintf(path, "/proc/%d/stat", i);
      arq = fopen(path, "r");

      if (arq == NULL)
        cont += 1;

      if (arq != NULL)
      {
        fscanf(arq, "%s", string);

        while(strcmp(string, "") != 0)
        {
          if(feof(arq)) break;
          if(j == 0)
          {
            printf("%s", string); // Le o PID
            tamString = strlen(string);
            quantEspaco = 7 - tamString;
            for(int k = 0; k < quantEspaco; k++)
              printf(" ");
            printf("|");
            j++;

            // Uma vez que o PID eh lido, precisamos ler o user
            idProc = atoi(string);
            tamString = imprimeAutorProc(idProc);
            quantEspaco = 11 - tamString;
            for(int k = 0; k < quantEspaco; k++)
              printf(" ");
            printf("| ");
          }
          else if(j == 1)
          {
            printf(" %s", string); // Le o Proc_Name
            j++;

            idProc = atoi(string);
            tamString = strlen(string);
            quantEspaco = 20 - tamString;
            for(int k = 0; k < quantEspaco; k++)
              printf(" ");
            printf("| ");
          }
          else if(j == 2)
          {
            printf(" %s", string); // Le o Estado
            j++;

            idProc = atoi(string);
            tamString = strlen(string);
            quantEspaco = 6 - tamString;
            for(int k = 0; k < quantEspaco; k++)
              printf(" ");
            printf("|");
          }
          else
          {
            j = 0;
            break;
          }
          fscanf(arq, "%c", &temp);
          fscanf(arq, "%s", string);
        }
        printf("\n");
      }
    }
}

int main(void)
{
    int opcao, pid_sinal, sinal;
    system("clear");
    printf("--------------------HTOP--------------------\n\n");
    printf("Digite: \n");
    printf("(1) para ver o HTOP atualizando constantemente. \n");
    printf("(2) para ver o HTOP e mandar sinais\n\n");

    do {
        scanf("%d", &opcao);
        if(opcao != 1 || opcao != 2)
            printf("Valor incorreto, digite novamente\n");
        if(opcao == 1 || opcao == 2)
            break;

    } while (1);

    printf("Valor digitado: %d\n", opcao);
    system("clear");

    if(opcao == 1) leProcessos(20);
    if(opcao == 2)
    {
        leProcessosMandaSinais(20);

        printf("\nEntre com o ID do processo e o sinal\n");
        scanf("%d %d", &pid_sinal, &sinal);
        enviar_sinal(pid_sinal, sinal);
        printf("\nFim de execucao\n");
    }

	return(0);
}
