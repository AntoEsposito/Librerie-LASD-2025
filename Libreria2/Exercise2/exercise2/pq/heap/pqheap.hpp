
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap {
  // Must extend PQ<Data>,
  // Could extend HeapVec<Data>

private:

  // ...

protected:

  // using Container::???;

  // ...

public:

  // Default constructor
  // PQHeap() specifiers;

  /* ************************************************************************ */

  // Specific constructors
  // PQHeap(argument) specifiers; // A priority queue obtained from a TraversableContainer
  // PQHeap(argument) specifiers; // A priority queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  // PQHeap(argument) specifiers;

  // Move constructor
  // PQHeap(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~PQHeap() specifiers;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  // type Tip(argument) specifiers; // Override PQ member (must throw std::length_error when empty)
  // type RemoveTip(argument) specifiers; // Override PQ member (must throw std::length_error when empty)
  // type TipNRemove(argument) specifiers; // Override PQ member (must throw std::length_error when empty)

  // type Insert(argument) specifiers; // Override PQ member (Copy of the value)
  // type Insert(argument) specifiers; // Override PQ member (Move of the value)

  // type Change(argument) specifiers; // Override PQ member (Copy of the value)
  // type Change(argument) specifiers; // Override PQ member (Move of the value)

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
