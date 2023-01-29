class Dog;
class Cat;


class Singleton{

    static Dog* pd;
    static Cat* pc;

protected:
    Singleton() = default;
    Singleton(const Singleton&) = default;

public:
    ~Singleton(){
        if(pd)
            delete pd;

        if(pc)
            delete pc;
        pd=0;
        pc=0;
    }
    static Dog* getDogInstance(){
        if(!pd)
            pd = new Dog("Gunner"); // init upon first usage
        return pd;
    }

    static Cat* getCatInstance(){
        if(!pc)
            pc = new Cat("Smokey");
        return pc;
    }
};

static Dog* Singleton::pd =0;
static Cat* Singleton::pc =0;


int int main(int argc, const char** argv) {
    Singleton sing;

    Singleton::getCatInstance()->meow();
    Singleton::getDogInstance()->bark();

    return 0;
}
