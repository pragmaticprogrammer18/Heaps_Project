#ifndef MIN_VALUE_HEAP_CPP_
#define MIN_VALUE_HEAP_CPP_
#include "MinValueHeap.h"

template<class T, int m_size>
MinValueHeap<T, m_size>::MinValueHeap() {
  Heap<T,m_size>::m_array = new T [m_size];
}
template<class T, int m_size>
void MinValueHeap<T, m_size>::PercolateUp(int index) {
  //copied from heap (assumed minheap)
  T compare = Heap<T,m_size>::m_array[index]; 

  int empty = index;

  for (; 
       (empty > 1 && (compare.GetValue() < Heap<T,m_size>::m_array[empty/2].GetValue()));
       empty /= 2)
    {
      //if empty is a valid index and empty isn't in the correct spot
      //check the parent
      //swap parent and child

      T temp = Heap<T,m_size>::m_array[empty];
      Heap<T,m_size>::m_array[empty] = Heap<T,m_size>::m_array[empty/2];
      Heap<T,m_size>::m_array[empty/2] = temp;
    }

  //found the right spot and made it empty 
  Heap<T,m_size>::m_array[empty] = compare;
}

template<class T, int m_size>
void MinValueHeap<T, m_size>::PercolateDown(int index) {
  //heap was assumed minheap
  T compare = Heap<T,m_size>::m_array[index]; 

  int empty = index; //avoids error with for loop
 
 
  for (; //place you want to move 
       (empty*2 < Heap<T,m_size>::numitems);
       empty *= 2)
    {
      if (compare.GetValue() > Heap<T,m_size>::m_array[empty*2].GetValue() ||
          (compare.GetValue()>Heap<T,m_size>::m_array[(empty*2)+1].GetValue()))
        {
          //if bigger than either child
          //swap with smaller child

          if (Heap<T,m_size>::m_array[empty*2].GetValue() < 
	      Heap<T,m_size>::m_array[(empty*2)+1].GetValue())
            {
              T temp = Heap<T,m_size>::m_array[empty];

              Heap<T,m_size>::m_array[empty] =
		Heap<T,m_size>::m_array[empty*2];
              Heap<T,m_size>::m_array[empty*2] = temp;
            }
          else
            {
              T temp = Heap<T,m_size>::m_array[empty];

              Heap<T,m_size>::m_array[empty] =
		Heap<T,m_size>::m_array[(empty*2)+1];

              Heap<T,m_size>::m_array[(empty*2)+1] = temp;
            }
        }
    }
  //found the right spot and made it empty 
  Heap<T,m_size>::m_array[empty] = compare;
}


template<class T, int m_size>
MinValueHeap<T, m_size>::
MinValueHeap(const Heap<T, m_size>& origHeap) {
  Heap<T,m_size>::m_array = new T [m_size];
  for (int i = 1; i <= (origHeap.GetNumItems()); i++)
    {
      Heap<T,m_size>::m_array[i] = origHeap.GetArray()[i];
    }
  Heap<T,m_size>::numitems = origHeap.GetNumItems();
}

#endif /* MIN_VALUE_HEAP_CPP_ */
