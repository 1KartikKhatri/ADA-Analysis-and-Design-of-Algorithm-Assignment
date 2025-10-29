#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void generateRandomArray(int *arr,int size){
    for(int i=0;i<size;i++){
        arr[i]=rand()%100000;
    }
}
void bubblesort(int arr[],int n){
    int temp;
    for (int j = 0; j < n; j++)
    {   for (int i = j+1; i < n-1; i++)
        {
            if(arr[i]>arr[i+1]){
                temp=arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=temp;
            }
        }   
    }
}

int main(){
    srand(time(NULL));
    FILE *fp = fopen("bubblesort_results.txt", "w");
    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }

    int size_arr[] = {1000,2000,3000,5000,7000,10000};
    int Num_Size=sizeof(size_arr)/sizeof(int);

    printf("Array Size\tTime (seconds)\n");
    printf("--------------------------------------------------\n");
    fprintf(fp, "Array Size\tTime Taken (seconds)\n");

    for (int i = 0; i < Num_Size; i++)
    {
        int *tempArr=(int*)malloc(size_arr[i]*(sizeof(int)));
        int size =size_arr[i];
        clock_t start =clock();
        for (int j = 0; j < 100; j++)
        {
            generateRandomArray(tempArr,size);
            bubblesort(tempArr,size_arr[i]);
        }
        clock_t end =clock();
        
        double time_taken = (double)(end -start) /CLOCKS_PER_SEC;
        double avg_time = time_taken/(100.0);
        printf("%d\t\t%f\n", size,avg_time);
        fprintf(fp, "%d\t\t%f\n", size, avg_time);

        free(tempArr);
    }
    fclose(fp);
    return 0;
    return 0;
}