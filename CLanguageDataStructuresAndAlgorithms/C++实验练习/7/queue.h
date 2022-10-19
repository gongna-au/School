// Queue.cpp: implementation of the Queue class.
//
//////////////////////////////////////////////////////////////////////

#include "Queue.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

template <class T>
Queue<T>::Queue(int s): size(s+1), front(0), rear(0)
{
	data = new T[size];
}

template <class T>
Queue<T>::~Queue()
{
	delete [] data;
}

template <class T>
void Queue<T>::insert(const T & x)
{
	data[rear ++ % size] = x;
}

template <class T>
T Queue<T>::remove()
{
	return data[front ++ % size];
}

template <class T>
int Queue<T>::is_empty() const
{
	return front == rear;
}

template <class T>
int Queue<T>::is_full() const
{
	return ((rear + 1) % size == front);
}