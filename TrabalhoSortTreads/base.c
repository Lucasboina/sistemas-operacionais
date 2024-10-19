#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void bubbleSort(int vetor[], int n) {
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
int main(){
    clock_t t; 
    int i;
    srand(time(NULL));
    int v[100];
    for (i=0;i<100;i++){
        v[i]= rand()%100;
    }
    t = clock(); //armazena tempo
    bubbleSort(v,100);
    t = clock() - t; //tempo final - tempo inicial
    printf("Tempo de execucao: %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000))); //conversão para double

    for (i=0;i<100;i++){
        printf("%d ", v[i]);
    }
    return 0;
}