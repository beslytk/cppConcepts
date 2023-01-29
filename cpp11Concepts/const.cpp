#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007

// #define CONST_PTR  1
#define  CONST_W_FN 1
// #define LOGIC_BIT_CONST

#ifdef CONST_PTR
//#############################################################
// const
//   - A compile time constraint that an object can not be modified
//

int main(){
    int i = 1;
    const int a = 9;
    // a =6; //wont compile
    const_cast<int&>(a) = 6; // works as it casts away const of a
    //1
    const int *p1 = &a;  // data is const, pointer is not
    // * p1 =5; // wont work as p1 points to read only location
    // p1++; // possible as ptr is changed
    
    //2
    int* const p2 = &i;  // pointer is const, data is not
    
    //3
    const int* const p3 = &a;  // data and pointer are both const


    // Triky one
    int const *p4 = &i;   // data is const, pointer is not

    int j;
    // static_cast<const int&>(j) = 7; //wont compile

}

//? If const is on the left  of *, data is const
//? If const is on the right of *, pointer is const

/*
  Why use const
    a.) Guard against inadvertent write to the variable.
    b.) Self documenting
    c.) Enable compiler to do more optimiztion, making code tighter.
    d.) const usually means the variable is put in ROM. 
*/

// ------------------------------------------------------------------------
#elif CONST_W_FN
// Casting

// const used with functions
class Dog {
   int age;
   string name;
public:
   Dog() { age = 3; name = "dummy"; }
   
   // const parameters
   void setAge(const int& a) { //called by Passing an rvalue parameter: or  Passing a const int parameter:
       age = a; }
   void setAge(int& a) { //  invoked by any lvalue parameter:
      age = a;} 
   // copy by value: doesnt make sense to make it const 
   // Const return value
   const string& getName() { // ref to improve efficiency.: const to make it not changeable for caller
      return name;}
   
   // const function
   void printDogName() const { cout << name << "const" << endl; } // const function cant change members of class
   void printDogName() { cout << getName() << " non-const" << endl; } // compile err if fn is const! : const fn can only call another const fn
};

int main() {
   Dog d;
   int i=9;
   d.setAge(i);
   cout<< i<<endl;

   const string& n = d.getName();
   cout<< n<<endl;

   d.printDogName(); // 1st print fn invoked
   
   const Dog d2;
   d2.printDogName();// 2nd print fn invoked
   
}

// // Function overloading: which const can overload function?

// // When const is useless
// void setAge(const int a) {}
// const int getAge() {}
// In both case, the int is a temparary. It doesn't make sense for them to be const

// Casting
// const Dog d2(8);
// d2.f();  // const f()
// const_cast<Dog&>(d2).f() // non-const f()

// Dog d(9);
// d.f(); // invoke non-const f()
// static_cast<const Dog&>(d).f(); // invoke const f()


//------------------------------------------------------------------------
#elif LOGIC_BIT_CONST
class BigArray {
   vector<int> v; // huge vector
   // int accessCounter;   
   mutable int accessCounter; // making it changeable from a const fn
   
   int* v2; // another int array

public:
   int getItem(int index) const {
      accessCounter++;
      // const_cast<BigArray*>(this)->accesscounter++; // also worls!
      return v[index];
   }
   
    void setV2Item(int index, int x) const{ // this fn maintained bit-wise constness of this class // so can be made const
      *(v2+index) = x;
   }
    
   // Quiz:
   const int*const fun(const int*const& p)const;
 };

 int main(){
    BigArray b;
 }

#endif






