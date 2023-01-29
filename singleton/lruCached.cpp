#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mod 1000000007

struct Node{
    int key;
    int val;

    Node* next;
    Node* prev;
};

class LRUCACHE{

    void insert(Node* nod){
        nod->next = mru;
        mru->prev = nod;
        mru->prev->next = nod;
        nod->prev = mru->prev;
        
    }

private:
    unordered_map<int, Node*> keyMap;
    Node* lru;
    Node* mru;
};



int main(){
    
    return 0;
}