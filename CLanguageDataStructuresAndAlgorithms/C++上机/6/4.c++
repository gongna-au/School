#include <iostream>
#include <cstdlib>
using namespace std;
 
// Define the default capacity of a stack
#define SIZE 10
 
// A class to represent a stack
template <class T>
class stack
{
    T *arr;
    int top;
    int capacity;
 
public:
    stack(int size = SIZE);         // constructor
 
    void push(T);
    T pop();
    T peek();
 
    int size();
    bool isEmpty();
    bool isFull();
 
    // destructor
    ~stack() {
        delete[] arr;
    }
};
 
// Constructor to initialize the stack
template <class T>
stack<T>::stack(int size)
{
    arr = new T[size];
    capacity = size;
    top = -1;
}
 
// Function to add an element `x` to the stack
template <class T>
void stack<T>::push(T x)
{
    if (isFull())
    {
        cout << "Overflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
 
    cout << "Inserting " << x << endl;
    arr[++top] = x;
}

// Function to pop the top element from the stack
template <class T>
T stack<T>::pop()
{
    // check for stack underflow
    if (isEmpty())
    {
        cout << "Underflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
 
    cout << "Removing " << peek() << endl;
 
    // decrease stack size by 1 and (optionally) return the popped element
    return arr[top--];
}
 
// Function to return the top element of the stack
template <class T>
T stack<T>::peek()
{
    if (!isEmpty()) {
        return arr[top];
    }
    else {
        exit(EXIT_FAILURE);
    }
}
// Utility function to return the size of the stack
template <class T>
int stack<T>::size() {
    return top + 1;
}
 
// Utility function to check if the stack is empty or not
template <class T>
bool stack<T>::isEmpty() {
    return top == -1;               // or return size() == 0;
}
 
// Utility function to check if the stack is full or not
template <class T>
bool stack<T>::isFull() {
    return top == capacity - 1;     // or return size() == capacity;
}

int main()
{
    stack<double> root(10);
 
    root.push(2.0);
    root.push(3.0);
 
    root.push(4.0);
 
    root.push(5.0);
 
    // Prints the top of the stack
    cout << "The top element is " << root.peek() << endl;
 
    // Returns the total number of elements present in the stack
    cout << "The stack size is " << root.size() << endl;
 
    root.pop();
 
    // check if the stack is empty or not
    if (root.isEmpty()) {
        cout << "The stack is empty\n";
    }
    else {
        cout << "The stack is not empty\n";
    }
 
    return 0;
}
 

 

