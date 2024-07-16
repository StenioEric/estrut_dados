void selectionSort(int a[], int n) {
    int i, j, minIdx, temp;
    for (i = 0; i < n-1; i++) {
        minIdx = i;
        for (j = i+1; j < n; j++)
            if (a[j] < a[minIdx])
                minIdx = j;
        temp = a[minIdx];
        a[minIdx] = a[i];
        a[i] = temp;
    }
}
