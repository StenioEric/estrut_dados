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

// Função para inserir um valor na árvore binária de forma sequencial (gerando pior caso)
struct Node* insertWorstCase(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    root->right = insertWorstCase(root->right, data); // Inserção sempre à direita

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

    FILE* arquivo = fopen("WorstSearch.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    // Executar o loop para diferentes valores de n
    for (n = 10; n <= 1000; n += 100) {
        lista = (int*)malloc(n * sizeof(int));

        // Preencher o array com valores em ordem crescente para gerar o pior caso
        for (i = 0; i < n; i++)
            lista[i] = i + 1;

        // Criar a árvore binária pior caso a partir do array
        struct Node* root = NULL;
        for (i = 0; i < n; i++) {
            root = insertWorstCase(root, lista[i]);
        }

        // printf("Árvore Binaria para n = %d: ", n);
        // printTreeInOrder(root);
        // printf("\n");
        // printf("\n");
        // printf("\n");

        // Realizar a busca binária múltiplas vezes no pior caso
        double tempo_total = 0.0;

        for (i = 0; i < num_execucoes; i++) {
            int valor = n + 1; // Valor que não está na árvore, causando o pior caso

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
