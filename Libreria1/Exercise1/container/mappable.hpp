
#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MappableContainer: virtual public TraversableContainer<Data> {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MappableContainer & operator=(const MappableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MappableContainer & operator=(MappableContainer &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MappableContainer &) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const MappableContainer &) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  using MapFun = std::function<void(Data &)>;

  virtual void Map(MapFun) = 0;

};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer: virtual public MappableContainer<Data>, virtual public PreOrderTraversableContainer<Data> {
  // Must extend MappableContainer<Data>,
  //             PreOrderTraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~PreOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderMappableContainer & operator=(const PreOrderMappableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PreOrderMappableContainer & operator=(PreOrderMappableContainer &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderMappableContainer &) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const PreOrderMappableContainer &) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void PreOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  virtual void Map(MapFun) override; // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer: virtual public MappableContainer<Data>, virtual public PostOrderTraversableContainer<Data> {
  // Must extend MappableContainer<Data>,
  //             PostOrderTraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~PostOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderMappableContainer & operator=(const PostOrderMappableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PostOrderMappableContainer & operator=(PostOrderMappableContainer &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderMappableContainer &) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const PostOrderMappableContainer &) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void PostOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  virtual void Map(MapFun) override; // Override MappableContainer member

};

/* ************************************************************************** */

}

#include "mappable.cpp"

#endif