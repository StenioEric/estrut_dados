#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *distributionSort(int arr[], int n){
    int i, j;
    int l = arr[0];
    int b = arr[0];
    for (i = 1; i < n; i++){
        if (arr[i] < l){
            l = arr[i];
        }
        if (arr[i] > b){
            b = arr[i];
        }
    }
    int k = b - l + 1;
    int *w = (int *)calloc(k, sizeof(int));
    int *y = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++){
        w[arr[i] - l]++;
    }
    for (j = 1; j <= b - l; j++){
        w[j] = w[j] + w[j - 1];
    }
    for (i = n - 1; i >= 0; i--){
        j = w[arr[i] - l];
        y[j - 1] = arr[i];
        w[arr[i] - l]--;
    }
    free(w);
    return y;
}

int findMin(int arr[], int n){
    int min_val = arr[0];
    for (int i = 1; i < n; i++){
        if (arr[i] < min_val){
            min_val = arr[i];
        }
    }
    return min_val;
}

int findMax(int arr[], int n){
    int max_val = arr[0];
    for (int i = 1; i < n; i++){
        if (arr[i] > max_val){
            max_val = arr[i];
        }
    }
    return max_val;
}

int main()
{
    int tamanho_max = 10000;

    FILE *arquivo = fopen("distribution.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de dados.\n");
        return 1;
    }

    // Executar o algoritmo de distribution Sort para diferentes tamanhos de vetor
    for (int tamanho = 10; tamanho <= tamanho_max; tamanho += 10)
    {
        // Criar o vetor de tamanho atual
        int *v = (int *)malloc(tamanho * sizeof(int));

        // Preencher o vetor com valores aleatórios
        srand(time(NULL));
        for (int i = 0; i < tamanho; i++)
        {
            v[i] = rand() % 1000;
        }

        clock_t inicio = clock();

        // Ordenar o vetor usando o algoritmo distribution Sort
        int *sorted_array = distributionSort(v, tamanho);

        clock_t fim = clock();

        // Calcular o tempo de execução em segundos
        double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

        // Escrever o tamanho do vetor e o tempo de execução no arquivo de dados
        fprintf(arquivo, "%d %lf\n", tamanho, tempo_execucao);

        // Liberar a memória alocada para o vetor ordenado
        free(sorted_array);
        // Liberar a memória alocada para o vetor
        free(v);
    }

    // Fechar o arquivo de dados
    fclose(arquivo);

    // Chamar o Gnuplot para gerar o gráfico
    FILE *gnuplot = popen("gnuplot -persistent", "w");

    return 0;
}
