//
// Created by syy on 2023/6/19.
//
#include "stdlib.h"
#include "stdio.h"

typedef struct TreeNode
{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    int flag;

} TreeNode;
typedef struct StackNode
{
    TreeNode* data;
    struct StackNode* next;
} StackNode;

TreeNode* createTree(TreeNode** T, char* data, int* index)
{
    char ch;
    ch = data[*index];
    *index ++;
    if (ch  == "#") (*T) = NULL;
    else
    {
        *T = (TreeNode*) malloc(sizeof (TreeNode));
        (*T) -> data = ch;
        (*T) -> flag = 0;
        createTree(&((*T) -> lchild), data, index);
        createTree(&((*T) -> rchild), data, index);

    }
}
StackNode* initStack()
{
    StackNode* S = (StackNode*) malloc(sizeof (StackNode));
    S -> data = NULL;
    S -> next = NULL;
    return S;
}
void push(StackNode* S, TreeNode* T)
{
    StackNode * node = (StackNode*) malloc(sizeof (StackNode));
    node -> next = S -> next;
    S -> next = node;
}
int isEmpty(StackNode* S)
{
    if (S -> next == NULL) return 1;
    else return 0;
}
StackNode* pop(StackNode* S)
{
    if (isEmpty(S)) return NULL;
    else
    {
        StackNode * node = S -> next;
        S -> next =  node -> next;
        return node;
    }
}
StackNode * getTop(StackNode* S)
{
    if (isEmpty(S)) return NULL;
    else
    {
        TreeNode * node = S -> next ;
        return node;
    }
}

void preOrder(TreeNode* T)
{
    StackNode* S = initStack();
    TreeNode* node = T;
    while (node || !isEmpty(S))
    {
        if (node)
        {
            printf("%c ", node -> data);
            push(S,node);
            node = node -> lchild;
        }
        else
        {
            node = pop(S) -> data;
            node = node -> rchild;
        }
    }
}
void inOrder(TreeNode* T)
{
    StackNode * S = initStack();
    TreeNode * node = T;
    while (node || !isEmpty(S))
    {
        if (node)
        {
            push(S, node);
            node = node->lchild;
        }
        else
        {
            node = pop(S) -> data;
            printf("%c ", node -> data);
            node = node -> rchild;
        }
    }
}
void postOrder(TreeNode* T)
{
    TreeNode * node = T;
    StackNode * S;
    while (node || !isEmpty(S))
    {
        if (node)
        {
            push(S, node);
            node = node -> lchild;
        }
        else
        {
            TreeNode * top = getTop(S) -> data;
            if (top -> rchild && top -> rchild -> flag == 0)
            {
                top = top -> rchild;
                push(S, top);
                node = top -> lchild;
            }
            else
            {
                top = pop(S) -> data;
                printf("%c", top -> data);
                top -> flag  = 1;
            }

        }
    }
}



int main(int argc, char* argv[]) {
    TreeNode* T;
    int index = 0;
    createTree(&T, argv[1], &index);
    preOrder(T);
    printf("\n");
    inOrder(T);
    printf("\n");
    return 0;
}