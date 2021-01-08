#ifndef HEAP_H_
#define HEAP_H_
#include "PinHit.h"
template<class T, int m_size> class Heap{

 public:

  // required functions by UML
  Heap();
  virtual ~Heap();
  Heap(const Heap<T, m_size>& origHeap);
  virtual bool Contains(T& needle) const;
  virtual T* Find(const T&) const;
  virtual T& Remove();
  virtual void Insert(T& insertable);
  virtual void PercolateUp(int index);
  virtual void PercolateDown(int index);

  // student-made functions below
  virtual int FindIndex(T& needle) const;
  virtual T* GetArray() const;
  virtual int GetNumItems() const;
  virtual void PrintHeap() ;
 protected:

  // UML-required member variables
  T* m_array;
  int numitems; //keeps track of num items in array
  // student-made member variables
  
};

#include "Heap.cpp"
#endif /* HEAP_H_ */
