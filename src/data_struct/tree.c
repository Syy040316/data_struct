//
// Created by syy on 2023/6/17.
//
#include "stdlib.h"
#include "stdio.h"

typedef struct TreeNode{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
} TreeNode;

void createTree(TreeNode** T, char* data, int* index) {
    char ch;
    ch = data[*index];
    *index++;
    if (ch == '#') (*T) = NULL;
    else {

        *T = (TreeNode *) malloc(sizeof(TreeNode));
        (*T)->data = ch;
        createTree(&((*T)->lchild), data, index);
        createTree(&((*T)->rchild), data, index);
    }
}

void preOrder(TreeNode* T)
{
    if ( T == NULL) return;
    else
    {
        printf("%c", T -> data);
        preOrder(T -> lchild);
        preOrder(T -> rchild);
    }
}
void inOrder(TreeNode* T)
{
    if (T == NULL) return;
    else
    {
        inOrder( T -> lchild);
        printf("%c", T -> data);
        inOrder(T -> rchild);
    }
}

void postOrder(TreeNode* T)
{
    if (T ==NULL) return ;
    else
    {
        postOrder(T -> lchild);
        postOrder(T -> rchild);
        printf("%c", T -> data);
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
    postOrder(T);
    printf("\n");
    return 0;
}
