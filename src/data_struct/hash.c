//
// Created by syy on 2023/9/15.
//

# include "stdio.h"
# include "stdlib.h"

typedef struct List{
    int length;
    char* data;
    int num;
}List;

List * initList(int length){
    List* list = (List*) malloc(sizeof (List));
    list -> length = length;
    list -> num = 0;
    list -> data = (char*) malloc( sizeof (char) * length);
    for (int i = 0; i < length; i++){
        list -> data[i] = 0;
    }
    return list;
}
int hash(int data, List* list){
    return data % list -> length;
}

int put(List* list, char data){
    if (list -> num == list -> length) return -1;
    int index = hash(data, list);
    if (list -> data[index] != 0){
        int count = 1;
        while (list -> data[index] != 0){
            index = hash(hash(data, list) + count, list);
            count ++;
        }

    }
    list -> data[index] = data;
    list -> num ++;
}


int main()
{
    List * list = initList(5);
    put(list, 'A');
    put(list, 'B');
    put(list, 'C');
    put(list, 'D');
    put(list, 'E');
    put(list, 'F');
    printf("put(list, 'G') = %d\n",put(list, 'G'));
   for (int i = 0; i < list -> num; i++) printf ("%c\n", list -> data[i]);
    return 0;
}