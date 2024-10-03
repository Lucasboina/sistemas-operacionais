#include <pthread.h> //threads
#include <stdio.h>   // entrada e saída padrão
#include <stdlib.h>  //uso de ponteiros e alocação dinâmica
#include <unistd.h>  //acesso ao POSIX do Sistema Operacional

int mat[3][7];

void *countSum(void *tid)
{
    int somaLinha = 0;
    // deve fazer a soma da linha da matriz
    // esperar todas as treads finalizaresm soma
}

int main()
{
    pthread_t t1, t2, t3; // criando t1 e t2 do tipo thread
    int create;           // variável que recebe o retorno da função pthread_create()
    int i, j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 7; j++)
        {
            mat[i][j] = rand() % 10;
        }
    }

    printf("Main: criando a thread %ld\n", 1);
    create = pthread_create(&t1, NULL, countSum, (void *)1); // criando thread 1
    printf("Main: criando a thread %ld\n", 2);
    create = pthread_create(&t2, NULL, countSum, (void *)2); // criando thread 2
    printf("Main: criando a thread %ld\n", 3);
    create = pthread_create(&t2, NULL, countSum, (void *)3); // criando thread 3
    printf("Main: finalizando\n");
    return 0;
}