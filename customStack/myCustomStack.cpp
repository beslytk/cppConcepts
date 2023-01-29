#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007

template<typename DT, int capacity>
class MyStack{
public:
    MyStack();

    void push(DT val);
    DT top();
    void pop();
    bool empty();
    int getSize();

private:
    DT* ptr;
    int size;
};

template<typename DT, int capacity>
MyStack<DT, capacity>::MyStack():ptr(new DT[capacity]),size(0){}

template<typename DT, int capacity>
void MyStack<DT, capacity>::push(DT val){
    ptr[size] = val;
    size++;
}
template<typename DT, int capacity>
DT MyStack<DT, capacity>::top(){
    if(size>0)
        return ptr[size - 1];
}

template<typename DT, int capacity>
void MyStack<DT, capacity>::pop(){
    size--;
}

template<typename DT, int capacity>
int MyStack<DT, capacity>::getSize(){
    return size;
}
int main(){
    
    MyStack<int, 5> s;
	s.push(10); // pushing into the stack
	s.push(20);
	s.push(30);
	s.push(40);
	cout << "Current size of the stack is " << s.getSize()
		<< endl;
	cout << "The top element of the stack is " << s.top()
		<< endl;
	s.pop(); // popping from the stack
	cout << "The top element after 1 pop operation is "
		<< s.top()
		<< endl; // printing the top of the stack
	s.pop(); // popping
	cout << "The top element after 2 pop operations is "
		<< s.top() << endl;
	cout << "Size of the stack after 2 pop operations is "
		<< s.getSize() << endl;
    return 0;
}