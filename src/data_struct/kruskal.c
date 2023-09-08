//
// Created by syy on 2023/6/26.
//
#include <stdlib.h>
#include <stdio.h>
#define MAX 32767
typedef struct Queue{
    int* data;
    int front;
    int rear;
    int lenght;

}Queue;
Queue* initQueue (int vexnum){
    Queue * Q = (Queue*) malloc(sizeof(Queue));
    Q -> data = (int *) malloc(sizeof (int) * vexnum);
    Q -> front = Q -> rear = 0;
    Q -> lenght = vexnum;
    return Q;
}
int isFull(Queue* Q){
    return Q -> front ==  (Q -> rear + 1) % Q -> lenght;
}
int enQueue(Queue* Q, int data){
    if (isFull(Q))
        return 0;
    else{
        Q -> data[Q -> rear] = data;
        Q -> rear = (Q -> rear + 1) % Q -> lenght ;
        return 1;
    }
}
int isEmpty(Queue* Q){
    return Q-> front == Q -> rear;
}
int deQueue(Queue* Q){
    if (isEmpty(Q)) return -1;
    else{
        int temp = Q -> data[Q -> front];
        Q -> front = (Q -> front + 1) % Q -> lenght;
        return temp;
    }
}

typedef struct Graph{
    char*  vexs;
    int ** arcs;
    int vexnum, arcnum;
}Graph;
typedef struct Edge{
    int start;
    int end;
    int  weight;
} Edge;

Edge * initEdge(Graph* G){
    int index = 0;
    Edge * edge = (Edge*) malloc(sizeof (Edge) * G -> arcnum);
    for (int i = 0; i < G -> vexnum; i ++){
        for(int j = i+1; j < G -> vexnum; j++){
            if (G -> arcs[i][j] != 0 && G -> arcs[i][j] != MAX){
                edge[index].start = i;
                edge[index].end = j;
                edge[index].weight = G -> arcs[i][j];
                index++;
            }
        }
    }
    return edge;
}
void sortEdge(Edge* edge, Graph* G) {
    Edge temp;
    for(int i = 0; i < G -> arcnum - 1; i++){
        for (int j = 0; j < G -> arcnum - i - 1; j++ ){
            if (edge[j].weight > edge[j+1].weight){
                temp = edge[j];
                edge[j] = edge[j+1];
                edge[j+1] = temp;
            }
        }
    }
}


void kruskal(Graph* G) {
    int* connected = (int*)malloc(sizeof(int) * G -> vexnum);
    for (int i = 0 ; i < G -> vexnum; i++) {
        connected[i] = i;
    }
    Edge* edge = initEdge(G);
    sortEdge(edge, G);
    for (int i = 0; i < G -> arcnum; i++) {
        int start = connected[edge[i].start];
        int end = connected[edge[i].end];
        if (start != end) {
            printf("v%c --> v%c weight = %d\n", G -> vexs[edge[i].start], G -> vexs[edge[i].end], edge[i].weight);
            for (int j = 0; j < G -> vexnum; j++) {
                if (connected[j] == end) {
                    connected[j] = start;
                }


            }
        }
    }
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

void DFS(Graph* G, int* visited, int index){
    printf("%c\x20", G -> vexs[index]);
    visited[index] =  1;
    for(int i = 0 ; i < G -> vexnum; i++){
        if (G -> arcs[index][i] > 0 && G -> arcs[index][i] < MAX && !visited[i] )
            DFS(G, visited, i);
    }
}
void BFS(Graph* G, int* visited){
    Queue* Q = initQueue(G -> vexnum);
    enQueue(Q, 0);
    visited[0] = 1;
    printf("%c\x20", G -> vexs[0]);
    while (!isEmpty(Q)){
         int temp = deQueue(Q);

         for(int i = 0 ; i < G -> vexnum; i++){
             if (G -> arcs[temp][i] > 0 && G -> arcs[temp][i] < MAX && !visited[i])
             {

                 printf("%c\x20", G -> vexs[i]);
                 visited[i] = 1;

                 enQueue(Q, i);
             }



         }
    }


}
int main()
{
    int arcs[6][6] = {
            0, 6, 1, 5, MAX, MAX,
            6, 0, 5, MAX, 3, MAX,
            1, 5, 0, 5, 6, 4,
            5, MAX, 5, 0, MAX, 2,
            MAX, 3, 6, MAX, 0, 6,
            MAX, MAX, 4, 2, 6, 0
    };
    Graph* G = initGraph(6);
    int* visited = (int* ) malloc(sizeof (int) * G -> vexnum);
    for (int i = 0; i < G -> vexnum; i++){
        visited[i] = 0;
    }
    creatGraph(G, (int*) arcs,"ABCDEF");
    DFS(G, visited, 0);
    printf("\n");
    for (int i = 0; i < G -> vexnum; i++){
        visited[i] = 0;
    }
    BFS(G, visited);
    printf("\n");
    kruskal(G);
    printf("\n");
}



