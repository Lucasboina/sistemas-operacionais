#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUMCONS 1       // define o numero de consumidores
#define NUMPROD 2       // define o numero de produtores
#define BUFFERSIZE 1000 // define o tamnaho do buffer do sistema

pthread_t cons[NUMCONS];      // Instancia treads de consumo
pthread_t prod[NUMPROD];      // Instancia treads de produção
pthread_mutex_t buffer_mutex; // Intancia o mutex

int buffer[BUFFERSIZE]; // instancia buffer
int currentidx;
sem_t buffer_full, buffer_empty; // Semafaro

void *produtor(void *arg)
{
    int n;
    while (1)
    {
        n = rand() % 1000;                   // cria valor aleatóeio
        sem_wait(&buffer_full);              // espera o buffer está cheio
        pthread_mutex_lock(&buffer_mutex);   // trava tread
        buffer[currentidx++] = n;            // instancia valor no buffer com id do tread
        pthread_mutex_unlock(&buffer_mutex); // destrava tread
        sem_post(&buffer_empty);             // libera semafaro
        printf("Produzindo numero %d\n", n);
        sleep((1 + rand() % 5)); // espera
    }
}

void *consumidor(void *arg)
{
    int n;
    while (1)
    {
        sem_wait(&buffer_empty);             // espera o buffer o retono do buffer vazio
        pthread_mutex_lock(&buffer_mutex);   // trava o tread
        n = buffer[--currentidx];            // peg ao valor do buffer com o id do tread
        pthread_mutex_unlock(&buffer_mutex); // destrava tread
        sem_post(&buffer_full);              // libera semafaro
        printf("Consumindo numero %d\n", n);
        sleep(1 + (rand() % 5)); // espera
    }
}
int main(int argc, char **argv)
{
    int i;
    pthread_mutex_init(&buffer_mutex, NULL); // inicializa o mutex
    sem_init(&buffer_full, 0, BUFFERSIZE);   // inicia o semafaro
    sem_init(&buffer_empty, 0, 0);
    for (i = 0; i < NUMCONS; i++)
        pthread_create(&(cons[i]), NULL, consumidor, NULL); // cria tread de consumo
    for (i = 0; i < NUMPROD; i++)
        pthread_create(&(prod[i]), NULL, produtor, NULL); // cria tread de produção
    for (i = 0; i < NUMCONS; i++)
        pthread_join(cons[i], NULL); // espera todas as treads de consumo chegar para finalizar
    for (i = 0; i < NUMPROD; i++)
        pthread_join(prod[i], NULL); // espera todas as treads de produção chegar para finalizar
}