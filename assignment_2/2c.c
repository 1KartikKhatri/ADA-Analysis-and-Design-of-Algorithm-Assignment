#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void generateRandomArray(int arr[],int n){
    for (int  i = 0; i < n; i++)
    {
        arr[i]=rand()%100000;
    }
}

void insertionSort(int arr[],int n){
    for (int i = 1; i < n; i++)
    {   int key = arr[i]; 
        int j = i-1;

        while (j>=0 && arr[j]>key)
        {
            arr[j+1]=arr[j];
            j-=1;
        }
        arr[j+1]=key;  
    }
}

int main(){
    srand(time(NULL));
    FILE *fp = fopen("insertionsort_results.txt", "w");
    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }

    int sizes[] = {1000,2000,3000,4000,5000,6000,7000}; 
    int numSizes = sizeof(sizes) / sizeof(int);

    printf("Array Size\tTime Taken (seconds)\n");
    fprintf(fp, "Array Size\tTime Taken (seconds)\n");


    for(int i=0;i<numSizes;i++){
        int n=sizes[i];
        int* arr=(int*)malloc(n*sizeof(int));
        
        clock_t start =clock();
        for (int i = 0; i < 1000; i++)
        {
            generateRandomArray(arr,n);
            insertionSort(arr,n);
        }
        clock_t end =clock();

        double total_time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        double avg_time_taken = total_time_taken/1000.0;
        
        printf("%d\t\t%f\n", n, avg_time_taken);
        fprintf(fp, "%d\t\t%f\n", n, avg_time_taken);

        free(arr);
    }
    fclose(fp);
    return 0;
}