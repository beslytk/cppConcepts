// In C++, stream insertion operator “<<” is used for output and extraction operator “>>” is used for input. 
// We must know the following things before we start overloading these operators. 
// 1) cout is an object of ostream class and cin is an object of istream class 
// 2) These operators must be overloaded as a global function. And if we want to allow them to access private data members of the class, we must make them friend. 
// Why these operators must be overloaded as global? 
// In operator overloading, if an operator is overloaded as a member, then it must be a member of the object on the left side of the operator. 
// For example, consider the statement “ob1 + ob2” (let ob1 and ob2 be objects of two different classes). To make this statement compile, 
//  we must overload ‘+’ in a class of ‘ob1’ or make ‘+’ a global function. 
// The operators ‘<<‘ and ‘>>’ are called like ‘cout << ob1’ and ‘cin >> ob1’. So if we want to make them a member method, then they must be made members of ostream 
// and istream classes, which is not a good option most of the time. Therefore, these operators are overloaded as global functions with two parameters, 
// cout and object of user-defined class.

#include <iostream>
using namespace std;

class Complex
{
private:
	int real, imag;
public:
	Complex(int r = 0, int i =0)
	{ real = r; imag = i; }
	friend ostream & operator << (ostream &out, const Complex &c);
	friend istream & operator >> (istream &in, Complex &c);
};

ostream & operator << (ostream &out, const Complex &c)
{
	out << c.real;
	out << "+i" << c.imag << endl;
	return out;
}

istream & operator >> (istream &in, Complex &c)
{
	cout << "Enter Real Part ";
	in >> c.real;
	cout << "Enter Imaginary Part ";
	in >> c.imag;
	return in;
}

ostream& endl(ostream& os){  // manipulator
	os.put('\n');
	os.flush();
	return os;
}

// ostream has lot of manipulators like:
// cout<<ends; // '\0'
// cout<<flush;
// cin>>ws;
// cout<<setw(8)<< left<<setfill('_')<<99<<endl;
// cout<<hex<<setbase<<14; // 0xe


ostream& ostream::operator<<(ostream&(*func)(ostream& os)){
	return (*func)(*this);
}

int main()
{
    Complex c1;
    cin >> c1;
    cout << "The complex object is ";
    cout << c1;
    return 0;
}
