void quickSort(int a[], int inicio, int fim);
int partition(int a[], int inicio, int fim);

void quickSort(int a[], int inicio, int fim) {
    if (inicio < fim) {
        int pi = partition(a, inicio, fim);
        quickSort(a, inicio, pi - 1);
        quickSort(a, pi + 1, fim);
    }
}

int partition(int a[], int inicio, int fim) {
    int pivot = a[fim];
    int i = (inicio - 1);
    for (int j = inicio; j < fim; j++) {
        if (a[j] <= pivot) {
            i++;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    int temp = a[i + 1];
    a[i + 1] = a[fim];
    a[fim] = temp;
    return (i + 1);
}