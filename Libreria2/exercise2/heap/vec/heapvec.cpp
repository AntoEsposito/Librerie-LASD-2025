namespace lasd {

/* ************************************************************************** */
// specific constructors

template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data> &traversableC): SortableVector<Data>(traversableC) {Heapify();}

template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data> &&mappableC) noexcept: SortableVector<Data>(std::move(mappableC)) {Heapify();}


// copy & move constructors

template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data> &toCopy): SortableVector<Data>(toCopy) {}

template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data> &&toMove) noexcept: SortableVector<Data>(std::move(toMove)) {}


// copy & move assignments

template <typename Data>
HeapVec<Data> & HeapVec<Data>::operator=(const HeapVec<Data> &toAssign)
{
    SortableVector<Data>::operator=(toAssign);
    return *this;
}

template <typename Data>
HeapVec<Data> & HeapVec<Data>::operator=(HeapVec<Data> &&toAssign) noexcept
{
    SortableVector<Data>::operator=(std::move(toAssign));
    return *this;
}


// comparison operators

template <typename Data>
bool HeapVec<Data>::operator==(const HeapVec<Data> &heapToCompare) const noexcept
{
    return SortableVector<Data>::operator==(heapToCompare);
}

template <typename Data>
bool HeapVec<Data>::operator!=(const HeapVec<Data> &heapToCompare) const noexcept
{
    return !(*this == heapToCompare);
}


// specific member functions (inherited from Heap)

template <typename Data>
bool HeapVec<Data>::IsHeap() const noexcept
{
    if (size <= 1) return true;

    for (ulong i = 0; i < size / 2; i++)
    {
        ulong left = (2 * i) + 1;
        ulong right = (2 * i) + 2;

        if (left < size && elements[i] < elements[left]) return false;
        if (right < size && elements[i] < elements[right]) return false;
    }
    return true;
}

template <typename Data>
void HeapVec<Data>::Heapify() 
{
    if (size <= 1) return;

    for (ulong i = (size / 2) - 1; i >= 0; i--) 
    {
        Heapify(i, size);
        if (i == 0) break; // Prevents underflow of index i
    }
}


// specific member function (inherited from SortableLinearContainer)

template <typename Data>
void HeapVec<Data>::Sort() // HeapSort
{
    if (size <= 1) return;

    ulong heapSize = size;
    for (ulong i = size - 1; i >= 1; i--)
    {
        std::swap(elements[0], elements[i]);
        heapSize--;
        Heapify(0, heapSize);
    }
}


// public heapify functions

template <typename Data>
void HeapVec<Data>::HeapifySize(ulong heapsize) 
{
    if (heapsize <= 1) return;
    
    for (ulong i = (heapsize / 2) - 1; i >= 0; i--) 
    {
        Heapify(i, heapsize);
        if (i == 0) break; // Prevents underflow of index i
    }
}
template <typename Data>
void HeapVec<Data>::HeapifyDown(ulong index, ulong heapsize) 
{
    ulong max = index;
    ulong left = 2 * index + 1;
    ulong right = 2 * index + 2;

    if (left < heapsize && elements[left] > elements[max]) max = left;

    if (right < heapsize && elements[right] > elements[max]) max = right;

    if (max != index)
    {
        std::swap(elements[index], elements[max]);
        HeapifyDown(max, heapsize);
    }
}
template <typename Data>
void HeapVec<Data>::HeapifyUp(ulong index, ulong heapsize) 
{
    if (index >= heapsize || index == 0) return;
    
    ulong parent = (index - 1) / 2;
    
    if (elements[index] > elements[parent])
    {
        std::swap(elements[index], elements[parent]);
        HeapifyUp(parent, heapsize);
    }
}


// auxiliary functions

template <typename Data>
void HeapVec<Data>::Heapify(ulong index, ulong heapSize)
{
    ulong max = index;
    ulong left = 2 * index + 1;
    ulong right = 2 * index + 2;

    if (left < heapSize && elements[left] > elements[max]) max = left;

    if (right < heapSize && elements[right] > elements[max]) max = right;

    if (max != index)
    {
        std::swap(elements[index], elements[max]);
        Heapify(max, heapSize);
    }
}


/* ************************************************************************** */

}
