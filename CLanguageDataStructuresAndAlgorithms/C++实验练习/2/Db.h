
#include <math.h>

#include <fstream>
#include <iostream>
#include <string>
#include<string.h>
#include "student.h"
#define DataOffset  (8+4+4)
#define BUFFSIZE        1024
using namespace std;

/* template <class T > */
class   DataBase{
    public:
        //数据库的版本
        string  version;
        //数据库的名字
        //也是存放数据的文件的名字
        char*   fileName;
        // 具体存放数据的变量
        fstream file;
        //数据库中存放数据的数目
        long recordNum;
        //存放数据的最大数目
        long recordMaxRestraint;

        //往数据库存数据
        void storeRecord(student* record ){
            this->recordNum=this->recordNum+1;
            char c[30];
            ofstream ofs;
            ofs.open("MyDatabase.txt");
            memset(c,0,30);	//c的初始化

            ofs<<record-> getStudentId() << record-> getStudentName()<< record-> getStudentScore()<<endl;
            /* ofs.close(); */
           
	
	
        };


        //从数据库取数据
      student* getRecord(string dataInformation){
            ifstream ifs;
            ifs.open(this->fileName, ios::in);
            if(!ifs.is_open())
            {
                    cout << "打开数据库" << endl;
                    return NULL;
            }

            char buf[BUFFSIZE] = { 0 };

            while(ifs.getline(buf, BUFFSIZE)){
                cout << buf << endl;
            }



        };
        //创建数据库
        void openDatabase(char*  name){
            this->fileName = name;

        };


        //关闭数据库
        void closeDatabase(){
            // 关闭打开的文件
           // this->file.close();
        };
        //得到数据库中总的记录的数目
        long getRecordNum(){

            return this->recordNum;
        };
        //返回数据中所有的数据
        void getAllRecordInDatabase(){
            ifstream ifs;
            ifs.open(this->fileName, ios::in);

            if(!ifs.is_open())
            {
                    cout << "打开失败" << endl;
                    
            }

            char buf[BUFFSIZE] = { 0 };

            while(ifs.getline(buf, BUFFSIZE)){
                cout << buf << endl;
            }
           
        };
        //删除数据库中的某一条数据
        void DeleteSpecificRecord(student* recordInformation ){

        };
        
        DataBase(){
            //数据库的名字
            string str= "MyDatabase.txt";
            this->fileName =  (char*)str.c_str();
            // 数据库的版本
            this->version ="DB-1.0.0";
            // 数据库中记录的最大数目
            this->recordMaxRestraint = 1000;
            //初始化数据时默认一条记录都没有
            this->recordNum = 0;
            
        };

        DataBase(string  name){
            //数据库的名字
            this->fileName =  (char*)name.c_str();
            // 数据库的版本
            this->version= "DB-1.0.0";
            // 数据库中记录的最大数目
            this->recordMaxRestraint = 1000;
            //初始化数据时默认一条记录都没有
            this->recordNum = 0;
            
        };
        


};


