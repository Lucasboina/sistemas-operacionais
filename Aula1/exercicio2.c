#include <pthread.h> //threads
#include <stdio.h>   // entrada e saída padrão
#include <stdlib.h>  //uso de ponteiros e alocação dinâmica
#include <unistd.h>  //acesso ao POSIX do Sistema Operacional

long mat[3][7];
int somaTotal = 0;
pthread_mutex_t mutexsum;

void *countSum(void *tid)
{
    long *linha;
    linha = (long *)tid;
    int somaLinha = 0;
    int i;
    for (i = 0; i < 7; i++)
    {
        somaLinha += linha[i];
    }
    pthread_mutex_lock(&mutexsum);
    somaTotal += somaLinha;
    pthread_mutex_unlock(&mutexsum);

    pthread_exit(NULL);
}

int main()
{
    pthread_t t1, t2, t3; // criando t1 e t2 do tipo thread
    int i, j;
    srand(time(NULL));
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 7; j++)
        {
            mat[i][j] = rand() % 10;
        }
    }

    printf("Main: criando a thread %d\n", 1);
    pthread_create(&t1, NULL, countSum, (void *)mat[0]); // criando thread 1
    printf("Main: criando a thread %d\n", 2);
    pthread_create(&t2, NULL, countSum, (void *)mat[1]); // criando thread 2
    printf("Main: criando a thread %d\n", 3);
    pthread_create(&t3, NULL, countSum, (void *)mat[2]); // criando thread 3
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Main: finalizando\n");
    printf("%d", somaTotal);
    pthread_mutex_destroy(&mutexsum);
    return 0;
}