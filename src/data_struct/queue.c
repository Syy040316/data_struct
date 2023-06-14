//
// Created by syy on 2023/6/12.
//
#include "stdio.h"
#include "stdlib.h"
typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* InitQueue()
{
    Node* Q = (Node*) malloc(sizeof (Node));
    Q -> data = 0;
    Q -> next = Q;
    Q -> prev = Q;
    return Q;
}
void Push(Node* Q,int data)
{
    Node* node = (Node*) malloc(sizeof (Node));
    node -> data = data;
    Q -> next -> prev = node;
    node -> next = Q -> next;
    node -> prev = Q;
    Q -> next = node;
    Q -> data ++;
}
int IsEmpty(Node* Q)
{
    if (Q -> data == 0 || Q -> next == Q) return 1;
    else return 0;
}
int Pop(Node* Q)
{
    if (IsEmpty(Q)) return 0;
    Node* Q1 = Q ->prev;
    int data = Q1 -> data;
    Q1 -> prev -> next = Q;
    Q -> prev = Q1 -> prev;
    free(Q1);
    Q -> data --;
    return data;
}
void PrintQue(Node* Q)
{
    Node* Q1 = Q -> next;
    while (Q1 != Q)
    {
        printf("%d\x20", Q1 -> data);
        Q1  = Q1 -> next;
    }
    printf("\n");
}
int main() {
    Node* Q = InitQueue();
    Push(Q, 1);
    Push(Q, 2);
    Push(Q, 3);
    Push(Q, 4);
    PrintQue(Q);
    printf("dequeue = %d\n", Pop(Q));
    printf("dequeue = %d\n", Pop(Q));
    PrintQue(Q);
    return 0;
}
