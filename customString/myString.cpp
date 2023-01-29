#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007

// C++ program to illustrate the
// above discussed functionality
#include <cstring>
#include <iostream>
using namespace std;

// Custom string class
class Mystring {

	// Initialise the char array
	char* str;

public:
	// No arguments Constructor
	Mystring();

	// Constructor with 1 arguments
	Mystring(char* val);

	// Copy Constructor
	Mystring(const Mystring& source);

	// Move Constructor
	Mystring(Mystring&& source);

	// Destructor
	~Mystring() { delete str; }
};

// Function to illustrate Constructor
// with no arguments
Mystring::Mystring()
	: str{ nullptr }
{
	str = new char[1];
	str[0] = '\0';
}

// Function to illustrate Constructor
// with one arguments
Mystring::Mystring(char* val)
{
	if (val == nullptr) {
		str = new char[1];
		str[0] = '\0';
	}

	else {

		str = new char[strlen(val) + 1];

		// Copy character of val[]
		// using strcpy
		strcpy(str, val);
		str[strlen(val)] = '\0';

		cout << "The string passed is: "
			<< str << endl;
	}
}

// Function to illustrate
// Copy Constructor
Mystring::Mystring(const Mystring& source)
{
	str = new char[strlen(source.str) + 1];
	strcpy(str, source.str);
	str[strlen(source.str)] = '\0';
}

// Function to illustrate
// Move Constructor
Mystring::Mystring(Mystring&& source)
{
	str = source.str;
	source.str = nullptr;
}

// Driver Code
int main()
{
	// Constructor with no arguments
	Mystring a;

	// Convert string literal to
	// char array
	char temp[] = "Hello";

	// Constructor with one argument
	Mystring b{ temp };

	// Copy constructor
	Mystring c{ a };

	char temp1[] = "World";

	// One arg constructor called,
	// then the move constructor
	Mystring d{ Mystring{ temp } };
	return 0;
}
