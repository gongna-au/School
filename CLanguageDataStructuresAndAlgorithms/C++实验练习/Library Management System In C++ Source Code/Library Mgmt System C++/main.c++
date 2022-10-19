#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include"getch.h"
class Lib
{
   public:
        //bookname 书名 auname 作者名  sc Book's ID  sc1 Publication name
       char bookname[100],auname[50],sc[20],sc1[50];
}
int main(){

    ifstream intf("student.txt",ios::binary);
        system("cls");
        
        intf.read((char*)this,sizeof(*this));
        i=0;
        while(!intf.eof())
    {
        i++;
        cout<<"\n\t\t********** "<<i<<". ********** \n";
        cout<<"\n\t\tStudent Name : "<<auname<<"\n\t\t"<<"Student's ID : "<<sc1<<"\n\t\t"<<"Book Name : "<<bookname<<"\n\t\t"<<"Book's ID : "<<sc<<"\n\t\t"<<"Date : "<<q<<"/"<<B<<"/"<<p<<"\n";
        intf.read((char*)this,sizeof(Lib));
    }
    intf.close();
    return 0
}
