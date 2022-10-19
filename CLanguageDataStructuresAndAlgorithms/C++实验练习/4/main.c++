#include<iostream>
#include<fstream>		//调用文件输入输出头文件
#include<string.h>
#include "DB.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
using namespace std;
#define RecordMaxNum 1000

template<class T>
class  DB{

    private:
        T   data[RecordMaxNum];
        string FileLogo;//FileLogo就是文件的名字
        int  recordMaxNum;
        int  recordNum;

    public:
       DB(){
        cout<<"Please Input filename:";
        cin >>this->FileLogo;
        this->recordMaxNum= RecordMaxNum;
        this->recordNum = 0;

       };
       int GetRecordNum(){
           return this->recordNum-1;

       };
       string GetFileLogo(){

           return this->FileLogo;
       };
       void ShowAllRecord(){
           cout << "Showing all the record in " << this->FileLogo << endl;
            for (int i=0; i<this->recordNum; i++){
                this->data[i].ShowInformation();
            }

       };
       void InsertRecordInDB(){
            string studentID;
            string studentName;
            int studentScore;

            cout<<"Please input studentID:";
            cin>>studentID;
            
            cout<<"Please input studentName:";
            cin>>studentName;
            
            cout<<"Please input studentScore:";
            cin>>studentScore;
            
            T * record=new T(studentID,studentName,studentScore);
            this->data[recordNum]= *record ;
            recordNum++;
       };

       void WriteDatabaseDataToFile(){

            FILE * pFile;
           
            const char* result = NULL;
            string temp = this->FileLogo + ".txt";
            pFile = fopen ((char*)(temp).c_str(),"a+");

            for (int i=0;i< this->recordNum;i++){
                fprintf (pFile, "%d\t\t\t\t%s\t\t\t\t%s\t\t\t\t\t\t%d\n",i,(char*)data[i].GetstudentId().c_str(),(char*)data[i].GetstudentName().c_str(),data[i].GetstudentScore());
            }

       };
       void ShowDatabase(){

            string file_name = this->FileLogo + ".txt";
            ofstream file_writer(file_name, ios_base::out);
            for (int i=0;i< this->recordNum;i++){
                file_writer << i <<"\t\t\t\t"<< data[i].GetstudentId() << "\t\t\t\t" << data[i].GetstudentName() << "\t\t\t\t"<< data[i].GetstudentScore() << endl;
                
            }
            file_writer.close();
            
       };

       void UpdateDatabase(){

            string file_name = this->FileLogo + ".txt";
            ofstream file_writer(file_name, ios_base::out);
            for (int i=0;i< this->recordNum;i++){
                file_writer << i <<"\t\t\t\t"<< data[i].GetstudentId() << "\t\t\t\t" << data[i].GetstudentName() << "\t\t\t\t"<< data[i].GetstudentScore() << endl;
                
            }
            file_writer.close();
            
       };

       
        void DeleteRecordInDatabase(){
            cout <<"Please input  information for deleting record";
            string information;
            cin>>information;
            for (int i=0;i< this->recordNum;i++){
               T record = this->data[i];
               if ((record.GetstudentId()==information)==1){
                   for(int j=i+1; j < this->recordNum; j++){
                       this->data[i] = this->data[j] ;
                   }
                   this->recordNum--;
                   
               }
           }
           UpdateDatabase();
           
       };

       void SearchRecordInDatabase(){
           cout <<"Please input  information for search record";
            string information;
            cin>>information;

            string file_name = this->FileLogo + ".txt";
            ofstream file_writer(file_name, ios_base::out);
            for (int i=0;i< this->recordNum;i++){
                if (data[i].GetstudentId() ==information){
                    cout << i <<"\t\t\t\t"<< data[i].GetstudentId() << "\t\t\t\t" << data[i].GetstudentName() << "\t\t\t\t"<< data[i].GetstudentScore() << endl;

                }
                
            }
            file_writer.close();
            
       };

};

       
class Student {
    public:
    string studentID;
    string studentName;
    int  studentScore;
    public:
    Student(){
       
    };
    
    Student(string id,string name,int score){
        this->studentID=id;
    
        this->studentName=name;

        this->studentScore =score;
       
    };
    string GetstudentId(){
        return this->studentID;
    };
    string GetstudentName(){
        return this->studentName;
    };
    int GetstudentScore(){
        return this->studentScore;

    };
    


    void ShowInformation(){
        cout<< this->studentID <<endl;
        cout<< this->studentName<<endl;
        cout<< this->studentScore<<endl; 
    };


};


int main(){
           
    DB<Student>  *db = new DB<Student>();
   
   
   int tag =1;
   do{
       db->InsertRecordInDB();
       
       cout<<"是否继续？  yes-1 No-0"<<endl;
       cin>>tag;
       if (tag ==0) {
           break;
       }else{
           continue;
       }
   }while(tag==1);
    
    db->ShowDatabase();
    db->SearchRecordInDatabase();
    db->DeleteRecordInDatabase();

}