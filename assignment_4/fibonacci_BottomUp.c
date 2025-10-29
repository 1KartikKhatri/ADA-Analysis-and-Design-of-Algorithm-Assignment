#include<stdio.h>

unsigned iter_fibonacci(unsigned int *arr,int ith){
    if(ith==1 || ith ==2) return arr[ith-1]=ith-1;
    arr[0]=0,arr[1]=1;
    for (int i = 3; i <=ith; i++)
    {
        arr[i-1]=arr[i-2]+arr[i-3];
    }
    return arr[ith-1];
}

int main(){
    int j;
    printf("enter ith number to get series upto that term\n");
    scanf("%d",&j);

    unsigned int arr[j];
    iter_fibonacci(arr,j);
    for (int i = 0; i < j; i++)
    {       
        printf("%d ",arr[i]);
    }
    return 0;
}