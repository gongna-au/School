#include<iostream>
#include<fstream>		//调用文件输入输出头文件
#include<string.h>
#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
using namespace std;
//判断学号是否合法
bool IsdigitAll(string str)
{
    if (str.size() != 10){
        return false;
    }

    for (int i = 0; i<str.size(); i++)
    {
        if (!isdigit(str[i]))
        {
            cout << str << " is not all digit" << endl;
            return false;
        }
    }
    return true;
}

class DB{
    public:
        string fileName;
        long recordNumber;


    public:

        DB(string name){

            name =name+".txt";
            this->fileName = name;
            this->recordNumber = 0;
             FILE * pFile;
            //以追加且格式化的方式写入
            pFile = fopen ((char*)(this->fileName).c_str(),"a+");
            fprintf (pFile, "StudentID\t\t\t\tstudentName\t\t\t\tstudentScore\n");
            fclose (pFile);
            
        };

        void DBwrite(int dataLenth ){
            FILE * pFile;
            //以追加且格式化的方式写入
            pFile = fopen ((char*)(this->fileName).c_str(),"a+");
            for (int i=0;i<dataLenth;i++){
                //输入学生信息
                string studentId;
                string studentName;
                int studentScore;

                cout<<"StudentId:";
                cin >>studentId;
                //如果不合法强制退出
                bool tag =IsdigitAll(studentId);
                if  (tag == false) {
                    exit(-1);
                }
                //经过测试C++中string类型都是32个字节
                //int value1 = sizeof(studentId);
                //限制输入的学号以及姓名的长度
                //便与对数据进行查找
                //string类型32个字节 int类型4个字节 一条记录32+32+4 = 68个字节

                cout<<"StudentName:";
                cin >>studentName;
                cout<<"StudentScore:";
                cin >>studentScore;
                student* data = new student(studentId,studentName,studentScore);
                 fprintf (pFile, "%s\t\t\t\t%s\t\t\t\t\t\t%d\n",(char*)(data->getStudentId().c_str()),(char*)(data->getStudentName().c_str()),data->getStudentScore());
               

            }
            this->recordNumber=this->recordNumber+dataLenth;
            fclose (pFile);
        


        };

        void DBLoad(){
            ifstream ifs(this->fileName);	
            //定义一个文件输入流ifs，要打开的文件是名为“myfile”的txt文件
            //输入流即读取流，通过流读取文件内容
            while(!ifs.eof()){	//若打开的文件里仍有内容
                char c2;
                ifs.get(c2);	
                //通过ifs.get函数通过读取流ifs读取文件内的一个字符并赋值给c2
                if(!ifs.eof()) {
                    cout<<c2;
                }      
            }
            ifs.close();	//关闭文件输入流

        };

        void DBelementSeek(){
            
            
            fstream fs((char*)(this->fileName).c_str(), ios::binary | ios::out | ios::in);
            //跳转到开头的第二个字节位置进行写入，正常写入
            char ch;
    
            // Get fifth byte from beginning of alphabet file
            fs.seekg(0L, ios::beg);
            
            ch = fs.get ();
            while (ch != EOF)
            {
                cout << ch;
                ch = fs.get();
            }
            
            
            //cout << "Byte 1 from beginning: " << ch << endl;
            /* fs.seekp(64L,ios::beg);
            fs.write("!!!", 3); */
            fs.close();
		   /*  fseek(fp,pos*sizeof(student),1);
            student*  data = new student(studentId);

		    if(fread(data,sizeof(student),1,fp)==1){	
            printf ("StudentID\t\t\t\tstudentName\t\t\t\tstudentScore\n");
            printf("%s\t\t\t\t%s\t\t\t\t\t\t%d\n",(char*)(data->getStudentId().c_str()),(char*)(data->getStudentName().c_str()),data->getStudentScore());
		    } */
        };

};



 
int main(){
        //数据库的初始化
        string dataBaseName;
        cout<<"Please input your dataBaseName:";
        cin>>dataBaseName;
	    DB* dataBase = new DB(dataBaseName);
        //输入学生信息的个数
        int studentNumber;
        cout<<"Please input StudentNumber:";
        cin >>studentNumber;
     
        //写入数据库
        dataBase->DBwrite(studentNumber);
        //加载数据库的数据
        dataBase->DBLoad();
        //删除数据库的数据
        dataBase->DBelementSeek();
        
	return 0;
}