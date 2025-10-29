#include<stdio.h>

unsigned iter_fibonacci(int ith){
    if(ith==1 || ith ==2) return ith-1;
    unsigned f,s=0,ans=1;
    for (int i = 3; i <= ith; i++)
    {
        s=ans,f=s;
        ans= f+s;
    }
    return ans;
}

int main(){
    int j;
    printf("enter ith number to get series upto that term\n");
    scanf("%d",&j);

    for (int i = 1; i <= j; i++)
    {       
        printf("%d ",iter_fibonacci(i));
    }
    return 0;
}