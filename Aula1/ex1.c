#include <pthread.h> //threads
#include <stdio.h>   // entrada e saída padrão
#include <stdlib.h>  //uso de ponteiros e alocação dinâmica
#include <unistd.h>  //acesso ao POSIX do Sistema Operacional
void *PrintHello(void *threadid)
{ // função a ser executada quando uma thread for
    criada long id;
    id = (long)threadid; // conversão de void pra long
    printf("Thread %ld: Olá mundo!\n", id);
    pthread_exit(NULL); // finalização da thread
}
int main()
{
    pthread_t t1, t2; // criando t1 e t2 do tipo thread
    int create;       // variável que recebe o retorno da função pthread_create()
    long num;         // identificador da thread
    num = 1;
    printf("Main: criando a thread %ld\n", num);
    create = pthread_create(&t1, NULL, PrintHello, (void *)num); // criando thread 1
    num = 2;
    printf("Main: criando a thread %ld\n", num);
    create = pthread_create(&t2, NULL, PrintHello, (void *)num); // criando thread 2
    printf("Main: finalizando\n");
    return 0;
}