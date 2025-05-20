
namespace lasd {

/* ************************************************************************** */

// Node specific constructors

template <typename Data>
List<Data>::Node::Node(const Data &data): element(data) {}

template <typename Data>
List<Data>::Node::Node(Data &&data) noexcept: element(std::move(data)) {}


// Node move & copy constructors

template <typename Data>
List<Data>::Node::Node(const Node &nodeToCopy): element(nodeToCopy.element) {}

template <typename Data>
List<Data>::Node::Node(Node &&nodeToMove): element(std::move(nodeToMove.element)) {}


// Node comparison operators

template <typename Data>
bool List<Data>::Node::operator==(const Node &nodeToCompare) const noexcept
{
    if (element != nodeToCompare.element) return false;

    if (nextNode == nullptr && nodeToCompare.nextNode == nullptr) return true;
    if (nextNode == nullptr || nodeToCompare.nextNode == nullptr) return false;
    return (*nextNode == *nodeToCompare.nextNode); // recursive
}

template <typename Data>
bool List<Data>::Node::operator!=(const Node &nodeToCompare) const noexcept
{
    return !(*this == nodeToCompare);
}


// List specific constructors

template <typename Data>
List<Data>::List(const TraversableContainer<Data> &traversableC)
{
    traversableC.Traverse([this] (const Data &data)
    {
        InsertAtBack(data);
    });
}

template <typename Data>
List<Data>::List(MappableContainer<Data> &&mappableC) noexcept
{
    mappableC.Map([this] (Data &data)
    {
        InsertAtBack(std::move(data));
    });
}


// List copy & move constructors

template <typename Data>
List<Data>::List(const List<Data> &listToCopy)
{
    if (listToCopy.head != nullptr)
    {
        Node *tmp = listToCopy.head;
        for (ulong i = 0; i < listToCopy.size; i++)
        {
            InsertAtBack(tmp->element);
            tmp = tmp -> nextNode;
        }
    }
}

template <typename Data>
List<Data>::List(List<Data> &&listToMove) noexcept
{
    std::swap(head, listToMove.head);
    std::swap(tail,  listToMove.tail);
    std::swap(size, listToMove.size);
}

// List destructor

template <typename Data>
List<Data>::~List()
{
    Node *tmp = head;
    for (ulong i = 0; i < size; i++)
    {
        Node *node = tmp -> nextNode;
        delete tmp;
        tmp = node;
    }
}


// List copy & move assignments

template <typename Data>
List<Data> & List<Data>::operator=(const List<Data> &newList)
{
    if (newList.Empty() && this != &newList) Clear();
    else if (this != &newList)
    {
        Node *tmp = head;
        Node *newTmp = newList.head;
        if (newList.size > size)
        {
            // copy of the nodes of the newlist
            for (ulong i = 0;  i < size; i++)
            {
                tmp -> element = newTmp -> element;
                tmp = tmp -> nextNode; newTmp =  newTmp -> nextNode;
            }
            // expanding the list
            for (ulong i = size; i < newList.size; i++)
            {
                InsertAtBack(newTmp -> element);
                newTmp = newTmp -> nextNode;
            }
        }
        else
        {
            // copy of the nodes of the newlist
            Node *previousNode = tmp;
            for (ulong i = 0;  i < newList.size; i++)
            {
                tmp -> element = newTmp -> element;
                previousNode = tmp;
                tmp = tmp -> nextNode; newTmp =  newTmp -> nextNode;
            }
            tail = previousNode; tail -> nextNode = nullptr;
            // deleting the nodes in excess
            for (ulong i = newList.size; i < size; i++)
            {
                Node *node = tmp -> nextNode;
                delete tmp;
                tmp = node;
            }
            size = newList.size;
        }
    }
    return *this;
}

template <typename Data>
List<Data> & List<Data>::operator=(List<Data> &&newList) noexcept
{
    std::swap(head, newList.head);
    std::swap(tail, newList.tail);
    std::swap(size, newList.size);
    return *this;
}

// List comparison operators

template <typename Data>
bool List<Data>::operator==(const List<Data> &listToCompare) const noexcept
{
    if (size != listToCompare.size) return false;

    if (head == nullptr && listToCompare.head == nullptr) return true;
    if (head == nullptr || listToCompare.head == nullptr) return false;
    return (*head == *listToCompare.head); // recursive
}

template <typename Data>
bool List<Data>::operator!=(const List<Data> &listToCompare) const noexcept
{
    return !(*this == listToCompare);
}


// List specific methods

template <typename Data>
void List<Data>::InsertAtFront(const Data &data)
{
    Node *newHead = new Node(data);
    if (Empty()) 
    {
        head = newHead;
        tail = head;
    }
    else
    {
        newHead -> nextNode = head;
        head = newHead;
    }
    size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data &&data)
{
    Node *newHead = new Node(std::move(data));
    if (Empty())
    {
        head = newHead;
        tail = head;
    }
    else
    {
        newHead -> nextNode = head;
        head = newHead;
    }
    size++;
}

template <typename Data>
void List<Data>::RemoveFromFront()
{
    if (Empty()) throw std::length_error("The list is empty.");

    Node *tmp = head;
    head = tmp -> nextNode;
    delete tmp; 
    size--;

    if (Empty()) tail = nullptr;
}

template <typename Data>
Data List<Data>::FrontNRemove()
{
    if (Empty()) throw std::length_error("The list is empty.");

    Node *tmp = head;
    Data dataToReturn(std::move(tmp->element));

    head = tmp -> nextNode;
    delete tmp;
    size--;

    if (Empty()) tail = nullptr;
    return dataToReturn;
}

template <typename Data>
void List<Data>::InsertAtBack(const Data &data)
{
    Node *newTail = new Node(data);
    if (Empty())
    {
        tail = newTail;
        head = tail;
    }
    else
    {
        tail -> nextNode = newTail;
        tail = newTail;
    }
    size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data &&data)
{
    Node *newTail = new Node(std::move(data));
    if (Empty())
    {
        tail = newTail;
        head = tail;
    }
    else
    {
        tail -> nextNode = newTail;
        tail = newTail;
    }
    size++;
}

template <typename Data>
void List<Data>::RemoveFromBack() 
{
    if (Empty()) throw std::length_error("The list is empty.");

    if (size == 1) 
    {
        delete tail;
        head = nullptr; 
        tail = nullptr;
    } 
    else 
    {
        Node *tmp = head;
        for (ulong i = 0; i < size - 2; i++) tmp = tmp->nextNode;
        delete tail;
        tail = tmp;
        tail -> nextNode = nullptr;
    }
    size--;
}


template <typename Data>
Data List<Data>::BackNRemove()
{
    if (Empty()) throw std::length_error("The list is empty.");

    Data dataToReturn;
    if (size == 1)
    {
        dataToReturn = (std::move(tail -> element));
        delete tail;
        head = nullptr; tail = nullptr;
    }
    else
    {
        Node *tmp = head;
        for (ulong i = 0; i < size - 2; i++) tmp = tmp -> nextNode;

        dataToReturn = (std::move(tail -> element));
        delete tail;
        tail = tmp;
        tail -> nextNode = nullptr;
    }
    size--;
    return dataToReturn;
}


// List inherited methods (from MutableLinearContainer & LinearContainer)

template <typename Data>
Data & List<Data>::operator[](const ulong index)
{
    if (index >= size) throw std::out_of_range("Invalid index");

    if (index == size) return Back();
    else
    {
        Node *tmp = head;
        for (ulong i = 0; i < index; i++) tmp = tmp -> nextNode;
        return tmp -> element;
    }
}

template <typename Data>
Data & List<Data>::Front()
{
    if (Empty()) throw std::length_error("The list is empty.");
    return head -> element;
}

template <typename Data>
Data & List<Data>::Back()
{
    if (Empty()) throw std::length_error("The list is empty.");
    return tail -> element;
}

template <typename Data>
const Data & List<Data>::operator[](const ulong index) const
{
    if (index >= size) throw std::out_of_range("Invalid index");

    if (index == size) return Back();
    else
    {
        Node *tmp = head;
        for (ulong i = 0; i < index; i++) tmp = tmp -> nextNode;
        return tmp -> element;
    }
}

template <typename Data>
const Data & List<Data>::Front() const
{
    if (Empty()) throw std::length_error("The list is empty.");
    return head -> element;
}

template <typename Data>
const Data & List<Data>::Back() const
{
    if (Empty()) throw std::length_error("The list is empty.");
    return tail -> element;
}

// List inherited methods (from PreOrder, PostOrder & MappableContainer)

template <typename Data>
void List<Data>::PreOrderMap(MapFun mapFunction)
{
    Node *tmp = head;
    for (ulong i = 0; i < size; i++)
    {
        mapFunction(tmp -> element);
        tmp = tmp -> nextNode;
    }
}

template <typename Data>
void List<Data>::Map(MapFun mapFunction)
{
    PreOrderMap(mapFunction);
}

template <typename Data>
void List<Data>::PostOrderMap(MapFun mapFunction)
{
    // Lambda function that recursively iterates to the list tail and then applies mapFunction in PostOrder
    std::function<void(Node *)> recursiveMap = [&recursiveMap, &mapFunction](Node *currentNode)
    {
        if (currentNode != nullptr)
        {
            recursiveMap(currentNode -> nextNode);
            mapFunction(currentNode -> element);
        }
    };
    recursiveMap(head);
}


// List inherited methods (from Preorder, PostOrder & TraversableContainer)

template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun traverseFunction) const
{
    Node *tmp = head;
    for (ulong i = 0; i < size; i++)
    {
        traverseFunction(tmp -> element);
        tmp = tmp -> nextNode;
    }
}

template <typename Data>
void List<Data>::Traverse(TraverseFun traverseFunction) const
{
    PreOrderTraverse(traverseFunction);
}

template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun traverseFunction) const
{
    // Lambda function that recursively iterates to the list tail and then applies traverseFunction in PostOrder
    std::function<void(Node *)> recursiveTraverse = [&recursiveTraverse, &traverseFunction](Node *currentNode)
    {
        if (currentNode != nullptr)
        {
            recursiveTraverse(currentNode -> nextNode);
            traverseFunction(currentNode -> element);
        }
    };
    recursiveTraverse(head);  
}


// List inherited  methods (from ClearableContainer)

template <typename Data>
void List<Data>::Clear()
{
    Node *tmp = head;
    for (ulong i = 0; i < size; i++)
    {
        Node *node = tmp -> nextNode;
        delete tmp;
        tmp = node;
    }
    head = nullptr; 
    tail = nullptr;
    size = 0;
}
/* ************************************************************************** */

}