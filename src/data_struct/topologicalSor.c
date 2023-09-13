//
// Created by syy on 2023/6/26.
//
#include <stdlib.h>
#include <stdio.h>
#define MAX 32767
typedef struct Node{
    int data;
    struct Node* next;

} Node;
Node * initStack(){
    Node * stack = (Node*) malloc(sizeof (Node) );
    stack -> data = 0;
    stack->next = NULL;
    return stack;
}
typedef struct Graph{
    char*  vexs;
    int ** arcs;
    int vexnum, arcnum;
}Graph;

int isEmpty(Node* stack){
    if (stack -> next == NULL) return 1;
    else return 0;
}

void push(Node* stack,int  data){
    Node* node = (Node*) malloc( sizeof (Node));
    node->data = data;
    node->next = stack->next;
    stack->next = node;
 }

int pop(Node* stack){
    if (!isEmpty(stack)){
        Node* node = stack->next;
        stack->next = node->next;
        return node->data;
    }
    else return -1;
}
Graph* initGraph(int vexnum)
{
    Graph* G = (Graph*) malloc( sizeof (Graph));
    G -> vexs = (char*) malloc(sizeof (char) * vexnum);
    G -> arcs = (int**) malloc(sizeof (int*) * vexnum);
    for(int i = 0; i < vexnum; i++)
        G -> arcs[i] = (int*) malloc(sizeof (int) * vexnum);
    G -> vexnum = vexnum;
    G -> arcnum = 0;
    return G;
}

void creatGraph(Graph* G, int* arcs, char* vexs)
{
    for(int i = 0; i < G -> vexnum; i++){
        G -> vexs[i] = vexs[i];

        for(int j = 0; j < G -> vexnum; j++ ){
            G -> arcs[i][j] = *(arcs + i * G -> vexnum + j);
            if (G -> arcs[i][j] != 0 && G -> arcs[i][j] < MAX)
                G -> arcnum ++;

        }
    }
    G -> arcnum /= 2;
}
int* findInDegrees(Graph* G){
    int* InDegrees = (int *) malloc(sizeof (int) * G -> vexnum);
    for (int i = 0; i < G -> vexnum; i++ ) InDegrees[i] = 0;
    for (int i = 0; i < G -> vexnum; i++){
        for (int j = 0 ; j < G -> vexnum; j++){
            if (G -> arcs[i][j])
                InDegrees[j] ++;
        }
    }
    return InDegrees;
}
void topologicalSort(Graph* G){
    int* InDegrees = findInDegrees(G);
    int* top = (int * ) malloc(sizeof (int ) * G -> vexnum);
    int index = 0;
    Node* stack = initStack();
    for (int i = 0; i < G -> vexnum; i++){
        if (InDegrees[i] == 0) push(stack,i);
    }

    while (!isEmpty(stack)){
        int vex = pop(stack);
        top[index++] = vex;
        for (int i = 0; i < G -> vexnum; i++){

            if (G -> arcs[vex][i]){
                InDegrees[i] --;
                if (InDegrees[i] == 0) push(stack,i);
            }

        }
    }
    for (int i = 0; i < G -> vexnum; i++ ){
        printf("%c\x20", G -> vexs[top[i]]);
    }
    printf("\n");
}
void DFS(Graph* G, int* visited, int index){
    printf("%c\x20", G -> vexs[index]);
    visited[index] =  1;
    for(int i = 0 ; i < G -> vexnum; i++){
        if (G -> arcs[index][i] == 1 && !visited[i] )
            DFS(G, visited, i);
    }
}

int main()
{
    int arcs[6][6] = {
            0,1,1,1,0,0,
            0,0,0,0,0,0,
            0,1,0,0,1,0,
            0,0,0,0,1,0,
            0,0,0,0,0,0,
            0,0,0,1,1,0
    };
    Graph* G = initGraph(6);
    int* visited = (int* ) malloc(sizeof (int) * G -> vexnum);
    for (int i = 0; i < G -> vexnum; i++) visited[i] = 0;
    creatGraph(G, (int*) arcs,"ABCDEF");
    DFS(G, visited, 0);
    printf("\n");
    topologicalSort(G);

}



