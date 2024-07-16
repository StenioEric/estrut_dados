#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

// Função de ordenação Insertion Sort
void insertion_sort(int *v, unsigned int n) {
  int i, j, k;
  for (i = 1; i < n; i++) {
    k = v[i];
    j = i - 1;
    while (j >= 0 && v[j] > k) {
      v[j + 1] = v[j];
      j = j - 1;
    }
    v[j + 1] = k;
  }
}

// Função para gerar vetor invertido (decrescente)
void geraVetorInvertido(int *v, unsigned int n) {
  for (unsigned int i = 0; i < n; i++) {
    v[i] = n - 1 - i; // Valores ordenados de n-1 a 0
  }
}

int main() {
  int n, *v;
  struct timeval b, a;
  long long unsigned int ub, ua;

  srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

  // Abrir arquivo para escrita
  FILE *fp = fopen("insertionPior.txt", "w");
  if (fp == NULL) {
    fprintf(stderr, "Could not open file for writing\n");
    return 1;
  }

  // Executar o loop para diferentes valores de n
  for (n = 100; n <= 10000; n = n + 100) {
    v = (int *)malloc(n * sizeof(int));
    if (!v) {
      fprintf(stderr, "Memory allocation failed\n");
      fclose(fp);
      return 1;
    }

    // Gera vetor invertido
    geraVetorInvertido(v, n);

    // Medir o tempo de execução
    gettimeofday(&b, NULL); // Início da contagem do tempo
    insertion_sort(v, n);   // Chamar a função de ordenação insertion_sort
    gettimeofday(&a, NULL); // Fim da contagem do tempo

    ub = 1000000 * b.tv_sec + b.tv_usec; // Tempo inicial em microssegundos
    ua = 1000000 * a.tv_sec + a.tv_usec; // Tempo final em microssegundos

    fprintf(fp, "%d %lld\n", n, ua - ub); // Salvar no arquivo

    free(v); // Liberar a memória alocada para o array
  }

  fclose(fp); // Fechar o arquivo

  return 0;
}
