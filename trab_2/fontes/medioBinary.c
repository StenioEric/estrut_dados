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

struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

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

struct Node* buildBalancedTree(int arr[], int start, int end) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    struct Node* root = createNode(arr[mid]);

    root->left = buildBalancedTree(arr, start, mid - 1);
    root->right = buildBalancedTree(arr, mid + 1, end);

    return root;
}

int comparar(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
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

    FILE* arquivo = fopen("AverageSearch.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    for (n = 10; n <= 1000; n += 10) {
        lista = (int*)malloc(n * sizeof(int));

        srand(time(NULL));
        for (i = 0; i < n; i++)
            lista[i] = 1 + rand() % n;

        qsort(lista, n, sizeof(int), comparar);

        struct Node* root = buildBalancedTree(lista, 0, n - 1);

        double tempo_total = 0.0;

        for (i = 0; i < num_execucoes; i++) {
            int valor = 1 + rand() % (2 * n); 
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
