#include <pthread.h> //threads
#include <stdio.h>   // entrada e saída padrão
#include <stdlib.h>  //uso de ponteiros e alocação dinâmica
#include <unistd.h>  //acesso ao POSIX do Sistema Operacional

pthread_mutex_t mutexdiferencia;
int num[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void *diferencia(void *tid)
{
    long diferenciador = (long)tid;
    pthread_mutex_lock(&mutexdiferencia);
    for (int i = 0; i < 10; i++)
    {
        if (num[i] % 2 == diferenciador)
        {
            printf("Tread %ld : %d\n", diferenciador + 1, num[i]);
        }
    }
    pthread_mutex_unlock(&mutexdiferencia);

    pthread_exit(NULL);
}

int main()
{
    pthread_t t1, t2; // criando t1 e t2 do tipo thread
    long diferenciador = 0;
    printf("Main: criando a thread %d\n", 1);
    pthread_create(&t1, NULL, diferencia, (void *)diferenciador); // criando thread 1
    printf("Main: criando a thread %d\n", 2);
    diferenciador = 1;
    pthread_create(&t2, NULL, diferencia, (void *)diferenciador); // criando thread 2
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main: finalizando\n");

    pthread_mutex_destroy(&mutexdiferencia);
    return 0;
}