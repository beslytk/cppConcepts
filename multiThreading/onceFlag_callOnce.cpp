#include<bits/stdc++.h>
using namespace std;

class LogFile {
   static int x;
	std::mutex m_mutex;
	ofstream f;
	std::once_flag m_flag;
	void init() { f.open("log.txt"); }
public:
	void shared_print(string id, int value) {
        std::call_once(m_flag, &LogFile::init, this); // init() will only be called once by one thread
		//std::call_once(m_flag, [&](){ f.open("log.txt"); });  // Lambda solution
		//std::call_once(_flag, [&](){ _f.open("log.txt"); });  // file will be opened only once by one thread
		f << "From " << id << ": " << value << endl;
	}
};
int LogFile::x = 9;

//Note: once_flag and mutex cannot be copied or moved.
//      LogFile can neither be copy constructed nor copy assigned

// static member data are guaranteed to be initialized only once.