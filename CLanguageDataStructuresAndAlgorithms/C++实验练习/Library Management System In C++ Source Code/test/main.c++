#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include"getch.h"

void StudentLogin();
void ViewBookList();
void SearchBook();
void MainMenu();
void CloseApplication();
void ModifyOrAddBook();
void IssueBook();
void IssueAllBooks();
void ViewIssuedBook();
void SearchStudentWhoIsuuedBooks();
void ReissueBook();
void  ReturnBook();
void WrongInput();
void LibrarianLogin();
void ChangePassword();
void ModificationInCurrentBooks();
void AddNewBook();
void DeleteABook();
void  SearchByName();
void  SearchById();









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
        cout<<"\n\t*********** Library Management System ***********\n"<<"\n\t\t\t\n";
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


//LibrarianLogin 后的选项


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
                SearchByName();
            }else if (i==2){
                SearchById();
            }else if (i==3){
                LibrarianLogin();
            }else{
                WrongInput();
            }
            cout<<"\n\t\tPress any key to continue.....";
            getch();
            system("cls");
            ModificationInCurrentBooks();
}
void  SearchByName(){

}
void SearchById(){

}

void IssueBook(){
    system("cls");
    cout<<"\n\t\t->Please Choose one option :-\n";
    cout<<"\n\t\t1.Issue Book All\n\n\t\t2.View Issued Book\n\n\t\t3.Search student who isuued books\n\n\t\t4.Reissue Book\n\n\t\t5.Return Book\n\n\t\t6.Go back\n\n\t\tEnter Your Choice : ";
    int i;
    cin>>i;
    fflush(stdin);
    if(i==1){
        IssueAllBooks();
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

void IssueAllBooks(){
    cout<<"IssueAllBooks";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");


}

void ViewIssuedBook(){
    cout<<"ViewIssuedBook";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");

}

void SearchStudentWhoIsuuedBooks(){
    cout<<"SearchStudentWhoIsuuedBooks";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");

}

void ReissueBook(){
    cout<<"ReissueBook";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    

}

void  ReturnBook(){
    cout<<" ReturnBook";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");


}

void ChangePassword(){
    cout<<"ChangePassword";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
}

void GetInformation(){
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
    cout<<"AddNewBook";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
}

void DeleteABook(){
    cout<<"DeleteABook(";
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");

}

int main(){
    MainMenu();
    return 0;
}