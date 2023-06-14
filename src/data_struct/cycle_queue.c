//
// Created by syy on 2023/6/13.
//
#include "stdlib.h"
#include "stdio.h"
#define MAXSIZE  5
typedef struct Queue{
    int rear;
    int front;
    int data[MAXSIZE];
} Queue;
Queue* InitQueue()
{
    Queue* Q = (Queue*) malloc(sizeof (Queue));
    Q -> front = Q -> rear = 0;
    return Q;
}
void PrintQueue(Queue* Q)
{
    int length = (Q -> rear - Q -> front + MAXSIZE) % MAXSIZE;
    int index = Q -> front;
    for(int i = 0; i < length; i++)
    {
        printf("%d -> ", Q -> data[index]);
        index = (index + 1) % MAXSIZE;
    }
    printf("NULL\n");
}
int isfull(Queue* Q)
{
    if (Q -> rear + 1 == Q -> front) return 1;
    else return 0;
}
int isEmpty(Queue* Q)
{
    if (Q -> front == Q -> rear) return 1;
    else return 0;
}
void push(Queue* Q, int data)
{
    if (isfull(Q)) printf("Q is full, failing to push\n");
    else
    {
        Q -> data[Q -> rear] = data;
        Q -> rear = Q -> rear + 1;
        printf("successfully pushed data\n");
    }
}
int pop(Queue* Q)
{
    if (isEmpty(Q)){
        printf("Q is empty, popping is fail\n");
        return 0;
    }
    else
    {
        int data = Q -> data[Q -> front];
        Q -> front = Q -> front + 1;
        printf("successfully popped\n");
        return data;
    }
}
int main() {
    Queue* Q = InitQueue();
    push(Q, 1);
    push(Q, 2);
    push(Q, 3);
    push(Q, 4);
    PrintQueue(Q);
    pop(Q);
    PrintQueue(Q);
    return 0;
}