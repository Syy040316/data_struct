#include "stdio.h"
#include "stdlib.h"
#define True 1
#define False 0
typedef struct Node
{
    int data;
    struct Node* next;
} Node;
Node* initlink(){
    Node* L  = (Node*) malloc(sizeof (Node));
    L -> data = 0;
    L -> next = NULL;
    return L;
};
void  HeaderInsert(Node* L,int data){
    Node* node = (Node*) malloc(sizeof (node));
    node -> data = data;
    node -> next = L->next;
    L->next = node;
    L -> data ++;
}
void TailInsert(Node* L, int data){
    Node* L1 = L;
    Node* node = (Node*) malloc(sizeof (Node));
    node -> data = data;
    node -> next = NULL;
    for(int i = 0; i < L -> data; i++) L1 = L1 -> next;
    L1 -> next = node;
    L -> data ++;
}
int Delete(Node* L, int data)
{
    Node* L1 = L -> next;
    Node* L2 = L;
    while(L1)
    {
        if  (L1 -> data == data)
        {
            L2 -> next = L1->next;
            free(L1);
            L -> data --;
            return True;
        }
        L2 = L1;
        L1 = L1 -> next;
    }
    return False;
}
void PrintLinklist(Node* L)
{
    Node* L1 = L -> next;
    while (L1)
    {
        printf("%d\x20", L1 -> data);
        L1 = L1 -> next;
    }

}
int main()
{
    Node* L = initlink();
    HeaderInsert(L,2);
    TailInsert(L,3);
    HeaderInsert(L,4);
    TailInsert(L,7);
    if (Delete(L,5)) printf("success delete\n");
    else printf("failure\n");
    if (Delete(L,2)) printf("success delete\n");
    else printf("failure\n");
    PrintLinklist(L);
    return 0;
}

