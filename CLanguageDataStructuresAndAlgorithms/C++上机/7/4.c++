//写一个文件拷贝程序my lecopy，其用法如下：
//my lecopy s. txt d. txt
//需要实现的功能：s. txt拷贝到d. txt，若d. txt存在，则该文件被覆盖。
#include <fstream>
#include <iostream> 
#include <string>      
#include <stdio.h> 
using namespace std;
int  main(){
    //预定义命令
    string command1("my");
    string command2("lecopy");

    //文件名
    
    string array[4];
    for(int i=0;i<4;i++){
       cin>> array[i];
    }
    
    //二进制读方式打开
    
        char c;

        ifstream inFile(array[2],ios::in|ios::binary);
        //以二进制形式打开文件
        ofstream outFile(array[3], ios::out | ios::binary);
        if(!inFile) {
            cout << "error" <<endl;
            return 0;
        }
        while(inFile.read((char *)&c, sizeof(c))) { //一直读到文件结束
            //写入文件
            outFile.put(c);  
        }
}
    
    
    //while(c=inFile.get()&&c!=EOF){
        //outFile.put(c);
    //}




