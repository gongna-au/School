// Queue.h: interface for the Queue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUEUE_H__34F72364_CB86_48B7_8EA7_8B026BA6BC00__INCLUDED_)
#define AFX_QUEUE_H__34F72364_CB86_48B7_8EA7_8B026BA6BC00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_QUEUE_H__34F72364_CB86_48B7_8EA7_8B026BA6BC00__INCLUDED_)