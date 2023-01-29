#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
template<typename T>
class threadsafe_queue
{
private:
 mutable std::mutex mut; 
 std::queue<T> data_queue;
 std::condition_variable data_cond;
public:
 threadsafe_queue()
 {}
 threadsafe_queue(threadsafe_queue const& other)
 {
 std::lock_guard<std::mutex> lk(other.mut);
 data_queue=other.data_queue;
 }
 void push(T new_value)
 {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
 }
 void wait_and_pop(T& value)
 {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk,[this]{return !data_queue.empty();});
    value=data_queue.front();
    data_queue.pop();
 }
 std::shared_ptr<T> wait_and_pop()
 {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk,[this]{return !data_queue.empty();});
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
 }
 bool try_pop(T& value)
 {
    std::lock_guard<std::mutex> lk(mut);
    if(data_queue.empty())
    return false;
    value=data_queue.front();
    data_queue.pop();
    return true;
 }
 std::shared_ptr<T> try_pop()
 {
    std::lock_guard<std::mutex> lk(mut);
    if(data_queue.empty())
    return std::shared_ptr<T>();
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
 }
 bool empty() const
 {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
 }
};

// Even though empty() is a const member function, and the other parameter to the
// copy constructor is a const reference, other threads may have non-const references
// to the object, and may be calling mutating member functions, so you still need to lock
// the mutex. Since locking a mutex is a mutating operation, the mutex object must be
// marked mutable B so it can be locked in empty() and in the copy constructor.
//  Condition variables are also useful where there’s more than one thread waiting for
// the same event. If the threads are being used to divide the workload, and thus only
// one thread should respond to a notification, exactly the same structure as shown in
// listing 4.1 can be used; just run multiple instances of the data-processing thread.
// When new data is ready, the call to notify_one() will trigger one of the threads

// The basic consequences of holding the data by std::shared_ptr<> are straightfor￾ward: the pop functions that take a reference to a variable to receive the new value
// now have to dereference the stored pointer, B and c, and the pop functions that
// return an std::shared_ptr<> instance can retrieve it from the queue, d and e,
// before returning it to the caller.
//  If the data is held by std::shared_ptr<>, there’s an additional benefit: the alloca￾tion of the new instance can now be done outside the lock in push() f, whereas in
// listing 6.2 it had to be done while holding the lock in pop(). Because memory alloca￾tion is typically quite an expensive operation, this can be beneficial for the perfor￾mance of the queue, because it reduces the time the mutex is held, allowing other
// threads to perform operations on the queue in the meantime.

//  Just like in the stack example, the use of a mutex to protect the entire data struc￾ture limits the concurrency supported by this queue; although multiple threads might
// be blocked on the queue in various member functions, only one thread can be doing
// any work at a time. But part of this restriction comes from the use of std::queue<> in
// the implementation; by using the standard container you now have one data item
// that’s either protected or not. By taking control of the detailed implementation of the
// data structure, you can provide more fine-grained locking and allow a higher level of
// concurrency.