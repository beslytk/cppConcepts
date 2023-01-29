#include<bits/stdc++.h>
using namespace std;
#include<memory>

#define ll long long
#define mod 1000000007

// #define SHARED_PTR 1
#define WEAK_PTR 1
#define UNIQUE_PTR 1


#ifdef SHARED_PTR
/*********** Shared_ptr ***********/

// 1. When a pointer outlives pointee: danling pointer
// 2. When a pointee outlives all its pointers: resource leak
//
// Smart Pointers: Make sure the lifetime of a pointer and pointee match.

class Dog {
    string m_name;
  public:
      void bark() { cout << "Dog " << m_name << " rules!" << endl; }
      Dog(string name) { cout << "Dog is created: " << name << endl; m_name = name; }
      Dog() { cout << "Nameless dog created." << endl; m_name = "nameless"; }
     ~Dog() { cout << "dog is destroyed: " << m_name << endl; }
     void bark() {cout<<"Dog"<< m_name<< "rules!"<<endl;_}
	  //void enter(DogHouse* h) { h->setDog(shared_from_this()); }  // Dont's call shared_from_this() in constructor
};

void foo_raw(){
    Dog* p = new Dog("Gunner");
    //...
    delete p;
    //...
    p->bark(); // p is dangling ptr -> undef behavior
}// even if 'delete p'  is deleted, it would lead to mem leak after end of foo()
// keeping track of when to delete obj is hard , therefore use smart pointer

void foo_shared(){
    shared_ptr<Dog> p(new Dog("Gunner")); // count = 1
    {
        shared_ptr<Dog> p2 = p; // count = 2
        p2->bark();
        cout<< p.use_count(); // 2 // use '.' to access shared_ptr members & '->' to access pointer obj members
    }
    // count = 1
    p->bark(); // p is dangling ptr -> undef behavior
}// count = 0

class DogHouse {
    shared_ptr<Dog> m_pD;
public:
    void setDog(shared_ptr<Dog> p) { m_pD = p; cout << "Dog entered house." << endl;}
};

int main ()
{
    foo_shared();
    // pitfalls with shared_ptr
    Dog* d = new Dog("Tank");  // BAD idea
    shared_ptr<Dog> p(d);  // p.use_count  ==1
    shared_ptr<Dog> p2(d); // p2.use_count ==1 //! both p & p2 doesnt know of each othere existence
    //! when either p or p2 goes out of scope Dog "Tank" will be destroyed
    //* An obj should be assigned to smart pointer as soon as it is created. Raw pointer should not be used again
    shared_ptr<Dog> p = make_shared<Dog>("Tank");  // preferred way of creating shared ptr //? faster & safer
    (*p).bark();
    //----------------cast---------------
    // static_pointer_cast
    // dynamic_pointer_cast
    // const_pointer_cast
    //-------------------------------

    shared_ptr<Dog> p3 = make_shared<Dog>("Gunner");  // preferred way of creating shared ptr //? faster & safer
    shared_ptr<Dog> p4 = make_shared<Dog>("Tank");  // preferred way of creating shared ptr //? faster & safer
    p3 = p4; // Gunner is deleted
    p3 = nullptr;// Gunner is deleted
    p3.reset(); // Gunner is deleted
    /********** Custom Deleter ************/
    shared_ptr<Dog> p5 = make_shared<Dog>("Gunner");  //use default delter: operator delete

    shared_ptr<Dog> p6( new Dog("Victor"), 
                        [](Dog* p) {cout << "deleting a dog.\n"; delete p;}
                        );
                        // default deleter is operator delete.
                        
    //shared_ptr<Dog> p7(new Dog[3]); // dog[1] and dog[2] have mem leak
    shared_ptr<Dog> p7(new Dog[3], [](Dog* p) {delete[] p;} ); // "custom deleter" ro delete all dogs
    //-------------------------------
    shared_ptr<Dog> p8 = make_shared<Dog>("Tyson");  //use default delter: operator delete
    Dog* d = p8.get(); // return raw pointer // !avoid using raw pointer after creating shared_ptr

    delete d; // 
    shared_ptr<Dog> p2(d); // ! d is already dangling


    //-------------------------------
    shared_ptr<Dog> pD(new Dog("Gunner"));
    shared_ptr<Dog> pD = make_shared<Dog>(new Dog("Gunner")); // faster and safer
    
    pD->bark();
    
    (*pD).bark();
    
    //    DogHouse h;
    //    DogHouse* ph = new DogHouse();
    //    ph->setDog(pD);
    //    delete ph;
        
        
    //    auto pD2 = make_shared<Dog>( Dog("Smokey") ); // Don't use shared pointer for object on stack.
    //    auto pD2 = make_shared<Dog>( *(new Dog("Smokey")) ); 
    //    pD2->bark();
    //
    //    Dog* p = new Dog();
    //    shared_ptr<int> p1(p);
    //    shared_ptr<int> p2(p);  // Erroneous
    
    shared_ptr<Dog> pD3;
    pD3.reset(new Dog("Tank")); // reassign new Dog obj to pointer and delete old
    pD3.reset();  // Dog destroyed. Same effect as: pD3 = nullptr;
//    
    //pD3.reset(pD.get());  // crashes
    
    /********** Custom Deleter ************/
    shared_ptr<Dog> pD4( new Dog("Victor"), 
                        [](Dog* p) {cout << "deleting a dog.\n"; delete p;}
                        );
                        // default deleter is operator delete.
                        
    //shared_ptr<Dog> pDD(new Dog[3]);
    shared_ptr<Dog> pDD(new Dog[3], [](Dog* p) {delete[] p;} );
}

#elif WEAK_PTR

/*********** weak_ptr *********************/
//weak_ptr has "no ownership" of the pointed object
// only provides "access" to object and have no ownership
// doesnt concern about deltion of object.
// similar to raw pointer but has "one level of protection that no-one can call delete op on this pointer". 
// that has an implication that the pointed object may be delted and weak_ptr may not be holding valid object
// also provides safer access to the pointer 
// cannot be used like regular pointer!
//? to use it we "need to lock()" .IT creates shared_ptr out of weak_ptr so as to "check if ptr is still pointing to valid object"
//? also make sure that while accessing the object will not be deleted
class Dog {
      //shared_ptr<Dog> m_pFriend; //! cyclic reference //! buggy as noth smokey and gunner own each other
      weak_ptr<Dog> m_pFriend;
  public:
      string m_name;
      void bark() { cout << "Dog " << m_name << " rules!" << endl; }
      Dog(string name) { cout << "Dog is created: " << name << endl; m_name = name; }
     ~Dog() { cout << "dog is destroyed: " << m_name << endl; }
     void makeFriend(shared_ptr<Dog> f) { m_pFriend = f; }
     
     void showFriend() { //cout << "My friend is: " << m_pFriend.lock()->m_name << endl;
                         if (!m_pFriend.expired()){
                             cout << "My friend is: " << m_pFriend.lock()->m_name << endl;
                         }
                         cout << " He is owned by " << m_pFriend.use_count() << " pointers." << endl; }
};

int main ()
{
    shared_ptr<Dog> pD(new Dog("Gunner"));
    shared_ptr<Dog> pD2(new Dog("Smokey"));
    pD->makeFriend(pD2);
    pD2->makeFriend(pD);
    
    pD->showFriend();
}


#elif UNIQUE_PTR

/*********** unique_ptr *********************/

// Unique Pointers: exclusive owenership
// light weight smart poiter. less expensive. Hence prefer this over share_ptr if not needed to be shared with other ptrs
//? ONe object can only be owned by one unique_ptr

class Bone{

};

class Dog {
      //Bone* pB;
      unique_ptr<Bone> pB;  // This prevents memory leak even if constructor fails.
  public:
      string m_name;
      void bark() { cout << "Dog " << m_name << " rules!" << endl; }
      Dog() { pB = make_unique<Bone>(); //pB = new Bone();
              cout << "Nameless dog created." << endl;
              m_name = "nameless"; }
      Dog(string name) { cout << "Dog is created: " << name << endl; m_name = name; }
     //~Dog() { delete pB; cout << "dog is destroyed: " << m_name << endl; }
};

void test() {
    
    //Dog* pD = new Dog("Gunner");
    unique_ptr<Dog> pD(new Dog("Gunner"));
    
    pD->bark();
    /* pD does a bunch of different things*/
    
    //Dog* p = pD.release(); //to get raw pointer // pD has given up ownership
    pD = nullptr;//pD.reset();
    //pD.reset(new Dog("Smokey"));
    
    if (!pD) {
        cout << "pD is empty.\n";
    }
    
    //delete pD;   
}

void f(unique_ptr<Dog> p) {
    p->bark(); //Dog "Gunner" is destroyed when p goes out of scope
}

unique_ptr<Dog> getDog() {
    unique_ptr<Dog> p(new Dog("Smokey"));
    return p; // use "move semantic"s as return type is unique_ptr
}

void test2() {
    unique_ptr<Dog> pD(new Dog("Gunner"));
    unique_ptr<Dog> pD2(new Dog("Smokey"));
    pD2 = move(pD);
    // 1. Smokey is destroyed
    // 2. pD becomes empty.
    // 3. pD2 owns Gunner.

    pD2->bark();
    f(move(pD));
    if (!pD) {
       cout << "pD is empty.\n";
    }
   
    unique_ptr<Dog> pD2 = getDog(); // pD2 becomes sole owner of "Smokey"
    pD2->bark();

    // unique_ptr is partially specialized for array(Dog[]) , so no need of special destructor for array
    unique_ptr<Dog[]> dogs(new Dog[3]); 
    dogs[1].bark();
    //(*dogs).bark(); // * is not defined
}

void test3() {
    // prevent resource leak even when constructor fails
}


int main ()
{
    test2();
}
#endif
