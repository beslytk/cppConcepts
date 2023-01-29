#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007

/* Deferred Lock */
class LogFile {
	std::mutex m_mutex;
	ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	}
	void shared_print(string id, int value) {
		//m_mutex.lock();  // lock before lock_guard is created
		//std::lock_guard<mutex> locker(m_mutex, std::adopt_lock);
		std::unique_lock<mutex> locker(m_mutex, std::defer_lock);
		locker.lock();  // Now the mutex is locked
		f << "From " << id << ": " << value << endl;
	}
};


class LogFile_DeferLock {
    std::mutex _mu;
    ofstream _f;
public:
    LogFile() {
        _f.open("log.txt");
    } // Need destructor to close file
    void shared_print(string id, int value) {
        //std::lock_guard<mutex> locker(_mu) ;
        std::unique_lock<mutex> locker(_mu, std::defer_lock);
        // do smth else
        locker.lock();

        _f << "From "<< id <<":"<< value<<endl;;
        locker.unlock();
        locker.lock();
        std::unique_lock<mutex> locker2 = std::move(locker); // not possible with lock_guard;
    }
};

// Objects cannot be copied but can be moved: thread, packaged_task, fstream, unique_ptr 
// unique_lock
// mutex can neither be copied nor moved

/* unique_lock for transferring mutex ownership */
class LogFile {
	std::mutex m_mutex;
	ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	}
	unique_lock<mutex> giveMeLock() {
		return unique_lock<mutex>(m_mutex);  // Moved
	}
	void shared_print(string id, int value) {
		std::unique_lock<mutex> locker(m_mutex);
		f << "From " << id << ": " << value << endl;
	}
};


int main() {
	LogFile log;
	unique_lock<mutex> locker = log.giveMeLock();
   // I don't want to shared_print anything, but I don't want anybody else to do that either untill I am done.

   // I can also release the lock before locker is destroyed
   locker.unlock();  // lock_guard can't unlock

   //...
   // allow other thread to use log

   locker.lock();  // lock again. -- finer grained lock alows more resource sharing 

	return 0;
}
