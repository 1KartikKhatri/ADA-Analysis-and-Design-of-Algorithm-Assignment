#include<stdio.h>

int t[100][100];

int max(int a ,int b){
    return (a>=b)?a:b;
}

int knapsack(int wt[],int v[],int W,int n){
    if(W==0 || n==0) return t[W][n]=0;
    
    if(t[W][n]!= -1) return t[W][n];
    
    if(W>=wt[n-1]){
        return t[W][n]= max((v[n-1]+knapsack(wt,v,W-wt[n-1],n-1)),(knapsack(wt,v,W,n-1)));
    }else{
        return t[W][n]= knapsack(wt,v,W,n-1);
    }
}

int main(){

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            t[i][j]=-1;
        }  
    }

    int wt[] = {4,8,10,2,6};
    int val[] = {30,16,15,10,5};
    int ans = knapsack(wt,val,10,5);
    printf("%d",ans);
    return 0;
}