
template <class T>
class Database : public Object
{
private:
	fstream file;
	char filename[40];
	long fileLen, recSize;
	typedef map< long, T, less<long> > mtype;
	mtype recMap;

public:
	Database(const char * filename)
	{
		strcpy(this->filename, filename);
		file.open(filename, ios::in | ios::binary);
		recSize = sizeof(T);
		if (file.is_open())
		{
			file.seekg(0, ios::end);
			if ((fileLen = file.tellg()) > 0)
			{
				T obj;
				file.seekg(0, ios::beg);
				do
				{
					file.read((char *)&obj, recSize);
					recMap.insert(typename mtype::value_type(obj.GetID(), obj));
				} while (file.tellg() < fileLen);
			}

			file.close();
		}
	}

	void SaveMap()
	{
		typename mtype::iterator iter;
		
		file.open(filename, ios::out | ios::binary | ios:: trunc);
		for (iter = recMap.begin(); iter != recMap.end(); ++iter)
		{
			file.write((char *)&iter->second, recSize);
		}

		file.close();
	}

	void Insert(T & obj)
	{
		recMap.insert(typename mtype::value_type(obj.GetID(), obj));
	}

	T * Query(long objID)
	{
		typename mtype::iterator iter;
		iter = recMap.find(objID);

		if (iter == recMap.end())
		{
			cout << objID << " not found!" << endl;
			return NULL;
		} else
		{
			return &(iter->second);
		}
	}

	T * QueryName(const char * objName)
	{
		typename mtype::iterator iter;
		for (iter = recMap.begin(); iter != recMap.end(); iter ++)
		{
			if (strstr((iter->second).GetName(), objName) != NULL)
			{
				return &(iter->second);
			}
		}

		cout << objName << " in " << typeid(T).name() << " not found " << endl;
		return NULL;
	}

	void Delete(long objID)
	{
		Query(objID);
		recMap.erase(objID);
	}

	void ShowAllData()
	{
		typename mtype::iterator iter;
		T obj;

		cout << "Data in " << typeid(T).name() << ":" << endl;
		for (iter = recMap.begin(); iter != recMap.end(); iter ++)
		{
			(iter->second).ShowData();
		}
	}
};