#include<stdio.h>
#include<stdlib.h>
typedef struct Node
{
    int start_time;
    int end_time;
}node;

void merge(node arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1; 
    int n2 = r - m;     


    node *L = (node *)malloc(n1 * sizeof(node));
    node *R = (node *)malloc(n2 * sizeof(node));

    for (i = 0; i < n1; i++){
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = arr[m + 1 + j];
    }

    i = 0; 
    j = 0; 
    k = l; 

    while (i < n1 && j < n2) {
        if (L[i].end_time <= R[j].end_time) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(node arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2; 

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int GetMaxNumberOfActivites(node* activity,int n){
    if(n==1 ) return 1;
    if(n<0) return -1;
    mergeSort(activity,0,n);
    int No_of_activity=1,current_endTime=activity[0].end_time;
    for (int i = 1; i < n; i++)
    {
        if(activity[i].start_time>=current_endTime){
            No_of_activity++;
            current_endTime=activity[i].end_time;
        }
    }
    return No_of_activity;
}

int main(){
    int n,temp;
    printf("Enter the size of array\n");
    scanf("%d",&n);
    node arr[n];
    printf("enter start time\n");
    for (int i = 0; i < n; i++){
        scanf("%d",&temp);
        arr[i].start_time=temp;
    } 
    
    printf("enter end time\n");
    for (int i = 0; i < n; i++){
        scanf("%d",&temp);
        arr[i].end_time=temp;
    } 
    int Max_no_ofActivity=GetMaxNumberOfActivites(arr,n);

    printf("%d",Max_no_ofActivity);
    return 0;
}
