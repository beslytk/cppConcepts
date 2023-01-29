#include <fstream>
#include <vector>
#include <signal.h>
#include <regex.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <iostream>
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include "Dog.h"
#include "Cat.h"
#include "Global.h"

using namespace std;

// Dog d("Gunner");
int main()
{
   // d.bark();
   Global g; // to make sure cat and dog will be deleted by g's destructor when it goes out of scope
   Global::getCat()->meow();


   cout << "hello" << endl;
   Global::getCat();
	return 0;
}

// program would not crash with such singleton class Global for cat and dog as they will be created only when they are needed.


