#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//merge sort
void generateRandomArray(int arr[],int n){
    for (int  i = 0; i < n; i++)
    {
        arr[i]=rand()%100000;
    }
}

void merge(int *arr,int left,int mid,int right){
    int n1=mid-left+1;
    int n2=right-mid;
    int L[n1],R[n2];
    for (int i = 0; i < n1; i++)L[i]=arr[left+i];
    for (int j =0; j < n2; j++)R[j]=arr[mid+1+j];

    int p1=0,p2=0,k=left;
    while(p1<n1 && p2<n2){
        if(L[p1]<=R[p2]){
            arr[k++]=L[p1++];
        }else{
            arr[k++]=R[p2++];
        }
    }

    while(p1<n1){
        arr[k++]=L[p1++];
    }
    while (p2<n2)
    {   arr[k++]=R[p2++];
    }
}
void mergeSort(int *arr,int left,int right){
     if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main(){
    srand(time(NULL));
    FILE *fp = fopen("mergesort_results.txt", "w");
    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }

    int size_arr[9] = {1000,3000,5000,7000,10000,13000,16000,19000,21000};

    printf("Array Size\tTime (seconds)\n");
    printf("--------------------------------------------------\n");
    fprintf(fp, "Array Size\tTime Taken (seconds)\n");

    for (int i = 0; i < 9; i++)
    {
        int *tempArr=(int*)malloc(size_arr[i]*(sizeof(int)));
        int size =size_arr[i];
        generateRandomArray(tempArr,size);
        clock_t start =clock();
        for (int j = 0; j < 1000; j++)
        {
            mergeSort(tempArr,0,size_arr[i]-1);
        }
        clock_t end =clock();
        
        double time_taken = (double)(end -start) /CLOCKS_PER_SEC;
        double avg_time = time_taken/(1000.0);
        printf("%d\t\t%f\n", size,avg_time);
        fprintf(fp, "%d\t\t%f\n", size, avg_time);

        free(tempArr);
    }
    fclose(fp);
    return 0;
}