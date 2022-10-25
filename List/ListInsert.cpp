#include"list.h"
#include<stdio.h>

int main(int argc, char const *argv[]){
    Sqlist L;
    Exchar tmp;
    tmp.num[0] = 'O';
    tmp.num[1] = 'K';
    InitList(L);
    PrintList(L);
    bool err = ListInsert(L, 5,tmp);
    if (err == 0) return 1;
    else {
        printf("\n");
        PrintList(L);
        return 0;
    } 
}