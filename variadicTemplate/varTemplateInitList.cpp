#include<sstream>
#include<iostream>
#include<vector>
// https://www.youtube.com/watch?v=o1EvPhz6UNE&t=1101s
// https://www.youtube.com/watch?v=CU3VYN6xGzM&t=360s
template<typename T>
std::string to_string_impl(const T& t){
    std::stringstream sss;
    sss<<t;
    return sss.str();
}

template<typename ... Param>
std::vector<std::string> to_string(const Param& ... param){
    return {to_string_impl(param)...};  // initializer list unwrapping param and call to_string_impl for each param & initializing vector<string>
}

int main(){

    const auto vec = to_string("hello", 1, 5.3, "world", 1.3f);

    for (const auto &o : vec)
    {
        std::cout<< o << "\n";
    }
    
}