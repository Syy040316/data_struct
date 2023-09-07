//
// Created by syy on 2023/6/25.
//
#include "stdio.h"
#include "stdlib.h"

typedef struct TreeNode
{
    int data;
    int height;
    struct TreeNode *lchild, *rchild;
} TreeNode;
int max(int i, int j){
    return i > j ? i : j;
}
int getHeight(TreeNode* node)
{
    return node ? node -> height : 0;
}

void rrRotation(TreeNode* T, TreeNode** root)
{
    TreeNode* temp = T -> rchild;
    T -> rchild = temp -> lchild;
    temp -> lchild = T;
    T -> height = max(getHeight(T -> lchild), getHeight(T -> rchild)) + 1;
    temp -> height = max(getHeight(temp -> lchild), getHeight(temp -> rchild)) + 1;
    *root = temp;
}
void llRotation(TreeNode* node , TreeNode** root)
{
    TreeNode* temp = node -> lchild;
    node -> lchild = temp -> rchild;
    temp -> rchild = node;
    node -> height = max(getHeight(node -> lchild), getHeight(node -> rchild)) + 1;
    temp -> height = max(getHeight(temp -> lchild), getHeight(temp -> rchild)) + 1;
    *root = temp;
}

void avlInsert(TreeNode** T, int data)
{
    if (*T == NULL)
    {
        (*T) = (TreeNode*) malloc(sizeof (TreeNode));
        (*T) -> data = data;
        (*T) -> lchild = NULL;
        (*T) -> rchild = NULL;
        (*T) -> height = 0;
    }
    else if (data < (*T) -> data) {
        avlInsert(&(*T)->lchild, data);
        int lHeight = getHeight((*T)->lchild);
        int rHeight = getHeight((*T)->rchild);
        if (lHeight - rHeight == 2) {
            if (data < (*T) -> lchild -> data) llRotation(*T, T);
            else rrRotation((*T)->lchild, &(*T)->lchild), llRotation(*T, T);
        }
    }
    else if (data > (*T) -> data)
    {
        avlInsert(&(*T) -> rchild, data);
        int lHeight = getHeight((*T) -> lchild);
        int rHeight = getHeight((*T) -> rchild);
        if (rHeight - lHeight == 2){
            if (data > (*T) -> rchild -> data) rrRotation(*T, T);
            else llRotation((*T) -> rchild, &(*T) -> rchild), rrRotation(*T, T);
        }
    }

    (*T) -> height = max(getHeight((*T) -> lchild), getHeight((*T) -> rchild)) + 1;
}

void preOrder(TreeNode* T) {
    if (T) {
        printf("%d ", T -> data);
        preOrder(T -> lchild);
        preOrder(T -> rchild);
    }
}

int main() {
    TreeNode* T = NULL;
    int nums[5] = {1,8,6,7,10};
    for (int i = 0; i < 5; i++) {
        avlInsert(&T, nums[i]);

    }
    preOrder(T);
    printf("\n");
}