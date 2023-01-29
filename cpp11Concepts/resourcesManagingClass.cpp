#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007
//case: 
//one object owning another object through a pointer: Person owning string object ptr

// use only one of the switches below
#define BUG 1  // buggy code
// #define SOL0 1    // solution using emplace_back for vector
// #define SOL1 1 // solution using explicit def for copy const and assign op
// #define SOL2 1 // soln using explicit deletion of copy const and ass op and using object pointer as type for vector data

#ifdef BUG
class Person{
public:
    Person(string name) : pName_(new string(name)){}
    ~Person(){delete pName_;}

    void printName(){ cout<< *pName_;} // segmentation fault here as push_back was made(shallow copy) with a rvalue of Person, which gets deleted immediately
    string* pName() const{
        return pName_;
    }
private:
    string* pName_;

}; 

int main(){

    vector<Person> persons;
    persons.push_back(Person("George")); // george is const // copy of George is made to vector persons // GEorge is destroyed
    persons.front().printName();

    return 0;
}
#elif SOL0 // C++11// use emplace back which avoids chances of temp object deletion after creation for copying to vector
class Person{
public:
    Person(string name) : pName_(new string(name)){}
    ~Person(){delete pName_;}

    void printName(){ cout<< *pName_;} // segmentation fault here as push_back was made(shallow copy) with a rvalue of Person, which gets deleted immediately
    string* pName() const{
        return pName_;
    }
private:
    string* pName_;

}; 

int main(){

    vector<Person> persons;
    persons.emplace_back("George"); // inplace construction of object in vectors assigned space
    persons.front().printName();

    return 0;
}
#elif SOL1

// Sol:
// 1> define copy constr and copy assign operator for deep copying
class Person{
public:
    Person(string name) : pName_(new string(name)){}
    ~Person(){delete pName_;}
    Person (const Person& rhs){
        pName_ = new string(*(rhs.pName()));
    }
    Person& operator=(const Person& rhs){
        pName_ = new string(*(rhs.pName()));
    }
    void printName(){ cout<< *pName_;} // segmentation fault here as push_back was made(shallow copy) with a rvalue of Person, which gets deleted immediately
    string* pName() const{
        return pName_;
    }
    Person* clone(){ // helps make object copy when copy constr and copy assi operat are deleted
        return (new Person(*(pName_)));
    }
private:
    string* pName_;

}; 

int main(){

    vector<Person> persons;
    persons.push_back(Person("George")); // george is const // copy of George is made to vector persons // GEorge is destroyed
    // persons.emplace_back("George"); // inplace construction of object in vectors assigned space
    persons.front().printName();
    return 0;
}
#elif SOL2
// Sol:
// 2> delete copy constr and copy assign operator
// STL containers require their containee to be copy constructible and copy assignable
// Workaround for this is to use objects pointers in container instead
class Person{
public:
    Person(string name) : pName_(new string(name)){}
    ~Person(){delete pName_;}

    void printName(){ cout<< *pName_;} // segmentation fault here as push_back was made(shallow copy) with a rvalue of Person, which gets deleted immediately
    string* pName() const{
        return pName_;
    }
    Person* clone(){ // helps make object copy when copy constr and copy assi operat are deleted
        return (new Person(*(pName_)));
    }
private:
    Person (const Person& rhs); // implicit copy can introcude error and will be easy to track
    Person& operator=(const Person& rhs);
    string* pName_;

}; 

int main(){

    vector<Person*> persons;
    persons.push_back(new Person("George"));
    persons.front()->printName();
    // make sure to delete objects after use
    return 0;
}
#endif
