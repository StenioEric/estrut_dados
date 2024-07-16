#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

void quickSort(int *v, int inicio, int fim);
// Função auxiliar para particionar o array durante o quicksort
int partition(int *v, int inicio, int fim);


void quickSort(int *v, int inicio, int fim) {
    if (fim > inicio ) {
      // Encontra o índice do pivô usando a função partition
        int p = partition(v, inicio, fim);
        // Chama recursivamente o quicksort para os subarrays à esquerda e à direita do pivô
        quickSort(v, inicio, p - 1);
        quickSort(v, p + 1, fim);
    }
}

int partition(int *v, int inicio, int fim) {
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = fim;
    pivo = v[inicio];
    while(esq < dir){ // Encontra o primeiro elemento à direita do pivô que é menor que ele
      while(v[esq] <= pivo)    
        esq++;
      while(v[dir] > pivo) // Encontra o primeiro elemento à esquerda do pivô que é maior que ele    
        dir--;
      if(esq < dir){ // Troca os elementos encontrados acima, se esq < dir
        aux = v[esq];
        v[esq] = v[dir];
        v[dir] = aux;
      }
    }
  // Coloca o pivô em sua posição correta no array ordenado
  v[inicio] = v[dir];
  v[dir] = pivo;
  // Retorna o índice do pivô
  return (inicio + fim)/2;
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
    // Medir o tempo de execução
    gettimeofday(&b, NULL); // Início da contagem do tempo
    quickSort(v,0,n-1); // Chamar a função de ordenação quicksort
    gettimeofday(&a, NULL); // Fim da contagem do tempo

    free(v); // Liberar a memória alocada para o array
    

    // Calcula o tempo de execução em microssegundos
    ub = 1000000 * b.tv_sec + b.tv_usec;
    ua = 1000000 * a.tv_sec + a.tv_usec;
  
    // Imprime o tamanho do array e o tempo de execução
    printf("%d %lld\n", n, ua - ub);
  }
  return 0;
}