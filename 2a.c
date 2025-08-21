#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void generateSortedArray(int arr[], int n) {
    arr[0] = rand() % 10;
    for (int i = 1; i < n; i++) {
        arr[i] = arr[i - 1] + (rand() % 10 + 1);
    }
}


int binarySearch(int arr[],int n,int target){
    int left=0,right=n,mid;
    while (left<right)
    {
        mid=left + (right-left)/2;
        if(arr[mid]==target) return 1;
        if(arr[mid]<target){
            for (volatile int j=0; j<100; j++);
            left=mid+1;
        }else{
            right=mid;
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
    
    generateSortedArray(arr, n);
    clock_t start =clock();
    
    for(int i=0;i<1000000;i++){
        binarySearch(arr,n,arr[n-1]+1);
    }
    clock_t end =clock();

    double time_taken = (double)(end -start) /CLOCKS_PER_SEC;
    double avg_time = time_taken/100000.0;
    printf("Total time: %f s,Average per search: %f s\n", time_taken,avg_time);

    return 0;
}