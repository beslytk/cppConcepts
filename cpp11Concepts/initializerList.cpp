// C++ 11 extended the support 
// vector<int> v = {3, 4, 1, 9};   // Calling initializer_list constructor
// All the relevant STL containers have been updated to accept initializer_list.

// Define your own initializer_list constructor:
#include<iostream>
#include <initializer_list>
#include<vector>
using namespace std;
class BoVector {
   vector<int> m_vec;
   public:
   BoVector(const initializer_list<int>& v) {
      for (initializer_list<int>::iterator itr = v.begin(); itr!=v.end(); ++ itr)
         m_vec.push_back(*itr);

    //   for(auto num:v){
    //     m_vec.push_back(num);
    //   }   
   }

   int length(){
        return m_vec.size();
   }
   void print(){
        for(int i=0;i<this->length();i++){
            cout<<m_vec[i]<<endl;
        }
   }
};

int main(){

    BoVector v1 = {0, 2, 3, 4};
    BoVector v2{0, 2, 3, 4};   // effectively the same
    v1.print();
    v2.print();

    return 0;
}
