
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List: virtual public MutableLinearContainer<Data>, virtual public ClearableContainer {
  // Must extend MutableLinearContainer<Data>,
  //             ClearableContainer

private:

  // ...

protected:

  using Container::size;

  struct Node {

    // Data
    Data element;
    Node *nextNode = nullptr;

    /* ********************************************************************** */

    // Default constructor
    Node() = default;

    // Specific constructors
    Node(const Data &);
    Node(Data &&) noexcept;

    /* ********************************************************************** */

    // Copy constructor
    Node(const Node &);

    // Move constructor
    Node(Node &&);

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node &) const noexcept;
    bool operator!=(const Node &) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    // ...

  };

  Node *head = nullptr;
  Node *tail = nullptr;

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const TraversableContainer<Data> &); // A list obtained from a TraversableContainer
  List(MappableContainer<Data> &&) noexcept; // A list obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List &);

  // Move constructor
  List(List &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  List & operator=(const List &);

  // Move assignment
  List & operator=(List &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List &) const noexcept;
  bool operator!=(const List &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  virtual inline void InsertAtFront(const Data &); // Copy of the value
  virtual inline void InsertAtFront(Data &&); // Move of the value
  virtual inline void RemoveFromFront(); // (must throw std::length_error when empty)
  virtual inline Data FrontNRemove(); // (must throw std::length_error when empty)

  virtual inline void InsertAtBack(const Data &); // Copy of the value
  virtual inline void InsertAtBack(Data &&); // Move of the value
  virtual void RemoveFromBack(); // (must throw std::length_error when empty)
  virtual Data BackNRemove(); // (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  virtual Data & operator[](const ulong) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

  virtual inline Data & Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  virtual inline Data & Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  virtual const Data & operator[](const ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  virtual const inline Data & Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

  virtual const inline Data & Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  virtual void Map(MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  virtual void PreOrderMap(MapFun) override ; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  virtual void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  virtual void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  virtual void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
