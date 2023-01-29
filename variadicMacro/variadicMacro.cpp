#include<bits/stdc++.h>
// #include<varargs.h>
using namespace std;
 
#define ll long long
#define mod 1000000007

//debug macro which stringifies the variable names and their values
#define debPrint(x) cout << #x << " " << x <<endl
//------------------------------------------

#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << vars << " = ";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
}
//------------------------------------------

//?Generic Reader and Writer for multiple variables and containers
template <typename... T>
void read(T &...args) {
    ((cin >> args), ...);
}

template <typename... T>
void write(string delimiter, T &&...args) {
    ((cout << args << delimiter), ...);
}

template <typename T>
void readContainer(T &t) {
    for (auto &e : t) {
        read(e);
    }
}

template <typename T>
void writeContainer(string delimiter, T &t) {
    for (const auto &e : t) {
        write(delimiter, e);
    }
    write("\n");
}
//------------------------------------------

// Decorators in C++ and Multiple Parameters/
// Printing as many variables in one line
template<typename ...T>
void printer(T&&... args) {
    ((cout << args << " "), ...);
}
//Powerful decorator functions in C++
template<typename F>
auto debug_func(const F& func) {
    return [func](auto &&...args) { // forward reference
        cout << "input = ";
        printer(args...);
        auto res = func(forward<decltype(args)>(args)...);
        cout << "res = " << res << endl;
        return res;
    };
}
//------------------------------------------

// Exploiting decorators by nesting them
template<typename F>
auto beautify(const F& func) {
    return [func](auto &&...args) { // forward reference
        cout << "========" << endl;
        func(forward<decltype(args)>(args)...);
        cout << "========" << endl;
    };
}

int main(){

//     int ten = 10;
//     debPrint(ten); // prints "ten = 10"

//     int xx = 3, yy = 10, xxyy = 103;
//     deb(xx); // prints "xx = 3"
//     deb(xx, yy, xxyy); // prints "xx, yy, xxyy = 3, 10, 103"
// //------------------------------------------

//     // No more nested min(x, min(y, ...))
//     int x=1, y=2,z=3, k= 4;
//     // int small = min(x, min(y, min(z, k))); // the old way
//     int small = min({x, y, z, k}); // life is easy
//     cout<< "smallest is: "<<small<<endl;
// //------------------------------------------

//     // python like unwrapping/ structured binding
//     pair<int, int> cur = {1, 2};
//     auto [s, t] = cur;
//     cout<<"\n unwrapped pair: "<< s<<" "<< t<<endl;
//     // x is now 1, y is now 2
//     // no need of cur.first and cur.second

//     array<int, 3> arr = {1, 0, -1};
//     auto [a, b, c] = arr;
//     cout<<"\n unwrapped static array of 3: "<< a<<" "<< b<<" "<< c<<endl;
//     // a is now 1, b is now 0, c is now -1

// //------------------------------------------

//     //Usage: Generic Reader and Writer for multiple variables and containers
//     // Question: read three space seprated integers and print them in different lines.
//     cout<<"enter 3 numbers seperated by space: "<<endl;
// 	read(x, y, z);
// 	write("\n", x, y, z);
// //------------------------------------------
	
//     // even works with variable data types :)
// 	int n;
// 	string st;
//     cout<<"enter vector array size and a string: "<<endl;
// 	read(n, st);
// 	write(" ", st, "has length", n, "\n");
// //------------------------------------------
	
//     // Question: read an array of `N` integers and print it to the output console.
// 	int N;
// 	read(N);
// 	vector<int> arra(N);
// 	readContainer(arra);
// 	writeContainer(" ", arra); // output: arr[0] arr[1] arr[2] ... arr[N - 1]
// 	writeContainer("\n", arra);
// 	/**
// 	* output:
// 	* arr[0]
// 	* arr[1]
// 	* arr[2]
// 	* ...
// 	* ...
// 	* ...
// 	* arr[N - 1]
// 	*/
// //------------------------------------------

//     //Printing as many variables in one line
//     int age = 32;
//     string name = "Thomas";
//     printer("I am", name, ',', age, "years old"); 
//     // ^ This prints the following
//     // I am Thomas, 32 years old
//------------------------------------------

    // Powerful decorator functions in C++
    debug_func(pow(2, 3));
    // ^ this automatically prints
    // input = 2 3 res = 8

    //Exploiting decorators by nesting them
    beautify(debug_func(pow(2, 3)));
    // ^ this now prints
    // ========
    // input = 2 3 res = 8
    // ========
    return 0;
}