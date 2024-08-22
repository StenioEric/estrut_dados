#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int maximum(int a, int b) {
    return (a > b) ? a : b;
}

struct Node* rotateRight(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = maximum(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = maximum(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

struct Node* rotateLeft(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = maximum(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = maximum(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else 
        return root;

    root->height = 1 + maximum(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // Caso esquerda-esquerda
    if (balance > 1 && data < root->left->data)
        return rotateRight(root);

    // Caso direita-direita
    if (balance < -1 && data > root->right->data)
        return rotateLeft(root);

    // Caso esquerda-direita
    if (balance > 1 && data > root->left->data) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Caso direita-esquerda
    if (balance < -1 && data < root->right->data) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return search(root->left, data);

    return search(root->right, data);
}

void freeTree(struct Node* root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int comparar(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

struct Node* buildBalancedTree(int* arr, int start, int end) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    struct Node* root = createNode(arr[mid]);

    root->left = buildBalancedTree(arr, start, mid - 1);
    root->right = buildBalancedTree(arr, mid + 1, end);

    root->height = 1 + maximum(getHeight(root->left), getHeight(root->right));

    return root;
} 

long long time_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

int main() {
    int n, *lista;
    int i;
    int num_execucoes = 500; 

    FILE* arquivo = fopen("BinarySearchAVL.txt", "w");
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

        int randIndex = rand() % n;
        while (randIndex == n / 2)
            randIndex = rand() % n; 
        int valor = lista[randIndex];

        double tempo_total = 0.0;

        for (i = 0; i < num_execucoes; i++) {
            long long inicio = time_ns();

            struct Node* resultado = search(root, valor); 

            long long fim = time_ns();

            double tempo_busca = (fim - inicio);
            tempo_total += tempo_busca;
        }
        tempo_total /= num_execucoes;

        freeTree(root); 
        free(lista); 
        fprintf(arquivo, "%d %.2f\n", n, tempo_total); 
    }
    fclose(arquivo);
    return 0;
}
