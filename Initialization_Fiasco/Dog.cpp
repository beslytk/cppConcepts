#include "Dog.h"
#include "Cat.h"
#include "Global.h"
#include <iostream>

//extern Cat c;

//Dog d("Gunner");
// Cat c("Smokey");

void Dog::bark() {
   std::cout << "Dog rules! My name is "  << _name << std::endl;
}

Dog::Dog(char* n) {
   std::cout << "Constructing Dog" << n << std::endl;
   _name = n;
   //c.meow(); // not sure if cat or dog will be constructed first as they are in diff source files
   Global::getCat()->meow();
}
