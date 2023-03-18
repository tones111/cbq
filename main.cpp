#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include "cbq.h"

int main(int argc, char *argv[])
{
   std::cout << "hello world" << std::endl;

   std::vector<uint8_t> tx_buf = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   Cbq q(2);

   assert(q.capacity() == 2);
   assert(q.empty());
   assert(!q.full());
   assert(q.size() == 0);

   assert(q.push(tx_buf.data(), 1));
   assert(!q.empty());
   assert(!q.full());
   assert(q.size() == 1);

   assert(q.push(tx_buf.data() + 1, 2));
   assert(q.full());
   assert(q.size() == 2);

   assert(!q.push(tx_buf.data() + 3, 3)); // full
   q.force_push(tx_buf.data() + 3, 3);
   assert(q.size() == 2);

   std::vector<uint8_t> rx_buf = {9, 8, 7, 6, 5, 0, 0, 0, 0, 0};

   // dropped
   //assert(q.pop(rx_buf.data(), rx_buf.size()) == 1);
   //assert(rx_buf[0] == 0);

   assert(q.pop(rx_buf.data(), rx_buf.size()) == 2);
   assert(q.size() == 1);
   assert(rx_buf[0] == 1);
   assert(rx_buf[1] == 2);

   assert(q.pop(rx_buf.data(), rx_buf.size()) == 3);
   assert(rx_buf[0] == 3);
   assert(rx_buf[1] == 4);
   assert(rx_buf[2] == 5);

   assert(q.size() == 0);
   assert(q.empty());
   assert(!q.pop(rx_buf.data(), rx_buf.size())); // empty

   return 0;
}
