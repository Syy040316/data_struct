//
// Created by syy on 2023/6/11.
//
#include "stdlib.h"
#include "stdio.h"


typedef struct Node{
    int data;
    struct Node* next;
} Node;
Node* InitStack()
{
    Node* L = (Node*) malloc(sizeof (Node));
    L -> data = 0;
    L -> next = NULL;
    return L;
}
void push(Node* L, int data)
{
    Node* node = (Node*) malloc(sizeof (Node));
    node -> data = data;
    node -> next = L -> next;
    L -> next = node;
    L -> data ++;
}
int pop(Node* L)
{
    if (L -> data == 0) return 0;

    Node* node = L -> next;
    int data = node-> data;
    L -> next = node -> next;
    L -> data --;
    free(node);
    return data;
}
int IsEmpty(Node* L)
{
    if (L -> data == 0) return 0;
    else return 1;
}
void PrintStack(Node* L)
{
    Node* L1 = L -> next;
    for(int i = 0; i< L -> data; i++)
    {
        printf("%d\x20", L1 -> data);
        L1 = L1 -> next;
    }
    printf("\n");
}
int main() {
    Node *stack = InitStack();
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);
    PrintStack(stack);
    printf("pop = %d\n", pop(stack));
    PrintStack(stack);
}