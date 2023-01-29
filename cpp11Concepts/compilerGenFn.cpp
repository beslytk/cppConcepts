#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007

// #define COMP_FN 1
#define DEL_COMP_FN 1

#ifdef COMP_FN

//  * Language Standard: C++03/ 
//############################################################################
/*
Compiler silently writes 4 functions if they are not explicitly declared:
1. Copy constructor.
2. Copy Assignment Operator.
3. Destructor.
4. Default constructor (only if there is no constructor declared).
*/

// class dog {};

/*//! equivalent to */

class dog {
	public:
		dog(const dog& rhs) {
            //.......
        };   // Member by member initialization

		dog& operator=(const dog& rhs) { // will not be created by compiler if there is a const or ref & member in class
            //.............              //? const and ref members cannot be copied they can only be instatiated
        }; // Member by member copying

		dog() {     // 1. Call base class's default constructor;  //not created if base clas doesnt have constr defined
            //...   // 2. Call data member's default constructor.
        };               
		               

		~dog() {            // 1. Call base class's destructor; //not created if base clas destructor is private
            // ...          // 2. Call data member's destructor.
        };               
		                
};
/*
Note:
1. They are public and inline.
2. They are generated only if they are needed. // if the above fns are not used in any other fns , they will not be generated
*/

// --------------------------------------------------------------------

class doggy {
	public:
        string m_name;
		// string& m_name; // conpy constr and assg op will be deleted coz of ref member

		doggy(string name = "Bob") {m_name = name; cout << name << " is born." << endl;}
		~doggy() { cout<< m_name << " is destroyed.\n" << endl; }
};

int main() {
  doggy dog1("Henry");
  doggy dog2;
  dog2 = dog1;
}

// OUTPUT:
// Henry is born.
// Bob is born.
// Henry is distroied.
// Henry is distroied.
/*  Example:
  1. Copy constructor.   - no -> not used
  2. Copy Assignment Operator. - yes
  3. Destructor.  - no  -> already defined
  4. Default constructor - no -> already defined
*/
//! The above class canoot be used with STL containers as they need its containee to be copy constr and copy assgnable

/*Questions: 
  What functions are silently written by compiler.


Notes:
 Compiler will refuse to generate default copy assignment operator when it is illegal.
 1. Reference member data
 2. Const member data
 Such classes cannot be used in STL containers because a container's elements has to
 be copy constructable and assignable.
*/


///------------------------------------------------------------------------------------------------

/* Example 2: */
class collar {
	public:
	//  collar(string color) { std::cout <<  " collar is born.\n"; } //!will result in error shown below
	collar() { std::cout <<  " collar is born.\n"; }  //? will compile with this
};

class dogg {
	collar m_collar;
	// string& m_name; //! ref not initialized
};

int main() {
	dogg dog1;
}
// output:
// main.cc:13: error: no matching function for call to `dog::dog()'
// main.cc:8: note: candidates are: dog::dog(const dog&)
//! compiler will try to generate edef constr for dogg-> which inturn will try to call data members def constr.
// However collar doesnt have def constr


// Add to dog:
// string& m_name; 
// Result: not compilable because age is not initialized.


/* //? C++ 11 Update: */
// class dog {
//    public:
//       dog() = default;
//       dog(string name) {...};
// }

//-----------------------------------------------------------------------------------
#elif DEL_COMP_FN
//############################################################################
/*
 * Disallow the use of compiler generated functions 
 *
 * Not all classes need the compiler generated functions.
 *
 * E.g.  a class "OpenFile" represents a file being opened. Its constructor at
 * least needs a file name as parameter. So default constructor is not needed.
 */

/*
 * C++ 11 Update:
 */
class OpenFile {
   public:
   OpenFile(string filename){} // make def constr deleted
   OpenFile(const OpenFile& ) = delete; // in c++11, Prevent copy constructor from being used.
                              // Useful when OpenFile holds unsharable resource.
    // g(OpenFile& f){ OpenFile f2(f);}
    private:
    // OpenFile(const OpenFile& ); // in c++03, make copy constr private and dont define it
    // OpenFile& operator=(const OpenFile& );
};

class OpenFile2 {
   public:
    OpenFile2(string filename){} // make def constr deleted
    void destroyFile(){delete this; }
    private:
    ~OpenFile2(){} //private destructor
};

int main(){
    OpenFile f(string("file"));
    // OpenFile f2(f);  OpenFile f holds unsharable resource as both objects cant be allowed to write to file
    // therefore explicitly delted copy constr here

    // OpenFile2 f2= OpenFile2(string("file")); //will lead to mem leak as the destr is private and cant be called
    // f2->destroyFile();
    
    //! instead define such class obj with priv destr in heap
    OpenFile2* f2 = new OpenFile2(string("file"));
    f2->destroyFile();
    //? useful in embedded where there is limited stack and we are forcing class obj to be stored in heap
}
//--------------------------------------------------

/* For C++ 03:
 *
1. Default constructor.      - easy
2. Copy constructor.         - see following solutions
3. Copy Assignment Operator. - see following solutions


Solution:
 Declare them as private functions, but not define them.
 -- Members and friends get link-time error, others get compile-time error.
*/
class dog {
   private:
   dog& operator=(const dog& rhs);   
};




/*
Solution 2:
 In its base class, declare them as private function, but not define them.
 -- Compile time error.
*/
class yellowdog : public dog {
};
int main() {
   yellowdog y1("henry");
   yellowdog  y2;
   y2 = y1;
}

// Note: the same techniques can used to disallow any function from being used.





/* Question: Can we disallow destructor from being used?
 */





/* Solution */
class dog {
  public:
     void destroyMe() { delete this; }
  private:
     ~dog() { cout<< m_name.m_str << " is destroyed.\n" << endl; }
};

int main ()
{
  dog* dog1 = new dog();
  dog1->destroyMe();
}


/* Usage: 1. Reference counting smart pointer.
 *        2. Small stack embedded programming.
 */


int main(){
    
    return 0;
}

#endif // COMP_FN
