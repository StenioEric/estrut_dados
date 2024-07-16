#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

void quickSort(int *v, int inicio, int fim);
int partition(int *v, int inicio, int fim);

void quickSort(int *v, int inicio, int fim) {
    if (fim > inicio) {
        int p = partition(v, inicio, fim);
        quickSort(v, inicio, p - 1);
        quickSort(v, p + 1, fim);
    }
}

int partition(int *v, int inicio, int fim) {
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = fim;
    pivo = v[inicio];
    while (esq < dir) {
        while (v[esq] <= pivo)
            esq++;
        while (v[dir] > pivo)
            dir--;
        if (esq < dir) {
            aux = v[esq];
            v[esq] = v[dir];
            v[dir] = aux;
        }
    }
    v[inicio] = v[dir];
    v[dir] = pivo;
    return dir;
}

void geraVetorAleatorio(int *v, int n) {
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 2000; // Valores aleatórios entre 0 e 1999
    }
}

int main() {
    int n, *v;
    struct timeval b, a;
    long long unsigned int ub, ua;

    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    FILE *arquivo = fopen("quickMedio.txt", "w");
    if (!arquivo) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    for (n = 100; n <= 10000; n += 100) {
        v = (int *)malloc(n * sizeof(int));
        if (!v) {
            fprintf(stderr, "Falha na alocação de memória.\n");
            return 1;
        }

        geraVetorAleatorio(v, n);

        gettimeofday(&b, NULL); // Início da contagem do tempo
        quickSort(v, 0, n - 1); // Chamar a função de ordenação quicksort
        gettimeofday(&a, NULL); // Fim da contagem do tempo

        ub = 1000000 * b.tv_sec + b.tv_usec; // Tempo inicial em microssegundos
        ua = 1000000 * a.tv_sec + a.tv_usec; // Tempo final em microssegundos

        fprintf(arquivo, "%d %lld\n", n, ua - ub);

        free(v); // Liberar a memória alocada para o array
    }

    fclose(arquivo);

    return 0;
}
