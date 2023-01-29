#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007

// #define IMPL_STD 1
// #define IMPL_USR 1
#define IMPL_USR_USE 1

#ifdef IMPL_STD
//############################################################################
/* User Defined Implicit Type Conversion 
 *
 * Categories of Type Conversion:
 *                                  Implicit      Explicit
 * Standard Type Conversion            A            B
 * User Defined Type Conversion        C            D
 *                                              (casting)
 *
 *
 * Category A: Implicit Standard Type Conversion
 */
char c = 'A';
int i = c;   // Integral promotion
char*  pc = 0;  // int -> Null pointer initialization

// void f(int i){}
// f(c);            // implicit conve

class Dog {
   public:
    Dog() {cout << "dog def constr\n";}
    void bark() { cout << "Whoof, I am just a dog.\n";};
};

class Yellowdog : public Dog{
   public:
   ~Yellowdog() {cout << "yellow dog def constr\n";}
    void bark() { cout << "Whoof, I am a yellow dog.\n";};
};

Dog* pd = new Yellowdog();  // pointer type conversion // not User Defined Type Conversion 

#elif IMPL_USR
//----------------------------------------------------------------------------
/* 
 * Category C: Implicit User Defined Type Conversion
 *
 * Defined inside class (user defined type)
 *
 * There are 2 methods to define implicit user defined type conversion:
 * Method 1: Use constructor that can accept a single parameter.
 *    - convert other types of object into your class
 * Method 2: Use the type conversion function  
 *    - convert an object of your class into other types
 */
class dog {
   public:

      // constr which takes single param is also a //!convertor
      dog(string name) {m_name = name; }  // NO explicit
      // If you only want to define a constructor, and no implicit type
      // conversion, always put //!"explicit" before the constructor to 
      // avoid inadvertent type conversion.
      //   explicit dog(string name) {m_name = name; }
      string getName() {return m_name;}
      //!type conversion fn
      operator string() const {return m_name;}
  private:
      string m_name;
};

void main ()
{
  string dogname = "Bob";
  dog dog1 = dogname; // use dog(string name)
  string dog2 = dog1; // use operator string()
  printf("My name is %s.\n", dog1.getName());
}

// OUTPUT:
// My name is Bob

/* //? PRINCIPLE: make interface easy to use correctly and hard to use incorrectly.
 * How hard is enough?  Ideally, uncompilable.
 *
 * General guideline: 
 *    1. Avoid defining seemingly unexpected conversion.
 *    2. Avoid defining two-way implicit conversion.
 */

//-------------------------------------------------------------------
#elif IMPL_USR_USE
/* Implicit type conversion is useful when creating numerical types of class,
 * such as a rational class.
 */
class Rational {
	public:
      Rational(int numerator = 0, int denominator = 1):
               num(numerator),den(denominator) {}
      int num;  // Demo only, public data members are not recommended
      int den;

      const Rational operator*(const Rational& rhs) {
         return Rational(num*rhs.num, den*rhs.den);
      }

    //   operator int() const {
    //     return num/den;
    //   }
};

int main (){
    Rational r1 = 23;
    // case a
    Rational r2 = r1 * 2; //! compile err as // 2 ambiguous path 1>const Rational operator* 2>operator int()
    //case b
    // Rational r3 = 3 * r1 ; //wont compile // need operator int()
    return 0;
}

//? To avoid the ambguity above,its better to have a non-member operator *() : both case a and b would work

//   Rational r3 = 3 * r1;
const Rational operator*( const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.num*rhs.num, lhs.den*rhs.den);
}

#endif