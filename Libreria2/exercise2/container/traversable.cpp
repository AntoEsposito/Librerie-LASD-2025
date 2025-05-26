
namespace lasd {

/* ************************************************************************** */

//TraversableC methods

template <typename Data>
template <typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const
{
    Traverse( [foldFunction, &accumulator] (const Data &data)
    {
        accumulator = foldFunction(data, accumulator);
    });
    return accumulator;
}

template <typename Data>
bool TraversableContainer<Data>::Exists(const Data &data) const noexcept
{
    bool exists = false;
    Traverse( [&exists, &data] (const Data &dataToCompare)
    {
        if (data == dataToCompare) exists = true;
    });
    return exists;
}


//PreOrderTraversableC methods

template <typename Data>
template <typename Accumulator>
Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const
{
    PreOrderTraverse( [foldFunction, &accumulator] (const Data &data)
    {
        accumulator = foldFunction(data, accumulator);
    });
    return accumulator;
}

template <typename Data>
void PreOrderTraversableContainer<Data>::Traverse(TraverseFun traverseFunction) const
{
    PreOrderTraverse(traverseFunction);
}


//PostOrderTraversableC methods

template <typename Data>
template <typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const
{
    PostOrderTraverse( [foldFunction, &accumulator] (const Data &data)
    {
        accumulator = foldFunction(data, accumulator);
    });
    return accumulator;
}

template <typename Data>
void PostOrderTraversableContainer<Data>::Traverse(TraverseFun traverseFunction) const
{
    PostOrderTraverse(traverseFunction);
}
/* ************************************************************************** */

}
