#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 50
#define INITLENGTH 10

//节点数据类型的定义
typedef struct Exchar{
    //extesion of char to represent the 2 digits number.
    char num[2];
    int value;
}Exchar;

//静态顺序表的定义
typedef struct Sqlist{
    //the static list of array.
    Exchar data[MAXSIZE];
    int length;
}Sqlist;

//动态顺序表的定义
typedef struct Seqist{
    //the malloc way.
    Exchar *data;
    int MaxSize,length;
}Seqist;

//单链表的定义
typedef struct LNode{
    Exchar data;
    struct LNode *next;
}LNode,*LinkList;

//双链表定义
typedef struct  DNode{
    Exchar data;
    struct DNode *prior, *next;
}DNode,*DLinkList;

//---------------------------------------------------------------------------------
//设置节点数据信息
bool Initexchar(Exchar &c, char c1,char c2){
    //use to assign the exchar var.
    c.num[0] = c1;
    c.num[1] = c2;
    if (c1 == ' ' && c2 == ' ')
        c.value = -1;
    else c.value = (c.num[0] - '0') * 10 + c.num[1] - '0';
    return true;
};

//打印节点数据信息
void Printexchar(Exchar c){
    printf(" {");
    for (int i = 0; i < 2; i++)
        printf("%c",c.num[i]);
    printf(":%d}  ",c.value);
};
 
//快捷对于数字的转换exchar类型
Exchar Int2exchar(int integer){
    //applies to 2 digits only
    Exchar tmp;
    tmp.num[0] = '0' + integer/10;
    tmp.num[1] = '0' + integer%10;
    tmp.value = integer;
    return tmp;
};
//----------------------------------------------------------------------------------
//静态有序表初始化
bool InitList(Sqlist &L){
    for(int i = 0; i < MAXSIZE; i++)
        Initexchar(L.data[i],' ',' '); 
    for(int i = 1; i <= INITLENGTH; i++)
        L.data[i]= Int2exchar(i);
    L.length = INITLENGTH;
    return true;
};

//打印静态顺序表
void PrintList(Sqlist L){
    printf("\nprint result:\n");
    for(int i = 1; i <= L.length; i++)
        Printexchar(L.data[i]);
    printf("\nthe length of the list is: %5d", L.length);
};

//顺序表的插入
bool ListInsert(Sqlist &L, int Index, Exchar e){
    //judge whether the location is in the range of L.
    if (Index < 1 || Index > L.length)
        return false;
    //judge whether the L has enough space to insert.
    if (L.length >= MAXSIZE)
        return false;
    //running to here show that the insert can be executed.
    for (int i = L.length++; i >= Index ; i--)
        L.data[i+1] = L.data[i];
    L.data[Index] = e;
    return true;
};

//顺序表的删除
bool ListDelete(Sqlist &L, int Index, Exchar &e){
    //judge if the index is in the range of L.
    if (Index < 1 || Index > L.length) return false;
    //if in the range of L,delete it and move elements.
    e = L.data[Index];
    for (int i = Index; i < L.length; i++)
        L.data[i] = L.data[i+1];
    L.length--;
    return true;
};

//顺序表的查找索引
int LocateElem(Sqlist L,Exchar e){
    //the simplist way to find the element.
    for (int i = 1; i <= L.length; i++)
        if (L.data[i].value == e.value)
            return i;
    return -1;
};
//----------------------------------------------------------------------------------
//初始化带头节点的单链表。头节点不存储信息
LinkList InitLinklist(){
    LinkList lhead;
    lhead = (LinkList)malloc(sizeof(LNode));
    Initexchar(lhead->data, 'L', 'H');
    lhead->next = NULL;
    return lhead;
};

//打印结点信息
void PrintLNode(LinkList L){
    if (L == NULL){
        printf("the node is not exsist.");
        return;
    }    
    Printexchar(L->data);
};

//打印整条链表
bool PrintLinkList(LinkList L){
    printf("\nthe linklist is :\n");
    LinkList p = L;
    if(p == NULL) return false;
    do{
        PrintLNode(p);
        p = p->next;
    } while (p != NULL);   
    return true;
};

//返回链表的长度
int LinkList_len(LinkList L){
    int count = 0;
    LinkList p = L;
    if(!p) return -1;
    while(p->next){
        count++;
        p = p->next;
    }
    return count;
};

//头插法建立单链表,一次输入一个
LinkList List_HeadInsert(LinkList &L){
    LinkList p;
    int num;
    printf("please input the values that you want to insert(999 means end):\n");
    scanf("%d",&num);
    while(num != 999){
        p = (LinkList)malloc(sizeof(LNode));\
        //注意顺序
        p->next = L->next;
        p->data = Int2exchar(num);
        L->next = p;
        scanf("%d",&num);
    }
    return L;
};

//采用尾插法建立单链表
LinkList List_TailInsert(LinkList &L){
    LinkList p,lrear;
    int num;
    lrear = L;
    printf("please input the values that you want to insert(999 means end):\n");
    scanf("%d",&num);
    while(num != 999){
        p = (LinkList)malloc(sizeof(LNode));
        lrear->next = p;
        lrear = p;
        p->data = Int2exchar(num);
        p->next = NULL;
        scanf("%d",&num);
    }
    return L;
};

//按序号查找结点的值
LNode *GetElem(LinkList L, int i){
    LinkList p = L;
    int count = 0;
    while(count != i){
        p = p->next;
        count++;
        if(p == NULL){
            printf("\nwrong index!\n");
            break;
        }
    }
    return p;
};

//按值查找表表结点,返回第一个等值结点
LNode *LocateElem(LinkList L, Exchar e){
    LinkList p = L;
    do{
        p = p->next;
        if (p == NULL){
            printf("\nthe value is not exsist!\n");
            break;
        }
    } while (p->data.value != e.value);
    return p;
};

//---------------------------------------------------------
//打印结点信息(双链表重载)
void PrintLNode(DLinkList L){
    if (L == NULL){
        printf("the node is not exsist.");
        return;
    }    
    Printexchar(L->data);
};

//打印整条链表（双链表重载）
bool PrintLinkList(DLinkList L){
    printf("\nthe linklist is :\n");
    DLinkList p = L;
    if(p == NULL) return false;
    do{
        PrintLNode(p);
        p = p->next;
    } while (p != NULL);   
    return true;
};

//双链表的初始化
DLinkList InitDLinkList(DLinkList &L){
    DLinkList p = (DLinkList)malloc(sizeof(DNode));
    Initexchar(p->data,'L','H');
    p->prior = NULL;
    p->next = NULL;
    return p;
};

//双链表的插入（前插）
DLinkList DLinkList_Insert(DLinkList &L, int index, Exchar e){
    DLinkList p = (DLinkList)malloc(sizeof(DNode));
    DLinkList q = GetElem(L,index-1);
    p->data = e;
    p->prior = q;
    p->next = q->next;
    q->next = p;
    if(p->next) p->next->prior = p;
    return L;
};

//双链表的删除（删除第一个值为给定值的结点）
DLinkList DLinkList_Delete(DLinkList &L, Exchar e){
    DLinkList p = LocateElem(L,e);
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return L;
};

//按序查找的一个重载，适用于双向链表，方法为遍历，较为低效
DNode *GetElem(DLinkList L, int i){
    DLinkList p = L;
    int count = 0;
    while(count != i){
        p = p->next;
        count++;
        if(p == NULL){
            printf("\nwrong index!\n");
            break;
        }
    }
    return p;
};

//按值查找表表结点,返回第一个等值结点(双链表重载)
DNode *LocateElem(DLinkList L, Exchar e){
    DLinkList p = L;
    do{
        p = p->next;
        if (p == NULL){
            printf("\nthe value is not exsist!\n");
            break;
        }
    } while (p->data.value != e.value);
    return p;
};
//-----------------------------------------------------------------
//循环链表和循环双链表和静态链表懒得写了，就这样吧
//--end--