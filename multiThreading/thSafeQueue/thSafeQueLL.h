#include <mutex>
#include <condition_variable>
#include <memory>
using namespace std;

template<typename T>
class threadsafe_queue
{
private:
 struct node
 {
    std::shared_ptr<T> data;
    std::unique_ptr<node> next;
 };
 std::mutex head_mutex;
 std::mutex tail_mutex;
 std::unique_ptr<node> head;
 node* tail;
 std::condition_variable data_cond;
public:
 threadsafe_queue():head(new node),tail(head.get())
 {}
 threadsafe_queue(const threadsafe_queue& other)=delete;
 threadsafe_queue& operator=(const threadsafe_queue& other)=delete;
//  std::shared_ptr<T> try_pop();
//  bool try_pop(T& value);
 std::shared_ptr<T> wait_and_pop();
 void wait_and_pop(T& value);
 void push(T new_value);
 bool empty();
};


template<typename T>
class ThSafeLLQueue{

   struct Node{
      shared_ptr<T> data;
      unique_ptr<Node> next;
   };

   mutex headMutex;
   mutex tailMutex;
   condition_variable cond;

   unique_ptr<Node> head;
   Node* tail;

public:
   ThSafeLLQueue():head(new Node()), tail(head.get()){}

   void push(T val){
      shared_ptr<T> newDat(make_shared(move(T));
      unique_ptr<Node> newNode( new Node());
      Node* newTail = newNode.get();
      {
         unique_lock<mutex> locker(tailMutex);
         tail->data =  newDat;
         tail->next = newNode;
         tail = newTail;
      }
      cond.notify_one();

   }

   shared_ptr<T> pop(){

      unique_lock<mutex> locker(headMutex);
      cond.wait(locker, [](){ return head.get() != getTail();})
      unique_ptr<Node> oldHead = move(head);
      head = move(oldHead->next);
      return oldHead->data;
   }
};