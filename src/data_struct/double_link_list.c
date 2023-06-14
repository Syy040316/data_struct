//
// Created by syy on 2023/6/9.
//
#include "stdio.h"
#include "stdlib.h"
#define True 1
#define False 0
typedef struct Node{
    int data;

    struct Node* next;
    struct Node* prev;
} Node;

Node* InitLink(){
    Node* L= (Node*) malloc(sizeof (Node));
    L -> data = 0;
    L -> prev = NULL;
    L -> next = NULL;
    return L;
}
void HeaderInsert(Node* L, int data)
{
    Node* node = (Node*) malloc(sizeof (Node));
    node -> data = data;
    node -> next = L -> next;
    node -> prev = L;
    L -> next = node;
    L -> data ++;
}
void TailInsert(Node* L, int data)
{
    Node* node = (Node*) malloc(sizeof (Node));
    node -> data = data;
    Node* L1 = L;
    for (int i = 0; i < L -> data; i++) L1 = L1 -> next;
    node -> next = L1 -> next;
    node -> prev = L1;
    L1 -> next = node;
    L -> data ++;
}
int Delete(Node* L, int data)
{
    Node* L1 = L;
    Node* L2 = L -> next;
    while(L2)
    {
        if (L2 -> data == data)
        {
            L1 -> next = L2 -> next;
            L2 -> next -> prev = L1;
            free(L2);
            L -> data --;
            printf("success delete\n");
            return True;
        }
        L1 = L2;
        L2 = L2 -> next;
    }
    printf("failure delete\n");
    return False;
}
void PrintLink(Node* L)
{
    Node* L1 = L -> next;
    for(int i = 0; i< L -> data; i++)
    {
        printf("%d\x20", L1 -> data);
        L1 = L1 -> next;
    }
    printf("\n");
}
int main(){
    Node* L = InitLink();
    HeaderInsert(L,2);
    PrintLink(L);
    TailInsert(L,3);
    PrintLink(L);
    HeaderInsert(L,4);
    PrintLink(L);
    TailInsert(L,7);
    PrintLink(L);
    Delete(L, 5);
    PrintLink(L);
    Delete(L,2);
    PrintLink(L);
    return 0;
}

