#include <pthread.h> //threads
#include <stdio.h>   // entrada e saída padrão
#include <stdlib.h>  //uso de ponteiros e alocação dinâmica
#include <unistd.h>  //acesso ao POSIX do Sistema Operacional
#include <time.h>


pthread_barrier_t barreiraTreads;

void bubbleSort(int vetor[], int n)
{
    int k, j, aux;
    for (k = 1; k < n; k++)
    {
        for (j = 0; j < n - 1; j++)
        {
            if (vetor[j] > vetor[j + 1])
            {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
        }
        int temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}
void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

void controlaBubbleSort(void *tid)
{
    clock_t t;
    long *vetor;
    vetor = (long *)tid;
    pthread_barrier_wait(&barreiraTreads);
    t = clock(); // armazena tempo}
    bubbleSort((int *)vetor, 1000);
    t = clock() - t;                                                                        // tempo final - tempo inicial
    printf("Tempo de execucao bubbleSort: %lf\n", ((double)t) / ((CLOCKS_PER_SEC))); // conversão para double
}
void controlaSelectionSort(void *tid)
{
    clock_t t;
    long *vetor;
    vetor = (long *)tid;
    pthread_barrier_wait(&barreiraTreads);
    t = clock(); // armazena tempo}
    selectionSort((int *)vetor, 1000);
    t = clock() - t;                                                                           // tempo final - tempo inicial
    printf("Tempo de execucao SelectionSort: %lf\n", ((double)t) / ((CLOCKS_PER_SEC))); // conversão para double
}
void controlaInsertionSort(void *tid)
{
    clock_t t;
    long *vetor;
    vetor = (long *)tid;
    pthread_barrier_wait(&barreiraTreads);
    t = clock(); // armazena tempo}
    insertionSort((int *)vetor, 1000);
    t = clock() - t;                                                                           // tempo final - tempo inicial
    printf("Tempo de execucao InsertionSort: %lf\n", ((double)t) / ((CLOCKS_PER_SEC))); // conversão para double
}
void controlaHeapSort(void *tid)
{
    clock_t t;
    long *vetor;
    vetor = (long *)tid;
    pthread_barrier_wait(&barreiraTreads);
    t = clock(); // armazena tempo}
    heapSort((int *)vetor, 1000);
    t = clock() - t;                                                                      // tempo final - tempo inicial
    printf("Tempo de execucao HeapSort: %lf\n", ((double)t) / ((CLOCKS_PER_SEC))); // conversão para double
}

int main()
{
    int i;
    srand(time(NULL));
    int a[1000];
    int b[1000];
    int c[1000];
    int d[1000];
    for (i = 0; i < 1000; i++)
    {
        a[i] = rand() % 100;
        d[i] = b[i] = c[i] = a[i];
    }
    pthread_t t1, t2, t3, t4;
    pthread_barrier_init(&barreiraTreads,NULL, 4);
    pthread_create(&t1, NULL, controlaBubbleSort, (void *)a);    // criando thread 1
    pthread_create(&t2, NULL, controlaSelectionSort, (void *)b); // scriando thread 2
    pthread_create(&t3, NULL, controlaInsertionSort, (void *)c); // criando thread 3
    pthread_create(&t4, NULL, controlaHeapSort, (void *)d);      // criando thread 4
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_barrier_destroy(&barreiraTreads);

    printf("Main: finalizando\n");
    return 0;
}