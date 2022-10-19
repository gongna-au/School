#include<iostream>
#include <math.h>
#include "student.h"
#include "Db.h"
#include <fstream>
using namespace std;
int main(){
    int n;
    cout<<"Please input student number:";
    cin>>n;

    student*  studentIDataArray[n];
    cout<<"Please input student information:";
    
    string  studentId;
    string  studentName;
    int  studentScore;

    for (int i=0;i<n;i++ ) {
        
        cout<<"studentID:";
        cin>>studentId;

        cout<<"studentName:";
        cin>>studentName;

        cout<<"studentScore:";
        cin>>studentScore;

        studentIDataArray[i]= new student(studentId,studentName,studentScore);
    }     
        
    
    string databaseName;

    /* cout<<"Please create your database:";
    cin >>databaseName; */

    DataBase* DB = new DataBase;

    for (int i = 0; i < 10;i++){

        DB->storeRecord(studentIDataArray[i]);

    }
    DB->getAllRecordInDatabase();

}