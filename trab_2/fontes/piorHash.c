#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 1  

struct Node
{
    int key;
    int value;
    struct Node *next;
};

struct Node *createNode(int key, int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

struct Node **createHashTable()
{
    struct Node **hashTable = malloc(TABLE_SIZE * sizeof(struct Node *));
    for (int i = 0; i < TABLE_SIZE; i++)
        hashTable[i] = NULL;
    return hashTable;
}

int hashFunction(int key)
{
    return 0;
}

void insertNode(struct Node **hashTable, int key, int value)
{
    int hashIndex = hashFunction(key);
    struct Node *newNode = createNode(key, value);

    if (hashTable[hashIndex] == NULL)
    {
        hashTable[hashIndex] = newNode;
    }
    else
    {
        struct Node *temp = hashTable[hashIndex];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

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

int main()
{
    int n;
    int i;
    int num_execucoes = 200; 

    FILE *arquivo = fopen("Hash_PiorCaso.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    struct timespec inicio, fim;

    for (n = 10; n <= 10000; n += 100)
    {
        struct Node **hashTable = createHashTable();

        for (i = 0; i < n; i++)
            insertNode(hashTable, i, i);

        double tempo_total = 0.0;

        for (i = 0; i < num_execucoes; i++)
        {
            clock_gettime(CLOCK_MONOTONIC, &inicio);


            searchNode(hashTable, n - 1);

            clock_gettime(CLOCK_MONOTONIC, &fim);

            double tempo_busca = (fim.tv_sec - inicio.tv_sec) * 1e9 + (fim.tv_nsec - inicio.tv_nsec);
            tempo_total += tempo_busca;
        }

        tempo_total /= num_execucoes;

        freeHashTable(hashTable);                      
        fprintf(arquivo, "%d %.2f\n", n, tempo_total); 
    }
    fclose(arquivo);
    return 0;
}
