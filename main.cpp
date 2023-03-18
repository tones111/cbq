#include <iostream>

extern "C"
{
   void* cbq__construct();
   void* cbq__destruct();
}

int main(int argc, char *argv[])
{
   std::cout << "hello world" << std::endl;
   cbq__construct();
   cbq__destruct();

   return 0;
}
