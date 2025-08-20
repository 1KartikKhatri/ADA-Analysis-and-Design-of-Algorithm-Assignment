#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void generateRandomArray(int arr[],int n){
    for (int  i = 0; i < n; i++)
    {
        arr[i]=rand()%100000;
    }
}

int linearSearch(int arr[],int target,int n){
    for(int i=0;i<n;i++){
        if(arr[i]==target){
            return 1;
        }
    }
    return 0;
}

int main(){
    int n;
    printf("Enter size of array\n");
    scanf("%d",&n);
    
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    generateRandomArray(arr, n);
    clock_t start =clock();
    
    for(int i=0;i<100000;i++){
        linearSearch(arr,arr[n-1],n);
    }
    clock_t end =clock();

    double time_taken = (double)(end -start) /CLOCKS_PER_SEC;
    double avg_time = time_taken/100000.0;
    printf("Total time: %f s,Average per search: %f s\n", time_taken,avg_time);

    return 0;
}