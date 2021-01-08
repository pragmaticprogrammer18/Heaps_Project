#ifndef MIN_VALUE_HEAP_H_
#define MIN_VALUE_HEAP_H_
#include "PinHit.h"
template<class T, int m_size>
  class Heap;


template<class T, int m_size>
  class MinValueHeap : public Heap<T,m_size>{

 public:
  MinValueHeap();
  MinValueHeap(const Heap<T, m_size>& origHeap);

  void PercolateUp(int index);
  void PercolateDown(int index);

  //all else is inherited
};

#include "MinValueHeap.cpp"
#endif /* MIN_VALUE_HEAP_H_ */
