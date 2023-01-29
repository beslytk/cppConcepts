#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007

// #define BUGGY 1
// #define VIRT_DEST 1
#define SHARED_PTR 1

#ifdef BUGGY
class Dog {
   public:
    ~Dog() {cout << "dog destroyed\n";}
    void bark() { cout << "Whoof, I am just a dog.\n";};
};

class Yellowdog : public Dog{
   public:
   ~Yellowdog() {cout << "yellow dog destroyed\n";}
    void bark() { cout << "Whoof, I am a yellow dog.\n";};
};

class DogFactory {
public:
    static Dog* createYellowDog() {return (new Yellowdog()); }
    // ..create other dogs
};

int main(){

    Dog* pd = DogFactory::createYellowDog();
    //
    //
    delete pd; //! only Dog destructor will be called
    
    return 0;
}
#elif VIRT_DEST //todo if we are using a class in polymorphic way, the base class destr should be virtual

class Dog {
   public:
    virtual ~Dog() {cout << "dog destroyed\n";} //? with this both yelloDog and DOg will be destroyed
    void bark() { cout << "Whoof, I am just a dog.\n";};
};

class Yellowdog : public Dog{
   public:
   ~Yellowdog() {cout << "yellow dog destroyed\n";}
    void bark() { cout << "Whoof, I am a yellow dog.\n";};
};

class DogFactory {
public:
    static Dog* createYellowDog() {return (new Yellowdog()); } //todo if we are using a class in polymorphic way, the base class destr should be virtual
    // ..create other dogs
};

int main(){

    Dog* pd = DogFactory::createYellowDog();
    //
    //
    delete pd; //! both Dog and YellowDog destructor will be called
    
    return 0;
}

#elif SHARED_PTR //todo if we are using a class in polymorphic way

class Dog {
   public:
    ~Dog() {cout << "dog destroyed\n";} //? destr need not be virtual if using shared_ptr for polymorphism
    //* unique_ptr 'wont' do the same job
    virtual void bark() { cout << "Whoof, I am just a dog.\n";};
};

class Yellowdog : public Dog{
   public:
   ~Yellowdog() {cout << "yellow dog destroyed\n";}
    void bark() { cout << "Whoof, I am a yellow dog.\n";};
};

class DogFactory {
public:
    //todo if we are using a class in polymorphic way,one option is to use share_ptr
    static shared_ptr<Dog> createYellowDog() {return shared_ptr<Yellowdog>(new Yellowdog()); } 
    // ..create other dogs
};

int main(){

    shared_ptr<Dog> pd = DogFactory::createYellowDog();
    //
    //
    
    return 0;
}
//! NOTE: All calasses in STL have no virtual destructor, so be careful inheriting from them
//* sol. : use shared_ptr when dealing with stl classses

#endif