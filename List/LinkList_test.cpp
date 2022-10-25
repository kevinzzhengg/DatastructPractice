#include"list.h"

int main(int argc, char const *argv[])
{
    LinkList L = InitLinklist();
    L = List_TailInsert(L);
    PrintLNode(LocateElem(L,Int2exchar(3)));
    PrintLinkList(L);
    return 0;
}
