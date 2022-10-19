template <class T>
class Queue  
{
private:
	int front;
	int rear;
	int size;
	T * data;

public:
	Queue(int s = 100); 
	virtual ~Queue();

	void insert(const T & x);
	T remove();
	int is_empty() const;
	int is_full() const;
};