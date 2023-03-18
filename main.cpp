#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

extern "C"
{
   void* cbq__construct(uint32_t cap);
   void cbq__destruct(void* cbq);

   uint8_t cbq__push(void* cbq, uint8_t *buf, uint32_t len);
   uint32_t cbq__pop(void* cbq, uint8_t *buf, uint32_t len);
}

int main(int argc, char *argv[])
{
   std::cout << "hello world" << std::endl;

   std::vector<uint8_t> tx_buf = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   void *q = cbq__construct(2);
   assert(cbq__push(q, tx_buf.data(), 1));
   assert(cbq__push(q, tx_buf.data() + 1, 2));
   assert(!cbq__push(q, tx_buf.data(), 3)); // full

   std::vector<uint8_t> rx_buf = {9, 8, 7, 6, 5, 0, 0, 0, 0, 0};
   assert(cbq__pop(q, rx_buf.data(), rx_buf.size()) == 1);
   assert(rx_buf[0] == 0);

   assert(cbq__pop(q, rx_buf.data(), rx_buf.size()) == 2);
   assert(rx_buf[0] == 1);
   assert(rx_buf[1] == 2);
   assert(!cbq__pop(q, rx_buf.data(), rx_buf.size())); // empty
   cbq__destruct(q);

   return 0;
}
