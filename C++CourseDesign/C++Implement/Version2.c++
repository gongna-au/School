
#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

//一旦登陆成功就把这个赋值

string UserGlobalIdCard="";
class chooseOrlers;

// -----------------------------------------------------抽象的接口
//观察者接口
class IObserver {
 public:
  virtual ~IObserver(){};
  virtual void Update() = 0;
};


//被观察者接口
class ISubject {
 public:
  virtual ~ISubject(){};
  virtual void Attach(IObserver *observer) = 0;
  virtual void Detach(IObserver *observer) = 0;
  virtual void Notify() = 0;
};


//Subject 一个抽象的状态变化的被观察者 
//所以需要存储观察者因为被观察者要通知观察者
//这个抽象的被观察者实现了把观察者添加到列表Attach
//这个抽象的被观察者实现了把观察者删除Detach
//这个抽象的被观察者实现了通知把观察者Notify() 
//Notify()的逻辑就是观察者开始执行自己的业务函数
//所以观察者都要把最终的业务逻辑放在Notify()里面
//然后其余的部分实现数据的数据以及存储
class Subject : public ISubject 
{
 public:
  list<IObserver *> ListObserver;
  string Message;
  int funcListNum;

 public:
    Subject(){
        this->funcListNum=0;
    }
    virtual ~Subject() {
        cout << "Goodbye, I was the Subject.\n";
    }

    // Attach 注册观察者
    // @param $observer ObserverInterface 观察者列表
    // Attach 注册观察者
    // @param $observer ObserverInterface 观察者列表
    // IObserver 把实现了观察者接口Update的都存储起来
  void Attach(IObserver *observer) override {
    ListObserver.push_back(observer);
  }

    // Detach 注销观察者
    // @param $observer ObserverInterface 待注销的观察者

  void Detach(IObserver *observer) override {
   ListObserver.remove(observer);
  }

// Notify 通知观察者
  void Notify() override {
     /*  list<IObserver *>::iterator iterator = ListObserver.end();
     (*iterator)->Update(); */


     list<IObserver *>::iterator iterator = ListObserver.begin();
    int i=0;
    while (iterator != ListObserver.end()) {
        //观察者开始执行函数
        if (i==funcListNum){
            (*iterator)->Update();
            this->funcListNum++;
            break;
        }
        i++;
        ++iterator;
    } 
    /* 因为都是插入在尾部，想要直接调用尾部的函数
    但是会报错*/
  }
};



// 具体的功能 ---------------------------------------------------------------------------
// 增加新的功能增加新的类  
// 只要重写Update()函数就会被被 Notify()执行
// 或者被Attacht添加到执行的列表当中
class  GeneralUserCreate: public IObserver {
 public:
  map < string, string > DetailsInformation;
 public:
  GeneralUserCreate(){  
  }
  void Input(){
      string s1,s2;
      cout<<"Please input user userId:";
      cin>>s1;
      DetailsInformation.insert(pair < string, string >("userId",s1));
      cout<<"Please input user password:";
      cin>>s2;
      DetailsInformation.insert(pair < string, string >("password",s2));
      for ( map < string, string >::iterator iter=DetailsInformation.begin();iter != DetailsInformation.end(); iter++){
            cout << iter->first << " : " << iter->second << endl;
    }

  }

  virtual ~GeneralUserCreate() {
    cout << "新增用户相关的操作处理完毕...\n";
  }

  void Update() override {
        cout<<"正在执行业务函数-新增用户\n";
        Input();
        cout<<"新增用户业务函数执行结束\n";
  }
};

class  SuperUserCreate: public IObserver {
  public:
  map < string, string > DetailsInformation;

 public:
  SuperUserCreate(){
    
    }
  void Input(){
      string s1,s2;
      cout<<"Please input librarian Id:";
      cin>>s1;
      DetailsInformation.insert(pair < string, string >("userId",s1));
      cout<<"Please input librarian password:";
      cin>>s2;
      DetailsInformation.insert(pair < string, string >("password",s2));
      for ( map < string, string >::iterator iter=DetailsInformation.begin();iter != DetailsInformation.end(); iter++){
            cout << iter->first << " : " << iter->second << endl;
        }
  }
  void InsertInDB(){
      cout << "往数据库插入图书管理员成功！\n";
  }
  virtual ~SuperUserCreate() {
    cout << "新增图书管理员相关的操作处理完毕...\n";
  }

  void Update() override {
       cout<<"正在执行业务函数-新增图书管理员\n";
        Input();
        InsertInDB();
        cout<<"新增图书管理员业务函数执行结束\n";
  }
  
};
class  UserLogin: public IObserver {
    public:
    string  userId;
    string  password;

    public:
    UserLogin(){

        userId="";
        password="";  
    }
    void Input(){
        for(;;){
            string s1,s2;
            cout<<"Please input userId :";
            cin>>s1;
            userId=s1;
            cout<<"Please input  password:";
            cin>>s2;
            password=s2;
            if (SearchInDB()){
                //用户身份得到赋值
                UserGlobalIdCard=s1;
                break;
            }else{
                cout << "账户和密码不正确！\n";
                continue;
            } 
        }  
    }
  virtual ~ UserLogin() {
    cout << "用户登陆的相关的操作处理完毕...\n";
  }
  //数据库和文件操作
  bool SearchInDB(){
      cout << "正在验证账户和密码是否正确...\n";
      cout << "账户和密码正确!\n";
      cout << "登陆成功！\n";
      return true;
  }
  void Update() override {
        cout<<"正在执行业务函数-读者登陆\n";
        Input();
        SearchInDB();
        cout<<"读者登陆业务函数执行结束!\n";
  }
  
};
class  SuperUserLogin: public IObserver {
    public:
    string  userId;
    string  password;

    public:
    SuperUserLogin(){
        userId="";
        password=""; 
    }

    void Input(){
        string s1,s2;
        cout<<"Please input librarian Id:";
        cin>>s1;
        userId=s1;

        cout<<"Please input librarian password:";
        cin>>s2;
        password=s2;
        for(;;){

            if (SearchInDB()){
                break;
            }else{
                cout << "账户和密码不正确！\n";
                continue;
            }
        } 
    }
    //数据库和文件操作
    bool SearchInDB(){
        cout << "正在验证图书管理员的账户和密码是否正确...\n";
        cout << "账户和密码正确!\n";
        cout << "图书管理员登陆成功！\n";
        return true;
    }
    virtual ~SuperUserLogin() {
            cout << "图书管理员登陆相关的操作处理完毕...\n";
    }

    void Update() override {
            cout<<"正在执行业务函数-图书管理员登陆\n";
            Input();
            SearchInDB();
            cout<<"图书管理员登陆业务函数执行结束\n";
    }
  
};



class  UserDelete: public IObserver {
    public:
        string  userId   ;
        string  password ;

    public:
    UserDelete(){
        userId ="";
        password ="";
    }
    void Input(){
        string s1,s2;
        cout<<"Please input user userId:";
        cin>>s1;
        this->userId=s1;
        cout<<"Please input user password:";
        cin>>s2;
        this->password=s2;
        cout<< "userId is "<<userId <<"password is "<<password;
        for(;;){
            if (SearchInDB()){
                break;
            }else{
                cout << "账户和密码不正确！\n";
                continue;
            }
        } 
    }
     //数据库和文件操作
    bool SearchInDB(){
        cout << "正在验证用户账户和密码是否正确...\n";
        cout << "账户和密码正确!\n";
        return true;
    }
    virtual ~UserDelete() {
        cout << "注销用户相关的操作处理完毕...\n";
    }
    void Update() override {
            cout<<"正在执行业务函数-注销用户\n";
            Input();
            SearchInDB();
            cout<<"注销用户业务函数执行结束\n";
    }
};

class  SearchBook: public IObserver {
    public:
        string  bookName ;

    public:
    SearchBook(){
        bookName ="";
    }
    void Input(){
        string s1,s2;
        cout<<"Please enter the book Name:";
        cin>>s1;
        this->bookName=s1;
        for(;;){
            if (SearchInDB()){
                break;
            }else{
                cout << "账户和密码不正确！\n";
                continue;
            }
        } 
    }
     //数据库和文件操作
    bool SearchInDB(){
        cout << "正在查找书籍...\n";
        cout << "书籍查找成功！\n";
        return true;
    }
    virtual ~SearchBook() {
        cout << "查找书籍相关的操作处理完毕...\n";
    }
    void Update() override {
            cout<<"正在执行业务函数-查找书籍\n";
            Input();
            SearchInDB();
            cout<<"查找书籍业务函数执行结束\n";
    }
};
class  BorrowBook: public IObserver {
    public:
        string  bookItemBarcode;
        string  userId;

    public:
    BorrowBook(){
        //书籍条码
        bookItemBarcode ="";
    }
    void Input(){
        string s1,s2;
        cout<<"Please enter the book barcode or scan the book barcode at the scanning port:";
        cin>>s1;
        this->bookItemBarcode=s1;
        for(;;){
            if (SearchInDB()){
                break;
            }else{
                cout << "账户和密码不正确！\n";
                continue;
            }
        } 
    }
     //数据库和文件操作
    bool SearchInDB(){
        cout << "正在借阅书籍...\n";
        cout <<"User:"<< UserGlobalIdCard;
        cout << "书籍借阅成功！\n";
        return true;
    }
    virtual ~BorrowBook() {
        cout << "借阅书籍相关的操作处理完毕...\n";
    }
    void Update() override {
            cout<<"正在执行业务函数-借阅书籍\n";
            Input();
            SearchInDB();
            cout<<"借阅书籍业务函数执行结束\n";
    }
};
class  BackBook: public IObserver {
    public:
        string  bookItemBarcode;
        string  userId;
    public:
    BackBook(){
        //书籍条码
        bookItemBarcode ="";
    }
    void Input(){
        string s1,s2;
        cout<<"Please enter the book barcode or scan the book barcode at the scanning port:";
        cin>>s1;
        this->bookItemBarcode=s1;

        for(;;){
            if (SearchInDB()){
                break;
            }else{
                cout << "账户和密码不正确！\n";
                continue;
            }
        } 
    }
     //数据库和文件操作
    bool SearchInDB(){
        cout << "正在归还书籍...\n";
        cout <<"User:"<< UserGlobalIdCard;
        cout << "书籍归还成功！\n";
        return true;
    }
    virtual ~BackBook() {
        cout << "归还书籍相关的操作处理完毕...\n";
    }
    void Update() override {
            cout<<"正在执行业务函数-归还书籍\n";
            Input();
            SearchInDB();
            cout<<"归还书籍业务函数执行结束\n";
    }
};
class NotifyReader: public IObserver {
    public:
    list<string>  readerOverdueList;
    public:
    NotifyReader(){
        readerOverdueList.push_back("2020213710");
        readerOverdueList.push_back("2020213720");
        readerOverdueList.push_back("2020213730");
        readerOverdueList.push_back("2020213740");
        readerOverdueList.push_back("2020213750");
        readerOverdueList.push_back("2020213760");
    }
     //数据库和文件操作
    bool SearchInDB(){

        cout << "正在查询逾期的读者...\n";
        list<string>::iterator it;
        cout << "已逾期的读者有\n";
        for (it =readerOverdueList.begin();it!=readerOverdueList.end();it++){
            cout<< (*it )<<endl;
        }
        cout << "通知已逾期的读者成功\n";
        return true;
    }
    virtual ~NotifyReader() {
        cout << "归还书籍相关的操作处理完毕...\n";
    }
    void Update() override {
            cout<<"正在执行业务函数-通知逾期读者\n";
            SearchInDB();
            cout<<"通知逾期读者业务函数执行结束\n";
    }
};
class Book {
    public:
    string ISBN;
    string Title;
    string Subject;
    string Publisher;
    string Language;
    string Author;
    public:
    Book(){
    };
    void Input (){
        cout<<"Please inoup book ISBN:";
        cin>>ISBN;
        cout<<"Please inoup book Title:";
        cin>>Title;
        cout<<"Please inoup book Subject:";
        cin>>Subject;
        cout<<"Please inoup book Publisher:";
        cin>>Publisher;
        cout<<"Please inoup book Language:";
        cin>>Language;
        cout<<"Please inoup book Author:";
        cin>>Author;
    }
    void ShowBookInfo(){
            cout<<"ISBN:"<<ISBN<<endl;
            cout<<"Title:"<<Title<<endl;
            cout<<"Subject:"<<Subject<<endl;
            cout<<"Publisher:"<<Publisher<<endl;
            cout<<"Language:"<<Language<<endl;
            cout<<"Author:"<<Author<<endl;
    }
};

class AddBook: public IObserver {
    public:
    list<Book* >  bookList;
    public:
    AddBook(){  
    }
    void Input(){
        cout << "请输入要上架的书籍的信息:";
        Book* book= new Book();
        book->Input();
        bookList.push_back(book); 

    }
     //数据库和文件操作
    bool InsertInDB(){
        cout << "正在往数据库添加书籍\n";
        bookList.back()->ShowBookInfo(); 
        cout << "书籍添加成功！\n";
        return true;
    }
    virtual ~AddBook() {
        cout << "添加书籍相关的操作处理完毕...\n";
    }
    void Update() override {
            cout<<"正在执行业务函数-往数据库添加书籍\n";
            Input();
            InsertInDB();
            cout<<"添加书籍业务函数处理完毕\n";
    }
};

class DeleteBook: public IObserver {
    public:
    list<Book* >  bookList;
    public:
    DeleteBook(){
             
    }
    void Input(){
        cout << "请输入要删除的书籍的信息:";
        Book* book= new Book();
        book->Input();
        bookList.push_back(book); 
    }
     //数据库和文件操作
    bool DeleteInDB(){
        cout << "正在删除目标书籍......\n";
        bookList.back()->ShowBookInfo(); 
        cout << "目标书籍删除成功！\n";
        return true;
    }
    virtual ~  DeleteBook() {
        cout << "删除书籍相关的操作处理完毕...\n";
    }
    void Update() override {
            cout<<"正在执行业务函数-删除数据库中的目标书籍\n";
            Input();
            DeleteInDB();
            cout<<"删除数据库中的目标书籍业务函数处理完毕\n";
    }
};

class EditBook: public IObserver {
    public:
    list<Book* >  bookList;
    public:
   EditBook(){
           
    }
    void Input (){

        Book* book= new Book();
        cout << "请输入更新后的书籍信息\n";
        book->Input();
        bookList.push_back(book);  

    }
     //数据库和文件操作
    bool UpdateInDB(){
        cout << "正在更新目标书籍......\n";
        bookList.back()->ShowBookInfo(); 
        cout << "目标书籍更新成功！\n";
        return true;
    }
    virtual ~   EditBook() {
        cout << "更新书籍相关的操作处理完毕...\n";
    }
    void Update() override {
            cout<<"正在执行业务函数-删除数据库中的目标书籍\n";
            Input();
            UpdateInDB();
            cout<<"删除数据库中的目标书籍业务函数处理完毕\n";
    }
};

//Reserve
class ReserveBook: public IObserver {
    public:
    list<Book* >  bookList;
    public:
   ReserveBook(){
       // cout << "新增一笔预定书籍业务\n";      
    }
    void Input(){
        cout << "请输入预定的书籍信息\n";
        Book* book= new Book();
        book->Input();
        bookList.push_back(book);
    }
     //数据库和文件操作
    bool ReserveInDB(){
        cout << "正在预定目标书籍......\n";
        bookList.back()->ShowBookInfo(); 
        cout << "预定目标书籍更新成功！\n";
        return true;
    }
    virtual ~   ReserveBook() {
        cout << "预定书籍相关的操作处理完毕...\n";
    }
    void Update() override {
            cout<<"正在执行业务函数-预定数据库中的目标书籍\n";
            Input();
            ReserveInDB();
            cout<<"预定数据库中的目标书籍业务函数处理完毕\n";
    }
};
//Cancel

class ReserveCancel: public IObserver {
    public:
    list<Book* >  bookList;
    public:
   ReserveCancel(){
        //cout << "新增一笔取消预定书籍业务\n"; 
    }
     void Input(){
        cout << "请输入取消预定的书籍信息\n";
        Book* book= new Book();
        book->Input();
        bookList.push_back(book);
    }
    

     //数据库和文件操作
    bool ReserveInDB(){
        cout << "正在取消预定......\n";
        bookList.back()->ShowBookInfo(); 
        cout << "取消预定操作成功！\n";
        return true;
    }
    virtual ~   ReserveCancel() {
        cout << "取消预定书籍相关的操作处理完毕...\n";
    }
    void Update() override {
            cout<<"正在执行业务函数-取消预定书籍\n";
            Input();
            ReserveInDB();
            cout<<"取消预定书籍业务函数处理完毕\n";
    }
};

//redecorate

class RedeCorateBook: public IObserver {
    public:
    list<Book* >  bookList;
    public:
   RedeCorateBook(){
        //cout << "新增一笔续借书籍业务\n";
    }
    void Input(){
        cout << "请输入续借的书籍信息\n";
        Book* book= new Book();
        book->Input();
        bookList.push_back(book);
    }
     //数据库和文件操作
    bool ReserveInDB(){
        cout << "正在续借书籍......\n";
        bookList.back()->ShowBookInfo(); 
        cout << "续借书籍操作成功！\n";
        return true;
    }
    virtual ~   RedeCorateBook() {
        cout << "续借书籍相关的操作处理完毕...\n";
    }
    void Update() override {
            cout<<"正在执行业务函数-续借书籍\n";
            Input();
            ReserveInDB();
            cout<<"续借书籍业务函数处理完毕\n";
    }
};
class Fine{
    public:
    int Amount;
    string FinedAccount;
    Fine(){
        cout<<"Please input FinedAccountId:";
        cin>>FinedAccount;
        //罚款金额
        cout<<"Please input penalty:";
        cin>>Amount;
    };

};


//Fine 
class ReaderFine: public IObserver {
    public:
    list<Fine* >  fineList;
    public:
   ReaderFine(){
       //cout << "新增一笔读者缴纳罚款业务\n";
         
    }
    void Input(){
         cout << "请输入罚款相关信息：\n";
         Fine* fine= new Fine();
         fineList.push_back(fine);   
    }
     //数据库和文件操作
    bool payFines(){
        cout << "正在缴纳罚款......\n";
        cout << "缴纳罚款操作成功！\n";
        return true;
    }
    virtual ~   ReaderFine() {
        cout << "缴纳罚款相关的操作处理完毕...\n";
    }
    void Update() override {
            cout<<"正在执行业务函数-缴纳罚款\n";
            Input();
            payFines();
            cout<<"缴纳罚款业务函数处理完毕\n";
    }
};

class SearchItem{
    public:
    ~SearchItem(){
    };
    virtual void TitleSearch() = 0;
    virtual void AuthorSearch() = 0;
    virtual void SubjectSearch() = 0;
    virtual void PublicationbDateSearch() = 0;
    virtual int GetChoiceType() = 0;
};


class SearchChoiceItem: public SearchItem{
    public:
    list<string> itemList;
    int searchType;
    list<string> userInputInfoList;
    public:
    SearchChoiceItem(){
        itemList.push_back("Title");
        itemList.push_back("Subject");
        itemList.push_back("Publisher");
        itemList.push_back("Author");
        int i=0;
        for (list<string> :: iterator it=itemList.begin();it!=itemList.end();it++){
                cout<<">>"<<i<<(*it)<<endl;
                i++;
        }
        cout<<"Please input your choice :";
           
        for(;;){
             cin>>searchType;
            if (searchType>=0 && searchType<i){ 
                break;
            }else{
                cout<<"Input Ilegal!Please input again!"<<endl;
            }
        }

    };
     //数据库和文件操作
     void TitleSearch()override{
         cout << "请输入书籍标题:";
         string info;
         cin>>info;
         userInputInfoList.push_front(info);
     };

     void AuthorSearch() override{
            cout << "请输入书籍作者:";
            string info;
            cin>>info;
            userInputInfoList.push_front(info);
     };
     void SubjectSearch()override{
         cout << "请输入学科类别:";
         string info;
        cin>>info;
        userInputInfoList.push_front(info);
     };
     void  PublicationbDateSearch()override{
         cout << "请输入出版时间:";
         string info;
         cin>>info;
         userInputInfoList.push_front(info);

     };
     int GetChoiceType(){
         return searchType;
     };

 
};


class SearchBycatalog: public IObserver {
    public:
    //抽象的接口做参数
    SearchItem* item;
    public:
   SearchBycatalog( ){
      
    }
    void Input(){

        SearchChoiceItem* s=new SearchChoiceItem();
         if(s->searchType==0){
             s->TitleSearch();
        }else if(s->searchType==1){
            s->SubjectSearch();
        }else if(s->searchType==2){
            s->PublicationbDateSearch();

        }else if(s->searchType==3){
            s->AuthorSearch();
            
        }
    }
     //数据库和文件操作
    bool SearchInDB(){
        cout << "正在查找......\n";
        cout << "查找操作成功！\n";
        return true;
    }
    virtual ~   SearchBycatalog() {
        cout << "按照书籍的不同类别查找相关的操作处理完毕...\n";
    }
    void Update() override {
            cout<<"正在执行业务函数-按照书籍的不同类别查找书籍\n";
            Input();
            SearchInDB();
            cout<<"按照书籍的不同类别查找书籍业务函数处理完毕\n";
    }
};

class  Commodity{
    public:
    string CommodityCoding;

    public:
    Commodity(){
       CommodityCoding="";
    }
    void Input(){
           cout<<"请输入你选择的商品的条码:";       
           cin>>this->CommodityCoding;    
    }
};


class BookOrlders{
    public:
    string user;
    list<Commodity* >  CommodityList;
    BookOrlders(){
    }
    //可以多次调用实现添加多个商品
    void AddOrlders(){
        Commodity* c=new Commodity();
        c->Input();
        CommodityList.push_back(c);
        cout<<"商品添加到购物车成功～\n";
    }
    list<Commodity*>  SubmitOrlders(){
        return  CommodityList;
    }
};

class Mediator ;
//提前声明
class ChooseOrlers: public IObserver {
    public:
    //抽象的接口做参数
    //通过中介者沟通
    Mediator *mediator;
    BookOrlders* orlders;
    string user;

    public:
    ChooseOrlers(){

            cout<<"Please input user Id And passsword to login!\n";
            cout<<"Please input user Id:";
            cin>>user;
            cout<<"Please input user password:";
            string temp;
            cin>>temp;
            cout<<" login success!You can choose book you want!\n";
            
    };

    void ChooseBooksInShoppingCart(){

            orlders =new BookOrlders();
            cout<<"start choose first book...\n";
            orlders->AddOrlders();
            cout<<"choose first book success!\n"; 
            cout<<"start choose second book...\n";
            orlders->AddOrlders();
            cout<<"choose second book success!\n"; 
            cout<<"choose over\n";
    }
     //数据库和文件操作
    bool InsertInDB(){
        cout << "正在用户购物车里面的数据插入到数据库...\n";
        return true;
    }
    virtual ~   ChooseOrlers() {
        cout << "往购物车中添加书籍相关的操作处理完毕...\n";
    }
    
    void Update() override {
            cout<<"正在执行业务函数-往购物车中添加书籍\n";
            ChooseBooksInShoppingCart();
            InsertInDB();
            cout<<"往购物车中添加书籍业务函数处理完毕\n";
    }
    
};

class Mediator  {
 public:
    //组件设置
     virtual void SetComponents(string event, IObserver *sender)  = 0;
     //组件交流
     virtual void ComponentsChat()  = 0;
};
//一个具体的中介者

class PaymentMediator : public Mediator {
    //支付业务需要沟通的组件有
 public:
  map<string,IObserver *>ComponentsMap;
  //map的特性导致在交流时
  //同一个类的指针只能有一个
 public:
    PaymentMediator(){
  }
  void SetComponents(string event,IObserver *sender) override {
      //把需要沟通的组件都放进
      ComponentsMap.insert(pair < string, IObserver *>(event,sender));
      //让他们进行沟通
  }
  //只能两个组件之间交流
   void ComponentsChat()override {
       //获取子类的成员变量
       //可以向下传递数据
        ChooseOrlers* chooseOrlers;

    if (ComponentsMap.find("ChooseOrlers") == ComponentsMap.end()){    

    }else{
        //cout<<"父类向子类转化成功！\n";
        chooseOrlers=dynamic_cast< ChooseOrlers *>( ComponentsMap["ChooseOrlers"]);
    }

    cout<< "user:"<<chooseOrlers->user<<"is paying....\n";
    chooseOrlers->Update();
    cout<< "user:"<<chooseOrlers->user<<"has paid  over\n";
    
  }
 
};

class SubmitBookOrlders: public IObserver {
    public:
    //通过中介者沟通
    Mediator *mediator;
   /*  BookOrlders* orlders;
    string user; */
    string discount;

    public:
       SubmitBookOrlders(){
           discount="90%";
    }
    
     //数据库和文件操作
    bool SearchInDB(){
        cout << "正在拉起支付页面......\n";
        cout << "支付成功！\n";
        return true;
    }
     ~SubmitBookOrlders() {
        cout << "购买书籍相关的操作处理完毕...\n";
    }
    void Update() override {

           cout<<"正在执行业务函数-新增一笔新的书籍购买订单\n";
                //设置好交流者调用他们之间的交流方式由具体的交流者PaymentIObserverMediator负责
               
                this->mediator =new PaymentMediator();
                
               
                //提交页面想要和选择页面进行沟通

                
                ChooseOrlers* fc =new ChooseOrlers();
                
                //放入的是一个空的交流者，因为我什么数据都没有填入到它里面
                //标志我放入的是哪个交流者，因为，可以和多个交流者进行交流，但是每个交流者只能有一个
                this->mediator->SetComponents("ChooseOrlers",fc);
                //开始交流
                this->mediator->ComponentsChat();     

                cout<<"书籍购物订单业务处理完毕\n";
    }
    
};


void TestPayment() {

    SubmitBookOrlders *s=new SubmitBookOrlders();
    cout<<"893893898";
    s->Update();
    
}



//--------------------------------------实现监听获得用户的输入-----------------------
class Button {
    public:
    list<string> Information;
    map<string,string>  legalOptionsInformation;
	string  bePressed ;
    bool   isLegal;
    string legalOptions;
    
    Button(const string a[],int n){
        cout<<"Start creating a new button......"<<endl;
        bePressed="";
        isLegal=false;
        for (int i=0;i<n;i++){
            Information.push_back(a[i]);   
            string key=to_string(i);
            legalOptionsInformation.insert(pair<string, string>(key, a[i])); 
            legalOptions=legalOptions+key;
            
        }
        cout<<"New button has been created!"<<endl;
    };
    void showbePressedButtonInfo(){
        map< string, string >::iterator iter = legalOptionsInformation.find(bePressed);
        if(iter!= legalOptionsInformation.end())
        {
            cout<<bePressed <<"number button is pressed......"<<endl;
            
        }
        
    };
    void showButtonInformation(){
        int i=0;
        for (list<string>::iterator iter = Information.begin(); iter != Information.end(); ++iter) {
            cout <<" >>" <<i <<"."<<*iter << "\n";
            i++;
        }
    };
    void listenButtonBePressed(){
         cout<<"The button starts listening for user input......"<<endl;
        for(;;){
            this->showButtonInformation();
            cout<<"Please input your choice:";
            cin>>bePressed;
            bePressed=bePressed.substr(0,1);
            if (InputIsLegal()==1){
              
                break;
            }else{
                cout<<"illegal Input\n";
                continue;  
            }
        }
         cout<<"Button listen user input over"<<endl;
    };
    bool InputIsLegal(){
        string::size_type idx;
        idx=legalOptions.find(bePressed); 
        if (idx == string::npos ){
            return false;
        }else {
            return true;
        }
    };
    string GetButtonInfo(){
        return legalOptionsInformation[bePressed];
    };

};


//---------------------------测试函数------------
void ClientCode() {
  //被观察者
 Subject *subject = new Subject;
    string a[]={"用户注册","用户登陆","搜索图书"};
    Button* button =new Button(a,3);
    button->listenButtonBePressed();
    cout<< button->GetButtonInfo();

    if (button->bePressed.compare("0")==0){
         GeneralUserCreate*u=new GeneralUserCreate();
         subject->Attach(u);
         subject->Notify();
          delete u; 
    }


};

// ----------------------------在获取到用户输入后触发执行函数---------
void ExcuteInterfaceFunc(ISubject* s ,IObserver * o){
    s->Attach(o);
    s->Notify();   
}
//页面的刷新？就是button的重新赋值 
class Page {
    public:
    int lastpageId;
    Subject * subject;
    Button* button;
    map<string,IObserver*> buttonfuncMap;

    //只调用一次
    Page(Subject *s ){
        lastpageId=0;
        subject=s;
    };
    //每个页面都知道每个按钮被按下时将会发生什么 只要传进去我们需要的按钮
    //就会得到得到新的页面 并且监听执行 
    void PageFeaturesInit( string a[] ,int n,IObserver* funcList[]){
        //加载按钮
        //主页面功能的初始化
        cout<<"Main Page Features Init......"<<endl;
        this->button =new Button(a,n);
        for (int i=0;i<n;i++){
           string key=to_string(i);
           //所有的功能都已经准备好了
           //等待用户输入执行函数就可以
           this->buttonfuncMap.insert(pair<string, IObserver*>(key, funcList[i]));  
        }
        cout<<"Main Page Has Loaded Button And Functions!"<<endl;

    };
    void PageListen(){
        //页面监听的本质是按钮监听
        //展示button信息
        //并获取用户输入
        cout<<"This page starts listening  user input......"<<endl;
        this->button->listenButtonBePressed();
        //要执行的函数在map中进行查找
        /* map<string,IObserver*>::iterator iter = this->buttonfuncMap.begin();
        //清空之前的列表
        this->buttonfuncMap.clear();
        while(iter != this->buttonfuncMap.end()){
            cout <<" func:" << iter->first  <<" has been insert in buttonfuncMap " << endl;
            iter++;
            //之前的函数List
        }  */

        /* IObserver* o=this->buttonfuncMap[button->bePressed];
        //调用触发的函数进行执行
        ExcuteInterfaceFunc(subject,o); 
        this->buttonfuncMap.clear(); */
        cout<<"This page listens user input over!"<<endl;
        //一定一定要记得清空map!!!!
    };
    void PageExcute(){
        IObserver* o=this->buttonfuncMap[button->bePressed];
         //调用触发的函数进行执行
        ExcuteInterfaceFunc(subject,o); 
        this->buttonfuncMap.clear();
        cout<<"This page excute  over!"<<endl;
    }
    void PageRefresh(string a[] ,int n,IObserver* funcList[]){
        //标记上一个页面是哪个页面
        //修改原来的button
        //更新按钮
        cout<<"Start refreshing the page......"<<endl;
        this->button =new Button(a,n);
        //与之前不同的是，需要先清空原来的map，然后才能往map中添加元素
        //不然会报错
        //更新按钮对应的函数
        for (int i=0;i<n;i++){
           string key=to_string(i);
           //所有的功能都已经准备好了
           //等待用户输入执行函数就可以
           this->buttonfuncMap.insert(pair<string, IObserver*>(key, funcList[i]));  
        }
        cout<<"Refresh page over!"<<endl;

    };
    void SetLastPageId(int id){
        this->lastpageId=id;
    }
};




// page0--读者注册","读者登陆","管理员登陆
// page1--"搜索图书","借阅图书","归还书籍","预定书籍","取消预定","续借书籍","购买图书"，
// page3--"搜索图书","归还书籍","通知逾期读者归还书籍","添加书籍","下架书籍","逾期读者罚款","修改书籍信息"
int main(){ 
    //TestPayment();
    //全局的观察者
    Subject *subject = new Subject;
    Page*page =new Page(subject);
  

        string a[]={"读者注册","读者登陆","管理员登陆"};
        IObserver* funcList[]={
            new GeneralUserCreate(),
            new UserLogin(),
            new SuperUserLogin(),
        };
        page->PageFeaturesInit(a,3,funcList);
        page->PageListen();
        page->PageExcute();
    
        
        int  pageId =0;
        if (page->button->bePressed.compare("0")==0){
                   //下一次要刷新的准备
                    string tempbutton[]={"读者注册","读者登陆","管理员登陆"};
                    IObserver* tempfuncList[]={
                        new GeneralUserCreate(),
                        new UserLogin(),
                        new SuperUserLogin(),
                    };
                    page->PageRefresh(tempbutton,3,tempfuncList);
                    page->PageListen();
                    page->PageExcute();
                    if (page->button->bePressed.compare("0")==0){
                        pageId=0;
                    }else if (page->button->bePressed.compare("1")==0){
                        pageId=1;
                    }else if (page->button->bePressed.compare("2")==0){
                        pageId=2;
                    }

                    

        }else if(page->button->bePressed.compare("1")==0){
                string tempbutton[]={"搜索图书","借阅图书","归还书籍","预定书籍","取消预定","续借书籍","购买图书"};
                IObserver* tempfuncList[]={
                    new SearchBycatalog(),
                    new BorrowBook(),
                    new BackBook(),
                    new ReserveBook(),
                    new ReserveCancel(),
                    new RedeCorateBook(),
                    new SubmitBookOrlders(),
    
                };
                page->PageRefresh(tempbutton,7,tempfuncList);
                page->PageListen();
                page->PageExcute();
                pageId=1;

              


        }else if(page->button->bePressed.compare("2")==0){
                string tempbutton[]={"搜索图书","归还书籍","通知逾期读者归还书籍","添加书籍","下架书籍","逾期读者罚款","修改书籍信息"};
                IObserver* tempfuncList[]={
                    new SearchBycatalog(),
                    new BackBook(),
                    new NotifyReader(),
                    new AddBook(),
                    new DeleteBook(),
                    new ReaderFine(),
                    new EditBook(),

                };
                page->PageRefresh(tempbutton,7,tempfuncList);
                page->PageListen();
                page->PageExcute();
                pageId=2;
              

        }
        for (;;){

                if (pageId==0){

                        if (page->button->bePressed.compare("0")==0){
                            //下一次要刷新的准备
                            
                                string tempbutton[]={"读者注册","读者登陆","管理员登陆"};
                                IObserver* tempfuncList[]={
                                    new GeneralUserCreate(),
                                    new UserLogin(),
                                    new SuperUserLogin(),
                                };
                                page->PageRefresh(tempbutton,3,tempfuncList);
                                page->PageListen();
                                page->PageExcute();
                                if (page->button->bePressed.compare("0")==0){
                                    pageId=0;
                                }else if (page->button->bePressed.compare("1")==0){
                                    pageId=1;
                                }else if (page->button->bePressed.compare("2")==0){
                                    pageId=2;
                                }

                                

                    }else if(page->button->bePressed.compare("1")==0){
                            string tempbutton[]={"搜索图书","借阅图书","归还书籍","预定书籍","取消预定","续借书籍","购买图书"};
                            IObserver* tempfuncList[]={
                                new SearchBycatalog(),
                                new BorrowBook(),
                                new BackBook(),
                                new ReserveBook(),
                                new ReserveCancel(),
                                new RedeCorateBook(),
                                new SubmitBookOrlders(),
                            };
                            page->PageRefresh(tempbutton,7,tempfuncList);
                            page->PageListen();
                            page->PageExcute();
                            pageId=1;


                    }else if(page->button->bePressed.compare("2")==0){
                           
                            string tempbutton[]={"搜索图书","归还书籍","通知逾期读者归还书籍","添加书籍","下架书籍","逾期读者罚款","修改书籍信息"};
                            IObserver* tempfuncList[]={
                                new SearchBycatalog(),
                                new BackBook(),
                                new NotifyReader(),
                                new AddBook(),
                                new DeleteBook(),
                                new ReaderFine(),
                                new EditBook(),

                            };
                                page->PageRefresh(tempbutton,7,tempfuncList);
                                page->PageListen();
                                page->PageExcute();
                                pageId=2;


                    }


    
            }else if (pageId==1){
                 string tempbutton[]={"搜索图书","借阅图书","归还书籍","预定书籍","取消预定","续借书籍","购买书籍"};
                            IObserver* tempfuncList[]={
                                new SearchBycatalog(),
                                new BorrowBook(),
                                new BackBook(),
                                new ReserveBook(),
                                new ReserveCancel(),
                                new RedeCorateBook(),
                                new SubmitBookOrlders(),

                            };
                            page->PageRefresh(tempbutton,7,tempfuncList);
                            page->PageListen();
                            page->PageExcute();
                            pageId=1;



            
            }else if (pageId==2){
               
                    string tempbutton[]={"搜索图书","归还书籍","通知逾期读者归还书籍","添加书籍","下架书籍","逾期读者罚款","修改书籍信息"};
                            IObserver* tempfuncList[]={
                                new SearchBycatalog(),
                                new BackBook(),
                                new NotifyReader(),
                                new AddBook(),
                                new DeleteBook(),
                                new ReaderFine(),
                                new EditBook(),

                            };
                                page->PageRefresh(tempbutton,7,tempfuncList);
                                page->PageListen();
                                page->PageExcute();
                                pageId=2;

                  


            }

        }

       

}





