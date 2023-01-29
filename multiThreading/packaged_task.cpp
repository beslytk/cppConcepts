#include<bits/stdc++.h>

using namespace std;
 
/* packaged_task */
int factorial(int N) {
     int res = 1;
     for (int i=N; i>1; i--)
         res *= i;
     cout << "Result is " << res << endl;
     return res;
}
std::deque<packaged_task<int()> >task_q;
std::mutex mu;
std::condition_variable cond;
void thread_1() {
    std::packaged_task<int()> t;
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){return !task_q.empty();});  // consumer waits witha a predicate to handle spurious wake
        t = std::move(task_q.front());
        task_q.pop_front();
    }
    t();
}

int main(){
    std::thread t1(thread_1);
    std::packaged_task<int()> t(bind (factorial, 6));
    std::future<int> fu = t.get_future();
    {
        std::lock_guard<std::mutex> locker (mu);
        task_q.push_back(std::move(t));
    }
    cond.notify_one();    // producer notifies
    cout <<"future value received at main: "<< fu.get();   // ret value received from child th using future
    t1.join();
    return 0;
}
//  Summary
//     3 ways to get a future:
//     - async() returns a future
//     - promise::get_future()
//     - packaged_task::get_future()
