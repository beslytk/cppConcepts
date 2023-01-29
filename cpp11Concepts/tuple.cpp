#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007

#include<tuple>

int main(){
    std::pair<int,string> p = make_pair(23, "hello");
    cout<< p.first<<" "<< p.second<<endl;

    tuple<int, string, char> t(32, "Penny", 'a');
    cout<< get<0>(t) <<endl;
    cout<< get<1>(t) <<endl;
    cout<< get<2>(t) <<endl;

    get<1>(t) = "Point";
    string&s = get<1>(t);
    s = "Patience is virtue";

    // ----------------   ----------------   
    tuple<int, string, char> t2; //default constr
    t2 = tuple<int, string, char>(12, "curosity", 'd');
    t2 = make_tuple(12, "curosity", 'd');

    if(t > t2){
        cout<<"t is larger than t2";
        t=t2; // member by member copying
    }

    // ----------------   ----------------   
    // Tuple can store references. 
    // None of other STL containers can do that. They always do copy or move
    string st = "in for a penny";
    tuple<string&> t3(st);
    t3 = make_tuple(ref(st)); // reference wrapper to the string st
    get<0>(t3) = "in for a pound"; // st should be modified
    
    t2 = make_tuple(12, "curosity", 'd');
    int x;
    string y;
    char z;
    make_tuple(ref(x), ref(y), ref(z)) = t2; // x=12; y="curosity";z= 'd'
    std::tie(x,y,z) = t2; // equivalent to above
    std::tie(x, std::ignore, z) = t2; // equivalent to above but ignoring string
    // ----------------   ----------------   

    auto t4 = std::tuple_cat(t2, t3); // t4 is a tuple<int,string,char, string>
    // ----------------   ----------------   

    //type traits
    cout<<std::tuple_size<decltype(t4)>::value<<endl; //4
    std::tuple_element<1, decltype(t4)>::type d; // d is a string
    
    return 0;
}