#include<stdio.h>
#include<stdlib.h>


typedef struct Node{
 int vertice;
 struct Node* next;
}vrts;

vrts* createVrts(int val){
    vrts* newvrts = (vrts*)malloc(sizeof(vrts));
    newvrts->vertice=val;
    newvrts->next=NULL;
    return newvrts;
}

void insertedge(vrts* list[],int vertice1,int vertice2){
    vrts* Vrts=createVrts(vertice2);
    
    vrts* temp=list[vertice1-1]->next;
    list[vertice1-1]->next=Vrts;
    Vrts->next=temp;
}

void DFS_iter(vrts* list[],int start){
    int stack[7];
    int top=-1;
    int visited[7]={0};
    stack[++top]=start;
    visited[start-1]=1;
    printf("%d ",start);
    while (top !=-1)
    {
        int isfound=0;
        vrts* temp=list[stack[top]-1]->next;
        while(temp!=NULL ){
            if(visited[temp->vertice-1]==0){
                stack[++top]=temp->vertice;
                printf("%d ",temp->vertice);
                visited[temp->vertice-1]=1;
                isfound=1;
                break;
            }
            temp=temp->next;
        }
        if(isfound==0){
            top--;
        }
    } 
}

void DFS_rec(vrts* list[],int start,int visited[]){
    printf("%d ",start);
    visited[start-1]=1;
    vrts* temp = list[start-1]->next;
    while (temp!=NULL)
    {
        if(visited[temp->vertice-1]==0){
            DFS_rec(list,temp->vertice,visited);
        }
        temp=temp->next;
    }
}

void BFS_iter(vrts* list[],int start){
    int front=0,rear=0,Queue[7],x;
    int visited[7]={0};
    Queue[rear++]=start;
    visited[start-1]=1;
    vrts* temp;

    while (front<rear)
    {   x=Queue[front];
        printf("%d ",x);
        front++; // deque
        
        temp=list[x-1]->next; // enquee non visited neibours connected vertices
        while (temp!=NULL)
        {   if (!visited[temp->vertice-1])
            {
                Queue[rear++]=temp->vertice;
                visited[temp->vertice-1]=1;
            }
            temp=temp->next;
        }
    }
}

void convertListToMatrix(vrts* list[], int V) {
    int** matrix=(int**)malloc(V*(sizeof(int*)));
    for (int i = 0; i < V; i++)
    {
        matrix[i]=(int*)malloc(V*sizeof(int));
    }
    
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            matrix[i][j] = 0;
        }
    }

    for(int i = 0; i < V; i++) {
        vrts* temp = list[i]->next; 
        while (temp != NULL) {
            matrix[i][temp->vertice - 1] = 1;
            temp = temp->next;
        }
    }

    printf("\nAdjacency Matrix Representation:\n");
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}


int main(){
    vrts* list[7];
    for(int i = 0; i < 7; i++) {
        list[i]=createVrts(i+1);
    }

    insertedge(list,1,2);
    insertedge(list,1,3);

    insertedge(list,2,4);
    insertedge(list,2,1);

    insertedge(list,3,4);
    insertedge(list,3,7);
    insertedge(list,3,1);

    insertedge(list,4,5);
    insertedge(list,4,2);
    insertedge(list,4,3);
    insertedge(list,4,6);
    
    insertedge(list,5,4);
    insertedge(list,6,4);
    insertedge(list,7,3);

    

    
    // BFS_iter(list,1);
    // convertListToMatrix(list,7);
    
    int visited[7]={0};
    DFS_rec(list,2,visited);
    
    return 0;
}