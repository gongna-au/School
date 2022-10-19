#include "ArrayImplementation.h"

void yanghui(int n)
{
    QElemType e, s;
    int k = 1, i;

    SqQueue Q;
    InitQueue_Sq(Q);

    //输出第0行
    for (i = 1; i <= n; i++)
        cout << " ";
    cout << '1' << endl;

    //第一行直接入队列
    EnQueue_Sq(Q, 0);
    EnQueue_Sq(Q, 1);
    EnQueue_Sq(Q, 1);

    while (k < n)
    {
        for (i = 1; i <= n - k; i++)
            cout << ' ';
        EnQueue_Sq(Q, 0);
        do
        {
            DeQueue_Sq(Q, s);
            GetHead_Sq(Q, e);
            if (e)
                cout << e << ' ';
            else
                cout << endl;
            EnQueue_Sq(Q, s + e);
        } while (e);
        k++;
    }
    DeQueue_Sq(Q, e);//e==0,最后一行的行首
    while (!QueueEmpty_Sq(Q))
    {
        DeQueue_Sq(Q, e);
        cout << e << ' ';
    }
}
int main()
{
    int n;

    cout << "please input the member of rows:";
    cin >> n;

    yanghui(n);

    return 0;
}