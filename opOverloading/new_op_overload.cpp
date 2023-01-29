#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007
// Note: new handler is afn invoked when operator new fails to allocate memory
// set_new_handler installs a new handler and return current new handler
void* operator new(size_t len)// throw( bad_alloc) 
{

    while(true){
        void* m = malloc(len);
        if(m)
            return m;

        std::new_handler _handler = set_new_handler(0); // get new handler
        set_new_handler(_handler);
        if(_handler)
            (*_handler)(); // invoke new handler
        else    
            throw bad_alloc();
    }
} 


void operator delete(void* ptr){

    free(ptr);
}

int main(){
    
    return 0;
}