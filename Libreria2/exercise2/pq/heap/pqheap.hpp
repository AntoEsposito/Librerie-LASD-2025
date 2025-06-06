#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap: virtual public PQ<Data>, protected HeapVec<Data> {
  // Must extend PQ<Data>,
  // Could extend HeapVec<Data>

private:

  // ...

protected:

  using Container::size;
  ulong capacity = 0; // Default capacity for the heap vector

  using Vector<Data>::elements;

public:

  // Default constructor
  PQHeap(): HeapVec<Data>(10) {size = 0; capacity = 10;}

  /* ************************************************************************ */

  // Specific constructors
  PQHeap(const TraversableContainer<Data> &); // A priority queue obtained from a TraversableContainer
  PQHeap(MappableContainer<Data> &&) noexcept; // A priority queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  PQHeap(const PQHeap &);

  // Move constructor
  PQHeap(PQHeap &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~PQHeap() = default;

  /* ************************************************************************ */

  // Copy assignment
  PQHeap & operator=(const PQHeap &);

  // Move assignment
  PQHeap & operator=(PQHeap &&) noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  virtual inline const Data & Tip() const override; // Override PQ member (must throw std::length_error when empty)
  virtual void RemoveTip() override; // Override PQ member (must throw std::length_error when empty)
  virtual Data TipNRemove() override; // Override PQ member (must throw std::length_error when empty)

  virtual void Insert(const Data &) override; // Override PQ member (Copy of the value)
  virtual void Insert(Data &&) override; // Override PQ member (Move of the value)

  virtual void Change(const ulong, const Data &) override; // Override PQ member (Copy of the value) 
  virtual void Change(const ulong, Data &&) override; // Override PQ member (Move of the value)



protected:

  virtual void Resize(ulong) override; // Override ResizableContainer member

};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
