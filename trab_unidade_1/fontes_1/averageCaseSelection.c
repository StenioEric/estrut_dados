#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

void selection_sort(int num[], int tam)
{
  int i, j, min, aux;
  for (i = 0; i < (tam - 1); i++)
  {
    min = i;
    for (j = (i + 1); j < tam; j++)
    {
      if (num[j] < num[min])
        min = j;
    }
    if (i != min)
    {
      aux = num[i];
      num[i] = num[min];
      num[min] = aux;
    }
  }
} //Gabriel Ygor Canuto

int main()
{
  int valores = 100;       // Valor inicial
  int incremento = 10;     // Incremento
  int max_valores = 10000; // Valor máximo
  int num[max_valores];    // Array para armazenar os valores

  FILE *arquivo = fopen("averageSelection.txt", "w"); // Abrir o arquivo para gravação

  while (valores <= max_valores)
  {
    // Preencher o array com valores de 1 até "valores"
    for (int i = 0; i < valores; i++)
    {
      num[i] = i + 1;
    }

    // Embaralhar os valores do array
    for (int i = 0; i < valores - 1; i++)
    {
      int j = i + rand() % (valores - i);
      int temp = num[i];
      num[i] = num[j];
      num[j] = temp;
    }

    // Calcular o tempo de execução
    struct timeval start, end;
    gettimeofday(&start, NULL);   // Início da contagem do tempo
    selection_sort(num, valores); // Chamar a função de ordenação
    gettimeofday(&end, NULL);     // Fim da contagem do tempo

    // Calcular o tempo de execução em microssegundos
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    long elapsed = seconds * 1000000 + microseconds;

    // Gravar o tempo de execução no arquivo
    fprintf(arquivo, "%d %ld\n", valores, elapsed);

    valores += incremento; // Incrementar o valor
  }

  fclose(arquivo); // Fechar o arquivo após a gravação

  return 0;
}