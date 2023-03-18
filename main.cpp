#include <cassert>
#include <cstdint>
#include <iostream>

extern "C"
{
   void* cbq__construct(uint32_t cap);
   void cbq__destruct(void* cbq);

   uint8_t cbq__push(void* cbq, uint8_t val);
   uint8_t cbq__pop(void* cbq, uint8_t *val);
}

int main(int argc, char *argv[])
{
   std::cout << "hello world" << std::endl;
   void *q = cbq__construct(2);
   assert(cbq__push(q, 1));
   assert(cbq__push(q, 2));
   assert(!cbq__push(q, 3)); // full

   uint8_t v;
   assert(cbq__pop(q, &v));
   assert(v == 1);
   assert(cbq__pop(q, &v));
   assert(v == 2);
   assert(!cbq__pop(q, &v)); // empty
   cbq__destruct(q);

   return 0;
}
