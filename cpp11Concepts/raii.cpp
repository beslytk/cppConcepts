#include<bits/stdc++.h>
#include <thread>  
#include<mutex>
using namespace std;
 
#define ll long long
#define mod 1000000007

 //############################################################################
/* Resource Acquisition is Initialization (RAII)
 * 
 * Use objects to manage resources: 
 * 	memory, hardware device, network handle, etc.
 */

// Mutex_t   mu = MUTEX_INITIALIZER;
 
// void functionA()
// {
//    Mutex_lock( &mu );
// //    ... // Do a bunch of things // may do early return
//    Mutex_unlock( &mu );      // Will this line always be executed?
// }

// /*
//  * Solution:
//  */ 
// class Lock {
//    private:
//       Mutext_t* m_pm;
//    public:
//       explicit Lock(Mutex_t *pm) { Mutex_lock(pm); m_pm = pm;};  
//       ~Lock() { Mutex_unlock(m_pm); };
// }

// void functionA()
// {
//    Lock mylock(&mu);
// //    ...  // Do a bunch of things
// }  // The mutex will always be released when mylock is destroied from stack


/* Conclusion:
 *
 ! The only code that can be guaranteed to be executed after exception is 
 ! thrown are the destructor of objects residing on the stack. 
 *
 * Resource management therefore needs to be tied to the lifespan of 
 * suitable objects in order to gain automatic deallocation and reclamation.
 */

//-----------------------------------------------------------
/* Note 1:
 * Another good example of RAII:  tr1:shared_ptr
 */
// int function_A() {
//    std::tr1::shared_ptr<dog> pd(new dog()); 
//    ...
// } // The dog is destructed when pd goes out of scope (no more pointer
  // points to pd).


// Another example:

// class dog;
// class Trick;
// void train(tr1::shared_ptr<dog> pd, Trick dogtrick);
// Trick  getTrick();

// int main() {
//    tr1::shared_ptr<dog> pd(new dog());
//    train(pd, getTrick());
// }
//Question: What's the problem with above code:


// What happens in train()'s parameter passing:
// 1. new dog();
// 2. getTrick();
// 3. construct tr1::shared_ptr<dog>.
// The order of these operations are determined by compiler.


//! Conclusion: Don't combine storing objects in shared pointer with other statement.
//------------------------------------------------------------------------

/* Note 3:
   What happens when resource management object is copied?
*/
   Lock L1(&mu);
   Lock L2(L1);

/* Solution 1: 
 * Prohibit copying. To see how to disallow copy constructor and copy 
 * assignment operator from being used, watch my another session: 
 * Disallow Compiler Generated Functions. 
 */

/* Solution 2:
 * Reference-count the underlying resource by using tr1::shared_ptr
 */

template<class Other, class D> shared_ptr(Other * ptr, D deleter);

// The default value for D is "delete", e.g.:
	std::tr1::shared_ptr<dog> pd(new dog());

class Lock {
   private:
      std::tr1::shared_ptr<Mutex_t> pMutex;
   public:
      explicit Lock(Mutex_t *pm):pMutex(pm, Mutex_unlock) { 
         Mutex_lock(pm); 
      // The second parameter of shared_ptr constructor is "deleter" function.
      }; 
 }
}

   Lock L1(&mu);
   Lock L2(L1);

int main(){
    
    return 0;
}
//-------------------------------------------------------------------
// mutex example  https://cplusplus.com/reference/mutex/mutex/
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex

std::mutex mtx;           // mutex for critical section

void print_block (int n, char c) {
  // critical section (exclusive access to std::cout signaled by locking mtx):
  mtx.lock();
  for (int i=0; i<n; ++i) { std::cout << c; }
  std::cout << '\n';
  mtx.unlock();
}

int main ()
{
  std::thread th1 (print_block,50,'*');
  std::thread th2 (print_block,50,'$');

  th1.join();
  th2.join();

  return 0;
}