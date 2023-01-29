#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007

/*
 * 2. Uniform Initialization
 */

// C++ 03
// class Dog {     // Aggregate class or struct
//    public:
//       int age;
//       string name;
// };
// Dog d1 = {5, "Henry"};   // Aggregate Initialization

// C++ 11 extended the scope of curly brace initialization
/* Uniform Initialization Search Order:
 * 1. Initializer_list constructor
 * 2. Regular constructor that takes the appropriate parameters.
 * 3. Aggregate initializer.
 */
class Dog {
   public:
      Dog(int age, string name) {
        
      };
};
Dog d1 = {5, "Henry"}; 


class Dog {
   public:
   int age;                                // 3rd choice

   Dog(int a) {                            // 2nd choice
      age = a;
   }

   Dog(const initializer_list<int>& vec) { // 1st choice
      age = *(vec.begin());      
   }
};
Dog d1{3};
 

int main(){
    
    return 0;
}