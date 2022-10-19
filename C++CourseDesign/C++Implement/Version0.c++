
#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;



//一旦登陆成功就把这个赋值

string UserGlobalIdCard="";

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
  virtual ~SuperUserCreate() {
    cout << "新增图书管理员相关的操作处理完毕...\n";
  }

  void Update() override {
       cout<<"正在执行业务函数-新增图书管理员\n";
        Input();
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
        cout << "注销用户相关的操作处理完毕...\n";
    }
    void Update() override {
            cout<<"正在执行业务函数-查找书籍\n";
            Input();
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
            cout<<"通知逾期读者业务函数执行结束\n";
    }
};







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
    Subject * subject;
    Button* button;
    map<string,IObserver*> buttonfuncMap;

    //只调用一次
    Page(Subject *s ){
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
     
        
        IObserver* o=this->buttonfuncMap[button->bePressed];
        //调用触发的函数进行执行
        ExcuteInterfaceFunc(subject,o); 
        this->buttonfuncMap.clear();
        cout<<"This page listens user input over!"<<endl;
        //一定一定要记得清空map!!!!
        
    };
    void PageRefresh(string a[] ,int n,IObserver* funcList[]){
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

    
};


class App{
    public:
    //都是单例
    Subject*  subject ;
    //都是单例
    //全局都只初始化一次
    Page*     page;

    App(Subject *s,Page*p){
        this->subject=s;
        this->page=p;
    };
    void AppInit(string a[] ,int n,IObserver* funcList[]){
        page->PageFeaturesInit(a,3,funcList);
        page->PageListen();
    };

    void pageRefresh(string a[] ,int n,IObserver* funcList[]){
        this->page->PageRefresh(a,n,funcList);
    };
    void pageRun(){
        this->page->PageListen();
    };


};
int main(){ 
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
    if (page->button->bePressed.compare("0")==0){
        string tempbutton[]={"读者注册","读者登陆","管理员登陆"};
        IObserver* tempfuncList[]={
            new GeneralUserCreate(),
            new UserLogin(),
            new SuperUserLogin(),
        };
        page->PageRefresh(tempbutton,1,tempfuncList);
        page->PageListen();

    }else if(page->button->bePressed.compare("1")==0){
        string tempbutton[]={"搜索图书","借阅图书","归还书籍"};
        IObserver* tempfuncList[]={
            new SearchBook(),
            new BorrowBook(),
            new BackBook(),
        };
        page->PageRefresh(tempbutton,3,tempfuncList);
        page->PageListen();

    }else if(page->button->bePressed.compare("2")==0){
        string tempbutton[]={"搜索图书","归还书籍","通知逾期读者归还书籍"};
        IObserver* tempfuncList[]={
            new SearchBook(),
            new BackBook(),
            new NotifyReader(),
        };
        page->PageRefresh(tempbutton,3,tempfuncList);
        page->PageListen();
    }


}





