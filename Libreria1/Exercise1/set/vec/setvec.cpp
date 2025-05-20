
namespace lasd {

/* ************************************************************************** */
// specific constructors

template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data> &traversableC)
{
    traversableC.Traverse([this] (const Data &data)
    {
        Insert(data);
    });
}

template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data> &&mappableC) noexcept
{
    mappableC.Map([this] (Data &data)
    {
        Insert(std::move(data));
    });
}


// copy & move constructors

template <typename Data>
SetVec<Data>::SetVec(const SetVec<Data> &newSet)
{
    head = 0;
    size = newSet.size;
    capacity = newSet.capacity;

    delete [] elements;
    elements = new Data[capacity];
    for (ulong i = 0; i < size; i++)
    {
        elements[i] = newSet[i];
    }
}

template <typename Data>
SetVec<Data>::SetVec(SetVec<Data> &&newSet) noexcept
{
    std::swap(head, newSet.head);
    std::swap(capacity, newSet.capacity);
    std::swap(size, newSet.size);
    std::swap(elements, newSet.elements);
}


// copy & move assignments

template <typename Data>
SetVec<Data> & SetVec<Data>::operator=(const SetVec<Data> &setToCopy)
{
    if (this != &setToCopy)
    {
        size = setToCopy.size;
        capacity = setToCopy.capacity;
        Data *newElements = new Data[capacity];
        for (ulong i = 0; i < size; i++)
        {
            newElements[i] = setToCopy[i];
        }
        delete [] elements;
        elements = newElements;
        head = 0;
    }
    return *this;
}

template <typename Data>
SetVec<Data> & SetVec<Data>::operator=(SetVec<Data> &&setToMove) noexcept
{
    if (this != &setToMove)
    {
        std::swap(capacity, setToMove.capacity);
        std::swap(size, setToMove.size);
        std::swap(elements, setToMove.elements);
        std::swap(head, setToMove.head);
    }
    return *this;
}


// comparison oeprators

template <typename Data>
bool SetVec<Data>::operator==(const SetVec<Data> &set) const noexcept
{
    return LinearContainer<Data>::operator==(set);
}

template <typename Data>
bool SetVec<Data>::operator!=(const SetVec<Data> &set) const noexcept
{
    return !(*this == set);
}


// inhterited methods (from OrderedDictionaryContainer)

template<typename Data>
const Data & SetVec<Data>::Min() const
{
    if (size == 0) throw std::length_error("The set is empty");
    else return elements[head];
}

template<typename Data>
const Data SetVec<Data>::MinNRemove()
{
    Data toReturn = Min();
    head = (head + 1) % capacity;
    if (--size < capacity / 4) Reduce();
    return toReturn;
}

template<typename Data>
void SetVec<Data>::RemoveMin()
{
    head = (head + 1) % capacity;
    if (--size < capacity / 4) Reduce();
}

template<typename Data>
const Data & SetVec<Data>::Max() const
{
    if (size == 0) throw std::length_error("The set is empty");
    else return operator[](size - 1);
}

template<typename Data>
const Data SetVec<Data>::MaxNRemove()
{
    Data toReturn = Max();
    if (--size < capacity / 4) Reduce();
    return toReturn;
}

template<typename Data>
void SetVec<Data>::RemoveMax()
{
    if (--size < capacity / 4) Reduce();
}

template<typename Data>
const Data & SetVec<Data>::Predecessor(const Data &data) const
{
    ulong position = BinarySearch(data);
    if (position == 0 || size == 0) throw std::length_error("Predecessor does not exist");
    else return operator[](position - 1);
}

template<typename Data>
const Data SetVec<Data>::PredecessorNRemove(const Data &data) 
{
    ulong position = BinarySearch(data);
    if (position == 0 || size == 0) throw std::length_error("Predecessor does not exist");
    Data toReturn = operator[](position - 1);
    
    if ((position - 1) > (size - position)) this->RemoveRightShift(position - 1);
    else this->RemoveLeftShift(position - 1);
    
    size--;
    if (size < capacity / 4) Reduce();
    return toReturn;  
}

template<typename Data>
void SetVec<Data>::RemovePredecessor(const Data &data) 
{
    ulong position = BinarySearch(data);
    if (position == 0 || size == 0) throw std::length_error("Predecessor does not exist");

    if ((position - 1) > (size - position)) this->RemoveRightShift(position - 1);
    else this->RemoveLeftShift(position - 1);
    
    size--;
    if (size < capacity / 4) Reduce();
}

template<typename Data>
const Data & SetVec<Data>::Successor(const Data &data) const
{
    ulong position = BinarySearch(data);
    if (position > size-1 || size == 0) throw std::length_error("Successor does not exist");
    else
    {
        if (operator[](position) == data && position < size - 1) return operator[](position+1);
        else return operator[](position);
    } 
    throw std::length_error("Successor does not exist");
}

template<typename Data>
const Data SetVec<Data>::SuccessorNRemove(const Data &data) 
{
    ulong position = BinarySearch(data);
    if (position > size - 1 || size == 0) throw std::length_error("Successor does not exist");
    
    ulong succIndex;
    if (operator[](position) == data && position < size - 1) succIndex = position + 1;
    else succIndex = position;
    Data toReturn = operator[](succIndex);

    if (succIndex > (size - succIndex - 1)) this->RemoveRightShift(succIndex);
    else this->RemoveLeftShift(succIndex);

    size--;
    if (size < capacity / 4) Reduce();
    return toReturn;
}

template<typename Data>
void SetVec<Data>::RemoveSuccessor(const Data &data) 
{
    ulong position = BinarySearch(data);
    if (position > size - 1 || size == 0) throw std::length_error("Successor does not exist");
    
    ulong succIndex;
    if (operator[](position) == data && position < size - 1) succIndex = position + 1;
    else succIndex = position;

    if (succIndex > (size - succIndex - 1)) this->RemoveRightShift(succIndex);
    else this->RemoveLeftShift(succIndex);

    size--;
    if (size < capacity / 4) Reduce();
}



// intherited methods (from DictionaryContainer)

template <typename Data>
bool SetVec<Data>::Insert(const Data &data)
{
    ulong position = BinarySearch(data);
    if (position < size && operator[](position) == data) return false;
    else
    {
        if (size == capacity) Expand();
        if (position > size - position) this -> InsertRightShift(position);
        else this -> InsertLeftShift(position);
        elements[(head + position) % capacity] = data;
        size ++;
        return true;
    }
}

template <typename Data>
bool SetVec<Data>::Insert(Data &&data)
{
    ulong position = BinarySearch(data);
    if (position < size && operator[](position) == data) return false;
    else
    {
        if (size == capacity) Expand();
        else if (position > size - position) this -> InsertRightShift(position);
        else this -> InsertLeftShift(position);
        elements[(head + position) % capacity] = std::move(data);
        size ++;
        return true;
    }
}

template <typename Data>
bool SetVec<Data>::Remove(const Data &data)
{
    ulong position = BinarySearch(data);
    if (position == size || operator[](position) != data) return false;
    else
    {
        if (position > size - position - 1) this -> RemoveRightShift(position);
        else this -> RemoveLeftShift(position);
        size--;
        if (size < capacity / 4) Reduce();
        return true;  
    }
}


// inherited methods (from LinearContainer)

template <typename Data>
const Data & SetVec<Data>::operator[](const ulong index) const
{
    if (index >= size) throw std::out_of_range("Set: invalid index");

    return elements[(head + index) % capacity];
}


// inherited methods (from TestableContainer)

template <typename Data>
bool SetVec<Data>::Exists(const Data &data) const noexcept
{
    ulong index = BinarySearch(data);
    if (index != size && operator[](index) == data) return true;
    return false;
}


// inherited methods (from ClearableContainer)

template <typename Data>
void SetVec<Data>::Clear()
{
    delete [] elements;
    elements = nullptr;
    size = 0;
    head = 0;
    capacity = 0;
}


// from ResizableContainer

template <typename Data>
void SetVec<Data>::Resize(const ulong newSize)
{
    if (newSize == 0) Clear();
    else if (size != newSize)
    {
        while (newSize > capacity) Expand();

        ulong smallestSize = std::min(newSize, size); 
        Data *tmpElements = new Data[newSize]();
        for (ulong i = 0; i < smallestSize; i++)
        {
            tmpElements[i] = std::move(operator[](i));
        }
        std::swap(elements, tmpElements);
        delete[] tmpElements;
        size = newSize;
        head = 0;
    }
}

// auxiliary functions

template <typename Data>
ulong SetVec<Data>::BinarySearch(const Data &data) const noexcept
{
    ulong left = 0;
    ulong right = size;

    while (left < right)
    {
        ulong mid = left + (right - left) / 2;

        if (operator[](mid) < data) left = mid + 1;
        else right = mid;
    }
    return left; // either the position of the data or the position where it should be
}

template <typename Data>
void SetVec<Data>::Expand()
{
    if (capacity == 0) capacity = 10;
    else capacity *= 2;

    Data * newElements = new Data[capacity]();
    for (ulong i = 0; i < size; i++)
    {
        newElements[i] = operator[](i);
    }
    delete[] elements;
    elements = newElements;
    head = 0;
}

template <typename Data>
void SetVec<Data>::Reduce()
{
    if (size == 0) capacity = 10;
    else capacity = size * 2;

    Data * newElements = new Data[capacity]();
    for (ulong i = 0; i < size; i++)
    {
        newElements[i] = operator[](i);
    }
    delete[] elements;
    elements = newElements;
    head = 0;
}

template <typename Data>
void SetVec<Data>::InsertLeftShift(const ulong left) noexcept 
{
    head = (head + capacity - 1) % capacity; // no risk of underflow
    for (ulong i = 0; i < left; ++i) 
    {
        elements[(head + i) % capacity] = std::move(elements[(head + i + 1) % capacity]);
    }
}

template <typename Data>
void SetVec<Data>::InsertRightShift(const ulong right) noexcept 
{
    for (ulong i = size; i > right; --i)
    {
        elements[(head + i) % capacity] = std::move(elements[(head + i - 1) % capacity]);
    }
}

template<typename Data>
void SetVec<Data>::RemoveLeftShift(const ulong pos) noexcept
{
    for (ulong i = pos; i > 0; i--) 
    {
        elements[(head + i) % capacity] = std::move(elements[(head + i - 1) % capacity]);
    }
    head = (head + 1) % capacity;
}

template<typename Data>
void SetVec<Data>::RemoveRightShift(const ulong pos) noexcept
{
    for (ulong i = pos; i + 1 < size; ++i)
    {
        elements[(head + i) % capacity] = std::move(elements[(head + i + 1) % capacity]);
    }
}
/* ************************************************************************** */

}
