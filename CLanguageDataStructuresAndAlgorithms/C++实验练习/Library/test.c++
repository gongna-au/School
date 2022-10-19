#include<iostream>
#include"MyDB.c++"
#include"DB.h"

using namespace std;


int main()
{
    MyDB db; 
    //连接数据库
    db.initDB("localhost","gongna2","123456","Test");
    //将用户信息添加到数据库
    
    //将所有用户信息读出，并输出。
    db.exeSQL("SELECT * from book_table;");

    return 0;
}
