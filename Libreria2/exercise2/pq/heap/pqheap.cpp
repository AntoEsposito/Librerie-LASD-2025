namespace lasd {

/* ************************************************************************** */

// specific constructors

template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data> &traversableC): heap(traversableC) 
{
    size = heap.Size();
    capacity = size;
}

template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data> &&mappableC) noexcept: heap(std::move(mappableC))
{
    size = heap.Size();
    capacity = size;
}


// copy & move constructors

template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data> &toCopy): heap(toCopy.heap)
{
    size = toCopy.size;
    capacity = toCopy.capacity;
}

template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data> &&toMove) noexcept: heap(std::move(toMove.heap))
{
    std::swap(size, toMove.size);
    std::swap(capacity, toMove.capacity);
}

// copy & move assignment

template <typename Data>
PQHeap<Data> & PQHeap<Data>::operator=(const PQHeap<Data> &toAssign)
{
    if (this != &toAssign) 
    {
        heap = toAssign.heap;
        size = toAssign.size;
        capacity = toAssign.capacity;
    }
    return *this;
}

template <typename Data>
PQHeap<Data> & PQHeap<Data>::operator=(PQHeap<Data> &&toAssign) noexcept
{
    std::swap(heap, toAssign.heap);
    std::swap(capacity, toAssign.size);
    std::swap(capacity, toAssign.capacity);
    return *this;
}


// Specific member functions (inherited from PQ)

template <typename Data>
const Data & PQHeap<Data>::Tip() const
{
    if (size == 0) throw std::length_error("The priority queue is empty");
    return heap.Front(); // vector method
}

template <typename Data>
void PQHeap<Data>::RemoveTip()
{
    if (size == 0) throw std::length_error("The priority queue is empty");
    
    std::swap(heap.Front(), heap[size - 1]);
    size --;
    
    if (size < capacity / 4) Reduce();
}

template <typename Data>
Data PQHeap<Data>::TipNRemove()
{
    if (size == 0) throw std::length_error("Empty priority queue");
    
    Data toReturn = heap.Front();

    std::swap(heap.Front(), heap[size - 1]);
    size --;
    if (size < capacity / 4) Reduce();
    
    return toReturn;
}

template <typename Data>
void PQHeap<Data>::Insert(const Data &data) 
{
    if (size == capacity) Expand();
    
    heap[size] = data;
    size++;
    
    heap.Heapify();
}

template <typename Data>
void PQHeap<Data>::Insert(Data &&data) noexcept 
{
    if (size == capacity) Expand();
    
    heap[size] = std::move(data);
    size++;

    heap.Heapify();
}

template <typename Data>
void PQHeap<Data>::Change(const ulong index, const Data &newData) {
    if (index >= size)
        throw std::out_of_range("Index out of bounds");
    
    // Store the original element at index
    heap[index] = newData;
    
    // Restore the heap property
    heap.Heapify();
}

template <typename Data>
void PQHeap<Data>::Change(const ulong index, Data &&newData) {
    if (index >= size)
        throw std::out_of_range("Index out of bounds");
    
    // Store the original element at index
    heap[index] = std::move(newData);
    
    // Restore the heap property
    heap.Heapify();
}


// auxiliary functions

template <typename Data>
void PQHeap<Data>::Expand()
{
    capacity *= 2;   
    if (capacity < 10) capacity = 10;
    heap.Resize(capacity);
}

template <typename Data>
void PQHeap<Data>::Reduce() 
{
    ulong newCapacity = size * 2;
    if (newCapacity < 10) newCapacity = 10;
    heap.Resize(newCapacity);
    capacity = newCapacity;
}

/* ************************************************************************** */

}
