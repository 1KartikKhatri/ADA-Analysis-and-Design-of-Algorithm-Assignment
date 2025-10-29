#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void generateRandomArray(int arr[],int n){
    for (int  i = 0; i < n; i++)
    {
        arr[i]=rand()%100000;
    }
}

void selectionsort(int arr[],int n){
    int MinIdx=0,temp;
    for (int i = 0; i < n; i++)
    {   MinIdx=i;
        for (int j = i+1; j < n; j++)
        {
            if (arr[j]<arr[MinIdx]) MinIdx=j;
        }
        temp=arr[i];
        arr[i]=arr[MinIdx];
        arr[MinIdx]=temp;
    }
}

int main(){
    FILE *fp = fopen("selectionsort_results.txt", "w");
    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(NULL));
    int sizes[] = {500,1000, 3000, 5000, 7000, 10000,}; 
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Array Size\tTime Taken (seconds)\n");
    fprintf(fp, "Array Size\tTime Taken (seconds)\n");

    for (int i = 0; i < numSizes; i++)
    {
        int n =sizes[i];
        int *arr=(int*)malloc(n*sizeof(int));
        generateRandomArray(arr,n);

        clock_t start =clock();
        for (int j = 0; j < 1000; j++)
        {
            selectionsort(arr,n);
        }
        clock_t  end =clock();

        double total_time = ((double)(end-start)/CLOCKS_PER_SEC);
        double avg_time_taken = total_time/1000.0;

        printf("%d\t\t%f\n", n, avg_time_taken);
        fprintf(fp, "%d\t\t%f\n", n, avg_time_taken);

        free(arr);
        
    }
    fclose(fp);
    return 0;
}