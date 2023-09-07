//
// Created by syy on 2023/6/25.
//
#include "stdlib.h"
#include "stdio.h"

typedef struct TreeNode
{
    int weight, lchild, rchild, parent;

} TreeNode;

typedef struct HFTree
{
    TreeNode* data;
    int length;
} HFTree;

HFTree* initTree(int* weight, int length)
{
    HFTree* T = (HFTree*) malloc(sizeof (HFTree));
    T -> length = length;
    T -> data = (TreeNode*) malloc(sizeof (TreeNode) * (2 * length - 1));
    for (int i = 0; i < length; i++)
    {
        T -> data[i].weight = weight[i];
        T -> data[i].lchild = -1;
        T -> data[i].rchild = -1;
        T -> data[i].parent = 0;
    }
    return T;
}

int* selectMin(HFTree* T)
{
    int Min = 10000, SecondMin = 10000, minIndex, secondIndex;


    for (int i = 0; i < T -> length; i++)
    {
        if (T -> data[i].parent == 0)
        {
            if (T -> data[i].weight < Min)
            {
                Min = T -> data[i].weight;
                minIndex = i;
            }
        }

    }
    for (int i = 0; i < T -> length; i++)
    {
        if (T -> data[i].parent == 0 && i != minIndex)
        {
            if (T -> data[i].weight < SecondMin )
            {
                SecondMin = T -> data[i].weight;
                secondIndex = i;
            }
        }

    }
    int* res = (int*) malloc(sizeof (int) * 2);
    res[0] = minIndex;
    res[1] = secondIndex;
    return res;
}

void createHFTree(HFTree* T)
{
    int minIndex, secondIndex;
    int* res;
    int length = T -> length * 2 - 1;
    for (int i = T -> length; i < length; i++)
    {
        res = selectMin(T);
        minIndex = res[0], secondIndex = res[1];
        T -> data[i].weight = T -> data[minIndex].weight + T -> data[secondIndex].weight;
        T -> data[i].parent = 0;
        T -> data[i].lchild = minIndex;
        T -> data[i].rchild = secondIndex;
        T -> data[minIndex].parent = i;
        T -> data[secondIndex].parent = i;
        T -> length++;
    }

}

void preOrder(HFTree* T, int index) {
    if (index != -1) {
        printf("%d ", T -> data[index].weight);
        preOrder(T, T -> data[index].lchild);
        preOrder(T, T -> data[index].rchild);
    }
}

int main() {
    int weight[7] = {5,1,3,6,11,2,4};
    HFTree* T = initTree(weight, 7);
    createHFTree(T);
    preOrder(T, T -> length - 1);
    printf("\n");
    return 0;
}

