#include "stdlib.h"
#include "stdio.h"
#define False 0
#define True 1
typedef struct Node
{
    int data;
    struct Node* next;
} Node;
Node* initNode()
{
    Node* L = (Node*)malloc(sizeof(Node));
    L -> data = 0;
    L -> next = L;
    return L;
}
void HeaderInsert(Node* L, int data){

    Node * node = (Node*) malloc(sizeof (Node));
    node -> data = data;
    node -> next = L -> next;
    L -> next = node;
    L -> data ++;
}
void  TailInsert(Node* L, int data){
    Node* L1 = L;
    Node* node = (Node*) malloc(sizeof (Node));
    node -> data = data;
    while (L1 -> next != L) L1  = L1 -> next;
    node -> next = L;
    L1 ->next = node;
    L -> data ++;
}
int Delete(Node* L, int data){
    Node* L1 = L ;
    Node* L2 = L -> next;
    while(L2 != L)
    {
        if (L2 -> data == data)
        {
            L1 -> next = L2 -> next;
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
void Print_List(Node* L){
    Node* L1 = L -> next;
    while(L1 != L) {
        printf("%d\x20", L1 -> data);
        L1  = L1 -> next;
    }
    printf("\n");
}
int main(){
    Node* L = initNode();
    HeaderInsert(L,2);
    Print_List(L);
    TailInsert(L,3);
    Print_List(L);
    HeaderInsert(L,4);
    Print_List(L);
    TailInsert(L,7);
    Print_List(L);
    Delete(L, 5);
    Print_List(L);
    Delete(L,2);
    Print_List(L);
    return 0;
}


