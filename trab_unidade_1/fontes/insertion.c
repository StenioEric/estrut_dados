void insertionSort(int a[], int n) {
    int i, k, j;
    for (i = 1; i < n; i++) {
        k = a[i];
        j = i - 1;
        
        while (j >= 0 && a[j] > k) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = k;
    }
}
