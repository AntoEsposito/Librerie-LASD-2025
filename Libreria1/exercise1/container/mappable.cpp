
namespace lasd {

/* ************************************************************************** */

// PreOrderMappableC methods

template <typename Data>
void PreOrderMappableContainer<Data>::Map(MapFun mapFunction)
{
    PreOrderMap(mapFunction);
}


// PostOrderMappableC methods

template <typename Data>
void PostOrderMappableContainer<Data>::Map(MapFun mapFunction)
{
    PostOrderMap(mapFunction);
}

/* ************************************************************************** */

}
