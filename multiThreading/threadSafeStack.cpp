#include<memory>


template<typename T> 
class concurrent_stack {
    struct Node { 
        T t;
        shared_ptr<Node> next; 
    };
    shared_ptr<Node> head;//atomic_shared_ptr<Node>
    // in C++11: remove “atomic_” and remember to use the special
    // functions every time you touch the variable
    concurrent_stack( concurrent_stack &) =delete;
    void operator=(concurrent_stack&) =delete;

public:
    concurrent_stack() =default;
    ~concurrent_stack() =default;
    class reference {
        shared_ptr<Node> p;
    public:
        reference(shared_ptr<Node> p_) : p{p_} { }
        T& operator* () { return p->t; }
        T* operator->() { return &p->t; }
    };

    auto find( T t ) const {
        auto p = atomic_load(&head);//head.load(); // in C++11: atomic_load(&head)
        while( p && p->t !=t )
            p = p->next;
        return reference(move(p));
    }
    auto front() const {
        return reference(atomic_load(&head)); //reference(head); // in C++11: atomic_load(&head)
    }
    void push_front( Tt ) {
        auto p = make_shared<Node>();
        p->t = t;
        p->next = atomic_load(&head); //head; // in C++11: atomic_load(&head)
        while( !head.compare_exchange_weak(p->next, p) ){ }
        // in C++11: atomic_compare_exchange_weak(&head, &p->next, p);
    }
    void pop_front() {
        auto p = head.load();
        // while( p && !head.compare_exchange_weak(p, p->next) ){ }
        while( p && !atomic_compare_exchange_weak(&head, &p, p->next) ){ }

        // in C++11: atomic_compare_exchange_weak(&head, &p, p->next);
    }
};

