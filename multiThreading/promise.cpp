#include<bits/stdc++.h>
using namespace std;

int factorial(std::future<int>& f) {
     int res = 1;
     int N = f.get();
     for (int i=N; i>1; i--)
         res *= i;
     cout << "Result is: " << res << endl ;
     return res;
}
int main() {
     int x;
     std::promise<int> p;  // to pass value to child th in future
     std::future<int> f = p.get_future();
     std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));
     // do something else
     std::this_thread::sleep_for(chrono::milliseconds(20));
     p.set_value(4);
     x = fu.get();
     return 0;
}