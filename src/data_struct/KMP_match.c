//
// Created by syy on 2023/6/15.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct String{
    int len;
    char* data;
} String;
String* initString()
{
    String* s = (String*) malloc(sizeof (String));
    s -> data = NULL;
    s -> len = 0;
    return s;
}
void stringAssign(String* s, char* data)
{
    if (s -> data) free(s -> data);
    int len = 0;
    char* temp = data;
    while (* temp)
    {
        len ++;
        temp++;
    }
    s -> len = len;
    s -> data = (char*) malloc(sizeof (char) * (len -1));
    for (int i = 0; i < len; i ++ ,temp++) s -> data[i] = * temp;
}
void printString(String* s)
{
    for ( int i = 0; i< s -> len; i ++ ) printf("%s", s -> data[i]);
    printf("\n");
}
int* getNext(String * s)
{
    int * next = (int*) malloc(sizeof (int) * (s -> len + 1));
    int i = 0;
    int j = -1;
    while (i < s -> len)
    {
        if (j == -1 || s-> data[i] == s -> data[j])
        {
            i ++ ;
            j ++ ;
            next[i] = j;
        } else j = next[j];
    }
    return next;
}
void printNext(int* next, int len)
{
    for(int i = 0; i< len; i++) printf("%d\x20", next[i] + 1);
    printf("\n");
}
void KMP_match(String* master, String* sub, int* next)
{
    int i = 0, j = 0;
    while ( i < master -> len && j < sub -> len )
    {
        if (j == -1 || master -> data[i] == sub -> data[j])
        {
            i ++ ;
            j ++ ;
            next[i] = j;
        } else j = next[j];
    }
    if (j == sub -> len - 1) printf("match successful\n");
    else printf("match failed\n");
}
int main(int argc, char* argv[]) {
    String* s = initString();
    String* s1 = initString();
    stringAssign(s, argv[1]);
    printString(s);
    stringAssign(s1, argv[2]);
    printString(s1);
    int* next = getNext(s1);
    printNext(next,s1 -> len);
    KMP_match(s, s1, next);
    String* name = initString();
    stringAssign(name, "shenyouyue");
    printNext(getNext(name), name -> len);
    return 0;
}