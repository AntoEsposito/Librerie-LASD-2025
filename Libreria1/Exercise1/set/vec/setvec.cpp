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
SetVec<Data>::SetVec(const SetVec<Data> &newSet): vector(newSet.vector)
{
    size = newSet.size;
    head = newSet.head;
    capacity = newSet.capacity;
}

template <typename Data>
SetVec<Data>::SetVec(SetVec<Data> &&newSet) noexcept: vector(std::move(newSet.vector))
{
    std::swap(size, newSet.size);
    std::swap(head, newSet.head);
    std::swap(capacity, newSet.capacity);
}


// copy & move assignments

template <typename Data>
SetVec<Data> & SetVec<Data>::operator=(const SetVec<Data> &setToCopy)
{
    if (this != &setToCopy)
    {
        vector = setToCopy.vector;
        size = setToCopy.size;
        head = setToCopy.head;
        capacity = setToCopy.capacity;
    }
    return *this;
}

template <typename Data>
SetVec<Data> & SetVec<Data>::operator=(SetVec<Data> &&setToMove) noexcept
{
    if (this != &setToMove)
    {
        std::swap(vector, setToMove.vector);
        std::swap(size, setToMove.size);
        std::swap(head, setToMove.head);
        std::swap(capacity, setToMove.capacity);
    }
    return *this;
}


// comparison operators

template <typename Data>
bool SetVec<Data>::operator==(const SetVec<Data> &set) const noexcept
{
    if(size != set.size) return false;
    
    for(ulong i = 0; i < size; i++) {if(operator[](i) != set[i]) return false;}
    
    return true;
}

template <typename Data>
bool SetVec<Data>::operator!=(const SetVec<Data> &set) const noexcept
{
    return !(*this == set);
}


// inherited methods (from OrderedDictionaryContainer)

template<typename Data>
const Data & SetVec<Data>::Min() const
{
    if (size == 0) throw std::length_error("The set is empty");
    return operator[](0);
}

template<typename Data>
const Data SetVec<Data>::MinNRemove()
{
    Data min = Min();
    head = (head + 1) % capacity;
    size--;
    
    if (size < capacity / 4) Reduce();
    
    return min;
}

template<typename Data>
void SetVec<Data>::RemoveMin()
{
    if (size == 0) throw std::length_error("The set is empty");
    
    head = (head + 1) % capacity;
    size--;
    
    if (size < capacity / 4) Reduce();
}

template<typename Data>
const Data & SetVec<Data>::Max() const
{
    if (size == 0) throw std::length_error("The set is empty");
    return operator[](size - 1);
}

template<typename Data>
const Data SetVec<Data>::MaxNRemove()
{
    Data max = Max();
    size--;
    
    if (size < capacity / 4) Reduce();
    return max;
}

template<typename Data>
void SetVec<Data>::RemoveMax()
{
    if (size == 0) throw std::length_error("The set is empty");
    size--;
    
    if (size < capacity / 4) Reduce();
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
    
    if ((position - 1) > (size - position)) RemoveRightShift(position - 1);
    else RemoveLeftShift(position - 1);
    
    size--;
    
    if (size < capacity / 4) Reduce();
    return toReturn;  
}

template<typename Data>
void SetVec<Data>::RemovePredecessor(const Data &data) 
{
    ulong position = BinarySearch(data);
    if (position == 0 || size == 0) throw std::length_error("Predecessor does not exist");

    if ((position - 1) > (size - position)) RemoveRightShift(position - 1);
    else RemoveLeftShift(position - 1);
    
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
        if (operator[](position) == data && position < size - 1) return operator[](position + 1);
        else return operator[](position);
    } 
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

    if (succIndex > (size - succIndex - 1)) RemoveRightShift(succIndex);
    else RemoveLeftShift(succIndex);

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

    if (succIndex > (size - succIndex - 1)) RemoveRightShift(succIndex);
    else RemoveLeftShift(succIndex);

    size--;
    
    if (size < capacity / 4) Reduce();
}


// inherited methods (from DictionaryContainer)

template <typename Data>
bool SetVec<Data>::Insert(const Data &data)
{
    ulong position = BinarySearch(data);
    if (position < size && operator[](position) == data) return false;
    else
    {
        if (size == capacity) Expand();
        
        if (position > size - position) InsertRightShift(position);
        else InsertLeftShift(position);
        
        vector[(head + position) % capacity] = data;
        size++;
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
        
        if (position > size - position) InsertRightShift(position);
        else InsertLeftShift(position);
        
        vector[(head + position) % capacity] = std::move(data);
        size++;
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
        if (position > size - position - 1) RemoveRightShift(position);
        else RemoveLeftShift(position);
        
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
    return vector[(head + index) % capacity];
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
    vector.Clear();
    size = 0;
    head = 0;
    capacity = 0;
}


// from ResizableContainer

template <typename Data>
void SetVec<Data>::Resize(const ulong newSize)
{
    if (newSize == 0) Clear();
    else if (newSize < size)
    {
        size = newSize;
        if (size < capacity / 4) Reduce();
    }
    else if (newSize > size)
    {
        while (capacity < newSize) Expand();
        size = newSize;
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
    return left; // either the position of the data or, if not found, the position of the predecessor
}

// Expand the vector by doubling its size

template <typename Data>
void SetVec<Data>::Expand()
{
    ulong oldCapacity = capacity;
    if (capacity == 0) capacity = 1;
    else capacity *= 2;
    
    Vector<Data> newVector(capacity);
    for (ulong i = 0; i < size; i++) {newVector[i] = std::move(vector[(head + i) % oldCapacity]);}
    
    vector = std::move(newVector);
    head = 0;
}

template <typename Data>
void SetVec<Data>::Reduce()
{
    if (size > 0) 
    {
        ulong oldCapacity = capacity;
        capacity = size * 2;
        
        Vector<Data> newVector(capacity);
        for (ulong i = 0; i < size; i++) {newVector[i] = std::move(vector[(head + i) % oldCapacity]);}
        vector = std::move(newVector);
        head = 0;
    }
}


template <typename Data>
void SetVec<Data>::InsertLeftShift(const ulong pos) noexcept
{
    head = (head + capacity - 1) % capacity;
    for (ulong i = 0; i < pos; i++) {vector[(head + i) % capacity] = std::move(vector[(head + i + 1) % capacity]);}
}
template <typename Data>
void SetVec<Data>::InsertRightShift(const ulong pos) noexcept
{
    for (ulong i = size; i > pos; i--) {vector[(head + i) % capacity] = std::move(vector[(head + i - 1) % capacity]);}
}
template <typename Data>
void SetVec<Data>::RemoveLeftShift(const ulong pos) noexcept
{
    for (ulong i = pos; i > 0; i--) {vector[(head + i) % capacity] = std::move(vector[(head + i - 1) % capacity]);}
    head = (head + 1) % capacity;
}
template <typename Data>
void SetVec<Data>::RemoveRightShift(const ulong pos) noexcept
{
    for (ulong i = pos; i + 1 < size; i++) {vector[(head + i) % capacity] = std::move(vector[(head + i + 1) % capacity]);}
}

/* ************************************************************************** */

}
