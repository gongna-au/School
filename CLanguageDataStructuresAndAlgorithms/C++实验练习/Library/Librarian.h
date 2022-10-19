/**
 * 图书管理员
 */

class Librarian: public Object
{
private:
	long ID;
	char name[20];
	char passwd[9];

public:
	Librarian(long ID, const char * name) : ID(ID)
	{
		strcpy(this->name, name);
		strcpy(passwd, "abc");
	}

	char login()
	{
		char pw[9];
		for (int i = 0; i < 3; i ++)
		{
			cout << "Enter Password:";
			cin >> pw;
			if (strcmp(pw, passwd) == 0)
				return 'X';
		}
		cout << "Login Failed!" << endl;
		return 'E';
	}
};