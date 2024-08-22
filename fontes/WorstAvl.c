#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura do nó da árvore AVL
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};

// Função para criar um novo nó
struct Node *createNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Função para calcular a altura de um nó
int getHeight(struct Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

// Função para calcular o máximo entre dois números
int maximum(int a, int b)
{
    return (a > b) ? a : b;
}

// Função para fazer uma rotação simples à direita
struct Node *rotateRight(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Realizar a rotação
    x->right = y;
    y->left = T2;

    // Atualizar as alturas
    y->height = maximum(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = maximum(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Função para fazer uma rotação simples à esquerda
struct Node *rotateLeft(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Realizar a rotação
    y->left = x;
    x->right = T2;

    // Atualizar as alturas
    x->height = maximum(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = maximum(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Função para calcular o fator de balanceamento de um nó
int getBalance(struct Node *node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Função para inserir um novo nó na árvore AVL
struct Node *insert(struct Node *root, int data)
{
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

    if (balance > 1 && data < root->left->data)
        return rotateRight(root);

    if (balance < -1 && data > root->right->data)
        return rotateLeft(root);

    if (balance > 1 && data > root->left->data)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && data < root->right->data)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Função para pesquisar um valor na árvore AVL
struct Node *search(struct Node *root, int data)
{
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return search(root->left, data);

    return search(root->right, data);
}

// Função para liberar a memória ocupada pela árvore AVL
void freeTree(struct Node *root)
{
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Função de comparação para a função qsort
int comparar(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// Função para calcular o tempo em nanossegundos
long long time_ns()
{
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

int main()
{
    int n, *lista;
    int i;
    int num_execucoes = 500;

    FILE *arquivo = fopen("WrostAvl.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    for (n = 10; n <= 1000; n += 10)
    {
        lista = (int *)malloc(n * sizeof(int));

        for (i = 0; i < n; i++)
            lista[i] = i + 1;

        struct Node *root = NULL;
        for (i = 0; i < n; i++)
        {
            root = insert(root, lista[i]);
        }

        // printf("Árvore AVL para n = %d: ", n);
        // printTreeInOrder(root);
        // printf("\n");
        // printf("\n");
        // printf("\n");

        int valor = n + 1; // Garantindo o pior caso

        double tempo_total = 0.0;

        for (i = 0; i < num_execucoes; i++)
        {
            long long inicio = time_ns();

            struct Node *resultado = search(root, valor); // Pesquisa na árvore AVL

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
