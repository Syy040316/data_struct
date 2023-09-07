//
// Created by syy on 2023/6/23.
//
#include "stdio.h"
#include "stdlib.h"
typedef struct TreeNode
{
    char data;
    struct TreeNode* lchild, *rchild, *parent;
    int ltag, rtag
} TreeNode;

TreeNode* createTree(TreeNode** T, char* data, int* index, TreeNode* parent)
{
    char ch;
    ch = data[*index];
    index++;
    if (ch == "#") (*T) = NULL;
    else
    {
        (*T) = (TreeNode*) malloc(sizeof (TreeNode));
        (*T) -> data = ch;
        (*T) -> ltag = 0;
        (*T) -> rtag = 0;
        (*T) -> parent = parent;
        createTree(&((*T) -> lchild), data, index, *T);
        createTree(&((*T) -> rchild), data, index, *T);
    }
}

void postThreadTree(TreeNode* T, TreeNode* pre)
{
    postThreadTree(T -> lchild, pre);
    postThreadTree(T -> rchild, pre);
    if (T)
    {
        if (T -> lchild == NULL) T -> ltag = 1, T -> lchild = pre;
        if (pre != NULL && pre -> rchild == NULL)
        {
            pre -> rtag = 1;
            pre -> rchild = T;
        }
        pre = T;
    }
}

TreeNode* getFirst(TreeNode* T)
{
    while (T -> ltag == 0) T = T -> lchild;
    if (T -> rtag == 0) return getFirst(T -> rchild);
    else return T;
}
TreeNode* getNext(TreeNode* T)
{
    if (T -> rtag == 1) return T -> rchild;
    else
    {
        if (T -> parent == NULL) return NULL;
        else if (T -> parent -> rchild == T) return T -> parent;
        else
        {
            if (T -> parent -> ltag == 0) return T -> rchild;
            else return T -> parent;
        }
    }
}

int main(int argc, char* argv[]) {
    TreeNode* T;
    TreeNode* pre = NULL;
    int index = 0;
    createTree(&T, argv[1], &index, NULL);
    postThreadTree(T, &pre);
    for (TreeNode* node = getFirst(T); node != NULL; node = getNext(node)) {
        printf("%c ", node -> data);
    }
    printf("\n");
    return 0;
}