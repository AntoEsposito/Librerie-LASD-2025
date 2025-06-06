#include <iostream>

/* ************************************************************************** */

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/linear.hpp"

#include "../zlasdtest/vector/vector.hpp"

#include "../zlasdtest/heap/heap.hpp"

#include "../heap/heap.hpp"
#include "../heap/vec/heapvec.hpp"

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

namespace mylasdtest {

void TestHeapInt(uint & testnum, uint & testerr) 
{
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of my Heap<int> Test:" << endl;
    try 
    {
        lasd::HeapVec<int> emptyHeap;
        Empty(loctestnum, loctesterr, emptyHeap, true);
        Size(loctestnum, loctesterr, emptyHeap, true, 0);
        
        emptyHeap.Sort();
        emptyHeap.Heapify();

        lasd::Vector<int> singleVec(1);
        SetAt(loctestnum, loctesterr, singleVec, true, 0, 42);
        lasd::HeapVec<int> singleHeap(singleVec);
        
        Size(loctestnum, loctesterr, singleHeap, true, 1);
        GetAt(loctestnum, loctesterr, singleHeap, true, 0, 42);
        
        singleHeap.Sort();
        GetAt(loctestnum, loctesterr, singleHeap, true, 0, 42);

        lasd::Vector<int> twoVec(2);
        SetAt(loctestnum, loctesterr, twoVec, true, 0, 5);
        SetAt(loctestnum, loctesterr, twoVec, true, 1, 10);
        lasd::HeapVec<int> twoHeap(twoVec);
        
        GetAt(loctestnum, loctesterr, twoHeap, true, 0, 10);
        GetAt(loctestnum, loctesterr, twoHeap, true, 1, 5);

        lasd::Vector<int> sortedVec(10);
        for(int i = 0; i < 10; i++) {SetAt(loctestnum, loctesterr, sortedVec, true, i, i + 1);}
        lasd::HeapVec<int> sortedHeap(sortedVec);

        lasd::Vector<int> reverseVec(10);
        for(int i = 0; i < 10; i++) {SetAt(loctestnum, loctesterr, reverseVec, true, i, 10 - i);}
        lasd::HeapVec<int> reverseHeap(reverseVec);

        lasd::Vector<int> negVec(6);
        SetAt(loctestnum, loctesterr, negVec, true, 0, -10);
        SetAt(loctestnum, loctesterr, negVec, true, 1, -5);
        SetAt(loctestnum, loctesterr, negVec, true, 2, -1);
        SetAt(loctestnum, loctesterr, negVec, true, 3, -20);
        SetAt(loctestnum, loctesterr, negVec, true, 4, -3);
        SetAt(loctestnum, loctesterr, negVec, true, 5, -15);
        
        lasd::HeapVec<int> negHeap(negVec);
        GetAt(loctestnum, loctesterr, negHeap, true, 0, -1);

        lasd::Vector<int> mixedVec(7);
        SetAt(loctestnum, loctesterr, mixedVec, true, 0, -5);
        SetAt(loctestnum, loctesterr, mixedVec, true, 1, 10);
        SetAt(loctestnum, loctesterr, mixedVec, true, 2, -2);
        SetAt(loctestnum, loctesterr, mixedVec, true, 3, 0);
        SetAt(loctestnum, loctesterr, mixedVec, true, 4, 15);
        SetAt(loctestnum, loctesterr, mixedVec, true, 5, -10);
        SetAt(loctestnum, loctesterr, mixedVec, true, 6, 7);
        
        lasd::HeapVec<int> mixedHeap(mixedVec);
        GetAt(loctestnum, loctesterr, mixedHeap, true, 0, 15);

        lasd::Vector<int> largeVec(50);
        for(int i = 0; i < 50; i++) {SetAt(loctestnum, loctesterr, largeVec, true, i, i * 10);}
        
        lasd::HeapVec<int> largeHeap(largeVec);
        Size(loctestnum, loctesterr, largeHeap, true, 50);
        GetAt(loctestnum, loctesterr, largeHeap, true, 0, 490);
        
        largeHeap.Sort();
        Size(loctestnum, loctesterr, largeHeap, true, 50);

        lasd::HeapVec<int> smallHeap;
        lasd::Vector<int> smallVec(3);
        SetAt(loctestnum, loctesterr, smallVec, true, 0, 100);
        SetAt(loctestnum, loctesterr, smallVec, true, 1, 200);
        SetAt(loctestnum, loctesterr, smallVec, true, 2, 300);
        
        lasd::HeapVec<int> smallHeap2(smallVec);
        
        largeHeap = smallHeap2;
        Size(loctestnum, loctesterr, largeHeap, true, 3);
        EqualLinear(loctestnum, loctesterr, largeHeap, smallHeap2, true);
        
        lasd::HeapVec<int> emptyHeap1;
        lasd::HeapVec<int> emptyHeap2;
        
        emptyHeap1 = std::move(emptyHeap2);
        Empty(loctestnum, loctesterr, emptyHeap1, true);
        Empty(loctestnum, loctesterr, emptyHeap2, true);

        EqualLinear(loctestnum, loctesterr, smallHeap2, mixedHeap, false);
        
        TraversePreOrder(loctestnum, loctesterr, emptyHeap, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, emptyHeap, true, &TraversePrint<int>);
        
        FoldPreOrder(loctestnum, loctesterr, emptyHeap, true, &FoldAdd<int>, 0, 0);
        FoldPostOrder(loctestnum, loctesterr, emptyHeap, true, &FoldAdd<int>, 0, 0);

        MapPreOrder(loctestnum, loctesterr, smallHeap2, true, &MapDouble<int>);
        SetAt(loctestnum, loctesterr, smallHeap2, true, 0, 1);
        IsHeap(loctestnum, loctesterr, smallHeap2, false);
        
        smallHeap2.Heapify();
        IsHeap(loctestnum, loctesterr, smallHeap2, true);

    } catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error!" << endl;
    }
    cout << "End of my Heap<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void TestHeapDouble(uint & testnum, uint & testerr) 
{
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of my Heap<double> Test:" << endl;
    try 
    {
        lasd::Vector<double> vec(14);
        SetAt(loctestnum, loctesterr, vec, true, 0, 4.5);
        SetAt(loctestnum, loctesterr, vec, true, 1, 3.25);
        SetAt(loctestnum, loctesterr, vec, true, 2, 1.125);
        SetAt(loctestnum, loctesterr, vec, true, 3, 0.0);
        SetAt(loctestnum, loctesterr, vec, true, 4, 2.25);
        SetAt(loctestnum, loctesterr, vec, true, 5, 5.5);
        SetAt(loctestnum, loctesterr, vec, true, 6, 0.0);
        SetAt(loctestnum, loctesterr, vec, true, 7, 8.25);
        SetAt(loctestnum, loctesterr, vec, true, 8, 10.5);
        SetAt(loctestnum, loctesterr, vec, true, 9, 11.5);
        SetAt(loctestnum, loctesterr, vec, true, 10, 7.25);
        SetAt(loctestnum, loctesterr, vec, true, 11, 3.125);
        SetAt(loctestnum, loctesterr, vec, true, 12, 9.5);
        SetAt(loctestnum, loctesterr, vec, true, 13, 6.25);

        lasd::HeapVec<double> heap1(vec);

        Traverse(loctestnum, loctesterr, heap1, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, heap1, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, heap1, true, &TraversePrint<double>);

        IsHeap(loctestnum, loctesterr, heap1, true);

        lasd::HeapVec<double> emptyHeap;
        Empty(loctestnum, loctesterr, emptyHeap, true);
        Size(loctestnum, loctesterr, emptyHeap, true, 0);
        IsHeap(loctestnum, loctesterr, emptyHeap, true);
        
        emptyHeap.Sort();
        emptyHeap.Heapify();
        IsHeap(loctestnum, loctesterr, emptyHeap, true);

        lasd::Vector<double> singleVec(1);
        SetAt(loctestnum, loctesterr, singleVec, true, 0, 3.14159265359);
        lasd::HeapVec<double> singleHeap(singleVec);
        
        IsHeap(loctestnum, loctesterr, singleHeap, true);
        Size(loctestnum, loctesterr, singleHeap, true, 1);
        GetAt(loctestnum, loctesterr, singleHeap, true, 0, 3.14159265359);

        lasd::Vector<double> smallVec(6);
        SetAt(loctestnum, loctesterr, smallVec, true, 0, 0.001);
        SetAt(loctestnum, loctesterr, smallVec, true, 1, 0.0001);
        SetAt(loctestnum, loctesterr, smallVec, true, 2, 0.00001);
        SetAt(loctestnum, loctesterr, smallVec, true, 3, 0.000001);
        SetAt(loctestnum, loctesterr, smallVec, true, 4, 0.0000001);
        SetAt(loctestnum, loctesterr, smallVec, true, 5, 0.00000001);
        
        lasd::HeapVec<double> smallHeap(smallVec);
        IsHeap(loctestnum, loctesterr, smallHeap, true);

        lasd::Vector<double> negVec(8);
        SetAt(loctestnum, loctesterr, negVec, true, 0, -10.5);
        SetAt(loctestnum, loctesterr, negVec, true, 1, -5.25);
        SetAt(loctestnum, loctesterr, negVec, true, 2, -1.125);
        SetAt(loctestnum, loctesterr, negVec, true, 3, -20.75);
        SetAt(loctestnum, loctesterr, negVec, true, 4, -3.333);
        SetAt(loctestnum, loctesterr, negVec, true, 5, -15.625);
        SetAt(loctestnum, loctesterr, negVec, true, 6, -0.5);
        SetAt(loctestnum, loctesterr, negVec, true, 7, -25.0);
        
        lasd::HeapVec<double> negHeap(negVec);
        IsHeap(loctestnum, loctesterr, negHeap, true);
        
        GetAt(loctestnum, loctesterr, negHeap, true, 0, -0.5);

        lasd::Vector<double> mixedVec(9);
        SetAt(loctestnum, loctesterr, mixedVec, true, 0, -5.5);
        SetAt(loctestnum, loctesterr, mixedVec, true, 1, 10.25);
        SetAt(loctestnum, loctesterr, mixedVec, true, 2, -2.125);
        SetAt(loctestnum, loctesterr, mixedVec, true, 3, 0.0);
        SetAt(loctestnum, loctesterr, mixedVec, true, 4, 15.75);
        SetAt(loctestnum, loctesterr, mixedVec, true, 5, -10.875);
        SetAt(loctestnum, loctesterr, mixedVec, true, 6, 7.5);
        SetAt(loctestnum, loctesterr, mixedVec, true, 7, -0.25);
        SetAt(loctestnum, loctesterr, mixedVec, true, 8, 3.14159265359);
        
        lasd::HeapVec<double> mixedHeap(mixedVec);
        IsHeap(loctestnum, loctesterr, mixedHeap, true);
        GetAt(loctestnum, loctesterr, mixedHeap, true, 0, 15.75);

        lasd::Vector<double> dupVec(10);
        SetAt(loctestnum, loctesterr, dupVec, true, 0, 5.5);
        SetAt(loctestnum, loctesterr, dupVec, true, 1, 5.5);
        SetAt(loctestnum, loctesterr, dupVec, true, 2, 3.25);
        SetAt(loctestnum, loctesterr, dupVec, true, 3, 3.25);
        SetAt(loctestnum, loctesterr, dupVec, true, 4, 7.75);
        SetAt(loctestnum, loctesterr, dupVec, true, 5, 7.75);
        SetAt(loctestnum, loctesterr, dupVec, true, 6, 1.125);
        SetAt(loctestnum, loctesterr, dupVec, true, 7, 1.125);
        SetAt(loctestnum, loctesterr, dupVec, true, 8, 0.0);
        SetAt(loctestnum, loctesterr, dupVec, true, 9, 0.0);
        
        lasd::HeapVec<double> dupHeap(dupVec);
        IsHeap(loctestnum, loctesterr, dupHeap, true);
        
        dupHeap.Sort();
        IsHeap(loctestnum, loctesterr, dupHeap, false);
        Traverse(loctestnum, loctesterr, dupHeap, true, &TraversePrint<double>);

        lasd::Vector<double> largeVec(7);
        SetAt(loctestnum, loctesterr, largeVec, true, 0, 1e15);
        SetAt(loctestnum, loctesterr, largeVec, true, 1, 5e14);
        SetAt(loctestnum, loctesterr, largeVec, true, 2, 2e15);
        SetAt(loctestnum, loctesterr, largeVec, true, 3, 1.5e15);
        SetAt(loctestnum, loctesterr, largeVec, true, 4, 3e14);
        SetAt(loctestnum, loctesterr, largeVec, true, 5, 8e14);
        SetAt(loctestnum, loctesterr, largeVec, true, 6, 1.2e15);
        
        lasd::HeapVec<double> largeHeap(largeVec);
        IsHeap(loctestnum, loctesterr, largeHeap, true);

        lasd::Vector<double> fracVec(8);
        SetAt(loctestnum, loctesterr, fracVec, true, 0, 1.0/3.0);
        SetAt(loctestnum, loctesterr, fracVec, true, 1, 2.0/3.0);
        SetAt(loctestnum, loctesterr, fracVec, true, 2, 1.0/7.0);
        SetAt(loctestnum, loctesterr, fracVec, true, 3, 3.0/7.0);
        SetAt(loctestnum, loctesterr, fracVec, true, 4, 5.0/7.0);
        SetAt(loctestnum, loctesterr, fracVec, true, 5, 1.0/9.0);
        SetAt(loctestnum, loctesterr, fracVec, true, 6, 4.0/9.0);
        SetAt(loctestnum, loctesterr, fracVec, true, 7, 7.0/9.0);
        
        lasd::HeapVec<double> fracHeap(fracVec);
        IsHeap(loctestnum, loctesterr, fracHeap, true);

        lasd::HeapVec<double> heap2(heap1);
        EqualLinear(loctestnum, loctesterr, heap1, heap2, true);
        
        lasd::HeapVec<double> heap3(std::move(heap2));
        EqualLinear(loctestnum, loctesterr, heap1, heap3, true);
        Empty(loctestnum, loctesterr, heap2, true);

        heap2 = heap3;
        EqualLinear(loctestnum, loctesterr, heap2, heap3, true);
        
        heap1 = std::move(heap3);
        EqualLinear(loctestnum, loctesterr, heap2, heap3, true);
        Empty(loctestnum, loctesterr, heap3, false);

        heap1.Sort();
        IsHeap(loctestnum, loctesterr, heap1, false);
        
        heap1.Heapify();
        IsHeap(loctestnum, loctesterr, heap1, true);

        FoldPreOrder(loctestnum, loctesterr, emptyHeap, true, &FoldAdd<double>, 0.0, 0.0);
        FoldPostOrder(loctestnum, loctesterr, emptyHeap, true, &FoldAdd<double>, 0.0, 0.0);
        
        FoldPreOrder(loctestnum, loctesterr, singleHeap, true, &FoldAdd<double>, 0.0, 3.14159265359);
        FoldPostOrder(loctestnum, loctesterr, singleHeap, true, &FoldAdd<double>, 0.0, 3.14159265359);

        MapPreOrder(loctestnum, loctesterr, mixedHeap, true, &MapDouble<double>);
        IsHeap(loctestnum, loctesterr, mixedHeap, true);
        
        mixedHeap.Heapify();
        IsHeap(loctestnum, loctesterr, mixedHeap, true);

        TraversePreOrder(loctestnum, loctesterr, emptyHeap, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, emptyHeap, true, &TraversePrint<double>);
        
        TraversePreOrder(loctestnum, loctesterr, negHeap, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, negHeap, true, &TraversePrint<double>);

        lasd::Vector<double> twoVec(2);
        SetAt(loctestnum, loctesterr, twoVec, true, 0, 2.5);
        SetAt(loctestnum, loctesterr, twoVec, true, 1, 7.5);
        lasd::HeapVec<double> twoHeap(twoVec);
        
        IsHeap(loctestnum, loctesterr, twoHeap, true);
        GetAt(loctestnum, loctesterr, twoHeap, true, 0, 7.5);

        lasd::Vector<double> sciVec(5);
        SetAt(loctestnum, loctesterr, sciVec, true, 0, 1.23e-10);
        SetAt(loctestnum, loctesterr, sciVec, true, 1, 4.56e-9);
        SetAt(loctestnum, loctesterr, sciVec, true, 2, 7.89e-8);
        SetAt(loctestnum, loctesterr, sciVec, true, 3, 1.11e10);
        SetAt(loctestnum, loctesterr, sciVec, true, 4, 2.22e11);
        
        lasd::HeapVec<double> sciHeap(sciVec);
        IsHeap(loctestnum, loctesterr, sciHeap, true);

        lasd::Vector<double> bigVec(100);
        for(int i = 0; i < 100; i++) {SetAt(loctestnum, loctesterr, bigVec, true, i, (i * 10) + 0.1);}
        
        lasd::HeapVec<double> bigHeap(bigVec);
        IsHeap(loctestnum, loctesterr, bigHeap, true);
        Size(loctestnum, loctesterr, bigHeap, true, 100);
        GetAt(loctestnum, loctesterr, bigHeap, true, 0, 990.1);
        
        bigHeap.Sort();
        GetAt(loctestnum, loctesterr, bigHeap, true, 0, 0.1);
        Size(loctestnum, loctesterr, bigHeap, true, 100);

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error!" << endl;
    }
    cout << "End of my Heap<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void TestHeapString(uint & testnum, uint & testerr)
{
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of my Heap<string> Test:" << endl;
    try 
    {
        lasd::Vector<string> vec(14);
        SetAt(loctestnum, loctesterr, vec, true, 0, string("E"));
        SetAt(loctestnum, loctesterr, vec, true, 1, string("D"));
        SetAt(loctestnum, loctesterr, vec, true, 2, string("B"));
        SetAt(loctestnum, loctesterr, vec, true, 3, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 4, string("C"));
        SetAt(loctestnum, loctesterr, vec, true, 5, string("F"));
        SetAt(loctestnum, loctesterr, vec, true, 6, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 7, string("I"));
        SetAt(loctestnum, loctesterr, vec, true, 8, string("K"));
        SetAt(loctestnum, loctesterr, vec, true, 9, string("L"));
        SetAt(loctestnum, loctesterr, vec, true, 10, string("H"));
        SetAt(loctestnum, loctesterr, vec, true, 11, string("D"));
        SetAt(loctestnum, loctesterr, vec, true, 12, string("J"));
        SetAt(loctestnum, loctesterr, vec, true, 13, string("G"));

        lasd::HeapVec<string> heap1(vec);

        Traverse(loctestnum, loctesterr, heap1, true, &TraversePrint<string>);
        TraversePreOrder(loctestnum, loctesterr, heap1, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, heap1, true, &TraversePrint<string>);

        IsHeap(loctestnum, loctesterr, heap1, true);

        lasd::HeapVec<string> emptyHeap;
        Empty(loctestnum, loctesterr, emptyHeap, true);
        Size(loctestnum, loctesterr, emptyHeap, true, 0);
        IsHeap(loctestnum, loctesterr, emptyHeap, true);
        
        emptyHeap.Sort();
        emptyHeap.Heapify();
        IsHeap(loctestnum, loctesterr, emptyHeap, true);

        lasd::Vector<string> singleVec(1);
        SetAt(loctestnum, loctesterr, singleVec, true, 0, string("Hello"));
        lasd::HeapVec<string> singleHeap(singleVec);
        
        IsHeap(loctestnum, loctesterr, singleHeap, true);
        Size(loctestnum, loctesterr, singleHeap, true, 1);
        GetAt(loctestnum, loctesterr, singleHeap, true, 0, string("Hello"));

        lasd::Vector<string> emptyStrVec(8);
        SetAt(loctestnum, loctesterr, emptyStrVec, true, 0, string(""));
        SetAt(loctestnum, loctesterr, emptyStrVec, true, 1, string(" "));
        SetAt(loctestnum, loctesterr, emptyStrVec, true, 2, string("  "));
        SetAt(loctestnum, loctesterr, emptyStrVec, true, 3, string("\t")); // Tab character
        SetAt(loctestnum, loctesterr, emptyStrVec, true, 4, string("\n")); // Newline character
        SetAt(loctestnum, loctesterr, emptyStrVec, true, 5, string("a"));
        SetAt(loctestnum, loctesterr, emptyStrVec, true, 6, string("A"));
        SetAt(loctestnum, loctesterr, emptyStrVec, true, 7, string("0"));
        
        lasd::HeapVec<string> emptyStrHeap(emptyStrVec);
        IsHeap(loctestnum, loctesterr, emptyStrHeap, true);

        lasd::Vector<string> numStrVec(10);
        SetAt(loctestnum, loctesterr, numStrVec, true, 0, string("1"));
        SetAt(loctestnum, loctesterr, numStrVec, true, 1, string("2"));
        SetAt(loctestnum, loctesterr, numStrVec, true, 2, string("10"));
        SetAt(loctestnum, loctesterr, numStrVec, true, 3, string("20"));
        SetAt(loctestnum, loctesterr, numStrVec, true, 4, string("100"));
        SetAt(loctestnum, loctesterr, numStrVec, true, 5, string("3"));
        SetAt(loctestnum, loctesterr, numStrVec, true, 6, string("30"));
        SetAt(loctestnum, loctesterr, numStrVec, true, 7, string("300"));
        SetAt(loctestnum, loctesterr, numStrVec, true, 8, string("9"));
        SetAt(loctestnum, loctesterr, numStrVec, true, 9, string("99"));
        
        lasd::HeapVec<string> numStrHeap(numStrVec);
        IsHeap(loctestnum, loctesterr, numStrHeap, true);
        GetAt(loctestnum, loctesterr, numStrHeap, true, 0, string("99"));

        lasd::Vector<string> specialVec(12);
        SetAt(loctestnum, loctesterr, specialVec, true, 0, string("!"));
        SetAt(loctestnum, loctesterr, specialVec, true, 1, string("@"));
        SetAt(loctestnum, loctesterr, specialVec, true, 2, string("#"));
        SetAt(loctestnum, loctesterr, specialVec, true, 3, string("$"));
        SetAt(loctestnum, loctesterr, specialVec, true, 4, string("%"));
        SetAt(loctestnum, loctesterr, specialVec, true, 5, string("^"));
        SetAt(loctestnum, loctesterr, specialVec, true, 6, string("&"));
        SetAt(loctestnum, loctesterr, specialVec, true, 7, string("*"));
        SetAt(loctestnum, loctesterr, specialVec, true, 8, string("("));
        SetAt(loctestnum, loctesterr, specialVec, true, 9, string(")"));
        SetAt(loctestnum, loctesterr, specialVec, true, 10, string("-"));
        SetAt(loctestnum, loctesterr, specialVec, true, 11, string("_"));
        
        lasd::HeapVec<string> specialHeap(specialVec);
        IsHeap(loctestnum, loctesterr, specialHeap, true);

        lasd::Vector<string> caseVec(8);
        SetAt(loctestnum, loctesterr, caseVec, true, 0, string("apple"));
        SetAt(loctestnum, loctesterr, caseVec, true, 1, string("Apple"));
        SetAt(loctestnum, loctesterr, caseVec, true, 2, string("APPLE"));
        SetAt(loctestnum, loctesterr, caseVec, true, 3, string("banana"));
        SetAt(loctestnum, loctesterr, caseVec, true, 4, string("Banana"));
        SetAt(loctestnum, loctesterr, caseVec, true, 5, string("BANANA"));
        SetAt(loctestnum, loctesterr, caseVec, true, 6, string("cherry"));
        SetAt(loctestnum, loctesterr, caseVec, true, 7, string("Cherry"));
        
        lasd::HeapVec<string> caseHeap(caseVec);
        IsHeap(loctestnum, loctesterr, caseHeap, true);

        lasd::Vector<string> longVec(6);
        SetAt(loctestnum, loctesterr, longVec, true, 0, string("S"));
        SetAt(loctestnum, loctesterr, longVec, true, 1, string("AnotherLongStringForTestingPurposes"));
        SetAt(loctestnum, loctesterr, longVec, true, 2, string("ShortString"));
        SetAt(loctestnum, loctesterr, longVec, true, 3, string("MediumLengthString"));
        SetAt(loctestnum, loctesterr, longVec, true, 4, string("VeryVeryVeryVeryVeryVeryVeryVeryVeryVeryVeryVeryLongString"));
        SetAt(loctestnum, loctesterr, longVec, true, 5, string("X"));
        
        lasd::HeapVec<string> longHeap(longVec);
        IsHeap(loctestnum, loctesterr, longHeap, true);

        lasd::Vector<string> dupVec(10);
        SetAt(loctestnum, loctesterr, dupVec, true, 0, string("duplicate"));
        SetAt(loctestnum, loctesterr, dupVec, true, 1, string("duplicate"));
        SetAt(loctestnum, loctesterr, dupVec, true, 2, string("duplicate"));
        SetAt(loctestnum, loctesterr, dupVec, true, 3, string("other"));
        SetAt(loctestnum, loctesterr, dupVec, true, 4, string("other"));
        SetAt(loctestnum, loctesterr, dupVec, true, 5, string("another"));
        SetAt(loctestnum, loctesterr, dupVec, true, 6, string("another"));
        SetAt(loctestnum, loctesterr, dupVec, true, 7, string("unique"));
        SetAt(loctestnum, loctesterr, dupVec, true, 8, string("single"));
        SetAt(loctestnum, loctesterr, dupVec, true, 9, string("test"));
        
        lasd::HeapVec<string> dupHeap(dupVec);
        IsHeap(loctestnum, loctesterr, dupHeap, true);
        dupHeap.Sort();
        IsHeap(loctestnum, loctesterr, dupHeap, false);
        Traverse(loctestnum, loctesterr, dupHeap, true, &TraversePrint<string>);

        lasd::HeapVec<string> heap2(heap1);
        EqualLinear(loctestnum, loctesterr, heap1, heap2, true);
        
        lasd::HeapVec<string> heap3(std::move(heap2));
        EqualLinear(loctestnum, loctesterr, heap1, heap3, true);
        Empty(loctestnum, loctesterr, heap2, true);

        heap2 = heap3;
        EqualLinear(loctestnum, loctesterr, heap2, heap3, true);
        
        heap1 = std::move(heap3);
        EqualLinear(loctestnum, loctesterr, heap2, heap3, true);
        Empty(loctestnum, loctesterr, heap3, false);

        MapPreOrder(loctestnum, loctesterr, heap1, true, [](string & str) {MapStringAppend(str, string("_suffix"));});
        IsHeap(loctestnum, loctesterr, heap1, true);
        heap1.Sort();
        IsHeap(loctestnum, loctesterr, heap1, false);

        lasd::Vector<string> twoVec(2);
        SetAt(loctestnum, loctesterr, twoVec, true, 0, string("beta"));
        SetAt(loctestnum, loctesterr, twoVec, true, 1, string("alpha"));
        lasd::HeapVec<string> twoHeap(twoVec);
        
        IsHeap(loctestnum, loctesterr, twoHeap, true);
        GetAt(loctestnum, loctesterr, twoHeap, true, 0, string("beta"));

        lasd::Vector<string> prefixVec(8);
        SetAt(loctestnum, loctesterr, prefixVec, true, 0, string("test"));
        SetAt(loctestnum, loctesterr, prefixVec, true, 1, string("testing"));
        SetAt(loctestnum, loctesterr, prefixVec, true, 2, string("tester"));
        SetAt(loctestnum, loctesterr, prefixVec, true, 3, string("tested"));
        SetAt(loctestnum, loctesterr, prefixVec, true, 4, string("te"));
        SetAt(loctestnum, loctesterr, prefixVec, true, 5, string("t"));
        SetAt(loctestnum, loctesterr, prefixVec, true, 6, string("tests"));
        SetAt(loctestnum, loctesterr, prefixVec, true, 7, string("testable"));
        
        lasd::HeapVec<string> prefixHeap(prefixVec);
        IsHeap(loctestnum, loctesterr, prefixHeap, true);

        FoldPreOrder(loctestnum, loctesterr, emptyHeap, true, &FoldStringConcatenate, string("START"), string("START"));
        FoldPostOrder(loctestnum, loctesterr, emptyHeap, true, &FoldStringConcatenate, string("START"), string("START"));
        
        FoldPreOrder(loctestnum, loctesterr, singleHeap, true, &FoldStringConcatenate, string(""), string("Hello"));
        FoldPostOrder(loctestnum, loctesterr, singleHeap, true, &FoldStringConcatenate, string(""), string("Hello"));

        lasd::Vector<string> largeVec(100);
        for(int i = 0; i < 100; i++) 
        {
            string randStr = "String" + to_string(rand() % 1000);
            SetAt(loctestnum, loctesterr, largeVec, true, i, randStr);
        }
        
        lasd::HeapVec<string> largeHeap(largeVec);
        IsHeap(loctestnum, loctesterr, largeHeap, true);
        Size(loctestnum, loctesterr, largeHeap, true, 100);
        largeHeap.Sort();
        IsHeap(loctestnum, loctesterr, largeHeap, false);

        lasd::HeapVec<string> emptyHeap1;
        lasd::HeapVec<string> emptyHeap2;
        
        emptyHeap1 = std::move(emptyHeap2);
        Empty(loctestnum, loctesterr, emptyHeap1, true);
        Empty(loctestnum, loctesterr, emptyHeap2, true);

        TraversePreOrder(loctestnum, loctesterr, emptyHeap, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, emptyHeap, true, &TraversePrint<string>);
        
        TraversePreOrder(loctestnum, loctesterr, singleHeap, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, singleHeap, true, &TraversePrint<string>);
        
        dupHeap.Heapify();
        IsHeap(loctestnum, loctesterr, dupHeap, true);

        EqualLinear(loctestnum, loctesterr, singleHeap, dupHeap, false);
        EqualLinear(loctestnum, loctesterr, emptyHeap, singleHeap, false);
        
    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error!" << endl;
    }
    cout << "End of my Heap<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}


void MyFullTest2A(unsigned int & testnum, unsigned int & testerr) 
{
    uint loctestnum = 0, loctesterr = 0;
    TestHeapInt(loctestnum, loctesterr);
    TestHeapDouble(loctestnum, loctesterr);
    TestHeapString(loctestnum, loctesterr);

    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "My test for Heaps (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}
}