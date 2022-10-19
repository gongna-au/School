/**
 * 自动图书馆 主程序
 */

#pragma warning(disable:4786)
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <map>

#include "global.h"
#include "date.h"
#include "BookData.h"
#include "ReaderData.h"
#include "Database.h"
#include "Librarian.h"
#include "Reader.h"
#include "Queue.h"


using namespace std;

// 动作相关类
class Action {
public:
	virtual void execute() = 0;
};

//应用程序类
class Application {
private:
	Queue<Action*> actions;  // 定义一个Action队列，应用程序会不停的从队列里取Action并执行
public:
	Application(Action * pAction = NULL) : actions(10000) {
		if (NULL != pAction)
		    actions.insert(pAction);
	}
	virtual ~Application() {
	}

	virtual void run() {
		while(!actions.is_empty()) {
			Action * pAction = actions.remove();
			if (NULL != pAction)
			    pAction->execute();
		}
	}

	virtual void pushAction(Action * pAction) {
		actions.insert(pAction);
	}
};

// 菜单命令回调函数指针
typedef void (Application::*ActionProcess)();

// 菜单和菜单项
class MenuItem {
private:
	char  text[64];
	ActionProcess callback;
	Application * app;

public:
	MenuItem(char * text = (char*)("")) {
		strcpy(this->text, text);
		callback = NULL;
	}

	void setData(char * text, Application * app, ActionProcess callback) {
		strcpy(this->text, text);
		this->app = app;
		this->callback = callback;
	}
	char * getText() {
		return text;
	}

	void click() {
		if (NULL != callback) {
			(app->*callback)();
		}
	}
};

class Menu : public Action {
private:
	char  menuName[12];
	MenuItem * items;
	int num;
public:
	Menu(char * menuName,  char * texts[], Application * app, ActionProcess * callbacks, int num) {
		strcpy(this->menuName, menuName);
		this->num = num;
		items = new MenuItem[num];
		for (int i = 0; i < num; i ++) {
			items[i].setData(texts[i], app, callbacks[i]);
		}
	}

	virtual void showMenu() {
		printf("----------------%s----------------\n", menuName);
		for (int i = 0; i < num; i ++) {
			printf("%d:%s\n", i, items[i].getText());
		}
	}

	virtual void listen() {
		int index = -1;
		
		do {
			cout << "\n请选择菜单项:";
			if (cin >> index) {
				if (index >= 0 && index < num) {
					items[index].click();
					break;
				}
			} else {
				cin.clear();             // 错误标志位清除
				cin.ignore(9999, '\n');  // 忽略缓冲区数据
			}
		} while (true);
	}

	virtual void execute() {
		this->showMenu();
		this->listen();
	}

	virtual ~Menu() {
		if (NULL != items) {
			delete[] items;
			items = NULL;
		}
	}
};

// 自定义应用程序
class LibApp : public Application {
private:
	Database<BookData>    bookBase;
	Database<ReaderData>  readerBase;

	Menu * pMainMenu;
	Menu * pLibMenu;
	Menu * pReaderMenu;

	Librarian * mgr;
	Reader * rdr;
	long PIN;

public:
	// 构造函数
	LibApp() : bookBase("books.dat"), readerBase("readers.dat") {
		char * mainMenuTexts[]           = {(char*)"Librarian entry", (char*)"Reader entry", (char*)"Return book", (char*)"Exit"};
		ActionProcess mainMenuCallback[] = {(ActionProcess)&LibApp::mainLibEntry, (ActionProcess)&LibApp::mainReaderEntry, (ActionProcess)&LibApp::mainReturnBook, (ActionProcess)&LibApp::mainExit};
		pMainMenu = new Menu((char*)"主菜单", mainMenuTexts, this, mainMenuCallback, 4);

		char * libMenuTexts[] = {(char*)"Add reader", (char*)"Add Book", (char*)"Query Reader", (char*)"Put book to shelf", (char*)"Show All", (char*)"Exit"};
		ActionProcess libMenuCallback[] = {(ActionProcess)&LibApp::libAddReader, (ActionProcess)&LibApp::libAddBook, (ActionProcess)&LibApp::libQueryReader, (ActionProcess)&LibApp::libPutBook, (ActionProcess)&LibApp::libShowAll, (ActionProcess)&LibApp::libExit};
		pLibMenu = new Menu((char*)"管理员菜单", libMenuTexts, this, libMenuCallback, 6);

		char * readerMenuTexts[] = {(char*)"Add book to Cart", (char*)"Check Out", (char*)"Query Book By Name", (char*)"List My Books", (char*)"Show My Cart", (char*)"Exit"};
		ActionProcess readerMenuCallback[] = {(ActionProcess)&LibApp::readerAddBook, (ActionProcess)&LibApp::readerCheckOut, (ActionProcess)&LibApp::readerQueryBook, (ActionProcess)&LibApp::readerListBook,(ActionProcess) &LibApp::readerCart, (ActionProcess)&LibApp::readerExit};
		pReaderMenu = new Menu((char*)"读者菜单", readerMenuTexts, this, readerMenuCallback, 6);

		mgr = NULL;
		rdr = NULL;

		// 初始化命令
		pushAction(pMainMenu);
	}

	~LibApp() {
		if (NULL != pMainMenu) {
		    delete pMainMenu;
			pMainMenu = NULL;
		}
		if (NULL != pLibMenu) {
		    delete pLibMenu;
			pLibMenu = NULL;
		}
		if (NULL != pReaderMenu) {
		    delete pReaderMenu;
			pReaderMenu = NULL;
		}
		if (NULL != mgr) {
		    delete mgr;
			mgr = NULL;
		}
		if (NULL != rdr) {
		    delete rdr;
			rdr = NULL;
		}
	}

	// 菜单处理函数
	//main
	void mainLibEntry() {
		mgr = new Librarian(101, "yjc");
		char ret = mgr->login(); 
		if (ret == 'X') {
			pushAction(pLibMenu);
		} else {
			cout << "您的密码三次输入错误！" << endl;
			pushAction(pMainMenu);
		}
	}
	void mainReaderEntry() {
		int i;

		for (i = 0; i < 3; i ++) {
			cout << "Input PIN:";
			cin >> PIN;
			if (readerBase.Query(PIN) != NULL) {
				rdr = new Reader(PIN);
				break;
			}
		}
		if (i == 3) {
			cout << "Check In Failed!" << endl;
			pushAction(pMainMenu);
		} else {
			cout << "读者菜单：" << endl;
			pushAction(pReaderMenu);
		}
	}
	void mainReturnBook() {
		long PIN, bookID;
		cout << "Input a book ID:";
		cin >> bookID;

		if (bookBase.Query(bookID) != NULL) {
			bookBase.Query(bookID)->SetState(LIB);
			if ((PIN = bookBase.Query(bookID)->GetPIN()) > 0) {
				readerBase.Query(PIN)->ReturnBook(bookID);
			}
		}
		pushAction(pMainMenu);
	}
	void mainExit() {
		cout << "程序结束" << endl;
		exit(0);
	}
	//lib
	void libAddReader() {
		long ID;
		char name[40];

		cout << "Give a reader PIN and input a name:";
		cin >> ID;
		cin.ignore();
		cin.get(name, 20, '\n');
		ReaderData temp=ReaderData(ID, name);
		readerBase.Insert(temp);

		pushAction(pLibMenu);
	}
	void libAddBook() {
		long ID;
		char name[40];

		cout << "Input a book ID and name:";
		cin >> ID;
		cin.ignore();
		cin.get(name, 40, '\n');
		BookData temp=BookData(ID, name);
		bookBase.Insert(temp);

		pushAction(pLibMenu);
	}
	void libQueryReader() {
		long ID;

		cout << "Input a reader's PIN:";
		cin >> ID;
		if (readerBase.Query(ID) == NULL)
		{
			cout << "No such a reader! " << endl;
		} else
		{
			readerBase.Query(ID)->ShowData();
		}

		pushAction(pLibMenu);
	}
	void libPutBook() {
		long ID;

		cout << "Input a book ID:";
		cin >> ID;
		if (bookBase.Query(ID) == NULL)
		{
			cout << "No such a book!" << endl;
		} else
		{
			bookBase.Query(ID)->SetState(SHELF);
		}

		pushAction(pLibMenu);
	}
	void libShowAll() {
		readerBase.ShowAllData();
		bookBase.ShowAllData();

		pushAction(pLibMenu);
	}
	void libExit() {
		pushAction(pMainMenu);
	}
	//reader
	void readerAddBook() {
		long bookID;

		cout << "Input a book ID:";
		cin >> bookID;
		if (bookBase.Query(bookID) != NULL && bookBase.Query(bookID)->GetState() == SHELF)
		{
			if (rdr->AddBook(bookID))
				bookBase.Query(bookID)->SetState(LIB);
		}

		pushAction(pReaderMenu);
	}
	void readerCheckOut() {
		int i, t1, t2;
		long bookID;

		t1 = rdr->GetNum();
		t2 = readerBase.Query(PIN)->GetNum();

		if (t1 > 0 && t2 < LIMIT)
		{
			cout << PIN << " " << readerBase.Query(PIN)->GetName() << " Book List" << endl;
			for (i = 0; i < t1 && i < (LIMIT - t2); i ++)
			{
				bookID = readerBase.Query(PIN)->BorrowBook(rdr->CheckOut());
				bookBase.Query(bookID)->SetState(READER);
				bookBase.Query(bookID)->SetPIN(PIN);
				cout << i + 1 << "\t" << bookBase.Query(bookID)->GetName() << endl;
			}
		}

		Date().Display();

		pushAction(pReaderMenu);
	}
	void readerQueryBook() {
		char name[40];

		cout << "Input a book name (part):";
		cin.ignore();
		cin.get(name, 40, '\n');
		if (bookBase.QueryName(name) != NULL)
		{
			bookBase.QueryName(name)->ShowData();
		}

		pushAction(pReaderMenu);
	}
	void readerListBook() {
		readerBase.Query(PIN)->ShowData();

		pushAction(pReaderMenu);
	}
	void readerCart() {
		rdr->ShowCart();

		pushAction(pReaderMenu);
	}
	void readerExit() {
		pushAction(pMainMenu);
	}
};

// 主函数
int main() {
	LibApp libApp;
	libApp.run();
	return 0;
}