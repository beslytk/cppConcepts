#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007

// #define BUGG1 1
// #define VIRT 1
#define BUGG2 1

#ifdef BUGG1
class Dog {
   public:
   Dog(){cout<< "Dog born"<<endl;}
   void bark( ) { cout << "I am just a dog" << endl; }
   void seeCat() { 
        bark();
   }      
};

class Yellowdog : public Dog {
   public:
   Yellowdog(){cout<< "Yellowdog born"<<endl;}
   void bark( ) { cout << "I am a Yellowdog" << endl; }
};


int main(){
    Yellowdog y;
    y.seeCat();

    return 0;
}
// Out:
// Dog born
// Yellowdog born
// I am just a dog //! expected:"I am a Yellowdog" 

#elif VIRT

class Dog {
   public:
   Dog(){cout<< "Dog born"<<endl;}
   virtual void bark( ) { cout << "I am just a dog" << endl; }
   void seeCat() { 
        bark();
   }      
};

class Yellowdog : public Dog {
   public:
   Yellowdog(){cout<< "Yellowdog born"<<endl;}
   virtual void bark( ) { cout << "I am a Yellowdog" << endl; }
};


int main(){
    Yellowdog y;
    y.seeCat();

    return 0;
}

// Dog born
// Yellowdog born
// I am a Yellowdog
//? This is Dynamic binding

#elif BUGG2

class Dog {
   public:
   Dog(){cout<< "Dog born"<<endl;
        bark();                     // bark from constr // virtual table is not created yet when base class constr is called
    }
   virtual void bark( ) { cout << "I am just a dog" << endl; }
   void seeCat() { 
        bark();
   }    
    ~Dog(){
        bark();      // by the time base class destr is calld, yelloDog obj already destroyed
    }

};

class Yellowdog : public Dog {
   public:
   Yellowdog(){cout<< "Yellowdog born"<<endl;}
   virtual void bark( ) { cout << "I am a Yellowdog" << endl; }
};


int main(){
    Yellowdog y;
    y.seeCat();

    return 0;
}

// Dog born
//"I am just a dog"
// Yellowdog born
// I am a Yellowdog
//"I am just a dog"
//! Avoid calling virt fn in constr or Destr
#endif