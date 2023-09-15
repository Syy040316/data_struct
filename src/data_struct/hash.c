//
// Created by syy on 2023/9/15.
//

# include "stdio.h"
# include "stdlib.h"

#define HashList List
#define HashList HashList
typedef struct Linklist{
    
    char data;
    struct Linklist* next;
}Linklist;
Linklist * initlist(){
    Linklist* link = (Linklist*) malloc(sizeof (Linklist));
    link -> data = 0;
    link -> next = NULL;
    return link;
}


typedef struct HashList{
    int length;
    Linklist ** data;
    int num;
}HashList;

HashList * initList(int length){
    HashList* list = (HashList*) malloc(sizeof (HashList));
    list -> length = length;
    list -> num = 0;
    list -> data = (Linklist **) malloc( sizeof (Linklist*) * length);
    for (int i = 0; i < length; i++){
        list -> data[i] = initlist();
    }
    return list;
}

int hash(int data, HashList* list){
    return data % list -> length;
}


void insert(Linklist* link, char data){
    Linklist * node = initlist();
    node -> data = data;
    while (link -> next != NULL) link = link -> next;
    link -> next = node;
}


void put(HashList* list, char data){

    int index = hash(data, list);
    insert(list->data[index],data);
    list -> num ++;
}

void printHash(HashList* list){
    for (int i = 0; i < list -> length; i++){
        while (list -> data[i] -> next != NULL){
            printf("%c \x20", list -> data[i] -> next -> data);
            list -> data[i] = list -> data[i] -> next;
        }
        printf("\n");
    }
}

int deleteHash(HashList* list, char data){
    int index = hash(data, list);
    Linklist* l1 = list -> data[index];
    Linklist* l2 = list -> data[index] -> next;
    while (l2){
        if (l2 -> data == data)
        {

            l1 -> next = l2 -> next;
            free(l2);
            return 1;
        }
        l1 = l2;
        l2 = l2 -> next;
    }
    return -1;

}


int main()
{
    HashList * list = initList(5);
    put(list, 'A');
    put(list, 'B');
    put(list, 'C');
    put(list, 'D');
    put(list, 'E');
    put(list, 'F');
    deleteHash(list, 'F');
    printHash(list);
    return 0;
}

