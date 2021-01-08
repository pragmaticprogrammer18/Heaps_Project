#ifndef HEAP_CPP_
#define HEAP_CPP_
#include "Heap.h"
#include <stddef.h> //NULL

#include <iostream>
template<class T, int m_size>
Heap<T, m_size>::Heap() {
  m_array = new T [m_size];
  numitems = 0;
}
template<class T, int m_size>
Heap<T, m_size>::~Heap() {
  delete [] m_array;
}

template<class T, int m_size>
Heap<T, m_size>::Heap(const Heap<T, m_size>& origHeap) {
  m_array = new T [m_size];
  for (int i = 1; i <= (origHeap.numitems); i++)
    {
      m_array[i] = origHeap.m_array[i];
    }
  numitems = origHeap.numitems;
}

template<class T, int m_size>
bool Heap<T, m_size>::Contains(T& needle) const{
  for (int i = 1; i <= numitems; i++)
    {
      if (m_array[i] == needle)
	{
	  return true;
	}
    }
  return false;
}


template<class T, int m_size>
T* Heap<T, m_size>::Find(const T& needle) const {
  for (int i = 1; i < numitems; i++)
    {
      if (m_array[i] == needle)
	{
	  return &m_array[i];
	}
    }
  return 0; //0 = NULL
}

template<class T, int m_size>
void Heap<T, m_size>::PercolateUp(int index) {
  T compare = m_array[index]; //get thing for comparison
  //if minheap compare needs to be bigger than parent to be correct
  //if maxheap compare need to be smaller than parent
  
  int empty = index;//avoids an error with for loops
  //assume minheap for now
  for (; //place you want to move
       (empty > 1 && (compare.GetValue() < m_array[empty/2].GetValue()));
       empty /= 2)
    {
      //compare = m_array[index];
      //if empty is a valid index and empty isn't in the correct spot
      //check the parent 
      //swap parent and child
      T temp = m_array[empty];     
      m_array[empty] = m_array[empty/2];
      m_array[empty/2] = temp;
    }

  //found the right spot and made it empty
   m_array[empty] = compare;
  
}

template<class T, int m_size>
void Heap<T, m_size>::PercolateDown(int index) {
  T compare = m_array[index]; //get thing for comparison
  //if minheap compare needs to be smaller than child to be correct
  //if maxheap compare need to be bigger than child
  
  int empty = index; //avoids error with for loop
  //assume minheap for now
  for (; //place you want to move
       (empty*2 < numitems);
       empty *= 2)
    {
      if (compare.GetValue() > m_array[empty*2].GetValue() || 
	  (compare.GetValue() > m_array[(empty*2)+1].GetValue()))
	{
	  //if bigger than either child
	  //swap with smaller child
	  if (m_array[empty*2].GetValue() < m_array[(empty*2)+1].GetValue())
	    {
	      T temp = m_array[empty];
	      m_array[empty] = m_array[empty*2];
	      m_array[empty*2] = temp;
	    }
	  else
	    {
	      T temp = m_array[empty];
	      m_array[empty] = m_array[(empty*2)+1];
	      m_array[(empty*2)+1] = temp;
	    }
	}
    }
  //found the right spot and made it empty
  m_array[empty] = compare;
}

template<class T, int m_size>
void Heap<T, m_size>::Insert(T& insertable) {

  if (Contains(insertable))
    {
      T* increment = Find(insertable);
      increment->IncHits();
      delete increment;
    }
  else
    {
      //put at end of list
      int hole = ++numitems;
     
      m_array[hole] = insertable;
      //percolate up puts in correct place and inserts the thing
      PercolateUp(hole);

    }

}

template<class T, int m_size>
T& Heap<T, m_size>::Remove() {

  m_array[0] = m_array[1]; //saving root node by putting it in empty spot
  m_array[1] = m_array[numitems];


  //move the hole down
  numitems--;
  PercolateDown(1);

  return m_array[0];
 
}



template<class T, int m_size>
int Heap<T, m_size>::FindIndex(T& needle) const{
  for (int i = 0; i < m_size; i++)
    {
      if (m_array[i] == needle)
	{
	  return i;
	}
    }
  return 0; //something went wrong 
}

template<class T, int m_size>
T* Heap<T, m_size>::GetArray() const{
  return m_array;
}

template<class T, int m_size>
int Heap<T, m_size>::GetNumItems() const{
  return numitems;
}

template<class T, int m_size>
void Heap<T, m_size>::PrintHeap() {
  for (int i = 0; i < m_size; i++)
    {
      std::cout << "Key: " << m_array[i].GetKey()
                << "Data: " << m_array[i].GetValue() << std::endl;
    }

  std::cout << "numitems: " << numitems << std::endl;


}


#endif /* HEAP_CPP_ */
