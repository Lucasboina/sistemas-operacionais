    #include <pthread.h> //threads
    #include <stdio.h>   // entrada e saída padrão
    #include <stdlib.h>  //uso de ponteiros e alocação dinâmica
    #include <unistd.h>  //acesso ao POSIX do Sistema Operacional
    #include <time.h>

    pthread_mutex_t mutexTravaSort;

    void *bubbleSort(int vetor[], int n) {
        int k, j, aux;
        for (k=1; k<n; k++) {
            for (j=0; j < n-1; j++) {
                if (vetor[j]>vetor[j+1]) {
                    aux = vetor[j];
                    vetor[j] = vetor[j+1];
                    vetor[j+1] = aux;
                }
            }
        
        }
    }
    void controlaBubleSort(void *tid){
        clock_t t; 
        long *vetor;
        vetor = (long *)tid;
        t = clock(); //armazena tempo}
        bubbleSort((int *)vetor,100);
        t = clock() - t; //tempo final - tempo inicial
        printf("Tempo de execucao: %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000))); //conversão para double
    }

    int main(){
        int i;
        srand(time(NULL));
        int a[100];
        int b[100];
        int c[100];
        int d[100];
        for (i=0;i<100;i++){
            a[i]= rand()%100;
            d[i] = b[i] = c[i] = a[i];
        }
        pthread_t t1, t2,t3,t4; // criando t1 e t2 do tipo thread

        printf("Main: criando a thread %d\n", 1);
        pthread_create(&t1, NULL, controlaBubleSort, (void *)a); // criando thread 1
        printf("Main: criando a thread %d\n", 2);
        pthread_create(&t2, NULL, controlaBubleSort, (void *)b); // criando thread 2
        printf("Main: criando a thread %d\n", 3);
        pthread_create(&t3, NULL, controlaBubleSort, (void *)c); // criando thread 3
        printf("Main: criando a thread %d\n", 4);
        pthread_create(&t4, NULL, controlaBubleSort, (void *)d); // criando thread 4

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        pthread_join(t3, NULL);
        pthread_join(t4, NULL);

        printf("Main: finalizando\n");


        return 0;
    }