//
// Created by syy on 2023/6/22.
//
#include "stdlib.h"
#include "stdio.h"

typedef struct TreeNode
{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    int ltag, rtag;
} TreeNode;

TreeNode * createTree(TreeNode** T, char* data, int* index)
{
    char ch;
    ch = data[* index];
    index ++;
    if ( ch == '3') *T = NULL;
    else
    {
        *T = (TreeNode*) malloc(sizeof (TreeNode));
        (*T) -> data = ch;
        (*T) -> ltag = 0;
        (*T) -> rtag = 0;
        createTree(&((*T) -> lchild), data, index);
        createTree(&((*T) -> rchild), data, index);
    }
}
TreeNode * getNext(TreeNode* node)
{
    if (node -> ltag == 1 || node -> rtag == 1) return node -> rchild;
    else return node -> lchild;
}
void preThreadTree(TreeNode* T, TreeNode** pre)
{
    if (T)
    {
        if (T -> lchild == NULL) T -> ltag = 1, T -> lchild = *pre;
        if ((*pre) != NULL && (*pre) -> rchild == NULL )
        {
            (*pre) -> rtag = 1;
            (*pre) -> rchild = T;
        }
        *pre = T;
        if ( T -> lchild) preThreadTree(T -> lchild, pre);
        preThreadTree(T -> rchild, pre);
    }

}

int main(int argc, char* argv[]) {
    TreeNode* T;
    TreeNode* pre = NULL;
    int index = 0;
    createTree(&T, argv[1], &index);
    preThreadTree(T, &pre);
    pre -> rtag = 1;
    pre -> rchild = NULL;
    for (TreeNode* node = T; node != NULL; node = getNext(node)) {
        printf("%c ", node -> data);
    }
    printf("\n");
    return 0;
}