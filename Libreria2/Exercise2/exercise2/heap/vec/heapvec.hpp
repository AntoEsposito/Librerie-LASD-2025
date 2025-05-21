
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec {
  // Must extend Heap<Data>,
  // Could extend Vector<Data>

private:

  // ...

protected:

  // using Container::???;

  // ...

public:

  // Default constructor
  // HeapVec() specifiers;

  /* ************************************************************************ */

  // Specific constructors
  // HeapVec(argument) specifiers; // A heap obtained from a TraversableContainer
  // HeapVec(argument) specifiers; // A heap obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  // HeapVec(argument) specifiers;

  // Move constructor
  // HeapVec(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~HeapVec() specifiers;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  // type IsHeap(argument) specifiers; // Override Heap member

  // type Heapify(argument) specifiers; // Override Heap member

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  // type Sort(argument) specifiers; // Override SortableLinearContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
