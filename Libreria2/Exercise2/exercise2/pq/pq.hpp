
#ifndef PQ_HPP
#define PQ_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQ {
  // Must extend LinearContainer<Data>,
  //             ClearableContainer

private:

protected:

public:

  // Destructor
  // ~PQ() specifiers

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  // type Tip(argument) specifiers; // (concrete function must throw std::length_error when empty)
  // type RemoveTip(argument) specifiers; // (concrete function must throw std::length_error when empty)
  // type TipNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)

  // type Insert(argument) specifiers; // Copy of the value
  // type Insert(argument) specifiers; // Move of the value

  // type Change(argument) specifiers; // Copy of the value
  // type Change(argument) specifiers; // Copy of the value

};

/* ************************************************************************** */

}

#endif
