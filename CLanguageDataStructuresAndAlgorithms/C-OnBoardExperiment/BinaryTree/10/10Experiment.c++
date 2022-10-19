//哈夫曼树的构造算法：
//构造树林全是根，选用两小造新树。
//删除两新人，重复建新根。
//首先要创建一个赫夫曼树，对于赫夫曼树
//概率我们当作权值，构造出树，对于编码就是赫夫曼的高明之处，将路径上左边改为0，
//右面改为1，就是我们的编码啦，当然我们要从叶子找到根

#include <iostream>
#include "10Experiment.h"
using namespace std;


int main()
{
    HuffmanTree H;
    int n;
    printf("Please input encoding number:");
    scanf("%d",&n);
    char array[n];
    printf("Please input char:\n");
    for (int q=0;q<n;q++){
        cin>>array[q];
    }
    
    
    createmanTree(H,n);
    //char result[n][n+1];
    bianma(H,n,array);      
}