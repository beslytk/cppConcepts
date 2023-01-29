#include<bits/stdc++.h>
using namespace std;

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

void function_1() { // publisher fn

    int count = 10;

    while(count > 0) {
        std::unique_lock<mutex> locker(mu) ;
        q.push_front(count) ;
        locker.unlock();
        cond.notify_one(); // Notify one waiting thread, if there is one.
        std::this_thread::sleep_for(chrono::seconds(1));
        count--;
    }
}

void function_2() { // consumer fn

    int data = 0;

    while ( data != 1) {
        std::unique_lock<mutex> locker(mu);
        cond.wait(locker, [](){ return !q.empty();}); // spurious wake
        data = q.back();
        q.pop_back();
        locker .unlock();
        cout << "t2 got a value from t1: " << data << endl;
    }
}

int main(){
    std::thread t1(function_1);
    std::thread t2(function_2);
    t1.join();
    t2.join();

    return 0;
}