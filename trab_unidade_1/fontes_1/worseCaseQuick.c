#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

void quickSort(int *v, int inicio, int fim);
// Função auxiliar para particionar o array durante o Quicksort
int partition(int *v, int inicio, int fim);


void quickSort(int *v, int inicio, int fim) {
  // Verifica se o fim é maior que o início, indicando que há elementos para ordenar
    if (fim > inicio ) {
        // Realiza o particionamento do array e obtém a posição final do pivô
        int p = partition(v, inicio, fim);
        // Chama recursivamente o Quicksort para ordenar os subarrays à esquerda e à direita do pivô
        quickSort(v, inicio, p - 1);
        quickSort(v, p + 1, fim);
    }
}

int partition(int *v, int inicio, int fim) {
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = fim;
    pivo = v[inicio]; // Seleciona o primeiro elemento como pivô
    while(esq < dir){
      while(v[esq] <= pivo) // Encontra um elemento à esquerda do pivô maior que ele
        esq++;
      while(v[dir] > pivo) // Encontra um elemento à direita do pivô menor ou igual a ele
        dir--;
      if(esq < dir){ // Troca os elementos encontrados
        aux = v[esq];
        v[esq] = v[dir];
        v[dir] = v[aux];
      }
    }
  // Coloca o pivô em sua posição final
  v[inicio] = v[dir];
  v[dir] = pivo;
  // Retorna a posição final do pivô
  return dir;
}


int main() {
  int n, *v;
  int i;
  struct timeval b, a;
  long long unsigned int ub, ua;
  

  for(n = 100; n <= 10000; n = n + 10){
    v = (int *) malloc(n * sizeof(int));
    for(i = 0; i < n; i++)
      v[i] = i;
    
    gettimeofday(&b, NULL); // Início da contagem do tempo
    quickSort(v,0,n-1); // Chama a função quickSort para ordenar o array
    gettimeofday(&a, NULL); // Finaliza a contagem de tempo

    free(v); // Libera a memória alocada para o array
  
    ub = 1000000 * b.tv_sec + b.tv_usec; // Tempo inicial em microssegundos
    ua = 1000000 * a.tv_sec + a.tv_usec; // Tempo final em microssegundos

    // Imprime o tamanho do array e o tempo de execução
    printf("%d %lld\n", n, ua - ub); 
  }
  return 0;
}