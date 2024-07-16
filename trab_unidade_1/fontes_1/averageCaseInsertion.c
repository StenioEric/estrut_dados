#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(int *v, unsigned int n)
{
  int i, j, k;
  for (i = 1; i < n; i++)
  {
    k = v[i];
    j = i - 1;
    while (j > 0 && v[j] > k)
    {
      v[j + 1] = v[j];
      j = j - 1;
    }

    v[j + 1] = k;
  }
} // Gabriel Ygor Canuto

int main()
{
  int n, *v;
  int i;
  struct timeval b, a;
  long long unsigned int ub, ua;

  // Executar o loop para diferentes valores de n
  for (n = 100; n <= 10000; n = n + 10)
  {
    v = (int *)malloc(n * sizeof(int));
    // Preencher o array com valores aleatórios
    srand(time(NULL));
    for (i = 0; i < n; i++)
      v[i] = 1 + rand() % n;
    // Medir o tempo de execução
    gettimeofday(&b, NULL); // Início da contagem do tempo
    insertion_sort(v, n);   // Chamar a função de ordenação
    gettimeofday(&a, NULL); // Fim da contagem do tempo

    free(v); // Liberar a memória alocada para o array

    ub = 1000000 * b.tv_sec + b.tv_usec; // Tempo inicial em microssegundos
    ua = 1000000 * a.tv_sec + a.tv_usec; // Tempo final em microssegundos

    printf("%d %lld\n", n, ua - ub); // Imprimir o tamanho do array e o tempo de execução
  }
  return 0;
}