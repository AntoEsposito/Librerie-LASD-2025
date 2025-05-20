namespace lasd {

/* ************************************************************************** */

// specific constructors

template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data> &traversableC)
{
    traversableC.Traverse([this] (const Data &data)
    {
        Insert(data);
    });
}

template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data> &&mappableC) noexcept
{
    mappableC.Map([this] (Data &data)
    {
        Insert(std::move(data));
    });
}


// copy & move constructors

template <typename Data>
SetLst<Data>::SetLst(const SetLst &newSet): List<Data>(newSet) {}

template <typename Data>
SetLst<Data>::SetLst(SetLst &&newSet) noexcept: List<Data>(std::move(newSet)) {}


// copy & move assignment

template <typename Data>
SetLst<Data> & SetLst<Data>::operator=(const SetLst &newSet)
{
    List<Data>::operator=(newSet);
    return *this;
}

template <typename Data>
SetLst<Data> & SetLst<Data>::operator=(SetLst &&newSet) noexcept
{
    List<Data>::operator=(std::move(newSet));
    return *this;
}

// comparison operators

template <typename Data>
bool SetLst<Data>::operator==(const SetLst &setToCompare) const noexcept
{
    return List<Data>::operator==(setToCompare);
}

template <typename Data>
bool SetLst<Data>::operator!=(const SetLst &setToCompare) const noexcept
{
    return !(*this == setToCompare);
}


// inherited methods (From OrderedDictionaryContainer)

template <typename Data>
const Data & SetLst<Data>::Min() const
{
    return List<Data>::Front();
}

template <typename Data>
const Data SetLst<Data>::MinNRemove()
{
    return List<Data>::FrontNRemove();
}

template <typename Data>
void SetLst<Data>::RemoveMin()
{
    List<Data>::RemoveFromFront();
}

template <typename Data>
const Data & SetLst<Data>::Max() const
{
    return List<Data>::Back();
}

template <typename Data>
const Data SetLst<Data>::MaxNRemove()
{
    return List<Data>::BackNRemove();
}

template <typename Data>
void SetLst<Data>::RemoveMax()
{
    List<Data>::RemoveFromBack();
}

template <typename Data>
const Data & SetLst<Data>::Predecessor(const Data &data) const
{
    if (size == 0 || head -> element >= data) throw std::length_error("Predecessor does not exist");

    Node *current = head;
    while (current -> nextNode != nullptr)
    {
        if (current -> nextNode -> element >= data) return current -> element;
        current = current -> nextNode;
    }
    return tail -> element;
}

template <typename Data>
const Data SetLst<Data>::PredecessorNRemove(const Data &data)
{
    if (size == 0 || head -> element >= data) throw std::length_error("Predecessor does not exist");

    Data toReturn;
    Node *toDelete = head;
    Node *prev = nullptr;
    while (toDelete -> nextNode != nullptr)
    {
        if (toDelete -> nextNode -> element >= data) break;
        prev = toDelete; 
        toDelete = toDelete -> nextNode;
    }

    if (toDelete == head) {toReturn = std::move(head -> element); RemoveMin();}
    else if (toDelete == tail) {toReturn = std::move(tail -> element); RemoveMax();}
    else
    {
        toReturn = std::move(toDelete -> element);
        prev -> nextNode = toDelete -> nextNode;
        delete toDelete;
        size--;
    }
    return toReturn;
}

template <typename Data>
void SetLst<Data>::RemovePredecessor(const Data &data)
{
    if (size == 0 || head -> element >= data) throw std::length_error("Predecessor does not exist");

    Node *toDelete = head;
    Node *prev = nullptr;
    while (toDelete -> nextNode != nullptr)
    {
        if (toDelete -> nextNode -> element >= data) break;
        prev = toDelete; 
        toDelete = toDelete -> nextNode;
    }

    if (toDelete == head) RemoveMin();
    else if (toDelete == tail) RemoveMax();
    else
    {
        prev -> nextNode = toDelete -> nextNode;
        delete toDelete;
        size--;
    }
}

template <typename Data>
const Data & SetLst<Data>::Successor(const Data &data) const
{
    const Node *node= Find(data);
    if (node == nullptr || node == tail) throw std::length_error("Successor does not exist");
    return node -> nextNode -> element;
}

template <typename Data>
const Data SetLst<Data>::SuccessorNRemove(const Data &data)
{
    Node *node = Find(data);
    if (node == nullptr || node == tail) throw std::length_error("Successor does not exist");

    Node *toDelete = node -> nextNode;
    Data toReturn = std::move(toDelete -> element);

    node -> nextNode = toDelete -> nextNode;
    if (toDelete == tail) tail = node;

    delete toDelete;
    size--;
    return toReturn;
}

template <typename Data>
void SetLst<Data>::RemoveSuccessor(const Data &data)
{
    Node *node = Find(data);
    if (node == nullptr || node == tail) throw std::length_error("Successor does not exist");

    Node *toDelete = node -> nextNode;

    node -> nextNode = toDelete -> nextNode;
    if (toDelete == tail) tail = node;

    delete toDelete;
    size--;
}


// inherited methods (from DictionaryContainer)

template <typename Data>
bool SetLst<Data>::Insert(const Data &data)
{
    Node *node = Find(data);

    if (node == nullptr) {List<Data>::InsertAtFront(data); return true;}
    else if (node -> element == data) return false;
    else
    {
        Node *newNode = new Node(data);
        newNode -> nextNode = node -> nextNode;
        node -> nextNode = newNode;
        if (newNode -> nextNode == nullptr) tail = newNode;
        size++;
        return true; 
    }
}

template <typename Data>
bool SetLst<Data>::Insert(Data &&data)
{
    Node *node = Find(data);

    if (node == nullptr) {List<Data>::InsertAtFront(std::move(data)); return true;}
    else if (node -> element == data) return false;
    else
    {
        Node *newNode = new Node(std::move(data));
        newNode -> nextNode = node -> nextNode;
        node -> nextNode = newNode;
        if (newNode -> nextNode == nullptr) tail = newNode;
        size++;
        return true; 
    }
}

template <typename Data>
bool SetLst<Data>::Remove(const Data &data)
{
    if (size == 0) return false;
    else if (head -> element == data) {RemoveMin(); return true;}
    else if (tail -> element == data) {RemoveMax(); return true;}
    else
    {
        Node *current = head;
        while (current -> nextNode != nullptr)
        {
            if (current -> nextNode -> element >= data) break;
            current = current -> nextNode;
        }
        if (current -> nextNode -> element == data)
        {
            Node *toDelete = current -> nextNode;
            current -> nextNode = toDelete -> nextNode;
            delete toDelete;
            size--;
            return true;
        }
        else return false; // data not found
    } 
}

// inherited methods (from LinearContainer)

template <typename Data>
const Data & SetLst<Data>::operator[](const ulong index) const
{
    return List<Data>::operator[](index);
}


// inherited methods (from TestableContainer)

template <typename Data>
bool SetLst<Data>::Exists(const Data &data) const noexcept
{
    const Node *node = Find(data);
    if (node == nullptr || node -> element != data) return false;
    return true;
}

// inherited methods (from ClearableContainer)

template <typename Data>
void SetLst<Data>::Clear()
{
    List<Data>::Clear();
}


// auxiliary functions

template <typename Data>
SetLst<Data>::Node * SetLst<Data>::Find(const Data &data) const
{
    Node *result = nullptr;
    Node *start = head;
    ulong remaining = size;

    while (remaining > 0)
    {
        ulong half = remaining / 2;
        Node *midNode = GetAt(start, half);

        if (midNode->element == data) return midNode;
            
        if (midNode->element < data)
        {
            result = midNode; // possible predecessor
            start = midNode->nextNode;
            remaining -= (half + 1);
        }
        else remaining = half;
    }
    return result; // the node containing the data or, if it doesn't exist, the node containing the predecessor
}

template <typename Data>
SetLst<Data>::Node * SetLst<Data>::GetAt(Node *start, const ulong n) const
{
    // this function is only used by Find, so no need to check if n is valid
    for (ulong i = 0; i < n && start != nullptr ; i++)
    {
        start = start -> nextNode;
    }
    return start;
}
/* ************************************************************************** */

}
