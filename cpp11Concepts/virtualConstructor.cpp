#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007

// #define BUGGY 1
#define VIRT_CONSTR 1

#ifdef BUGGY
class Dog {
   public:
    Dog() {cout << "dog def constr\n";}
    void bark() { cout << "Whoof, I am just a dog.\n";};
};

class Yellowdog : public Dog{
   public:
   ~Yellowdog() {cout << "yellow dog def constr\n";}
    void bark() { cout << "Whoof, I am a yellow dog.\n";};
};

void foo(Dog* d){         // d is Yellowdog
    Dog* c = new Dog(*d); // c is a Dog //! c is not identical copy of d
    //
    //
}

int main(){

    Yellowdog d;
    foo(&d);
    
    return 0;
} 

#elif VIRT_CONSTR
//! co-variant return type. It allows overridden virtual fn to have different return type
class Dog {
   public:
    Dog() {cout << "dog def constr\n";}
    void bark() { cout << "Whoof, I am just a dog.\n";};

    virtual Dog* clone() {          // acts like a virt constr. MAke sure appropriate type of obj will be constr
        return (new Dog(*this));
    }
};

class Yellowdog : public Dog{
   public:
   ~Yellowdog() {cout << "yellow dog def constr\n";}
    void bark() { cout << "Whoof, I am a yellow dog.\n";};

    virtual Yellowdog* clone() {  //! co-variant return type. It allows overridden virtual fn to have different return type
        return (new Yellowdog(*this));
    }
};

void foo(Dog* d){         // d is Yellowdog
    // Dog* c = new Dog(*d); // c is a Dog //! c is not identical copy of d
    Dog* c = d->clone();     // c is a Yellowdog
    //
}

int main(){

    Yellowdog d;
    foo(&d);
    
    return 0;
} 

#endif