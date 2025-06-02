
#ifndef PQ_HPP
#define PQ_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQ: virtual public LinearContainer<Data>, virtual public ClearableContainer {
  // Must extend LinearContainer<Data>,
  //             ClearableContainer

private:

protected:

public:

  // Destructor
  virtual ~PQ() = default;

  /* ************************************************************************ */

  // Copy assignment
  PQ & operator=(const PQ &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PQ & operator=(PQ &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data & Tip() const = 0; // (concrete function must throw std::length_error when empty)
  virtual void RemoveTip() = 0; // (concrete function must throw std::length_error when empty)
  virtual Data TipNRemove() = 0; // (concrete function must throw std::length_error when empty)

  virtual void Insert(const Data &) = 0; // Copy of the value
  virtual void Insert(Data &&) = 0; // Move of the value

  virtual void Change(const ulong, const Data &) = 0; // Copy of the value
  virtual void Change(const ulong, Data &&) = 0; // Move of the value

};

/* ************************************************************************** */

}

#endif
