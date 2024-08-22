#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura de um nó da árvore binária
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Função para criar um novo nó
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um valor na árvore binária
struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

// Função para pesquisar um valor na árvore binária
struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

// Função para construir uma árvore binária balanceada a partir de um array ordenado
struct Node* buildBalancedTree(int arr[], int start, int end) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    struct Node* root = createNode(arr[mid]);

    root->left = buildBalancedTree(arr, start, mid - 1);
    root->right = buildBalancedTree(arr, mid + 1, end);

    return root;
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

void printTreeInOrder(struct Node *root)
{
    if (root != NULL)
    {
        printTreeInOrder(root->left);
        printf("%d ", root->data);
        printTreeInOrder(root->right);
    }
}

int main() {
    int n, *lista;
    int i;
    int num_execucoes = 200; // Número de execuções para calcular a média do tempo

    FILE* arquivo = fopen("AverageSearch.txt", "w");
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

        // Criar a árvore binária a partir do array
        struct Node* root = buildBalancedTree(lista, 0, n - 1);

        // printf("Árvore Binaria para n = %d: ", n);
        // printTreeInOrder(root);
        // printf("\n");
        // printf("\n");
        // printf("\n");

        // Realizar a busca binária múltiplas vezes com valores aleatórios
        double tempo_total = 0.0;

        for (i = 0; i < num_execucoes; i++) {
            int valor = 1 + rand() % (2 * n); // Valor aleatório que pode ou não estar na árvore
            long long inicio = time_ns();

            struct Node* resultado = search(root, valor); // Pesquisa na árvore binária

            long long fim = time_ns();

            double tempo_busca = (fim - inicio);
            tempo_total += tempo_busca;
        }
        // Calcular a média do tempo de busca
        tempo_total /= num_execucoes;

        free(lista); // Liberar a memória alocada para o array
        fprintf(arquivo, "%d %.2f\n", n, tempo_total); // Gravar os dados no arquivo
    }
    fclose(arquivo);
    return 0;
}
