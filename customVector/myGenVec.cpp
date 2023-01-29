#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007

template<typename DT>
class MyVec{
    DT* ptr;
    int capacity;
    int length;

public:
    MyVec();
    MyVec(ll);
    void push_back(DT val);
    DT pop_back();
    ll size();
    ll getCapacity();
    bool empty();
    DT& operator[](ll);

    class Iterator{
        DT* itr;

        public:
        Iterator():itr(nullptr){}
        Iterator(DT* otherPtr):itr(otherPtr){}

        DT operator*(){
            return *itr;
        }

        bool operator==(Iterator rhs){
            return itr==rhs.itr;
        }
        bool operator!=(Iterator rhs){
            return !(*this==rhs);
        }
        Iterator& operator++(){
            ++itr;
            return *this;
        }
        Iterator& operator*(int i){
            Iterator temp(*this);
            ++(*this);
            return temp;
        }
    };
    Iterator begin();
    Iterator end();
}; 

template<typename DT>
MyVec<DT>::MyVec(): ptr(nullptr), capacity(0), length(0){}

template<typename DT>
MyVec<DT>::MyVec(ll cap):ptr(new DT[cap]), capacity(cap), length(0){}

template<typename DT>
void MyVec<DT>::push_back(DT val){

    if(length==capacity){
        DT* temp = ptr;
        ptr = new DT[capacity = capacity*2];
        copy(temp, temp+length, ptr);
        delete[] temp;
    }

    ptr[length++] = val;
}

template<typename DT>
DT MyVec<DT>::pop_back(){
    return ptr[length-- -1];
}

template<typename DT>
ll MyVec<DT>::size(){
    return length;
}

template<typename DT>
ll MyVec<DT>::getCapacity(){
    return capacity;
}

template<typename DT>
bool MyVec<DT>::empty(){
    return (length==0);
}

template<typename DT>
DT& MyVec<DT>::operator[](ll idx){
    if(idx>length)
        cout<<"out of bounds"<<endl;

    return *(ptr+idx);
}

template<typename DT>
typename MyVec<DT>::Iterator MyVec<DT>::begin(){
    return Iterator(ptr);
}

template<typename DT>
typename MyVec<DT>::Iterator MyVec<DT>::end(){
    return Iterator(ptr+length);
}

// https://learn.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
template<typename DT>
ostream& operator<<(ostream& os, MyVec<DT>& genVec){
    
    for(const auto&& el:genVec){
        os<<el<<"->";
    }
    return os;
}

template<typename V>
void displayVector(V& genVec)
{
    cout<<genVec<<" ";
    cout<<endl;
}

int main(){
    
    MyVec<int> v;
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);

	// Declare iterator for traversal in vector v
	MyVec<int>::Iterator it;

	// Function called to display element in
	// vector in v
	cout << "Element in vector v : ";
	displayVector(v);
    return 0;
}