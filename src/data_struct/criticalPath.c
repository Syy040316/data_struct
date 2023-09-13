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
}
int* findInDegrees(Graph* G){
    int* InDegrees = (int *) malloc(sizeof (int) * G -> vexnum);
    for (int i = 0; i < G -> vexnum; i++ ) InDegrees[i] = 0;
    for (int i = 0; i < G -> vexnum; i++){
        for (int j = 0 ; j < G -> vexnum; j++){
            if (G -> arcs[i][j] > 0 && G -> arcs[i][j] < MAX)
                InDegrees[j] ++;
        }
    }
    return InDegrees;
}
int* topologicalSort(Graph* G){
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

            if (G -> arcs[vex][i] > 0 && G -> arcs[vex][i]  < MAX){
                InDegrees[i] --;
                if (InDegrees[i] == 0) push(stack,i);
            }

        }
    }
    for (int i = 0; i < G -> vexnum; i++ ){
        printf("%c\x20", G -> vexs[top[i]]);
    }
    printf("\n");
    return top;
}
int getIndex(Graph* G, int* top, int i){
    int j = 0;
    for (j = 0; j < G -> vexnum; j++){
        if (top[j] == i) break;
    }
    return j;
}
void criticalPath(Graph* G){
    int* top = topologicalSort(G);
    int* early = (int*) malloc(sizeof (int) * G -> vexnum);
    int* late = (int*) malloc(sizeof (int) * G -> vexnum);
    for (int i = 0; i < G -> vexnum; i++){
        early[i] = 0;
        late[i] = 0;
    }
    for (int i = 0; i < G -> vexnum; i++){
        int max = 0;
        for (int j = 0; j < G -> vexnum; j++){
             if (G -> arcs[j][top[i]]  > 0 && G -> arcs[j][top[i]] < MAX){
                 int index = getIndex(G, top, j);
                 if (G -> arcs[j][top[i]] + early[index] > max){
                     max = G -> arcs[j][top[i]] + early[index];
                 }
             }
        }
        early[i] = max;
    }
    for (int i = 0; i< G -> vexnum; i++) printf("%d\x20", early[i]);
    printf("\n");
    late[G -> vexnum - 1] = early[G -> vexnum - 1];
    for (int i = G -> vexnum - 2; i >= 0; i--){
        int min = MAX;
        for (int j = 0; j < G -> vexnum; j++){
            if (G -> arcs[top[i]][j] > 0 && G -> arcs[top[i]][j] < MAX){
                int index = getIndex(G, top, j);
                if (late[index] - G -> arcs[top[i]][j] < min)
                    min = late[index] - G -> arcs[top[i]][j];
            }
        }
        late[i] = min;
    }

    for (int i = 0; i< G -> vexnum; i++) printf("%d\x20", late[i]);
    printf("\n");

    for (int i = 0; i < G -> vexnum; i++){
        for (int j = 0; j < G -> vexnum; j++){
            if (G -> arcs[i][j] > 0 && G -> arcs[i][j] < MAX){
                int start = getIndex(G, top, i);
                int end = getIndex(G, top, j);
                if (late[end] - early[start] - G -> arcs[i][j] == 0) printf("start = %d, end = %d\n", i, j );
            }
        }
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

int main()
{
    int arcs[9][9] = {
            0, 6, 4, 5, MAX, MAX, MAX, MAX, MAX,
            MAX, 0, MAX, MAX, 1, MAX, MAX, MAX, MAX,
            MAX, MAX, 0, MAX, 1, MAX, MAX, MAX, MAX,
            MAX, MAX, MAX, 0, MAX, 2, MAX, MAX, MAX,
            MAX, MAX, MAX, MAX, 0, MAX, 9, 7, MAX,
            MAX, MAX, MAX, MAX, MAX, 0, MAX, 4, MAX,
            MAX, MAX, MAX, MAX, MAX, MAX, 0, MAX, 2,
            MAX, MAX, MAX, MAX, MAX, MAX, MAX, 0, 4,
            MAX, MAX, MAX, MAX, MAX, MAX, MAX, MAX, 0
    };
    Graph* G = initGraph(9);
    int* visited = (int* ) malloc(sizeof (int) * G -> vexnum);
    for (int i = 0; i < G -> vexnum; i++) visited[i] = 0;
    creatGraph(G, (int*) arcs,"012345678");
    DFS(G, visited, 0);
    printf("\n");
    criticalPath(G);

}



