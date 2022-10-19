

class BookData : public Object
{
private:
	long bookID;
	char name[40];
	State state;
	long PIN;

public:
	BookData(long bookID, const char * name, State state = SHELF, long PIN = 0)
	{
		SetID(bookID);
		SetName(name);
		SetState(state);
		SetPIN(PIN);
	}

	BookData()
	{
		bookID = 0;
		PIN = 0;
	}

	long GetID() const
	{
		return bookID;
	}

	const char * GetName() const
	{
		return name;
	}

	State GetState() const
	{
		return state;
	}

	long GetPIN() const
	{
		return PIN;
	}

	void ShowData()
	{
		cout << bookID << "\t" << name << "\t" << state << "\t" << PIN << endl;
	}

	void SetID(long bookID)
	{
		this->bookID = bookID;
	}

	void SetName(const char * name)
	{
		strcpy(this->name, name);
	}

	void SetState(State state)
	{
		this->state = state;
	}

	void SetPIN(long PIN)
	{
		this->PIN = PIN;
	}
};