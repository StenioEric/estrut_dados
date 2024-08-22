#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura de um nó da árvore AVL
struct Node {
    int data;
    int height;
    struct Node* left;
    struct Node* right;
};

// Função para criar um novo nó
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para obter a altura de um nó
int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Função para calcular o fator de balanceamento de um nó
int getBalanceFactor(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Função para atualizar a altura de um nó
void updateHeight(struct Node* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Função para fazer uma rotação simples à direita
struct Node* rotateRight(struct Node* node) {
    struct Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Função para fazer uma rotação simples à esquerda
struct Node* rotateLeft(struct Node* node) {
    struct Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Função para balancear um nó
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

// Função para inserir um valor na árvore AVL
struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root; // Valor duplicado, não é permitido na árvore AVL

    return balanceNode(root);
}

// Função para pesquisar um valor na árvore AVL
struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

// Função para liberar a memória ocupada pela árvore AVL
void freeTree(struct Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Função para construir uma árvore AVL balanceada a partir de um array ordenado
struct Node* buildBalancedTree(int arr[], int start, int end) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    struct Node* root = createNode(arr[mid]);

    root->left = buildBalancedTree(arr, start, mid - 1);
    root->right = buildBalancedTree(arr, mid + 1, end);

    return balanceNode(root);
}

// Função de comparação para qsort
int comparar(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Função para calcular o tempo em nanossegundos
long long time_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

// Função para imprimir a árvore AVL em ordem
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
    int num_execucoes = 200; // Número de execuções para calcular a média do tempo

    FILE* arquivo = fopen("BetterByTreeAVL.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    // Executar o loop para diferentes valores de n
    for (n = 10; n <= 1000; n += 10) {
        lista = (int*)malloc(n * sizeof(int));

        // Preencher o array com valores aleatórios
        srand(time(NULL));
        for (i = 0; i < n; i++)
            lista[i] = 1 + rand() % n;

        // Ordenar a lista em ordem crescente
        qsort(lista, n, sizeof(int), comparar);

        // Criar a árvore AVL balanceada a partir do array
        struct Node* root = buildBalancedTree(lista, 0, n - 1);

        // printf("Árvore AVL para n = %d: ", n);
        // printTreeInOrder(root);
        // printf("\n");
        // printf("\n");
        // printf("\n");

        int valor = root->data;
        double tempo_total = 0.0;

        for (i = 0; i < num_execucoes; i++) {
            long long inicio = time_ns();

            struct Node* resultado = search(root, valor); // Pesquisa na árvore AVL

            long long fim = time_ns();

            double tempo_busca = (fim - inicio);
            tempo_total += tempo_busca;
        }
        // Calcular a média do tempo de busca
        tempo_total /= num_execucoes;

        freeTree(root); // Liberar a memória ocupada pela árvore AVL
        free(lista); // Liberar a memória alocada para o array
        fprintf(arquivo, "%d %.2f\n", n, tempo_total); // Gravar os dados no arquivo
    }
    fclose(arquivo);
    return 0;
}
