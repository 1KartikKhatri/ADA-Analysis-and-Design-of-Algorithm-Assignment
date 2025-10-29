#include<stdio.h>

int fibonacci(unsigned int *arr,int ith){
    if(ith==1 || ith == 2) return arr[ith-1]= ith-1;
    
    if(arr[ith-2]!=-1 && arr[ith-1]!=-1){
        return arr[ith-1]=arr[ith-2]+arr[ith-3];
    }
    return arr[ith-1]=fibonacci(arr,ith-1)+fibonacci(arr,ith-2);
}
int main(){
    int j;
    printf("Enter ith upto which you want fibonacci series (1 - base indexing)\n");
    scanf("%d",&j);
    unsigned int arr[j];
    for(int k=0 ;k<j;k++){
        arr[k]=-1;
    }
    fibonacci(arr,j);
    for(int k=0 ;k<j;k++){
        printf("%u ",arr[k]);
    }


    return 0;
}