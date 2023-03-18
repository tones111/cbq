#include <cassert>
#include <cstdint>
#include <iostream>
#include <array>
#include <thread>
#include <vector>

#include "cbq.h"

void test_single_thread();
void test_multi_thread();

int main(int argc, char *argv[])
{
   std::cout << "hello world" << std::endl;
   test_single_thread();
   test_multi_thread();
   return 0;
}

void test_single_thread()
{
   const std::vector<uint8_t> tx_buf = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

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
}


void test_multi_thread()
{
   constexpr uint32_t NUM_THREADS = 10;
   constexpr uint32_t NUM_ITEMS = 10'000;
   Cbq q(500);

   std::array<std::thread, NUM_THREADS> tx_threads;
   for (std::thread &t : tx_threads)
   {
      t = std::thread([&q] {
         uint8_t buf = 10;
         for (int i = 0; i < NUM_ITEMS; ++i)
         {
            while (!q.push(&buf, 1)) {}
         }
      });
   }

   std::array<std::thread, NUM_THREADS> rx_threads;
   for (std::thread &t : rx_threads)
   {
      t = std::thread([&q] {
         uint8_t buf = 0;
         for (int i = 0; i < NUM_ITEMS; ++i)
         {
            while (!q.pop(&buf, 1)) {}
         }
      });
   }

   std::cout << "begin tx join" << std::endl; 
   for (std::thread &t : tx_threads)
   {
      t.join();
   }

   std::cout << "begin rx join" << std::endl; 
   for (std::thread &t : rx_threads)
   {
      t.join();
   }
   std::cout << "join complete" << std::endl; 

   assert(q.empty());
}
