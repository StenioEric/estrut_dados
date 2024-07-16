#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

void quickSort(int *v, int inicio, int fim);
int partition(int *v, int inicio, int fim);

void quickSort(int *v, int inicio, int fim)
{
  if (fim > inicio)
  {
    int p = partition(v, inicio, fim);
    quickSort(v, inicio, p - 1);
    quickSort(v, p + 1, fim);
  }
}

int partition(int *v, int inicio, int fim)
{
  int esq, dir, pivo, aux;
  esq = inicio;
  dir = fim;
  pivo = v[inicio];
  while (esq < dir)
  {
    while (esq < fim && v[esq] <= pivo)
      esq++;
    while (dir > inicio && v[dir] > pivo)
      dir--;
    if (esq < dir)
    {
      aux = v[esq];
      v[esq] = v[dir];
      v[dir] = aux;
    }
  }
  v[inicio] = v[dir];
  v[dir] = pivo;
  return dir;
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
    srand(time(NULL));
    for (i = 0; i < n; i++)
      v[i] = 1 + rand() % n;
    // Medir o tempo de execução
    gettimeofday(&b, NULL); // Início da contagem do tempo
    quickSort(v, 0, n - 1); // Chamar a função de ordenação quickSort
    gettimeofday(&a, NULL); // Fim da contagem do tempo

    free(v); // Liberar a memória alocada para o array

    ub = 1000000 * b.tv_sec + b.tv_usec; // Tempo inicial em microssegundos
    ua = 1000000 * a.tv_sec + a.tv_usec; // Tempo final em microssegundos

    printf("%d %lld\n", n, ua - ub); // Imprimir o tamanho do array e o tempo de execução
  }
  return 0;
}