#include<iostream>

typedef long long ll;
template<typename T>
class GenVec{

    T* ptr;
    int capacity;
    int length;
public:
    GenVec(ll cap):capacity(cap),ptr(new T[capacity]) length(0):{}

    void push_back(T val){
        if(length == capacity){
            T* old = ptr;
            ptr = new T[capacity=capacity*2];
            copy(old, old+length, ptr);
            delete[] old;
        }
        ptr[length++] = val;
    }

    T pop_back(){
        ptr[length-- -1];
    }

    T operator[](ll idx){
        return *(ptr+idx);
    }

    class Iterator{
        T* itr;

    public:
        Iterator():itr(nullptr){}
        Iterator(T* ptr):itr(ptr){}

        Iterator& operator++(){
            ++itr;
            return *this;
        }

        Iterator& operator++(int){
            Iterator temp(*this);
            ++(*this);
            return temp;
        }

        T operator*(){
            return *itr;
        }
    }

    Iterator begin();
    Iterator end();

};

template<typename T>
typename GenVec<T>::Iterator GenVec<T>::begin(){
    return Iterator(ptr);
}

template<typename T>
typename GenVec<T>::Iterator GenVec<T>::end(){
    return Iterator(ptr+length);
}