//
// Created by syy on 2023/6/23.
//
#include "stdlib.h"
#include "stdio.h"
typedef struct TreeNode
{
    int data;
    struct TreeNode *lchild, *rchild;
} TreeNode;

TreeNode* bstSearch(TreeNode* T, int data)
{
    if (T == NULL) return NULL;
    else
    {
        if (T -> data == data) return T;
        else if (T -> data > data) return bstSearch(T -> lchild, data);
        else return bstSearch(T -> rchild, data);
    }
}
void bstInsert(TreeNode** T, int data)
{
    if (*T == NULL)
    {
        (*T) = (TreeNode*) malloc(sizeof (TreeNode));
        (*T) -> data = data;
        (*T) -> lchild = NULL;
        (*T) -> rchild = NULL;
    }
    else
    {
        if ((*T) -> data == data) return;
        else if ((*T) -> data > data)  bstInsert(&((*T) -> lchild), data);
        else bstInsert(&((*T) -> rchild), data);
    }
}

void preOrder(TreeNode* T)
{
    if (T)
    {
        printf("%d\x20", T -> data);
        preOrder(T -> lchild);
        preOrder(T -> rchild);
    }
}

int main() {
    TreeNode* T = NULL;
    int nums[6] = {8, 6, 10, 9, 11, 23};
    for (int i = 0; i < 6; i++) {
        bstInsert(&T, nums[i]);
    }
    preOrder(T);
    printf("\n");
}