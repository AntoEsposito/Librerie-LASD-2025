#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec: virtual public Set<Data>, virtual public ResizableContainer{
  // Must extend Set<Data>,
  //             ResizableContainer

private:

  // ...

protected:

  using Container::size;
  Vector<Data> vector;
  ulong head = 0;
  ulong capacity = 0; // size of the vector

public:

  // Default constructor
  SetVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  SetVec(const TraversableContainer<Data> &); // A set obtained from a TraversableContainer
  SetVec(MappableContainer<Data> &&) noexcept; // A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SetVec(const SetVec &);

  // Move constructor
  SetVec(SetVec &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~SetVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  SetVec & operator=(const SetVec &);

  // Move assignment
  SetVec & operator=(SetVec &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SetVec &) const noexcept;
  bool operator!=(const SetVec &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  virtual inline const Data & Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual const Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  virtual inline const Data & Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual const Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  virtual const Data & Predecessor(const Data &) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  virtual const Data PredecessorNRemove(const Data &) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  virtual void RemovePredecessor(const Data &) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  virtual const Data & Successor(const Data &) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  virtual const Data SuccessorNRemove(const Data &) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  virtual void RemoveSuccessor(const Data &) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual bool Insert(const Data &) override; // Override DictionaryContainer member (copy of the value)
  virtual bool Insert(Data &&) override; // Override DictionaryContainer member (move of the value)
  virtual bool Remove(const Data &) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from LinearContainer)

  virtual inline const Data & operator[](const ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  virtual bool Exists(const Data &) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual inline void Clear() override; // Override ClearableContainer member

  // Specific member function (inherited from ResizableContainer)

  virtual void Resize(const ulong) override;

protected:

  // Auxiliary functions
  virtual ulong BinarySearch(const Data &) const noexcept;
  virtual void Expand(); // Doubles the vector size
  virtual void Reduce(); // Reduces vector size when needed
  
  // Circular vector operations
  virtual void InsertLeftShift(const ulong) noexcept;
  virtual void InsertRightShift(const ulong) noexcept;
  virtual void RemoveLeftShift(const ulong) noexcept;
  virtual void RemoveRightShift(const ulong) noexcept;
};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif
