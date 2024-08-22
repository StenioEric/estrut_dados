#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


struct Node* insertWorstCase(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    root->right = insertWorstCase(root->right, data); 

    return root;
}

struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

long long time_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

int main() {
    int n, *lista;
    int i;
    int num_execucoes = 200; 

    FILE* arquivo = fopen("WorstSearch.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    for (n = 10; n <= 10000; n += 100) {
        lista = (int*)malloc(n * sizeof(int));

        for (i = 0; i < n; i++)
            lista[i] = i + 1;

        struct Node* root = NULL;
        for (i = 0; i < n; i++) {
            root = insertWorstCase(root, lista[i]);
        }

      
        double tempo_total = 0.0;

        for (i = 0; i < num_execucoes; i++) {
            int valor = n + 1; 

            long long inicio = time_ns();

            struct Node* resultado = search(root, valor); 

            long long fim = time_ns();

            double tempo_busca = (fim - inicio);
            tempo_total += tempo_busca;
        }

        tempo_total /= num_execucoes;


        free(lista); 
        fprintf(arquivo, "%d %.2f\n", n, tempo_total); 
    }
    fclose(arquivo);
    return 0;
}
