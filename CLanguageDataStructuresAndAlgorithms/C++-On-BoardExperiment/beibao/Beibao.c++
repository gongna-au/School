#include "SqStack.h"

void knapstack( SqStack S, int w[ ],  int T,  int n )
{
  // 已知n件物品的体积分别为 w[0], w[1], …, w[n-1]，背包的总体积为 T,
  // 本算法输出所有恰好能装满背包的物品组合解
  // 例如：T=10, w[6]={1,8,4,3,5,2}
  InitStack_Sq(S);
  int k = 0;        // 从第0 件物品考察起
  do {
     while ( T > 0  &&  k < n ) {
        if ( T - w[k] >= 0 ) {               // 第k件物品可选，则k入栈
            Push_Sq( S, k );
            //cout<<k<<"-"<<w[k]<<"进栈"<<endl;
            T -= w[k];        // 背包剩余体积减少wk
        }
        k++;                                // 继续考察下一件物品
     }if  ( T == 0 )  {
        cout<<"找到一组解（物品的序号）：";
        StackTraverse_Sq(S);       // 输出一组解，之后回溯寻找下一组解
    }
    Pop_Sq( S, k );
     //cout<<k+1<<"-"<<w[k]<<"出栈"<<endl;
    T += w[k];              // 退出栈顶物品，背包剩余体积增添wk
    k ++;                                   // 继续考察下一件物品
  } while ( !StackEmpty_Sq(S) || ( k < n ));      // 若栈不空或仍有可选物件则继续回溯

} // knapsack

void main()
{
    int t, n, i, *w;
    SqStack S;

    InitStack_Sq(S);

    cout<<"请输入物品个数n=";
    cin>>n;
    cout<<endl;
    w = new int[n];
    cout<<"请输入每个物品的体积:"<<endl;
    for(i=0; i<n; i++)
    {
        cout<<"第"<<i+1<<"个物品的体积=";
        cin>>w[i];
    }
    cout<<endl;
    cout<<"请输入背包体积T=";
    cin>>t;
    cout<<endl;

    knapstack(S, w, t, n);
}