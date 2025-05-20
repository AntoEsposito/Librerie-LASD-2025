
#include <stdexcept>

namespace lasd {


/* ************************************************************************** */

// LinearC operators

template <typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer<Data> &containerToCompare) const noexcept
{
    if (containerToCompare.Size() != this->size) return false;
    for (ulong i = 0; i < this->size; i++)
    {
        if (containerToCompare.operator[](i) != operator[](i)) return false;
    }
    return true;
}

template <typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer<Data> &containerToCompare) const noexcept
{
    return !(*this == containerToCompare);
}


// LinearC specific methods

template <typename Data>
const Data & LinearContainer<Data>::Front() const
{
    if (this->Empty()) throw std::length_error("LinearContainer is empty\n");
    else return operator[](0);
}

template <typename Data>
const Data & LinearContainer<Data>::Back() const
{
    if (this->Empty()) throw std::length_error("LinearContainer is empty\n");   
    else return operator[]((this->size)-1);
}

// LinearC inherited methods

template <typename Data>
void LinearContainer<Data>::PreOrderTraverse(TraverseFun traverseFun) const
{
    for (ulong i = 0; i < this->size; i++)
    {
        traverseFun(operator[](i));
    }
}

template <typename Data>
void LinearContainer<Data>::Traverse(TraverseFun traverseFun) const
{
    PreOrderTraverse(traverseFun);
}

template <typename Data>
void LinearContainer<Data>::PostOrderTraverse(TraverseFun traverseFun) const
{
    ulong i = (this->size);
    while (i > 0)
    {
        traverseFun(operator[](--i));
    }
}


// MutableLinearC specific methods

template <typename Data>
Data & MutableLinearContainer<Data>::Front()
{
    return (const_cast<Data &>(Front()));
}

template <typename Data>
Data & MutableLinearContainer<Data>::Back()
{
    return (const_cast<Data &>(Back()));
}


// MutableLinearC inherited methods

template<typename Data>
void MutableLinearContainer<Data>::PreOrderMap(MapFun mapFunction)
{
    for (ulong i = 0; i < this->size; i++)
    {
        mapFunction(operator[](i));
    }
}

template<typename Data>
void MutableLinearContainer<Data>::Map(MapFun mapFunction)
{
    PreOrderMap(mapFunction);
}

template<typename Data>
void MutableLinearContainer<Data>::PostOrderMap(MapFun mapFunction)
{
    ulong i = (this->size);
    while (i > 0)
    {
        mapFunction(operator[](--i));
    }
}



// SortableLinearC specific methods

template<typename Data>
void SortableLinearContainer<Data>::Sort() //InsertionSort
{
    for (ulong i = 1; i < this -> size; i++)
    {
        const Data x = (*this)[i];
        ulong j = i;
        while (j > 0 && (*this)[j-1] > x) // no risk of j becoming < 0
        {
            (*this)[j] = (*this)[j-1];
            j--;
        }
        (*this)[j] = x;
    }
}

/* ************************************************************************** */

}
