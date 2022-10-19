#include <stdio.h>
#include <stdlib.h>
/*定义结构体节点*/
struct GradeInfo
{
    int score;
    struct GradeInfo *next;
};
typedef struct GradeInfo NODE;

/*链表的创建CreateLinkList*/
NODE *CreateLinkList()
{
    NODE *head, *tail, *pnew;
    int score;
    //为头指针分配内存并强制类型转化
    head = (NODE *)malloc(sizeof(NODE));

    //创建成功未成功就进行错误处理
    if (head == NULL)
    {
        printf("没有足够的内存来给链表的节点来分配内存");
        return (NULL);
    }
    //创建成功，此时头节点里的Next没有指向任何节点，所以让指向头结点的头指针的next赋值为NULL
    head->next = NULL;
    //让尾指针也指向第一个节点
    tail = head;
    //头节点的数据域往往不存数据，循环接受用户输入的数据，并把它放在每一个新建节点的数据域里
    printf("请输入学生的成绩(输入0结束)：\n");
    //循环接受输入的数据
    do
    {
        scanf("%d", &score);
        if (score < 0)
            break;

        //每次输入一个数据就创建一个新的节点
        pnew = (NODE *)malloc(sizeof(NODE));
        //创建失败的错误处理
        if (pnew == NULL)
        {
            printf("没有足够的内存来给链表的节点来分配内存!\n");
            return (NULL);
        }
        //新节点的数据域存放输入的数据
        pnew->score = score;
        //新节点的next指向空
        pnew->next = NULL;
        //把新的节点与旧的节点连接起来
        //把新旧节点连接起来的关键是节点之间的next相互指向的关系
        //头指针与尾指针都指向第一个节点，头指针与尾指针都可以操作第一个节点的next的指向
        tail->next = pnew;
        //让尾指针指向新节点
        // tail->next=pnew与tail=pnew的赋值顺序不可以改变
        tail = pnew;
    } while (score != 0);

    //返回的必须是头指针，因为我们需要的链表，返回尾指针没有丝毫的用处
    return (head);
}

/*链表的插入InsertLinkList*/
//调用时只要传入你要插入链表的头指针和你新建的节点以及你要插入的位置，就可以实现插入
void InsertLinkList(NODE *head, NODE *pnew, int InsertPosition)
{
    //定义一个指针p来定位我们要插入的节点位置
    NODE *p;
    // p指针一开始只能指向头指针或者尾指针，定位通过不断地移动p指针的位置
    p = head;
    // p指针的移动通过循环来实现
    //为了程序的健壮性，万一你输入的数字大于了链表的长度，也能更好的处理，而不是异常处理终端
    for (int i = 1; i < InsertPosition && p != NULL; i++)
    {
        //定位指针p的移动
        p = p->next;
    }
    //错误处理，如果输入的数字大于链表的长度
    if (p == NULL)
    {
        printf("这个%d号要插入的位置没有找到！\n", InsertPosition);
        return;
    }
    //此时定位指针已经在要插入位置的前一个节点，让新指针的next指向插入位置前一个节点的next
    pnew->next = p->next;
    //断开前一个节点与后一个节点的连接
    p->next = pnew;
}

/*链表的删除DeleteLinkList*/
void DeleteLinkList(NODE *head, int DeletePosition)
{
    //定位指针p
    NODE *p;
    NODE *q;

    if (DeletePosition == 0)
    {
        return;
    }
    p = head;

    //利用循环来定位指针
    for (int i = 1; i < DeletePosition && p != NULL; i++)
    {
        p = p->next;
    }
    if (p == NULL)
    {

        printf("这个%d号位置不存在！\n", DeletePosition);
        return;
    }

    //定位指针p为删除位置的前一个节点
    //定位指针q为删除位置的那一个节点

    q = p->next;
    //断开删除位置与下一个节点的连接
    p->next = q->next;
    //千万不能忘记释放删除节点的内存
    free(q);
}

/*链表的销毁FreeLinkList*/
void FreeLinkList(NODE *head)
{
    NODE *p;
    NODE *q;

    p = head;

    while (p->next != NULL)
    {

        p->next = q;

        //断开删除位置的节点的具体操作是，让它的前一个节点直接指向删除位置的下一个节点
        p->next = q->next;
        free(q);
    }
    //释放头指针
    free(head);
}

/*输出链表中的值ShowLinkList*/

void ShowLinkList(NODE *head)
{
    NODE *p;
    p = head->next;
    //利用循环来打印数据
    for (p = head->next; p != NULL; p = p->next)
    {
        printf("%d", p->score);
        printf("\n");
    }
}

/*链表的调用*/
void main()
{
    NODE *head;
    NODE *pnew;

    int input, insertNodeNumber;
    int NeedDeleteNumber;
    //创建链表
    head = CreateLinkList();
    if (head == NULL)
    {
        printf("创建链表失败，没有足够的空间来创建链表!\n");
        return;
    }
    else
    {
        printf("创建链表成功！\n");
    }
    //打印新建链表的值
    ShowLinkList(head);
    //新建节点
    pnew = (NODE *)malloc(sizeof(NODE));

    if (pnew == NULL)
    {
        printf("创建节点失败，没有足够的空间来创建链表!\n");
        return;
    }
    else
    {
        printf("创建节点成功！\n");
    }

    printf("请输入要插入节点的值");
    scanf("%d", &input);
    pnew->score = input;
    printf("请输入你要把输入的数插到第几个节点");
    scanf("%d", &insertNodeNumber);
    InsertLinkList(head, pnew, insertNodeNumber);
    printf("插入数据后的链表为:\n");
    //输出链表中的值
    ShowLinkList(head);
    printf("已经输出插入数据后的链表：\n");
    printf("请告诉我你要删除那个节点的数据:\n");
    scanf("%d", &NeedDeleteNumber);
    DeleteLinkList(head, NeedDeleteNumber);
    printf("已经删除%d这个节点的值\n", NeedDeleteNumber);
    //输出链表中的值
    printf("新的链表的值为：\n");
    ShowLinkList(head);
    //销毁链表
    FreeLinkList(head);
}
