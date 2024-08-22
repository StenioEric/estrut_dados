#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    int height;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalanceFactor(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void updateHeight(struct Node* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

struct Node* rotateRight(struct Node* node) {
    struct Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

struct Node* rotateLeft(struct Node* node) {
    struct Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

struct Node* balanceNode(struct Node* node) {
    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
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

    return balanceNode(root);
}

struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

void freeTree(struct Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

struct Node* buildBalancedTree(int arr[], int start, int end) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    struct Node* root = createNode(arr[mid]);

    root->left = buildBalancedTree(arr, start, mid - 1);
    root->right = buildBalancedTree(arr, mid + 1, end);

    return balanceNode(root);
}

int comparar(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

long long time_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

void printTreeInOrder(struct Node* root) {
    if (root != NULL) {
        printTreeInOrder(root->left);
        printf("%d ", root->data);
        printTreeInOrder(root->right);
    }
}

int main() {
    int n, *lista;
    int i;
    int num_execucoes = 200; 

    FILE* arquivo = fopen("BetterByTreeAVL.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }


    for (n = 10; n <= 10000; n += 10) {
        lista = (int*)malloc(n * sizeof(int));


        srand(time(NULL));
        for (i = 0; i < n; i++)
            lista[i] = 1 + rand() % n;


        qsort(lista, n, sizeof(int), comparar);

   
        struct Node* root = buildBalancedTree(lista, 0, n - 1);

        // Imprimir a árvore AVL em ordem
        // printf("Árvore AVL para n = %d: ", n);
        // printTreeInOrder(root);
        // printf("\n");

        int valor = root->data;
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
