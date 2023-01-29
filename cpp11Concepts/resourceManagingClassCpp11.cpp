#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007
//case: 
//one object owning another object through a pointer: Person owning string object ptr

// C++ 11 provide more tools to handle this case  
// 0> emplace_back
// 1> delete operator


// use only one of the switches below
// #define BUG 1  // buggy code
// #define SOL0 1    // emplace_back
// #define SOL1 1 // solution using delete op for deleting copy const and ass op  and using deque
// #define SOL2 1 // soln using smart pointer shared_ptr
#define SOL3 1 // soln using unique pointer


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

#elif SOL0 // use emplace back which avoids chances of temp object deletion after creation for copying to vector

class Person{
public:
    Person(string name) : pName_(new string(name)){}
    ~Person(){delete pName_;}
    Person(const Person& )  = delete; // explicit deletion of copy constr
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
    cout<< "Solution0"<<endl;

    persons.front().printName();

    return 0;
}

#elif SOL1 // use delete op and use deque instead of vector as vector requires its containee to have copy or move constr

class Person{
public:
    Person(string name) : pName_(new string(name)){}
    ~Person(){delete pName_;}
    Person(const Person& )  = delete; // explicit deletion of copy constr
    void printName(){ cout<< *pName_;} // segmentation fault here as push_back was made(shallow copy) with a rvalue of Person, which gets deleted immediately
    string* pName() const{
        return pName_;
    }
private:
    string* pName_;

}; 

int main(){

    deque<Person> persons;
    persons.emplace_back("George"); // inplace construction of object in vectors assigned space
    cout<< "Solution1"<<endl;

    persons.front().printName();

    return 0;
}

#elif SOL2 // use smart pointer - shared_ptr

class Person{
public:
    Person(string name) : pName_(new string(name)){}
    // destructor not required
    void printName(){ cout<< *pName_;} // segmentation fault here as push_back was made(shallow copy) with a rvalue of Person, which gets deleted immediately
private:
    shared_ptr<string> pName_; // track count of no. of pointers to this object. Obj deleted when it becomes 0.
}; 

int main(){

    vector<Person> persons;
    persons.push_back(Person("George")); // shared _ptr count incremented on copying
    cout<< "Solution2"<<endl;

    persons.front().printName();
    return 0;
}

#elif SOL3 // use unique pointer

class Person{
public:
    Person(string name) : pName_(new string(name)){}
    // destructor not required
    // ?But if we add a destructor, compiler wont create move constructor and the soln wont work with moving rvalue while pushing_back
    // *To counter this we need explicitly request the compiler to create a default move contructor
    // ~Person(){}
    // Person(Person&&) = default;
    void printName(){ cout<< *pName_;} // segmentation fault here as push_back was made(shallow copy) with a rvalue of Person, which gets deleted immediately
private:
    unique_ptr<string> pName_; // track count of no. of pointers to this object. Obj deleted when it becomes 0.
}; 

int main(){

    vector<Person> persons;
    persons.push_back(std::move(Person("George"))); //! unique _ptr needs to be moved not copied!
    cout<< "Solution3"<<endl;
    persons.front().printName();
    return 0;
}
#endif