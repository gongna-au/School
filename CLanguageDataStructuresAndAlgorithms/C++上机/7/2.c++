//有一整数集，其中允许有重复的元素，集合初始为空。定义如下操作：
//– add i 把i加入集合
//– del i 删除集合中所有与i相等的元素
//– ask i 查询集合中元素i的情况
//• 对每种操作，要求输出如下：
//– add 输出操作后集合中i的个数
//– del 输出操作前集合中i的个数
//– ask 先输出0或1表示i是否曾经被加入集合（0表示不曾加入），再输出当前集合中i的个数，中间用空格格开。
#include <iostream>
#include <set>
#include <string>
#include <iterator>

using namespace std;

int main()
{   
    multiset<int> msetA;
    set<int> setB;
    char commend[5];
    int i,n,num,amount;
    multiset<int>::iterator it;
    cin >> n;
    for (i=0; i<n; i++)
    {
        cin >> commend >> num;
        switch(commend[1])
        {
        case 'd': 
            msetA.insert(num);
            setB.insert(num);
            cout << msetA.count(num) << endl;
            break;                
        case 'e': 
            cout << msetA.count(num) << endl;
            msetA.erase(num);
            break;
        case 's': 
            if (setB.find(num)==setB.end())
                cout << "0 0" << endl;
            else
            {
                cout << "1 ";
                cout << msetA.count(num) << endl;
            }
            break;
        }
    }
    return 0;
}