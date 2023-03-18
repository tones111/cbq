#include <cstdint>

class Cbq
{
public:
   Cbq(uint32_t cap);
   ~Cbq();
   Cbq(const Cbq&) = delete;

   bool push(const uint8_t *buf, uint32_t len);
   void force_push(const uint8_t *buf, uint32_t len);
   uint32_t pop(uint8_t *buf, uint32_t len);

   uint32_t capacity();
   bool empty();
   bool full();
   uint32_t size();

private:
   void *q;
};
