#ifndef MAX_VALUE_HEAP_H_
#define MAX_VALUE_HEAP_H_
#include "PinHit.h"
template<class T, int m_size>
  class Heap;

template<class T, int m_size>
  class MaxValueHeap : public Heap<T,m_size>{

 public:
  MaxValueHeap();
  MaxValueHeap(const Heap<T, m_size>& origHeap);
  void PercolateUp(int index);
  void PercolateDown(int index);

  //everything else is inherited
};

#include "MaxValueHeap.cpp"
#endif /* MAX_VALUE_HEAP_H_ */
