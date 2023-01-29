#include<bits\stdc++.h>
using namespace std;
#define ll long long

template<typename T>
class MyVec{
    T* arr;
    ll capacity;
    ll length;

public:

    MyVec();
    MyVec(ll _capcaity);

    ll push_back(T data);
    T pop_back();
    int size();

    T& operator[](ll index);

    class Iterator{
        T* ptr;
      public:
        Iterator():ptr(nullptr){}
        Iterator(T* a){
            ptr = a;
        }
        T& opertor*(){
            return *ptr;
        }
        bool operator==(const Iterator& right){
            return ptr == right.ptr;
        }

        bool operator!=(const Iterator& right){
            return !(this==right);
        }
        T operator*()const{

            return *ptr;
        }
        Iterator& operator++(){
            ++ptr;
            return *this;
        }

        Iterator operator++(int){
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

    };

    Iterator begin() const;
    Iterator end() const;

};

template<typename T>
MyVec<T>::MyVec(){
        capacity = 1;
        arr = new T[1];
        length = 0;
}

template<typename T>
MyVec<T>::MyVec(ll _cap):capacity(_cap), arr(new T[_cap]), length(0){

}

 
template<typename T>
ll MyVec<T>::push_back(T data){

    if(length == capacity){

        T* buff = arr;
        arr = new T[capacity = capacity*2];
        copy(buff, buff+length, arr);
        delete[] buff;
    }
    arr[length++] = data;
    return length;
}


template<typename T>
T MyVec<T>::pop_back(){

    return arr[length-- -1];
}

template<typename T>
T& MyVec<T>::operator[](ll index){
        return *(arr + index)
}

template<typename T>
int MyVec<T>::size(){
    return lenght;
}

template<typename T>
typename MyVec<T>::Iterator MyVec<T>::begin() const{

    return Iterator(arr);
}

template<typename T>
typename MyVec<T>::Iterator MyVec<T>::end() const{

    return Iterator(arr+length);
}

template<typename V>
void displayVector(V inVec){
    typename V::Iterator it;

    for (it = inVec.begin(); i < inVec.end(); it++)
    {
        cout<< *it << " ";
    }
    
}