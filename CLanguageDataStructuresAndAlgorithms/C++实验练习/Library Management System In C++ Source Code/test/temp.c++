#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include"getch.h"

void StudentLogin();
void ViewBookList();
void SearchForABook(int );
void CloseApplication();
void LibrarianLogin();
void ModifyOrAddBook();
void IssueBook();
void ChangePassword();
void MainMenu();
int SearchForABookByDifferentbranch(int );
void SearchByName(int user);
void SearchById(int user);
void AllBooks(int user);
void  GetInformation();

void IssueBook();
void ViewIssuedBook();
void SearchStudentWhoIsuuedBooks();
void ReissueBook();
void ReturnBook();

void ModificationInCurrentBooks();
void AddNewBook();
void DeleteABook();
void WrongInput();
void IssueBook();
void IssueBookAll();
void Search();
void ViewBookList();





using namespace std;
class Book
{

   public:
        //bookname 书名 auname 作者名  sc Book's ID  sc1 Publication name
       char bookname[100],auname[50],sc[20],sc1[50];
       // Quantity 数量   Price 价格
       int q,B,p;
       Book()
       {
           strcpy(bookname,"NO Book Name");
           strcpy(auname,"No Author Name");
           strcpy(sc,"No Book ID");
           strcpy(sc1,"No Book ID");
           q=0;
           B=0;
           p=0;
       }

};
class ViewBookService
{
public:
    string type;
    //调用公共的函数
	
    ViewBookService(){
        this->type="student";
    }
    ViewBookService(string x){
        this->type=x;
    }
    void ViewBookList();

};
void ViewBookService:: ViewBookList(){
            //从文件中读取数据
        
            cout<<"\n\t\tPress any key to continue.....";
            getch();
            system("cls");
            if(type=="student"){
                StudentLogin();
            }else if (type=="librarian"){
                LibrarianLogin();
            }else{
                
            }
}


void StudentLogin(){
    int i;
        cout<<"\n\t************ Welcome Student ************\n";
        cout<<"\n\t\t>>Please Choose One Option:\n";
        cout<<"\n\t\t1.View BookList\n\n\t\t2.Search for a Book\n\n\t\t3.Go to main menu\n\n\t\t4.Close Application\n";
        cout<<"\n\t\tEnter your choice : ";
        cin>>i;
            if(i==1){
               ViewBookList();

            }else if(i==2){
               SearchBook();

            }else if(i==3){
                MainMenu();

            }else if(i==4){
                CloseApplication();

            } else{
               WrongInput();
            }
            StudentLogin();


}

void ViewBookList(){
    system("cls");
    cout<<"View Book List";
}

void SearchBook(){
    system("cls");
    cout<<"Search book";
}
void MainMenu()
{   
    system("cls");
   int i;
        cout<<"\n\t*********** Library Management System ***********\n"<<"\n\t\t\t         \n";
        cout<<"\n\t\t>>Please Choose Any Option To login \n";
        cout<<"\n\t\t1.Student\n\n\t\t2.Librarian\n\n\t\t3.Close Application\n";
        cout<<"\n\t\tEnter your choice : ";
        cin>>i;
        if(i==1)
        {
            StudentLogin();
        }else if(i==2){
            LibrarianLogin();

        }else if(i==3){
            CloseApplication();

        }else{
            WrongInput();
        }
        MainMenu();
}

void CloseApplication(){
    exit(0);
}
void WrongInput(){
    cout<<"\n\t\tPlease enter correct option :(";
    getch();
    system("CLS");

}








//studentLogin 后的选项
void SearchForABook(int user){

    int department;
    department=SearchForABookByDifferentbranch(user);
    
     //得到类别   
    ifstream intf("Booksdata.txt",ios::binary);
    //根据类别查找
    if (department==8){
        AllBooks(user);
    }else{
        if(!intf){
                cout<<"\n\t\tFile Not Found.\n";
                cout<<"\n\t\t->Press any key to continue.....";
                getch();
                system("cls");
                //回调
                if(user==2){
                    LibrarianLogin();
                }else {
                    StudentLogin();
                }
        }else{
            system("cls");
            cout<<"\n\t\tPlease Choose one option :-\n";
            cout<<"\n\t\t1.Search By Name\n\n\t\t2.Search By Book's ID\n";
            cout<<"\n\t\tEnter Your Choice : ";
            int i;
            cin>>i;
            fflush(stdin);
            if (i==1){
                SearchByName(user);
            }else if (i==2){
                SearchById(user);
            }else{
                cout<<"\n\t\tPress any key to continue.....";
                //getch();
                system("cls");
                //回调
                if(user==1){
                    StudentLogin();
                }else{
                    LibrarianLogin();
                }
            }

        }
            
    }

}


void AllBooks(int user){

    cout<<"AllBooks";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    if(user==2){
         LibrarianLogin();
    }else{
        StudentLogin();
    }
    
}
void SearchByName(int user){
    cout<<"SearchByName";
    if(user==2){
         LibrarianLogin();
    }else{
        StudentLogin();
    }


}
void SearchById(int user){
     cout<<"SearchById";
     if(user==2){
         LibrarianLogin();
    }else{
        StudentLogin();
    }

}

int SearchForABookByDifferentbranch(int user){
    
      cout<<"\n\t\t>>Please Choose one Branch :-\n";
        //IT类的书籍     教育学   犯罪学   工程学
      cout<<"\n\t\t1.IT Department\n\n\t\t2.Educate Department\n\n\t\t3.Criminology Department\n\n\t\t4.Art Book Department\n\n\t\t5.Engineering Department\n\n\t\t6.Computer Science Department\n\n\t\t7.Go to menu\n\n\t\t8.All Departments";
      cout<<"\n\t\tEnter your choice : ";
      int i;
      cin>>i;

      switch(i)
      {
          case 1: return 1;
                  break;
          case 2: return 2;
                  break;
          case 3: return 3;
                  break;
          case 4: return 4;
                  break;
          case 5: return 5;
                  break;
          case 6: return 6;
                  break;
          case 8: return 8;
                  break;
          case 7: system("cls");
                  if(user==1){
                      StudentLogin();
                  }else{
                      LibrarianLogin();
                  }

          default : cout<<"\n\t\tPlease enter correct option :(";
                    getch();
                    //调用系统命令cls完成清屏操作。
                    system("cls");
                    //继续调用自己
                    SearchForABookByDifferentbranch(user);
                   
        }
         return 8;

}
void ShowInformation(int user){
        cout<<"\n\t\tBook Name : "<<endl;
        cout<<"\n\t\tBook's Author Name : "<<endl;
        cout<<"\n\t\tBook's ID : "<<endl;
        cout<<"\n\t\tBook's Publication : "<<endl;
        if(user==2)
        {
            cout<<"\n\t\tBook's Price : "<<" "<<endl;
            cout<<"\n\t\tBook's Quantity : "<<" "<<endl;
        }

}



//studentLogin 后的选项


void LibrarianLogin(){
    int i;
        cout<<"\n\t************ Welcome Librarian ************\n";
        cout<<"\n\t\t>>Please Choose One Option:\n";
        cout<<"\n\t\t1.View BookList\n\n\t\t2.Search for a Book\n\n\t\t3.Modify/Add Book\n\n\t\t4.Issue Book\n\n\t\t5.Go to main menu\n\n\t\t6.Change Password\n\n\t\t7.Close Application\n";
        cout<<"\n\t\tEnter your choice : ";
        cin>>i;
        if (i==1){
             ViewBookList();
                

        }else{
            switch(i){
            case 2:
                    SearchBook();
                    break;
            case 3:
                    ModifyOrAddBook();
                     break;
            case 4:
                    IssueBook();
                     break;
            case 5:
                    MainMenu();
                    break;
            case 6:
                    ChangePassword();
                    break;
            case 7:
                    CloseApplication();
            default:
                    WrongInput();
                   
            }

        }   
        LibrarianLogin();

}

//LibrarianLogin 后的选项
void ModifyOrAddBook(){
    int i=0;
    system("cls");
    cout<<"\n\t\t>>Please Choose one option :-\n";
    cout<<"\n\t\t1.Modification In Current Books\n\n\t\t2.Add New Book\n\n\t\t3.Delete A Book\n\n\t\t4.Go back\n";
    cout<<"\n\n\t\tEnter your choice : ";
    cin>>i;
    if(i==1){
        ModificationInCurrentBooks();                     
    }else if(i==2){

        AddNewBook();
    }else if(i==3){

        DeleteABook();

    }else if(i==4){
        LibrarianLogin();

    }else{
        WrongInput();
        
    }
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    ModifyOrAddBook();
}

void ModificationInCurrentBooks(){
            int i;
            cout<<"\n\t\tPlease Choose One Option :-\n";
            cout<<"\n\t\t1.Search By Book Name\n\n\t\t2.Search By Book's ID\n\n\t\t3.Go back\n";
            cout<<"\n\t\tEnter Your Choice : ";
            cin>>i;
            if (i==1){
                SearchByName(2);
            }else if (i==2){
                SearchById(2);
            }else{
                WrongInput();
                ModificationInCurrentBooks();
            }
            ModificationInCurrentBooks();


}



void IssueBook(){
    system("cls");
    cout<<"\n\t\t->Please Choose one option :-\n";
    cout<<"\n\t\t1.Issue Book All\n\n\t\t2.View Issued Book\n\n\t\t3.Search student who isuued books\n\n\t\t4.Reissue Book\n\n\t\t5.Return Book\n\n\t\t6.Go back\n\n\t\tEnter Your Choice : ";
    int i;
    cin>>i;
    fflush(stdin);
    if(i==1){
        IssueBook();
    }else if(i==2){
        ViewIssuedBook();
    }else if(i==3)
    {
        SearchStudentWhoIsuuedBooks();
    }else if(i==4){
        ReissueBook();
    }else if(i==5){
        ReturnBook();
    }else if(i==6){
        LibrarianLogin();
    }else{
          WrongInput();
    }

    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    IssueBook();

}

void ChangePassword(){
    cout<<"ChangePassword";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
}

void  GetInformation(){
                int i;
                    fflush(stdin);
                    cout<<"\n\t\tEnter the details  :-\n";
                    cout<<"\n\t\tEnter the details :";
                    cout<<"\n\t\tEnter Author's Name : ";
                    //cin.getline(auname,50);
                    cout<<"\n\t\tEnter Publication name : ";
                   // cin.getline(sc1,50);
                    cout<<"\n\t\tEnter Book's ID : ";
                    //cin.getline(sc,20);
                    cout<<"\n\t\tEnter Book's Price : ";
                    //cin>>p;
                    cout<<"\n\t\tEnter Book's Quantity : ";
                    //cin>>q;


}




void AddNewBook(){



}
void DeleteABook(){


}






//-------------------------------------------------


void IssueBookALL(){
    cout<<"IssueBook";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    LibrarianLogin();
    
}
void ViewIssuedBook(){
    cout<<"ViewIssuedBook";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    LibrarianLogin();

}
void SearchStudentWhoIsuuedBooks(){
    cout<<"SearchStudentWhoIsuuedBooks";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    LibrarianLogin();
}
void ReissueBook(){
    cout<<"ReissueBook";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    LibrarianLogin();

}
void ReturnBook(){
    cout<<"ReturnBook";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    LibrarianLogin();


}
//------------------------------------------------------------




//LibrarianLogin 后的选项


int main(){
    MainMenu();
    return 0;
}