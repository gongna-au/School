#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <map>
using namespace std;

class Action {
public:
	virtual void execute() = 0;
};



class Application {
private:
	Queue<Action*> actions;  
public:
	Application(Action * pAction = NULL) : actions(10000) {
		if (NULL != pAction){
			 actions.insert(pAction);

		}
		   
	}
	virtual ~Application() {
	}

	virtual void run() {
		while(!actions.is_empty()) {
			//不断的取出要执行的函数
			Action * pAction = actions.remove();
			if (NULL != pAction){
				pAction->execute();
			}
			    
		}
	}

	virtual void pushAction(Action * pAction) {
		actions.insert(pAction);
	}
};
//定义了函数类型
typedef void (Application::*ActionProcess)();

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
			cout << "\n��ѡ��˵���:";
			if (cin >> index) {
				if (index >= 0 && index < num) {
					items[index].click();
					break;
				}
			} else {
				cin.clear();             // �����־λ���
				cin.ignore(9999, '\n');  // ���Ի���������
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


