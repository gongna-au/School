#include<iostream>
#include<list>
#include<cstring>
#include<iterator>
using namespace std;
int n,number1,number2;
string s;
list<int>lit[10001];
int main()
{
    cout<<"Please input n"<<endl;
    cin>>n;
    for(int i=1;i<=n;i++)
    {  
        cin>>s;
        if(s=="new") {
            cin>>number1;
        }
        else if(s=="add")
        {
            cin>>number1>>number2;
            lit[number1].push_back(number2);//list[number1]后面插入元素number2
        }
        else if(s=="merge")
        {
            cin>>number1>>number2;
            lit[number1].merge(lit[number2]);//讲list[number2]接到list[number1]后面，同时清空list[number2]
        }
        else if(s=="unique")
        {
            cin>>number1;
            lit[number1].sort();
            lit[number1].unique();
        }
        else
        {
            cin>>number1;
            if(!lit[number1].empty())//首先判断非空
            {
                lit[number1].sort();
                ostream_iterator<int> output(cout," ");
                copy(lit[number1].begin(),lit[number1].end(),output);//输出，并以空格分隔
                cout<<endl;
            }
            else {
                cout<<endl;
                }
        }
    }
}
