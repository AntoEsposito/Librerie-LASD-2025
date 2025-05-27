namespace lasd {

/* ************************************************************************** */
// specific constructors

template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data> &traversableC): SortableVector<Data>(traversableC) {Heapify();}

template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data> &&mappableC) noexcept: SortableVector<Data>(std::move(mappableC)) {Heapify();}


// copy & move constructors

template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data> &heapToCopy): SortableVector<Data>(heapToCopy) {Heapify();}

template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data> &&heapToMove) noexcept: SortableVector<Data>(std::move(heapToMove)) {Heapify();}


// copy & move assignments

template <typename Data>
HeapVec<Data> & HeapVec<Data>::operator=(const HeapVec<Data> &heapToAssign)
{
    SortableVector<Data>::operator=(heapToAssign);
    return *this;
}

template <typename Data>
HeapVec<Data> & HeapVec<Data>::operator=(HeapVec<Data> &&heapToAssign) noexcept
{
    SortableVector<Data>::operator=(std::move(heapToAssign));
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
    if (size == 0) return true;
    for (ulong i = 0; i < size / 2; i++)
    {
        ulong leftChildIndex = 2 * i + 1;
        ulong rightChildIndex = 2 * i + 2;
        if (leftChildIndex < size && elements[i] < elements[leftChildIndex]) return false;
        if (rightChildIndex < size && elements[i] < elements[rightChildIndex]) return false;
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

template <typename Data>
void HeapVec<Data>::HeapifyAt(ulong index, ulong heapsize) 
{
    Heapify(index, heapsize);
}

template <typename Data>
void HeapVec<Data>::HeapifyFromSize(ulong heapsize) 
{
    for (ulong i = (heapsize / 2) - 1; i >= 0; i--) 
    {
        Heapify(i, heapsize);
        if (i == 0) break;
    }
}


/* ************************************************************************** */

}
