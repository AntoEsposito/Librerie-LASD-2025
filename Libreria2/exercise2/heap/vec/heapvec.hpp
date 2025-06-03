#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec: virtual public Heap<Data>, public SortableVector<Data> {
  // Must extend Heap<Data>,
  // Must extend SortableVector<Data>

private:

  // ...

protected:

  using Container::size;
  using Vector<Data>::elements;

  // ...

public:

  // Default constructor
  HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  HeapVec(const ulong u): SortableVector<Data>(u) {}; // A heap with a given initial dimension
  HeapVec(const TraversableContainer<Data> &); // A heap obtained from a TraversableContainer
  HeapVec(MappableContainer<Data> &&) noexcept; // A heap obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HeapVec(const HeapVec &);

  // Move constructor
  HeapVec(HeapVec &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  HeapVec & operator=(const HeapVec &);

  // Move assignment
  HeapVec & operator=(HeapVec &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HeapVec &) const noexcept;
  bool operator!=(const HeapVec &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  virtual bool IsHeap() const noexcept override; // Override Heap member

  virtual void Heapify() override; // Override Heap member

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  virtual void Sort() override; // Override SortableLinearContainer member
  
  // Heapify functions
  void HeapifySize(ulong heapsize);
  void HeapifyDown(ulong index, ulong heapsize);
  void HeapifyUp(ulong index, ulong heapsize);

protected:

  void Heapify(ulong, ulong); // index, heapsize

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
