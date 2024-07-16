#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

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

  // Loop para diferentes tamanhos de array
  for (n = 100; n <= 10000; n = n + 10)
  {
    // Aloca memória para o array de tamanho n
    v = (int *)malloc(n * sizeof(int));
    // Preenche o array com valores decrescentes de n a 1
    for (i = 0; i < n; i++)
      v[i] = n - i;
    // Medir o tempo de execução
    gettimeofday(&b, NULL); // Início da contagem do tempo
    insertion_sort(v, n);   // Chama a função de ordenação insertion sort
    gettimeofday(&a, NULL); // Finaliza a contagem de tempo

    free(v); // Libera a memória alocada para o array

    // Calcula o tempo de execução em microssegundos
    ub = 1000000 * b.tv_sec + b.tv_usec;
    ua = 1000000 * a.tv_sec + a.tv_usec;

    // Imprime o tamanho do array e o tempo de execução
    printf("%d %lld\n", n, ua - ub);
  }
  return 0;
}