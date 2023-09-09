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

void floyd(Graph* G){
    int d[G -> vexnum][G -> vexnum];
    int p[G -> vexnum][G -> vexnum];
    for (int i = 0; i< G -> vexnum; i++){
        for (int j = 0; j < G -> vexnum; j++) {
            d[i][j] = G->arcs[i][j];
            if (G->arcs[i][j] == MAX) {
                p[i][j] = -1;
            } else p[i][j] = 1;
        }
    }

    for (int i = 0; i < G -> vexnum; i++){
        for (int j = 0; j < G -> vexnum; j++){
            for(int k = 0; k < G -> vexnum; k++){
                if (d[j][i] + d[i][k] < d[j][k]){
                    d[j][k] = d[j][i] + d[i][k];
                    p[j][k] = p[i][k];
                }
            }
        }
    }
    for (int i = 0; i < G -> vexnum; i++){
        for (int j = 0; j < G -> vexnum; j++)
            printf("%c -> %c, length = %d\n", G -> vexs[i] , G -> vexs[j], d[i][j]);

    }

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
    int arcs[7][7] = {
            0, 12, MAX, MAX, MAX, 16, 14,
            12, 0, 10, MAX, MAX, 7, MAX,
            MAX, 10, 0, 3, 5, 6, MAX,
            MAX, MAX, 3, 0, 4, MAX, MAX,
            MAX, MAX, 5, 4, 0, 2, 8,
            16, 7, 6, MAX, 2, 0, 9,
            14, MAX, MAX, MAX, 8, 9, 0
    };
    Graph* G = initGraph(7);
    int* visited = (int* ) malloc(sizeof (int) * G -> vexnum);
    for (int i = 0; i < G -> vexnum; i++){
        visited[i] = 0;
    }
    creatGraph(G, (int*) arcs,"ABCDEFG");
    DFS(G, visited, 0);
    printf("\n");
    for (int i = 0; i < G -> vexnum; i++){
        visited[i] = 0;
    }
    BFS(G, visited);
    printf("\n");
    floyd(G);
    printf("\n");
}



