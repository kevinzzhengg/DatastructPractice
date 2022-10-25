#include"list.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[]){
    Sqlist L;
    Exchar e;
    InitList(L);
    PrintList(L);
    ListDelete(L,5,e);
    PrintList(L);
    printf("\nthe delete element is :");
    Printexchar(e);
    system("pause");
    return 0;
}
