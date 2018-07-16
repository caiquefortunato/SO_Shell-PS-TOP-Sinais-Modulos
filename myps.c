#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // Biblioteca DIR

// Calcula a quantidade de termos presentes dentro da pasta proc
int numProc(int proc, int itensTask[])
{
	DIR *dp;
	struct dirent *ep;
	char path[50];
	sprintf(path, "/proc/%d/task/", proc);
	dp = opendir (path);
	int cont = 0, contProc = 0;
	int k = 0;

	if (dp != NULL)
	{
		while (ep = readdir (dp))
		{
		  if(k >= 2)
		  {
			  itensTask[contProc] = atoi(ep->d_name);
			  contProc++;
		  }

		  k++;
		}
		(void) closedir (dp);
	}
	else
		perror ("Couldn't open the directory");

	return contProc;
}

void limpa_vetor(int processos[]) {
    int i;
    for(i = 0; i < 1000; i++)
        processos[i] = 0;
}

int preenche_vetor(int proc, int processos[]) {
    char path[50];
	char string[100];
	int i, j = 0, cont = 0;
	char temp;
	FILE *arq;

    limpa_vetor(processos);

	sprintf(path, "/proc/%d/task/%d/children", proc, proc);
	arq = fopen(path, "r");

	if (arq != NULL)
	{
		limpa_vetor(processos);

		fscanf(arq, "%s", string);
		while(strcmp(string, "") != 0)
		{
			if(feof(arq)) break;
            processos[j] = atoi(string);
            cont++;

			fscanf(arq, "%c", &temp);
			fscanf(arq, "%s", string);
            j++;
		}
	}
	fclose(arq);
    return cont;
}

void imprimeNomeProcesso(int proc) {
    char path[50];
	char string[100];
	int i, j = 0;
	char temp;
	FILE *arq;

	sprintf(path, "/proc/%d/stat", proc);
	arq = fopen(path, "r");

	if (arq != NULL)
	{
		fscanf(arq, "%s", string);
		while(strcmp(string, "") != 0)
		{
            if(feof(arq)) break;

            if(j == 1)
            {
                printf("%s ", string);
                break;
            }

			fscanf(arq, "%c", &temp);
			fscanf(arq, "%s", string);
            j++;
		}
		printf("\n");
	}
	fclose(arq);

}

void imprime_Pstree(int i, int ntabs, int lidos[])
{
    int k = 0, j = 0, l, quantProc = 0;
    int procAtual, contTask = 0;
    int processos[1000];
    int itensTask[1000] = {0};

    // Imprime a quantidade de tabs
    for(k = 0; k < ntabs; k++)
        printf("\t");
        
    // Imprime o nome do processo
    imprimeNomeProcesso(i);

    contTask = numProc(i, itensTask);

    quantProc = preenche_vetor(i, processos);

    for(j = 0; j < quantProc; j++) {
        imprime_Pstree(processos[j], ntabs+1, lidos);
    }

    for(k = 0; k < contTask; k++){
    	if(itensTask[k] != i && lidos[i] == 0){
	    	imprime_Pstree(itensTask[k], ntabs, lidos);
	    }
		lidos[i] = 1;
    }

}

int main()
{
	int lidos[100000] = {0};

    imprime_Pstree(1, 0, lidos);

    return 0;
}
