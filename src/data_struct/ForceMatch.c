//
// Created by syy on 2023/6/14.
//
#include "stdio.h"
#include "stdlib.h"
typedef struct String{
    char* data;
    int len;
} String;
String * initString()
{
    String* s = (String*) malloc(sizeof (String));
    s -> data = NULL;
    s -> len = 0;
    return 0;
}
void StringAssign(String* s, char* data)
{
    if (s -> data) free(s -> data);
    int len = 0;
    char* temp = data;
    while (* temp)
    {
        len ++;
        temp++;
    }
    if (len == 0)
    {
        s -> data =NULL;
        s -> len = 0;
    }
    else
    {
        s -> len = len;
        s -> data = (char*) malloc(sizeof (char) * (len+1));
        for (int i = 0; i < len; i++, temp++) s -> data[i] = *temp;
    }
}
void PrintString(String* s)
{
    for ( int i= 0; i < s -> len; i++) printf("%s", s -> data[i]);
    printf("\n");
}
int ForceMatch(String* master, String* sub)
{
    int i = 0, j = 0;
    while (i < master -> len && j < sub -> len)
    {
        if (master -> data[i] == sub -> data[j]) i++, j++;
        else i = i - j + 1, j = 0;
    }
    if (j == sub -> len) printf(" match success.\n");
    else printf("match fail.\n");
}
int main(int argc, char* argv[]) {
    String* s = initString();
    String* s1 = initString();
    StringAssign(s, argv[1]);
    StringAssign(s1, argv[2]);
    PrintString(s);
    PrintString(s1);
    ForceMatch(s, s1);
    return 0;
}