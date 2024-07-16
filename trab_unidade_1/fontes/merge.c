void mergeSort(int v[], int s, int e);
void merge(int v[], int s, int m, int e);

void merge(int v[], int s, int m, int e) {
    int tam = e - s + 1;
    int *w = (int *)malloc(tam * sizeof(int));
    int i = s;
    int j = m + 1;
    
    for (int k = 0; k < tam; k++) {
        if (j > e || (i <= m && v[i] <= v[j])) {
            w[k] = v[i];
            i++;
        } else {
            w[k] = v[j];
            j++;
        }
    }
    
    for (int p = 0; p < tam; p++) {
        v[s + p] = w[p];
    }
    
    free(w);
}

void mergeSort(int v[], int s, int e) {
    if (s < e) {
        int m = s + (e - s) / 2;

        mergeSort(v, s, m);
        mergeSort(v, m + 1, e);
        merge(v, s, m, e);
    }
}
