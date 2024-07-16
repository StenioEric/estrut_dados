#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

void merge(int *v, int s, int m, int e);
void mergeSort(int *v, int s, int e);

void merge(int *v, int s, int m, int e) {
    int tam = e - s + 1;
    int *w = (int *)malloc(tam * sizeof(int));
    int i = s;
    int j = m + 1;
    
    for (int k = 0; k < tam; k++) {
        if (j > e || (i <= m && v[i] <= v[j])) {
            w[k] = v[i];
            i++;
        } else {
            w[k] = v[j];
            j++;
        }
    }
    
    for (int p = 0; p < tam; p++) {
        v[s + p] = w[p];
    }
    
    free(w);
}

void mergeSort(int *v, int s, int e) {
    if (s < e) {
        int m = s + (e - s) / 2;

        mergeSort(v, s, m);
        mergeSort(v, m + 1, e);
        merge(v, s, m, e);
    }
}

int main() {
    int n, *v;
    int i;
    struct timeval b, a;
    long long unsigned int ub, ua;

    // Abrir arquivo para escrita
    FILE *arquivo = fopen("merge.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    // Executar o loop para diferentes valores de n
    for (n = 100; n <= 10000; n = n + 10) {
        v = (int *)malloc(n * sizeof(int));
        // Preencher o array com valores aleatórios
        for (i = 0; i < n; i++)
            v[i] = 1 + rand() % n;

        // Medir o tempo de execução
        gettimeofday(&b, NULL); // Início da contagem do tempo
        mergeSort(v, 0, n - 1); // Chamar a função de ordenação mergeSort
        gettimeofday(&a, NULL); // Fim da contagem do tempo

        free(v); // Liberar a memória alocada para o array

        ub = 1000000 * b.tv_sec + b.tv_usec; // Tempo inicial em microssegundos
        ua = 1000000 * a.tv_sec + a.tv_usec; // Tempo final em microssegundos

        // Calcular o tempo de execução em microssegundos
        long long int tempo_execucao = ua - ub;

        // Escrever no arquivo o tamanho do array e o tempo de execução
        fprintf(arquivo, "%d %lld\n", n, tempo_execucao);
    }

    // Fechar o arquivo após a escrita
    fclose(arquivo);

    return 0;
}
