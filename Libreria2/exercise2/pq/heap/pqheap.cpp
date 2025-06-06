namespace lasd {

/* ************************************************************************** */

// specific constructors

template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data> &traversableC): HeapVec<Data>(traversableC)
{
    capacity = size;
}

template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data> &&mappableC) noexcept: HeapVec<Data>(std::move(mappableC))
{
    capacity = size;
}


// copy & move constructors

template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data> &toCopy): HeapVec<Data>(toCopy)
{
    capacity = toCopy.capacity;
}

template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data> &&toMove) noexcept: HeapVec<Data>(std::move(toMove))
{
    std::swap(capacity, toMove.capacity);
}


// copy & move assignment

template <typename Data>
PQHeap<Data> & PQHeap<Data>::operator=(const PQHeap<Data> &toAssign)
{
    HeapVec<Data>::operator=(toAssign);
    capacity = toAssign.capacity;
    return *this;
}

template <typename Data>
PQHeap<Data> & PQHeap<Data>::operator=(PQHeap<Data> &&toAssign) noexcept
{
    HeapVec<Data>::operator=(std::move(toAssign));
    capacity = std::move(toAssign.capacity);
    return *this;
}


// Specific member functions (inherited from PQ)

template <typename Data>
const Data & PQHeap<Data>::Tip() const
{
    if (size == 0) throw std::length_error("Priority queue is empty");
    return elements[0];
}

template <typename Data>
void PQHeap<Data>::RemoveTip()
{
    if (size == 0) throw std::length_error("Priority queue is empty");

    std::swap(elements[0], elements[size-1]);
    size--;
    HeapVec<Data>::HeapifyDown(0, size);

    if (size < capacity / 4) Resize(size * 2);
}

template <typename Data>
Data PQHeap<Data>::TipNRemove()
{ 
    if (size == 0) throw std::length_error("Priority queue is empty");

    Data toReturn = elements[0];
    std::swap(elements[0], elements[size-1]);
    size--;
    HeapVec<Data>::HeapifyDown(0, size);

    if (size < capacity / 4) Resize(size * 2);
    return toReturn;
}

template <typename Data>
void PQHeap<Data>::Insert(const Data &data)
{
    if (size == capacity) Resize(capacity * 2);
    elements[size] = data;
    size++;
    
    HeapVec<Data>::HeapifyUp(size-1);
}

template <typename Data>
void PQHeap<Data>::Insert(Data &&data)
{
    if (size == capacity) Resize(capacity * 2);
    elements[size] = std::move(data);
    size++;

    HeapVec<Data>::HeapifyUp(size-1);
}

template <typename Data>
void PQHeap<Data>::Change(const ulong index, const Data &newData)
{
    if (index >= size) throw std::out_of_range("Index out of range");
    Data oldData = elements[index];
    elements[index] = newData;
    
    if (newData > oldData) HeapVec<Data>::HeapifyUp(index); 
    else if (newData < oldData) HeapVec<Data>::HeapifyDown(index, size);
}

template <typename Data>
void PQHeap<Data>::Change(const ulong index, Data &&newData)
{
    if (index >= size) throw std::out_of_range("Index out of range");
    Data oldData = elements[index];
    elements[index] = std::move(newData);
    
    if (newData > oldData) HeapVec<Data>::HeapifyUp(index); 
    else if (newData < oldData) HeapVec<Data>::HeapifyDown(index, size);
}


// auxiliary functions

template <typename Data>
void PQHeap<Data>::Resize(ulong newCapacity)
{
    ulong oldSize = size;
    if (newCapacity < 10) newCapacity = 10;

    HeapVec<Data>::Resize(newCapacity);
    capacity = newCapacity;
    size = oldSize;
}

/* ************************************************************************** */

}
