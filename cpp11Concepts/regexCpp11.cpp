#include<bits/stdc++.h>
using namespace std;
#include <regex>

#define ll long long

 

int main(){
    string str;
    while (true){
    
        cin>>str;
        regex e("abc.", regex_constants::icase);  // . any char
        regex e("^abc.", regex_constants::icase);  // ^ beginning of string
        regex e("abc.$", regex_constants::icase);  // $ end of string

        regex e1("abc?", regex_constants::icase); // ? 0 or 1 preceding char
        regex e2("abc*", regex_constants::icase); // * 0 or more precedin char
        regex e3("abc+", regex_constants::icase); // + 1 or more precedin char
        regex e4("ab[cd]*", regex_constants::icase); // either c or d ->* 0 or more precedin char
        regex e5("ab[^cd]*", regex_constants::icase); // neither c or d ->* 0 or more precedin char | neg of above case
        regex e6("ab[^cd]{3}}", regex_constants::icase); // neither c or d ->exact 3 occurence of  precedin char
        regex e7("ab[^cd]{3,}}", regex_constants::icase); // neither c or d -> 3 or more occurence of  precedin char
        regex e8("abd|de[fg]", regex_constants::icase); // | or
        regex e9("abd|de[\]fg]", regex_constants::icase); // \ escaped ]
        regex e10("(abc)de+\\1]", regex_constants::icase); // () to capture grooup -> \1 first group
        regex e11("(ab)c(de+)\\2\\1]", regex_constants::icase); // () to capture grooup -> \1 first group \2 2nd grp
        regex e12("[[:w:]]+@[[:w:]]+\.com", regex_constants::icase); // [[:w:]] word char: digit, number or underscore

        bool match = regex_match(str,e);
        cout<<(match?"Matched":"Not Matched")<<endl;
    }
    
    return 0;
}