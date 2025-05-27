
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector: virtual public MutableLinearContainer<Data>, virtual public ResizableContainer {
  // Must extend MutableLinearContainer<Data>,
  //             ResizableContainer

private:

  // ...

protected:

  using Container::size;

  Data * elements = nullptr;

  // ...

public:

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector(const ulong); // A vector with a given initial dimension
  Vector(const TraversableContainer<Data> &) ; // A vector obtained from a TraversableContainer
  Vector(MappableContainer<Data> &&) noexcept; // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector &);

  // Move constructor
  Vector(Vector &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector & operator=(const Vector &);

  // Move assignment
  Vector & operator=(Vector &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector &) const noexcept;
  bool operator!=(const Vector &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  virtual inline Data & operator[](const ulong) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

  virtual inline Data & Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  virtual inline Data & Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  virtual inline const Data & operator[](const ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  virtual inline const Data & Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

  virtual inline const Data & Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  virtual void Resize(ulong) override; // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual inline void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector: public Vector<Data>, virtual public SortableLinearContainer<Data> {
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:

  using Container::size;

  // ...

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  SortableVector(const ulong); // A vector with a given initial dimension
  SortableVector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
  SortableVector(MappableContainer<Data> &&) noexcept; // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SortableVector(const SortableVector &);

  // Move constructor
  SortableVector(SortableVector &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~SortableVector() = default; // uses the Vector<Data> destructor

  /* ************************************************************************ */

  // Copy assignment
  SortableVector & operator=(const SortableVector &);

  // Move assignment
  SortableVector & operator=(SortableVector &&) noexcept;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
