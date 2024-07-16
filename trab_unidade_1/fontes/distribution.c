int *distributionSort(int arr[], int n){
    int i, j;
    int l = findMin(arr, n);
    int b = findMax(arr, n);
    int k = b - l + 1;
    int *w = (int *)calloc(k, sizeof(int));
    int *y = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++){
        w[arr[i] - l]++;
    }
    for (j = 1; j <= b - l; j++){
        w[j] = w[j] + w[j - 1];
    }
    for (i = n - 1; i >= 0; i--){
        j = w[arr[i] - l];
        y[j - 1] = arr[i];
        w[arr[i] - l]--;
    }
    free(w);
    return y;
} 

int findMin(int arr[], int n){
    int min_val = arr[0];
    for (int i = 1; i < n; i++){
        if (arr[i] < min_val){
            min_val = arr[i];
        }
    }
    return min_val;
}

int findMax(int arr[], int n){
    int max_val = arr[0];
    for (int i = 1; i < n; i++){
        if (arr[i] > max_val){
            max_val = arr[i];
        }
    }
    return max_val;
}