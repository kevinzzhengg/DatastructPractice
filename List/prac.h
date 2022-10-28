#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAXLENGTH 30

//using namespace std;

//--------------------------------------
//定义结构体区

//结点元素
typedef struct Element
{
    char str[4] = {'v','a','r','\0'};
    int value = -1;
    int weight = 0;
}Element;

//顺序表定义
typedef struct Sqlist
{
    Element data[MAXLENGTH+1]; //保留0号索引
    int length = 0; //初始表为空
}Sqlist;

//单链表定义
typedef struct LNode
{
    Element data;
    struct LNode *next;
}LNode,*LinkList;

//--------------------------------------
//基础操作函数区

//顺序表区
//打印顺序表
void PrintSqlist(Sqlist L)
{
    if (L.length == 0)
    {
        printf("\nthe list is empty!\n");
        return;
    }
    printf("\nthe list is:\n");
    for (int i = 1; i <= L.length; i++)
        printf(" {%s(%d):%2d} ",L.data[i].str, L.data[i].weight,L.data[i].value);
}
//生成顺序表(有序)
bool Init_Sqlist(Sqlist &L,int length, int begin = 1,int step = 1,bool SET_ZERO = false)
{
    if (length > MAXLENGTH)
        return false;
    
    L.length = length;
    for (int i = 1; i <= length; i++){
        L.data[i].str[0] = 'v';
        L.data[i].str[1] = 'a';
        L.data[i].str[2] = 'r';
        L.data[i].str[3] = '\0';
        L.data[i].value = begin+(i-1)*step;
        if (SET_ZERO) L.data[i].weight = 0;
        else L.data[i].weight = 1;
    } 
    L.data[0].value = -999;
    L.data[0].weight = 0;
    return true; 
}
//生成顺序表（随机排列）
bool Init_Sqlist_Random(Sqlist &L, int length,int start = 1, int end = 10)
{
    srand((unsigned int)time(NULL));
    if (length > MAXLENGTH)
        return false;
    L.length = length;
    for (int i = 1; i <= length; i++)
    {
        L.data[i].str[0] = 'v';
        L.data[i].str[1] = 'a';
        L.data[i].str[2] = 'r';
        L.data[i].str[3] = '\0';
        L.data[i].value = rand() % (end - start + 1)  + start;  //范围根据自己需要修改
        L.data[i].weight = 1;
    }
    L.data[0].value = -999;
    L.data[0].weight = 0 ;
    return true;
}
//顺序表插入
bool Sqlist_Insert(Sqlist &L, int index , int value)
{
    //judge whether the location is in the range of L.
    if (index < 1 || index > L.length + 1)
    {
        printf("\nthe input is illegal! \n");
        return false;
    }
    //judge whether the L has enough space to insert.
    if (L.length >= MAXLENGTH)
    {
        printf("\nthe list has no space more!\n");
        return false;
    }
       
    //running to here show that the insert can be executed.
    for (int i = ++L.length; i > index ; i--)
        L.data[i].value = L.data[i-1].value;
    L.data[L.length].weight = 1;
    L.data[index].value = value;
    return true;
}
//顺序表的折半查找(客制化版)
int Sqlist_bisearch(Sqlist L, int value, int begin, int end)
{
    /*该二分查找做了些修改，如果找到了就返回索引，如果没有找到就返回插入的位置*/
    if (L.data[(begin + end)/2].value < value && begin < end -1)
        return Sqlist_bisearch(L,value,(begin + end)/2,end);
    else if (L.data[(begin + end)/2].value > value && begin < end -1)
        return Sqlist_bisearch(L,value,begin,(begin + end)/2-1);
    else if (L.data[begin].value >= value)
        return begin;
    else if (L.data[begin].value < value && L.data[end].value >= value)
        return end;
    else return end + 1;
}

//链表区
//打印单个结点
void PrintLNode(LinkList p)
{
    if (p == NULL){
        printf("the node is not exsist.");
        return;
    }    
    printf("-{%s:%2d}-",p->data.str,p->data.value);
}
//打印单链表
bool PrintLinkList(LinkList L)
{
    if (L == NULL)
    {
        printf("\nthe head node is not existed！\n");
        return false;
    }
    
    printf("\nthe linklist is :\n");
    LinkList p = L;
    if(p == NULL) return false;
    do{
        PrintLNode(p);
        p = p->next;
    } while (p != NULL);   
    printf("-NULL\n");
    return true;
}
//初始化链表头结点
LinkList InitLinklist()
{
    LinkList lhead;
    lhead = (LinkList)malloc(sizeof(LNode));
    lhead->data.str[0] = 'h';
    lhead->data.str[1] = 'e';
    lhead->data.str[2] = 'a';
    lhead->data.str[3] = 'd';
    lhead->data.value = 0;
    lhead->next = NULL;
    return lhead;
};
//采用尾插法建立单链表
LinkList List_TailInsert(LinkList L, int length)
{
    LinkList p,lrear;
    lrear = L;
    for (int i = 1; i <= length; i++)
    {
        p = (LinkList)malloc(sizeof(LNode));
        lrear->next = p;
        lrear = p;
        p->data.str[0] = 'v';
        p->data.str[1] = 'a';
        p->data.str[2] = 'r';
        p->data.str[3] = '\0';
        p->data.value = i;
        p->data.weight = 1;
        p->next = NULL;
    }
    return L;
};
//生成随机数链表
LinkList List_TailInsert_Random(LinkList L, int length, int start = 1,int end = 10)
{
    LinkList p,lrear;
    srand((unsigned int)time(NULL));
    lrear = L;
    for (int i = 1; i <= length; i++)
    {
        p = (LinkList)malloc(sizeof(LNode));
        lrear->next = p;
        lrear = p;
        p->data.str[0] = 'v';
        p->data.str[1] = 'a';
        p->data.str[2] = 'r';
        p->data.str[3] = '\0';
        p->data.value = rand() % (end - start + 1) + start;
        p->data.weight = 1;
        p->next = NULL;
    }
    return L;
}
//生成不带头结点的链表
LinkList NoHeadLinklist(LinkList L)
{
    LinkList p = L;
    if (p->next == NULL)
    {
        printf("\nthis linklist is empty!\n");
        return L;
    }
    else
    {
        p = p->next;
        return p;
    }  
}
//返回尾结点指针
LinkList GetRearNode(LinkList L)
{
    LinkList rear = L;
    while(rear->next != NULL)
        rear = rear->next;
    return rear;
}
//单链表按序查找
LinkList GetElem(LinkList L, int i)
{
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
//递归按值删除链表中的结点(无头链表)
void LinkList_Delete_value(LinkList &L,int value)
{   
    LinkList p;
    if (L == NULL)
        return;
    if (L->data.value == value)
    {
        p = L;
        L = L->next;
        free(p);
        LinkList_Delete_value(L,value);
    }
    else
        LinkList_Delete_value(L->next,value);
}
//返回链表中最小值结点的前驱指针(带头结点)
LinkList LinkList_FindMin(LinkList L)
{
    LinkList p,q;
    int min = 999;
    p = L;
    while (p->next != NULL)
    {
        if (p->next->data.value <= min)
        {
            min = p->next->data.value;
            q = p;
        }
        p = p->next;
    }
    return q;
}
//返回链表中最大值的结点的前驱指针（带头结点）
LinkList LinkList_FindMax(LinkList L)
{
    LinkList p,q;
    int max = -1;
    p = L;
    while (p->next != NULL)
    {
        if (p->next->data.value >= max)
        {
            max = p->next->data.value;
            q = p;
        }
        p = p->next;
    }
    return q;
}
//选择排序单链表（带头结点）
void Linklist_SelectSort(LinkList &L)
{
    //算法部分 选择插入排序
    LinkList p,q,r;
    p = L;
    //这里先排一次是为了让p指向分界的结点处
    q = LinkList_FindMax(p);
    r = q->next;
    q ->next = r->next;
    r->next = L->next;
    L->next = r;
    p = r;
    while (p->next != NULL)
    {   
        q = LinkList_FindMax(p); 
        r = q->next;
        q ->next = r->next;

        r->next = L->next;
        L->next = r;
    }
}

//静态链表区
//生成静态链表的指针表（附加在原来的顺序表中，使用顺序表生成）
bool Static_linklist_Init(Sqlist L, int *array)
{
    //初始的头结点就按顺序表的初始顺序，指向第一个结点
    array[0] = 1;
    //一样保留头元素，用作静态头结点
    //每一个地方存取下一个元素的索引
    for (int i = 1; i <= L.length ; i++)
        array[i] = i % L.length + 1;  //取模是为了循环
    return true;
}
//打印静态链表
void Static_linklist_Print(Sqlist L, int* array)
{
    if (L.length == 0)
    {
        printf("\nthe list is empty!\n");
        return;
    }
    printf("\nthe list is:\n");
    int link = 0;
    for (int i = 0; i < L.length; i++)  //限制读取次数
    {
        link = array[link];
        printf(" {%s:%2d} ",L.data[link].str, L.data[link].value);
    }    
}

//一些其他的辅助函数
//计算绝对值
int abs(int a)
{
    return a >= 0 ? a : -a;
}
//计算三数最大值
int max_in_tri(int a, int b,int c)
{
    return a >= b ? (c >= a ? c : a) : ( c >= b ? c : b);
}
//--------------------------------------
//练习函数区
//顺序表习题
void P18_01(){
    //初始化随机顺序表
    Sqlist L;
    Init_Sqlist_Random(L,10);
    PrintSqlist(L);
    //设置两个变量一个用于存储索引，一个用于存储临时最小值
    int index = 0, min = 1000;
    if (L.length == 0)
    {
        printf("\n--the list is null!--");
        return;
    }

    for (int i = 1; i <= L.length; i++)
    {
        if (L.data[i].value <= min )
        {
            min = L.data[i].value;
            index = i;
        }
    }
   //返回最小值信息，并用最后一个元素填补 
    printf("\nthe minimum number is : %d\n",L.data[index].value);
    L.data[index].value = L.data[L.length].value; 
    PrintSqlist(L);
}
void P18_02(){
    //初始化顺序表，随机
    Sqlist L;
    Init_Sqlist_Random(L,9);
    PrintSqlist(L);
    //逆置算法
    int tmp;
    for (int i = 1; i <= L.length/2; i++)
    {
        tmp = L.data[i].value;
        L.data[i].value = L.data[L.length-i+1].value;
        L.data[L.length-i+1].value = tmp;
    }
    PrintSqlist(L);
}
void P18_03(){
    //初始化顺序表，随机
    Sqlist L;
    Init_Sqlist_Random(L,10);
    PrintSqlist(L);
    int del_target = L.data[5].value;
    //算法部分,使用双指针思想
    int p = 1, q = 1, tmp = 0;
    while (q <= L.length)
    {
        if (L.data[p].value == del_target){
            while (L.data[q].value == del_target){
                if (q == L.length)
                    break;
                q++;
            } 
            if (L.data[q].value == del_target)
                break;
            tmp = L.data[p].value;
            L.data[p].value = L.data[q].value;
            L.data[q].value = tmp;  
        }
        p++;
        q++;
    }
    L.length = p - 1;
    PrintSqlist(L);
}
void P18_04(){
    int s = 30;
    int t = 99;
    //初始化有序表，顺序表
    Sqlist L;
    Init_Sqlist(L,10);
    L.data[7].value = L.data[6].value;
    PrintSqlist(L);
    //算法部分
    if (s >= t || L.length == 0)
    {
        printf("\n--wrong input!--\n");
        return;
    }
    //双指针定位删除区间
    int p = 1, q = 1, tmp = 0;
    while (L.data[p].value <= s && p <= L.length)  //注意溢出问题
        p++;
    while (L.data[q].value < t && q <= L.length) //也是防止溢出
        q++;
    
    //进行删除操作
    for (int i = q; i <= L.length; i++)
    {
        tmp = L.data[p].value;
        L.data[p].value = L.data[q].value;
        L.data[q].value = tmp;
        p++;
        q++;
    }
    L.length = p - 1;
    PrintSqlist(L);
}
void P18_05(){
    int s = 20;
    int t = 30;
    //初始化有序表，顺序表
    Sqlist L;
    Init_Sqlist_Random(L,10);
    PrintSqlist(L);
    //算法部分，使用双指针思想
    if (s >= t || L.length == 0)
    {
        printf("\n--wrong input!--\n");
        return;
    }

    int p = 1, q = 1, tmp = 0;
    while (q <= L.length)
    {
        if (L.data[p].value >= s && L.data[p].value <= t){
            while (L.data[q].value >= s && L.data[q].value <= t){
                if (q == L.length)
                    break;
                q++;
            } 
            if (L.data[q].value >= s && L.data[q].value <= t)
                break;
            tmp = L.data[p].value;
            L.data[p].value = L.data[q].value;
            L.data[q].value = tmp;  
        }
        p++;
        q++;
    }
    L.length = p - 1;
    PrintSqlist(L);
}
void P18_06(){
   //初始化顺序表，随机
    Sqlist L;
    Init_Sqlist(L,10);
    //测试数据
    L.data[7].value = L.data[6].value;
    L.data[5].value = L.data[6].value;
    L.data[3].value = L.data[2].value;
    PrintSqlist(L);

    //算法部分,使用三指针思想
    int p = 2, q = 2, r = 1, tmp = 0;
    while (q <= L.length)
    {
        if (L.data[p].value <= L.data[r].value){
            while (L.data[q].value <= L.data[r].value){
                if (q == L.length)
                    break;
                q++;
            }
            if (L.data[q].value <= L.data[r].value)
                break;
            tmp = L.data[p].value;
            L.data[p].value = L.data[q].value;
            L.data[q].value = tmp;  
        }
        r++;
        p++;
        q++;
    }
    L.length = p - 1;
    PrintSqlist(L); 
}
void P18_07(){
    //初始化两个有序顺序表
    Sqlist L1,L2;
    Sqlist res;
    Init_Sqlist(L1,5,1,2);
    Init_Sqlist(L2,5,2,2);
    PrintSqlist(L1);
    PrintSqlist(L2);
    if (L1.length+L2.length > MAXLENGTH)
    {
        printf("\noverflow!\n");
        return;
    }
    //还是双指针,两个核酸队伍一起排一个窗口，两两比较装弹。
    int p = 1, q = 1;   //p和q是两个数组
    for (int i = 1; i <= L1.length+L2.length; i++)
    {
        if (L1.data[p].value <= L2.data[q].value && p <= L1.length) //这一步是防止溢出
        {
            res.data[i].value = L1.data[p].value;
            p++;
        }else{
            res.data[i].value = L2.data[q].value;
            q++;
        }    
    }
    res.length = L1.length+L2.length;
    PrintSqlist(res);
}
void P18_08(){
    //初始化数组
    Sqlist L;
    Init_Sqlist(L,10);
    PrintSqlist(L);
    int m = 3;
    int n = 7;
    //逆置三次完事
    int tmp;
    for (int i = 1; i <= L.length/2; i++)
    {
        tmp = L.data[i].value;
        L.data[i].value = L.data[L.length-i+1].value;
        L.data[L.length-i+1].value = tmp;
    }

    for (int i = 1; i <= n/2; i++)
    {
        tmp = L.data[i].value;
        L.data[i].value = L.data[n - i + 1].value;
        L.data[n - i + 1].value = tmp;
    }

    for (int i = 1; i <= m/2; i++)
    {
        tmp = L.data[n + i].value;
        L.data[n + i].value = L.data[m + n - i + 1].value;
        L.data[m + n - i + 1].value = tmp;
    }

    PrintSqlist(L);
}
void P18_09(){
    //注：这B题目没说清楚，我就当取模运算来写了。
    //初始化递增有序顺序表
    Sqlist L;
    Init_Sqlist(L,9,1,2);  //测试使用奇数序列
    PrintSqlist(L);
    //使用折半查找指针p
    int x = 4, tmp = 0;
    int index = Sqlist_bisearch(L,x,1,L.length); //使用二分查找
    printf("\nthe index is pointed to: %d\n",index);

    if (index <= L.length && L.data[index].value == x)
    {
        printf("the element is existed and finded!");
        tmp = L.data[index].value;
        L.data[index].value = L.data[(index+1)%L.length].value;
        L.data[(index+1)%L.length].value = tmp;
        PrintSqlist(L);
    }else{
        printf("the elements is not finded in this list! so i add it.");
        Sqlist_Insert(L,index,x);
        PrintSqlist(L);
    }
}
void P18_10(){
    //生成静态链表
    Sqlist L;
    Init_Sqlist(L,10);
    PrintSqlist(L);
    int arr[L.length + 1];  //先申请一下空间，不然会溢出报错 
    Static_linklist_Init(L,arr);
    //只要改一下头结点的索引值就可以
    int p = 6;//偏移量
    arr[0] += p;
    Static_linklist_Print(L,arr);
}
void P18_11(){
    //初始化测试顺序表
    Sqlist L1,L2;
    int length = 6;
    Init_Sqlist(L1,length,3,2);
    Init_Sqlist(L2,length,2,3);
    PrintSqlist(L1);
    PrintSqlist(L2);
    //算法
    int p1 =1 , q1 = 1;
    int p2 = length, q2 = length;
    while (p1 != p2 && q1 != q2)
    {   
        //之所以用值而不直接用下标是为了让值输出更准确，纯用下标没有通过测试
        //还是把两个相邻的情况单独处理了
        if (L1.data[(p1 + p2)/2].value == L2.data[(q1 + q2)/2].value)
            break;
        else if ((L1.data[(p1+p2)/2].value + L1.data[(p1+p2+1)/2].value) < (L2.data[(q1+q2)/2].value + L2.data[(q1+q2+1)/2].value) && p1<p2-1 && q1<q2-1)
        {
            q2 = (q1 + q2)/2;
            p1 = (p1 + p2 + 1)/2;
        }
        else if ((L1.data[(p1+p2)/2].value + L1.data[(p1+p2+1)/2].value) > (L2.data[(q1+q2)/2].value + L2.data[(q1+q2+1)/2].value) && p1<p2-1 && q1<q2-1)
        {
            q1 = (q1 + q2 + 1)/2;
            p2 = (p1 + p2)/2;
        }
        else if ((L1.data[(p1+p2)/2].value + L1.data[(p1+p2+1)/2].value) < (L2.data[(q1+q2)/2].value + L2.data[(q1+q2+1)/2].value))
        {
            p1 = p2;
            q2 = q1;
        }else if ((L1.data[(p1+p2)/2].value + L1.data[(p1+p2+1)/2].value) > (L2.data[(q1+q2)/2].value + L2.data[(q1+q2+1)/2].value))
        {
            p2 = p1;
            q1 = q2;
        }
        printf("\np:[%d,%d],q:[%d,%d]\n",p1,p2,q1,q2);
    }
    int middle = L1.data[p1].value > L2.data[q1].value ? L1.data[p1].value : L2.data[q1].value;
    printf("\nthe middle number is : %d\n",middle);
}
void P18_12(){
    //这里暂时写的是O(n^2)复杂度的，排序的那个等到后续写到了再说
    //初始化，还是用随机化那个轮子吧
    Sqlist L;
    Init_Sqlist_Random(L,8);
    PrintSqlist(L);

    //算法思想：用一个数组存储变量以及变量出现的次数的次数
    Sqlist cnt;
    bool INSERT_KEY;
    for (int i = 1; i <= L.length; i++)
    {
        INSERT_KEY = true;
        for (int j = 1; j <= cnt.length + 1 ; j++)
        {
            if (L.data[i].value == cnt.data[j].value)
            {
                cnt.data[j].weight++;
                INSERT_KEY = false; //找到就不用新添加键值了
            }        
        }
        if (INSERT_KEY)
            Sqlist_Insert(cnt,(cnt.length+1),L.data[i].value);
    }
    //再统计最大值输出索引信息
    int max = -999, num = -999;
    for (int i = 1; i <= cnt.length; i++)
    {
        if (cnt.data[i].weight > max)
        {
            max = cnt.data[i].weight;
            num = cnt.data[i].value;
        }
    }
    PrintSqlist(cnt);
    if (max < (L.length + 1)/2)
        printf("\nthe list havn't main element!\n");
    else
        printf("\nthe list has main element %d\n",num);

    
}
void P18_13(){
    //这题我的建议是用排序做，
    //用n个空间换时间是非常不值得的，因为只要出现一个极大的数，很容易就会使空间大量浪费
    Sqlist L;
    Sqlist Cnt;
    int length = 5;
    Init_Sqlist_Random(L,length);
    Init_Sqlist(Cnt,length,1,1,true);
    PrintSqlist(L);
    PrintSqlist(Cnt);
    
}
void P18_14(){
    //初始化测试样例
    int length_1 = 3;
    int length_2 = 4;
    int length_3 = 5;
    Sqlist L1,L2,L3;
    Init_Sqlist(L1,length_1,1,7);
    Init_Sqlist(L2,length_2,3,4);
    Init_Sqlist(L3,length_3,4,2);
    PrintSqlist(L1);
    PrintSqlist(L2);
    PrintSqlist(L3);

    //算法使用三指针来解决
    int p = 1,q = 1,r = 1;
    int min = 100;
    int min_index[3];
    while (p < length_1 || q < length_2 || r < length_3)
    {
        int distance = max_in_tri(abs(L1.data[p].value-L2.data[q].value),abs(L1.data[p].value-L3.data[r].value),abs(L2.data[q].value-L3.data[r].value));
        if (distance < min)
        {
            min = distance;
            min_index[0] = L1.data[p].value;
            min_index[1] = L2.data[q].value;
            min_index[2] = L3.data[r].value;
        }
            
        if (L1.data[p].value <= L2.data[q].value && L1.data[p].value <= L3.data[r].value)
            p++;
        else if (L2.data[q].value <= L1.data[p].value && L2.data[q].value <= L3.data[r].value)
            q++;
        else r++;
    }
    printf("\n\nthe min distance is %d,in (%d,%d,%d)",2*min,min_index[0],min_index[1],min_index[2]);
}
//链表习题
void P40_01(){
    //初始化
    LinkList L;
    L = InitLinklist();
    L = List_TailInsert_Random(L,10,1,3);
    L = NoHeadLinklist(L);
    PrintLinkList(L);
    int del_target = 3;
    LinkList_Delete_value(L,del_target);
    PrintLinkList(L);
}
void P40_02(){
    //初始化
    LinkList L;
    L = InitLinklist();
    L = List_TailInsert_Random(L,10,1,3);
    PrintLinkList(L);
    int x = 3;

    //算法部分  void delete_headlinklist(linklist &l,int x)
    LinkList p,q;
    p = L;
    while (p->next != NULL)
    {
        q = p->next;
        if (q->data.value == x)
        {
            p->next = q->next;
            free(q);
        }
        else
            p = p->next;
    }
    PrintLinkList(L);
}
void P40_03(){
    //初始化部分
    LinkList L;
    L = InitLinklist();
    L = List_TailInsert(L,5);
    PrintLinkList(L);

    //算法部分 
    LinkList stack;
    stack = InitLinklist();
    LinkList p,q,r;
    p = L;
    q = stack; 
    while (p->next != NULL)
    {
        r = (LinkList)malloc(sizeof(LNode));
        r->data.str[0] = 'v';
        r->data.str[1] = 'a';
        r->data.str[2] = 'r';
        r->data.str[3] = '\0';
        r->data.value = p->next->data.value;
        r->data.weight = p->next->data.weight;
        r->next = q->next;
        q->next = r;
        p = p->next;
    }
    PrintLinkList(stack);
}
void P40_04(){
    //初始化
    LinkList L;
    L = InitLinklist();
    L = List_TailInsert_Random(L,5,20,50);
    PrintLinkList(L);

    //算法部分
    int min = 1000,cnt = 0,index = 0;
    LinkList p,q;
    p = L;
    while (p->next != NULL)
    {
        p = p->next;
        cnt++;
        if (p->data.value < min)
        {
            min = p->data.value;
            index = cnt;
        }    
    }
    if (index == 0)
    {
        printf("\nthe linklist is empty!\n");
        return;
    }
    p = L;
    q = L->next;
    for (int i = 1; i < index; i++)
    {
        p = p->next;
        q = q->next;
    }
    p->next = q->next;
    free(q);
    PrintLinkList(L);
}
void P40_05(){
    //初始化
    LinkList L;
    L = InitLinklist();
    L = List_TailInsert(L,5);
    PrintLinkList(L);
    //算法部分
    LinkList p,q,r;
    p = L;
    if (p->next == NULL || p->next->next == NULL)
    {
        printf("\nthe linklist has no need to revrese.\n");
        return;
    }
    q = p->next;
    r = q;
    while (r->next != NULL)
    {
        q = r->next;
        r->next = q->next;
        q->next = p->next;
        p->next = q;
    }
    PrintLinkList(L);
}
void P40_06(){
    //初始化
    LinkList L;
    L = InitLinklist();
    L = List_TailInsert_Random(L,5,10,80);
    PrintLinkList(L);

    //算法部分 选择插入排序
    LinkList p,q,r;
    p = L;
    //这里先排一次是为了让p指向分界的结点处
    q = LinkList_FindMax(p);
    r = q->next;
    q ->next = r->next;
    r->next = L->next;
    L->next = r;
    p = r;
    while (p->next != NULL)
    {   
        q = LinkList_FindMax(p); 
        r = q->next;
        q ->next = r->next;

        r->next = L->next;
        L->next = r;
    }
    PrintLinkList(L);
}
void P40_07(){
    //初始化
    LinkList L;
    L = InitLinklist();
    L = List_TailInsert_Random(L,10,1,4);
    PrintLinkList(L);
    int start = 2;
    int end = 3;

    //算法部分  void delete_headlinklist(linklist &l,int start，int end)
    LinkList p,q;
    p = L;
    while (p->next != NULL)
    {
        q = p->next;
        if (q->data.value <= end && q->data.value>=start)
        {
            p->next = q->next;
            free(q);
        }
        else
            p = p->next;
    }
    PrintLinkList(L);
}
void P40_08(){
    //初始化
    LinkList L1,L2;
    L1 = InitLinklist();
    L2 = InitLinklist();
    L1 = List_TailInsert_Random(L1,10,10,30);
    L2 = List_TailInsert_Random(L2,10,10,25);
    
    //算法部分，先进行排序，然后再使用双指针
    Linklist_SelectSort(L1);
    Linklist_SelectSort(L2);
    PrintLinkList(L1);
    PrintLinkList(L2);
    LinkList p,q;
    if (L1->next == NULL || L2->next == NULL)
    {
        printf("\nthe empty list is existed in input ,so no same node.\n");
        return;
    }
    
    p = L1->next;
    q = L2->next;
    printf("\n");
    while (p != NULL && q != NULL)
    {
        if (p->data.value == q->data.value)
        {
            PrintLNode(p);
            if (p->next->data.value == p->data.value && p->next != NULL)
            {
                p = p->next;
                continue;
            }
            if (q->next->data.value == q->data.value && q->next != NULL)
            {
                q = q->next;
                continue;
            }
            p = p->next;
            q = q->next;      
        }
        else if (p->data.value < q->data.value)
            p = p->next;
        else q = q->next;
    }
}
void P40_09(){
    //初始化
    LinkList L;
    L = InitLinklist();
    L = List_TailInsert_Random(L,5,10,80);
    PrintLinkList(L);
    //算法部分，每找到一个最小值就输出并且删除
    LinkList p,q;
    while (L->next != NULL)
    {
        p = LinkList_FindMin(L);
        q = p->next;
        PrintLNode(q);
        p->next = q->next;
        free(q);
    }
    PrintLinkList(L);
    free(L);  //最后一个free掉之后一定要重新指定NULL，不然会导致野指针
    L = NULL;
    PrintLinkList(L);
}
void P40_10(){
    //初始化
    LinkList L,res1,res2;
    L = InitLinklist();
    res1 = InitLinklist();
    res2 = InitLinklist();
    L = List_TailInsert(L,10);

    //算法部分
    LinkList p,q,r;
    int cnt = 1;
    p = L->next;
    while (p != NULL)
    {
        if (cnt % 2 == 1)
        {
            
        }
        
    }
    
}
void P40_11(){
    
}
void P40_12(){
    
}
void P40_13(){
    
}
void P40_14(){
    
}
void P40_15(){
    
}
void P40_16(){
    
}
void P40_17(){
    
}
void P40_18(){
    
}

void P42_25(){
    //初始化头结点
    LinkList L = InitLinklist();
    //创建测试单链表
    int num = 8;
    L = List_TailInsert(L,num);
    //打印初始化的单链表信息
    PrintLinkList(L);
    //实现算法部分,首先实现链表逆置
    LinkList p,q,r,s;
    p = GetElem(L,(num+1)/2); 
    q = p->next;
    s = q;
    while (q->next != NULL)
    {
        q = q->next;
        s->next = q->next;
        q->next = p->next;
        p->next = q;
        q = s;
    }
    //断链
    q = p->next;
    p->next = NULL;
    p = L->next;
    r = q;
    //拼接
    while (r != NULL)
    {   
        q = q->next;
        r->next = p->next;
        p->next = r;
        p = r->next;
        r = q;
    }
    //输出结果
    PrintLinkList(L);
}