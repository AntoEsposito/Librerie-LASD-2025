
#include <stdexcept>
namespace lasd {

/* ************************************************************************** */

// DictionaryC methods

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &traversableC)
{
    bool allInserted = true;
    traversableC.Traverse([this, &allInserted] (const Data &data)
    {
        allInserted &= Insert(data);
    });
    return allInserted;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> &&mappableC)
{
    bool allInserted = true;
    mappableC.Map([this, &allInserted] (Data &data)
    {
        allInserted &= Insert(std::move(data));
    });
    return allInserted;
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> &traversableC)
{
    bool allRemoved = true;
    traversableC.Traverse([this, &allRemoved] (const Data &data)
    {
        allRemoved &= Remove(data);
    });
    return allRemoved;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> &traversableC)
{
    bool someInserted = false;
    traversableC.Traverse([this, &someInserted] (const Data &data)
    {
        someInserted |= Insert(data);
    });
    return someInserted;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> &&mappableC)
{
    bool someInserted = false;
    mappableC.Map([this, &someInserted] (Data &data)
    {
        someInserted |= Remove(std::move(data));
    });
    return someInserted;
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> &traversableC)
{
    bool someRemoved = false;
    traversableC.Traverse([this, &someRemoved] (const Data &data)
    {
        someRemoved |= Remove(data);
    });
    return someRemoved;
}

/* ************************************************************************** */

}
