
#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetLst: virtual public Set<Data>, virtual protected List<Data> {
  // Must extend Set<Data>,
  //             List<Data>

private:

  // ...

protected:

  using Container::size;

  using typename List<Data>::Node;
  using List<Data>::head;
  using List<Data>::tail;

public:

  // Default constructor
  SetLst() = default;

  /* ************************************************************************ */

  // Specific constructors
  SetLst(const TraversableContainer<Data> &); // A set obtained from a TraversableContainer
  SetLst(MappableContainer<Data> &&) noexcept; // A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SetLst(const SetLst &);

  // Move constructor
  SetLst(SetLst &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~SetLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  SetLst & operator=(const SetLst &);

  // Move assignment
  SetLst & operator=(SetLst &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SetLst &) const noexcept;
  bool operator!=(const SetLst &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  virtual inline const Data & Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual inline const Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual inline void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

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

  // Specific member functions (inherited from LinearContainer)

  virtual const Data & operator[](const ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  virtual bool Exists(const Data &) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() override; // Override ClearableContainer member

protected:

  virtual Node * Find(const Data &) const; // returns a pointer to the node or to his predecessor if it does not exist

  virtual Node * GetAt(Node *, const ulong) const; // return a pointer to the node n positions after the start

};

/* ************************************************************************** */

}

#include "setlst.cpp"

#endif
