#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

int main() {
    FILE *fp = fopen("quicksort_results.txt", "w");
    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(NULL));
    int sizes[] = {500,1000, 3000, 5000, 7000, 10000}; 
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Array Size\tTime Taken (seconds)\n");
    fprintf(fp, "Array Size\tTime Taken (seconds)\n");

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int *arr = (int *)malloc(n * sizeof(int));
        generateRandomArray(arr, n);

        clock_t start = clock();
        for(int i=0;i<100;i++){
            quickSort(arr, 0, n - 1);

        }
        clock_t end = clock();

        double total_time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        double avg_time_taken = total_time_taken/1000.0;

        printf("%d\t\t%f\n", n, avg_time_taken);
        fprintf(fp, "%d\t\t%f\n", n, avg_time_taken);

        free(arr);
    }

    fclose(fp);

    return 0;
}
