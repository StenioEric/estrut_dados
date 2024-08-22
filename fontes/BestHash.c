#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Tamanho da tabela de dispersão
#define TABLE_SIZE 10000

// Estrutura de um nó da tabela de dispersão
struct Node
{
    int key;
    int value;
    struct Node *next;
};

// Função para criar um novo nó
struct Node *createNode(int key, int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Função para criar a tabela de dispersão
struct Node **createHashTable()
{
    struct Node **hashTable = malloc(TABLE_SIZE * sizeof(struct Node *));
    for (int i = 0; i < TABLE_SIZE; i++)
        hashTable[i] = NULL;
    return hashTable;
}

// Função de dispersão
int hashFunction(int key)
{
    return key % TABLE_SIZE;
}

// Função para inserir um valor na tabela de dispersão
void insertNode(struct Node **hashTable, int key, int value)
{
    int hashIndex = hashFunction(key);
    struct Node *newNode = createNode(key, value);
    newNode->next = hashTable[hashIndex];
    hashTable[hashIndex] = newNode;
}

// Função para pesquisar um valor na tabela de dispersão
struct Node *searchNode(struct Node **hashTable, int key)
{
    int hashIndex = hashFunction(key);
    struct Node *temp = hashTable[hashIndex];
    while (temp)
    {
        if (temp->key == key)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Função para liberar a memória ocupada pela tabela de dispersão
void freeHashTable(struct Node **hashTable)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct Node *entry = hashTable[i];
        while (entry)
        {
            struct Node *temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
    free(hashTable);
}

// Função para imprimir a tabela de dispersão no terminal
void printHashTable(struct Node **hashTable)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct Node *entry = hashTable[i];
        if (entry != NULL)
        {
            printf("Index %d: ", i);
            while (entry)
            {
                printf("(Key: %d, Value: %d) -> ", entry->key, entry->value);
                entry = entry->next;
            }
            printf("NULL\n");
            printf("\n");
        }
    }
}

int main()
{
    int n;
    int i;
    int num_execucoes = 200; // Número de execuções para calcular a média do tempo

    FILE *arquivo = fopen("Hash_MelhorCaso.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    struct timespec inicio, fim;

    // Executar o loop para diferentes valores de n
    for (n = 10; n <= 1000; n += 10)
    {
        struct Node **hashTable = createHashTable();

        srand(time(NULL));

        // Escolher um valor aleatório para a busca
        int valor = 1 + rand() % n;

        // Insere o valor a ser buscado primeiro no índice correspondente (melhor caso)
        insertNode(hashTable, valor, valor);

        // Preencher a tabela de dispersão com outros valores aleatórios
        for (i = 1; i < n; i++)
            insertNode(hashTable, i, 1 + rand() % n);

        double tempo_total = 0.0;

        for (i = 0; i < num_execucoes; i++)
        {
            clock_gettime(CLOCK_MONOTONIC, &inicio);

            struct Node *resultado = searchNode(hashTable, valor); // Pesquisa na tabela de dispersão
            clock_gettime(CLOCK_MONOTONIC, &fim);

            double tempo_busca = (fim.tv_sec - inicio.tv_sec) * 1e9 + (fim.tv_nsec - inicio.tv_nsec);
            tempo_total += tempo_busca;
        }
        // Calcular a média do tempo de busca
        tempo_total /= num_execucoes;

        // printHashTable(hashTable);

        freeHashTable(hashTable);                      // Liberar a memória ocupada pela tabela de dispersão
        fprintf(arquivo, "%d %.2f\n", n, tempo_total); // Gravar os dados no arquivo
    }
    fclose(arquivo);
    return 0;
}
