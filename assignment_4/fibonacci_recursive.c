#include<stdio.h>

int fibonacci(int ith){
    if(ith==1 || ith ==2) return ith-1;
    return fibonacci(ith-2)+fibonacci(ith-1); 
}
int main(){
    int j;
    printf("enter ith number to get series upto that term\n");
    scanf("%d",&j);
    for (int i = 1; i <= j; i++)
    {       
        printf("%d ",fibonacci(i));
    }
    return 0;
}