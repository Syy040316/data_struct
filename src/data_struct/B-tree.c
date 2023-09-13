//
// Created by syy on 2023/9/12.
//

#include "stdlib.h"
#include "stdio.h"

typedef struct Node{
    int level;
    int keyNum;
    int childNum;
    int* keys;
    struct Node* parent;
    struct Node** child;

} Node;

Node* initTree(int level){
    Node* T = (Node*) malloc(sizeof (Node));
    T -> level = level;
    T -> keyNum = 0;
    T -> childNum = 0;
    T -> parent = NULL;
    T -> keys = (int *) malloc(sizeof (int) * (level + 1));
    T -> child = (Node ** ) malloc(sizeof (Node *) * level);
    for (int i = 0; i < level; i++){
        T -> child[i]  = NULL;
        T -> keys[i] = 0;
    }
    return T;
}

int findSuiteIndex(Node* node, int data){
    int index;
    for (index = 1; index <= node -> keyNum; index++){
        if (node -> keys[index] > data) break;
    }
    return index;
}

void addData(Node* node, int data, Node** T){
    int index = findSuiteIndex(node, data);
    for(int i = node -> keyNum; i >= index; i--) node -> keys[i+1] = node -> keys[i];
    node -> keys[index] = data;
    node -> keyNum ++;
    if (node -> keyNum == node -> level){
        int mid = node -> level/2 + node -> level % 2;
        Node * lchild = initTree(node -> level);
        Node * rchild = initTree(node -> level);
        for (int i = 1; i < mid; i++){
            addData(lchild, node -> keys[i], T);
            addData(rchild, node -> keys[mid + i], T);
        }

        for (int i = 0; i < mid; i++){
            lchild -> child[i] = node -> child[i];
            if (node -> child[i] != NULL){
                node -> child[i] -> parent = lchild;
                lchild -> childNum ++;
            }
        }
        int index = 0;

        for (int i = mid; i < node -> childNum; i++){
            rchild -> child[index++] = node -> child[i];
            if (node -> child[i] != NULL){
                node -> child[i] -> parent = rchild;
                rchild->childNum ++;
            }
        }

        if (node -> parent == NULL) {
            Node* newParent = initTree(node -> level);
            addData(newParent, node -> keys[mid], T);
            newParent -> child[0] = lchild;
            newParent -> child[1] = rchild;
            newParent -> childNum = 2;
            lchild -> parent = newParent;
            rchild -> parent = newParent;
            *T = newParent;
        } else {
            int index = findSuiteIndex(node -> parent, node -> keys[mid]);
            lchild -> parent = node -> parent;
            rchild -> parent = node -> parent;
            node -> parent -> child[index - 1] = lchild;
            if (node -> parent -> child[index] != NULL){
                for (int i = node -> parent -> childNum - 1; i >= index; i--) node -> parent -> child[i+1] = node -> parent -> child[i];
            }
            node -> parent -> child[index] = rchild;
            node -> parent -> childNum ++;
            addData(node -> parent, node -> keys[mid], T);

        }
    }
}


Node* findSuiteLeafNode(Node* T, int data){
    if (T -> childNum == 0) return T;
    else{
        int index = findSuiteIndex(T, data);
        return findSuiteLeafNode(T -> child[index-1], data);
    }
}


Node* find(Node* node, int data){
    if (node == NULL) return NULL;
    for (int i = 1; i <= node -> keyNum; i++){
        if (data == node -> keys[i]) return node;
        else if (data < node -> keys[i]) return find(node -> child[i-1], data);
        else {
            if (i != node -> childNum && data < node -> keys[i + 1]) return findSuiteLeafNode(node -> child[i], data);
        }
    }
    return findSuiteLeafNode(node -> child[node -> keyNum], data);
}

void insert(Node** T, int data){
    Node* node = findSuiteLeafNode(*T, data);
    addData(node, data, T);
}

void printTree(Node* T){
    if (T != NULL){
        for (int i = 1; i <= T -> keyNum; i++) printf("%d", T -> keys[i]);
        printf("\n");
        for (int i = 0; i < T -> childNum; i++) printTree(T -> child[i]);
    }
}

int main() {
    Node* T = initTree(5);
    insert(&T, 1);
    insert(&T, 2);
    insert(&T, 6);
    insert(&T, 7);
    insert(&T, 11);
    insert(&T, 4);
    insert(&T, 8);
    insert(&T, 13);
    insert(&T, 10);
    insert(&T, 5);
    insert(&T, 17);
    insert(&T, 9);
    insert(&T, 16);
    insert(&T, 20);
    insert(&T, 3);
    insert(&T, 12);
    insert(&T, 14);
    insert(&T, 18);
    insert(&T, 19);
    insert(&T, 15);
    printTree(T);
    Node* node = find(T, 7);
    if (node) {
        for (int i = 1; i <= node -> keyNum; i++) {
            printf("%d ", node -> keys[i]);
        }
        printf("\n");
    }
    return 0;
}