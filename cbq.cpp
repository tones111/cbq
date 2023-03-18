#include "cbq.h"

extern "C"
{
   void* cbq__construct(uint32_t cap);
   void cbq__destruct(void* cbq);

   uint8_t cbq__push(void* cbq, const uint8_t *buf, uint32_t len);
   void cbq__force_push(void* cbq, const uint8_t *buf, uint32_t len);
   uint32_t cbq__pop(void* cbq, uint8_t *buf, uint32_t len);

   uint32_t cbq__capacity(void* cbq);
   uint8_t cbq__is_empty(void* cbq);
   uint8_t cbq__is_full(void* cbq);
   uint32_t cbq__len(void* cbq);
}


Cbq::Cbq(uint32_t cap)
{
   q = cbq__construct(cap);
}


Cbq::~Cbq()
{
   cbq__destruct(q);
}


bool Cbq::push(const uint8_t *buf, uint32_t len)
{
   return cbq__push(q, buf, len) != 0;
}


void Cbq::force_push(const uint8_t *buf, uint32_t len)
{
   cbq__force_push(q, buf, len);
}


uint32_t Cbq::pop(uint8_t *buf, uint32_t len)
{
   return cbq__pop(q, buf, len);
}


uint32_t Cbq::capacity()
{
   return cbq__capacity(q);
}


bool Cbq::empty()
{
   return cbq__is_empty(q) != 0;
}


bool Cbq::full()
{
   return cbq__is_full(q) != 0;
}


uint32_t Cbq::size()
{
   return cbq__len(q);
}
