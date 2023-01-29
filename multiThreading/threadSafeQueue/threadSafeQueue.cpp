#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<memory>
using namespace std;

template<typename T>
class ThSafeLLQueue{

    struct Node{
        shared_ptr<T> data;
        unique_ptr<T> next;
    }
    mutex headMutex;
    mutex tailMutex;
    condition_variable dataAlert;

    unique_ptr<Node> head;
    Node* tail;

    Node* getTail(){
        lock_guard<mutex> tailLock(tailMutex);
        return tail;
    }
public:
    ThSafeLLQueue():head(new Node()), tail(head.get()){}

    shared_ptr<T> pop(){
        unique_lock<mutex> headLock(headMutex);
        dataAlert.wait(headLock, [&](){ head.get()!= getTail();})
        unique_ptr<Node> oldHead = move(head);
        head = move(oldHead->next);
        return oldHead->data;
    }

    void push(T val){
        shared_ptr<T> newData(make_shared<T>(move(val)));
        unique_ptr<Node> newNode (new Node());
        Node* newTail = newNode.get();
        {
            unique_lock<mutex> tailLock(tailMutex);
            tail->data = newData;
            tail-next = newNode;
            tail = newTail
        }
        dataAlert.notify_one();
    }

    bool empty(){
        lock_guard<mutex> headLock(headMutex);
        return head.get() == getTail();
    }

}; 

int main(){
    
    return 0;
}