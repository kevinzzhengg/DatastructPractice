#include"list.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    Sqlist L;
    InitList(L);
    PrintList(L);
    Exchar e;
    Initexchar(e,'0','5');
    Printexchar(e);
    int index = LocateElem(L,e);
    if (index == -1) printf("\nfail to locate!\n");
    else printf("\nthe index of the element is:%5d\n",index);
    return 0;
}
