#include <iostream>

/* ************************************************************************** */

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/linear.hpp"

#include "../zlasdtest/vector/vector.hpp"

#include "../zlasdtest/pq/pq.hpp"

#include "../pq/pq.hpp"
#include "../pq/heap/pqheap.hpp"

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

namespace mylasdtest {

void TestPQInt(uint & testnum, uint & testerr) 
{
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of PQ<int> Test:" << endl;
    
    try {
        
        lasd::PQHeap<int> pq_empty;
        Empty(loctestnum, loctesterr, pq_empty, true);
        Size(loctestnum, loctesterr, pq_empty, true, 0);
        
        lasd::Vector<int> vec1(10);
        SetAt(loctestnum, loctesterr, vec1, true, 0, -15);
        SetAt(loctestnum, loctesterr, vec1, true, 1, 42);
        SetAt(loctestnum, loctesterr, vec1, true, 2, 0);
        SetAt(loctestnum, loctesterr, vec1, true, 3, -3);
        SetAt(loctestnum, loctesterr, vec1, true, 4, 17);
        SetAt(loctestnum, loctesterr, vec1, true, 5, 99);
        SetAt(loctestnum, loctesterr, vec1, true, 6, -42);
        SetAt(loctestnum, loctesterr, vec1, true, 7, 1);
        SetAt(loctestnum, loctesterr, vec1, true, 8, 88);
        SetAt(loctestnum, loctesterr, vec1, true, 9, -99);
        
        lasd::PQHeap<int> pq(vec1);
        Empty(loctestnum, loctesterr, pq, false);
        Size(loctestnum, loctesterr, pq, true, 10);
        
        Tip(loctestnum, loctesterr, pq, true, 99);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        
        TipNRemove(loctestnum, loctesterr, pq, true, 99);
        TipNRemove(loctestnum, loctesterr, pq, true, 88);
        Size(loctestnum, loctesterr, pq, true, 8);
        
        Insert(loctestnum, loctesterr, pq, 100);
        Tip(loctestnum, loctesterr, pq, true, 100);
        Insert(loctestnum, loctesterr, pq, -100);
        Size(loctestnum, loctesterr, pq, true, 10);
        
        Exists(loctestnum, loctesterr, pq, true, 100);
        Exists(loctestnum, loctesterr, pq, false, 999);
        GetAt(loctestnum, loctesterr, pq, true, 0, 100);
        GetAt(loctestnum, loctesterr, pq, false, 10, 0);
        
        Change(loctestnum, loctesterr, pq, 0, 10);
        Tip(loctestnum, loctesterr, pq, true, 42);
        
        uint size = pq.Size();
        Change(loctestnum, loctesterr, pq, size-1, 200);
        Tip(loctestnum, loctesterr, pq, true, 200);
        
        lasd::PQHeap<int> pq_copy(pq);
        EqualLinear(loctestnum, loctesterr, pq, pq_copy, true);
        
        lasd::PQHeap<int> pq_moved(std::move(pq_copy));
        Empty(loctestnum, loctesterr, pq_copy, true);
        Size(loctestnum, loctesterr, pq_moved, true, 10);
        
        lasd::PQHeap<int> empty_pq;
        RemoveTip(loctestnum, loctesterr, empty_pq, false);
        Tip(loctestnum, loctesterr, empty_pq, false, 0);
        
        Insert(loctestnum, loctesterr, empty_pq, 42);
        TipNRemove(loctestnum, loctesterr, empty_pq, true, 42);
        Empty(loctestnum, loctesterr, empty_pq, true);
        
        lasd::PQHeap<int> dup_pq;
        for(int i = 0; i < 5; i++) {Insert(loctestnum, loctesterr, dup_pq, 5);}
        Size(loctestnum, loctesterr, dup_pq, true, 5);
        
        for(int i = 0; i < 5; i++) {TipNRemove(loctestnum, loctesterr, dup_pq, true, 5);}
        Empty(loctestnum, loctesterr, dup_pq, true);
        
        lasd::PQHeap<int> order_pq;
        lasd::Vector<int> insertion_order(7);
        SetAt(loctestnum, loctesterr, insertion_order, true, 0, 10);
        SetAt(loctestnum, loctesterr, insertion_order, true, 1, 30);
        SetAt(loctestnum, loctesterr, insertion_order, true, 2, 20);
        SetAt(loctestnum, loctesterr, insertion_order, true, 3, 50);
        SetAt(loctestnum, loctesterr, insertion_order, true, 4, 40);
        SetAt(loctestnum, loctesterr, insertion_order, true, 5, 60);
        SetAt(loctestnum, loctesterr, insertion_order, true, 6, 15);
        
        for(uint i = 0; i < insertion_order.Size(); i++) {Insert(loctestnum, loctesterr, order_pq, insertion_order[i]);}
        
        TipNRemove(loctestnum, loctesterr, order_pq, true, 60);
        TipNRemove(loctestnum, loctesterr, order_pq, true, 50);
        TipNRemove(loctestnum, loctesterr, order_pq, true, 40);
        TipNRemove(loctestnum, loctesterr, order_pq, true, 30);
        TipNRemove(loctestnum, loctesterr, order_pq, true, 20);
        TipNRemove(loctestnum, loctesterr, order_pq, true, 15);
        TipNRemove(loctestnum, loctesterr, order_pq, true, 10);
        Empty(loctestnum, loctesterr, order_pq, true);
        
        lasd::PQHeap<int> stress_pq;
        for(int i = 1; i <= 20; i++) {Insert(loctestnum, loctesterr, stress_pq, i * 3);}
        Size(loctestnum, loctesterr, stress_pq, true, 20);
        Tip(loctestnum, loctesterr, stress_pq, true, 60);
        
        for(int i = 0; i < 10; i++) {RemoveTip(loctestnum, loctesterr, stress_pq, true);}
        Size(loctestnum, loctesterr, stress_pq, true, 10);
        Tip(loctestnum, loctesterr, stress_pq, true, 30);
        
        lasd::PQHeap<int> boundary_pq;
        Insert(loctestnum, loctesterr, boundary_pq, -100);
        Insert(loctestnum, loctesterr, boundary_pq, 0);
        Insert(loctestnum, loctesterr, boundary_pq, -1);
        Insert(loctestnum, loctesterr, boundary_pq, 1);
        Insert(loctestnum, loctesterr, boundary_pq, -50);
        
        Tip(loctestnum, loctesterr, boundary_pq, true, 1);
        TipNRemove(loctestnum, loctesterr, boundary_pq, true, 1);
        Tip(loctestnum, loctesterr, boundary_pq, true, 0);
        TipNRemove(loctestnum, loctesterr, boundary_pq, true, 0);
        Tip(loctestnum, loctesterr, boundary_pq, true, -1);
        TipNRemove(loctestnum, loctesterr, boundary_pq, true, -1);
        
        lasd::PQHeap<int> prop_pq;
        Insert(loctestnum, loctesterr, prop_pq, 100);
        Insert(loctestnum, loctesterr, prop_pq, 50);
        Insert(loctestnum, loctesterr, prop_pq, 75);
        Insert(loctestnum, loctesterr, prop_pq, 25);
        Insert(loctestnum, loctesterr, prop_pq, 30);
        
        Change(loctestnum, loctesterr, prop_pq, 3, 150);
        Tip(loctestnum, loctesterr, prop_pq, true, 150);
        
        Change(loctestnum, loctesterr, prop_pq, 0, 10);
        Tip(loctestnum, loctesterr, prop_pq, true, 100);
        
        lasd::PQHeap<int> alt_pq;
        for(int i = 0; i <= 15; i++)
        {
            Insert(loctestnum, loctesterr, alt_pq, i * 2);
            if(i % 3 == 0) {RemoveTip(loctestnum, loctesterr, alt_pq, true);}
        }
        
        Size(loctestnum, loctesterr, alt_pq, true, 10);
        Tip(loctestnum, loctesterr, alt_pq, true, 28);
        
        lasd::PQHeap<int> rebuild_pq;
        for(int i = 1; i <= 5; i++) {Insert(loctestnum, loctesterr, rebuild_pq, i * 10);}
        
        while(!rebuild_pq.Empty()) {RemoveTip(loctestnum, loctesterr, rebuild_pq, true);}
        Empty(loctestnum, loctesterr, rebuild_pq, true);
        
        for(int i = 100; i >= 90; i--) {Insert(loctestnum, loctesterr, rebuild_pq, i);}
        Size(loctestnum, loctesterr, rebuild_pq, true, 11);
        Tip(loctestnum, loctesterr, rebuild_pq, true, 100);
    }
    catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    
    cout << "End of PQ<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}


void TestPQDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of PQ<double> Test:" << endl;
    
    try {
        lasd::PQHeap<double> pq_empty;
        Empty(loctestnum, loctesterr, pq_empty, true);
        Size(loctestnum, loctesterr, pq_empty, true, 0);
        
        lasd::Vector<double> vec1(15);
        SetAt(loctestnum, loctesterr, vec1, true, 0, -15.75);
        SetAt(loctestnum, loctesterr, vec1, true, 1, 42.5);
        SetAt(loctestnum, loctesterr, vec1, true, 2, 0.0);
        SetAt(loctestnum, loctesterr, vec1, true, 3, -3.14159);
        SetAt(loctestnum, loctesterr, vec1, true, 4, 17.89);
        SetAt(loctestnum, loctesterr, vec1, true, 5, 99.999);
        SetAt(loctestnum, loctesterr, vec1, true, 6, -42.001);
        SetAt(loctestnum, loctesterr, vec1, true, 7, 1.001);
        SetAt(loctestnum, loctesterr, vec1, true, 8, 88.88);
        SetAt(loctestnum, loctesterr, vec1, true, 9, -1.5);
        SetAt(loctestnum, loctesterr, vec1, true, 10, 33.33);
        SetAt(loctestnum, loctesterr, vec1, true, 11, 0.00001);
        SetAt(loctestnum, loctesterr, vec1, true, 12, 55.123);
        SetAt(loctestnum, loctesterr, vec1, true, 13, -88.456);
        SetAt(loctestnum, loctesterr, vec1, true, 14, 77.777);
        
        lasd::PQHeap<double> pq(vec1);
        Empty(loctestnum, loctesterr, pq, false);
        Size(loctestnum, loctesterr, pq, true, 15);
        
        Tip(loctestnum, loctesterr, pq, true, 99.999);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        
        TipNRemove(loctestnum, loctesterr, pq, true, 99.999);
        TipNRemove(loctestnum, loctesterr, pq, true, 88.88);
        Size(loctestnum, loctesterr, pq, true, 13);
        
        Insert(loctestnum, loctesterr, pq, 150.5);
        Tip(loctestnum, loctesterr, pq, true, 150.5);
        Insert(loctestnum, loctesterr, pq, -200.25);
        Insert(loctestnum, loctesterr, pq, 75.75);
        Size(loctestnum, loctesterr, pq, true, 16);
        
        Exists(loctestnum, loctesterr, pq, true, 150.5);
        Exists(loctestnum, loctesterr, pq, true, -200.25);
        Exists(loctestnum, loctesterr, pq, false, 999.999);
        
        GetAt(loctestnum, loctesterr, pq, true, 0, 150.5);
        GetAt(loctestnum, loctesterr, pq, false, 20, 0.0);
        
        Change(loctestnum, loctesterr, pq, 0, 10.5);
        Tip(loctestnum, loctesterr, pq, true, 77.777);
        
        uint size = pq.Size();
        Change(loctestnum, loctesterr, pq, size-1, 300.789);
        Tip(loctestnum, loctesterr, pq, true, 300.789);
        
        lasd::PQHeap<double> pq_copy(pq);
        EqualLinear(loctestnum, loctesterr, pq, pq_copy, true);
        
        lasd::PQHeap<double> pq_moved(std::move(pq_copy));
        Empty(loctestnum, loctesterr, pq_copy, true);
        Size(loctestnum, loctesterr, pq_moved, true, 16);
        
        lasd::PQHeap<double> empty_pq;
        RemoveTip(loctestnum, loctesterr, empty_pq, false);
        Tip(loctestnum, loctesterr, empty_pq, false, 0.0);
        
        Insert(loctestnum, loctesterr, empty_pq, 42.42);
        TipNRemove(loctestnum, loctesterr, empty_pq, true, 42.42);
        Empty(loctestnum, loctesterr, empty_pq, true);
        
        lasd::PQHeap<double> precision_pq;
        Insert(loctestnum, loctesterr, precision_pq, 1.0);
        Insert(loctestnum, loctesterr, precision_pq, 1.0000000001);
        Insert(loctestnum, loctesterr, precision_pq, 0.9999999999);
        
        Tip(loctestnum, loctesterr, precision_pq, true, 1.0000000001);
        
        lasd::PQHeap<double> dup_pq;
        for(int i = 0; i < 5; i++) {Insert(loctestnum, loctesterr, dup_pq, 5.5);}
        Size(loctestnum, loctesterr, dup_pq, true, 5);
        
        for(int i = 0; i < 5; i++) {TipNRemove(loctestnum, loctesterr, dup_pq, true, 5.5);}
        Empty(loctestnum, loctesterr, dup_pq, true);
        
        lasd::PQHeap<double> seq_pq;
        for(int i = 0; i < 10; i++) {Insert(loctestnum, loctesterr, seq_pq, 1.0 + i * 0.001);}
        
        for(int i = 9; i >= 0; i--)
        {
            double expected = 1.0 + i * 0.001;
            TipNRemove(loctestnum, loctesterr, seq_pq, true, expected);
        }
        Empty(loctestnum, loctesterr, seq_pq, true);
        
        lasd::PQHeap<double> mixed_pq;
        Insert(loctestnum, loctesterr, mixed_pq, 50.5);
        Insert(loctestnum, loctesterr, mixed_pq, 25.75);
        Insert(loctestnum, loctesterr, mixed_pq, 75.25);
        Tip(loctestnum, loctesterr, mixed_pq, true, 75.25);
        
        Insert(loctestnum, loctesterr, mixed_pq, 100.0);
        Tip(loctestnum, loctesterr, mixed_pq, true, 100.0);
        
        TipNRemove(loctestnum, loctesterr, mixed_pq, true, 100.0);
        Tip(loctestnum, loctesterr, mixed_pq, true, 75.25);
        
        Insert(loctestnum, loctesterr, mixed_pq, 80.5);
        Tip(loctestnum, loctesterr, mixed_pq, true, 80.5);
        
        lasd::PQHeap<double> assign_source;
        Insert(loctestnum, loctesterr, assign_source, 10.5);
        Insert(loctestnum, loctesterr, assign_source, 20.5);
        Insert(loctestnum, loctesterr, assign_source, 30.5);
        
        lasd::PQHeap<double> assign_target;
        assign_target = assign_source;
        EqualLinear(loctestnum, loctesterr, assign_source, assign_target, true);
        
        lasd::PQHeap<double> move_target;
        move_target = std::move(assign_target);
        Empty(loctestnum, loctesterr, assign_target, true);
        Size(loctestnum, loctesterr, move_target, true, 3);
    }
    catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    
    cout << "End of PQ<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}


void TestPQString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of PQ<string> Test:" << endl;
    
    try {
        
        lasd::PQHeap<string> pq_empty;
        Empty(loctestnum, loctesterr, pq_empty, true);
        Size(loctestnum, loctesterr, pq_empty, true, 0);
        
        lasd::Vector<string> vec1(15);
        SetAt(loctestnum, loctesterr, vec1, true, 0, string("z"));
        SetAt(loctestnum, loctesterr, vec1, true, 1, string("a"));
        SetAt(loctestnum, loctesterr, vec1, true, 2, string(""));
        SetAt(loctestnum, loctesterr, vec1, true, 3, string("Z"));
        SetAt(loctestnum, loctesterr, vec1, true, 4, string("A"));
        SetAt(loctestnum, loctesterr, vec1, true, 5, string("b"));
        SetAt(loctestnum, loctesterr, vec1, true, 6, string("c"));
        SetAt(loctestnum, loctesterr, vec1, true, 7, string("x"));
        SetAt(loctestnum, loctesterr, vec1, true, 8, string("y"));
        SetAt(loctestnum, loctesterr, vec1, true, 9, string("B"));
        SetAt(loctestnum, loctesterr, vec1, true, 10, string("C"));
        SetAt(loctestnum, loctesterr, vec1, true, 11, string("m"));
        SetAt(loctestnum, loctesterr, vec1, true, 12, string("n"));
        SetAt(loctestnum, loctesterr, vec1, true, 13, string("X"));
        SetAt(loctestnum, loctesterr, vec1, true, 14, string("Y"));
        
        lasd::PQHeap<string> pq(vec1);
        Empty(loctestnum, loctesterr, pq, false);
        Size(loctestnum, loctesterr, pq, true, 15);
        
        Tip(loctestnum, loctesterr, pq, true, string("z"));
        
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        
        TipNRemove(loctestnum, loctesterr, pq, true, string("z"));
        TipNRemove(loctestnum, loctesterr, pq, true, string("y"));
        TipNRemove(loctestnum, loctesterr, pq, true, string("x"));
        
        Size(loctestnum, loctesterr, pq, true, 12);
        
        Insert(loctestnum, loctesterr, pq, string("zzz"));
        Tip(loctestnum, loctesterr, pq, true, string("zzz"));
        
        Insert(loctestnum, loctesterr, pq, string(""));
        Insert(loctestnum, loctesterr, pq, string("aa"));
        Insert(loctestnum, loctesterr, pq, string("bb"));
        Insert(loctestnum, loctesterr, pq, string("ZZZ"));
        
        Size(loctestnum, loctesterr, pq, true, 17);
        
        Exists(loctestnum, loctesterr, pq, true, string("zzz"));
        Exists(loctestnum, loctesterr, pq, true, string(""));
        Exists(loctestnum, loctesterr, pq, true, string("a"));
        Exists(loctestnum, loctesterr, pq, true, string("A"));
        Exists(loctestnum, loctesterr, pq, false, string("Apple"));
        Exists(loctestnum, loctesterr, pq, false, string("nonexistent"));
        
        GetAt(loctestnum, loctesterr, pq, true, 0, string("zzz"));
        GetAt(loctestnum, loctesterr, pq, false, 25, string(""));
        
        Change(loctestnum, loctesterr, pq, 0, string("k"));
        
        uint size = pq.Size();
        Change(loctestnum, loctesterr, pq, size-1, string("zzzz"));
        
        lasd::PQHeap<string> pq_copy(pq);
        EqualLinear(loctestnum, loctesterr, pq, pq_copy, true);
        
        string current_tip = pq.Tip();
        TipNRemove(loctestnum, loctesterr, pq, true, current_tip);
        EqualLinear(loctestnum, loctesterr, pq, pq_copy, false);
        
        uint original_size = pq_copy.Size();
        lasd::PQHeap<string> pq_moved(std::move(pq_copy));
        
        Empty(loctestnum, loctesterr, pq_copy, true);
        Size(loctestnum, loctesterr, pq_moved, true, original_size);
        
        lasd::PQHeap<string> empty_pq;
        RemoveTip(loctestnum, loctesterr, empty_pq, false);
        Tip(loctestnum, loctesterr, empty_pq, false, string(""));
        
        Insert(loctestnum, loctesterr, empty_pq, string("test"));
        Tip(loctestnum, loctesterr, empty_pq, true, string("test"));
        TipNRemove(loctestnum, loctesterr, empty_pq, true, string("test"));
        Empty(loctestnum, loctesterr, empty_pq, true);
        
        lasd::PQHeap<string> case_pq;
        Insert(loctestnum, loctesterr, case_pq, string("Z"));
        Insert(loctestnum, loctesterr, case_pq, string("a"));
        Insert(loctestnum, loctesterr, case_pq, string("A"));
        Insert(loctestnum, loctesterr, case_pq, string("z"));
        
        Tip(loctestnum, loctesterr, case_pq, true, string("z"));
        TipNRemove(loctestnum, loctesterr, case_pq, true, string("z"));
        Tip(loctestnum, loctesterr, case_pq, true, string("a"));
        
        lasd::PQHeap<string> prefix_pq;
        Insert(loctestnum, loctesterr, prefix_pq, string("test"));
        Insert(loctestnum, loctesterr, prefix_pq, string("testing"));
        Insert(loctestnum, loctesterr, prefix_pq, string("tester"));
        Insert(loctestnum, loctesterr, prefix_pq, string("tests"));
        Insert(loctestnum, loctesterr, prefix_pq, string("te"));
        
        Tip(loctestnum, loctesterr, prefix_pq, true, string("tests"));
        
        lasd::PQHeap<string> dup_pq;
        for(int i = 0; i < 5; i++) {Insert(loctestnum, loctesterr, dup_pq, string("duplicate"));}
        
        Size(loctestnum, loctesterr, dup_pq, true, 5);
        
        for(int i = 0; i < 5; i++) {TipNRemove(loctestnum, loctesterr, dup_pq, true, string("duplicate"));}
        
        Empty(loctestnum, loctesterr, dup_pq, true);
        
        lasd::PQHeap<string> special_pq;
        Insert(loctestnum, loctesterr, special_pq, string("9"));
        Insert(loctestnum, loctesterr, special_pq, string("1"));
        Insert(loctestnum, loctesterr, special_pq, string(" "));
        Insert(loctestnum, loctesterr, special_pq, string("!"));
        Insert(loctestnum, loctesterr, special_pq, string(""));
        
        Tip(loctestnum, loctesterr, special_pq, true, string("9"));
        
        lasd::PQHeap<string> long_pq;
        
        for(int i = 1; i <= 10; i++)
        {
            string long_str(i * 5, 'a' + (i % 26));
            Insert(loctestnum, loctesterr, long_pq, long_str);
        }
        
        Size(loctestnum, loctesterr, long_pq, true, 10);
        
        lasd::PQHeap<string> final_pq;
        Insert(loctestnum, loctesterr, final_pq, string("d"));
        Insert(loctestnum, loctesterr, final_pq, string("z"));
        Insert(loctestnum, loctesterr, final_pq, string("b"));
        Insert(loctestnum, loctesterr, final_pq, string("f"));
        Insert(loctestnum, loctesterr, final_pq, string("j"));
        
        Tip(loctestnum, loctesterr, final_pq, true, string("z"));
        
        TraversePreOrder(loctestnum, loctesterr, final_pq, true, &TraversePrint<string>);
        
        lasd::PQHeap<string> case_heap;
        Insert(loctestnum, loctesterr, case_heap, string("apple"));
        Insert(loctestnum, loctesterr, case_heap, string("Zebra"));
        Insert(loctestnum, loctesterr, case_heap, string("banana"));
        Insert(loctestnum, loctesterr, case_heap, string("Apple"));
        
        Tip(loctestnum, loctesterr, case_heap, true, string("banana"));
        TipNRemove(loctestnum, loctesterr, case_heap, true, string("banana"));
        Tip(loctestnum, loctesterr, case_heap, true, string("apple"));
        
        lasd::PQHeap<string> assign_src;
        Insert(loctestnum, loctesterr, assign_src, string("xyz"));
        Insert(loctestnum, loctesterr, assign_src, string("abc"));
        Insert(loctestnum, loctesterr, assign_src, string("mno"));
        
        lasd::PQHeap<string> assign_dest;
        assign_dest = assign_src;
        EqualLinear(loctestnum, loctesterr, assign_src, assign_dest, true);
        
        lasd::PQHeap<string> move_dest;
        move_dest = std::move(assign_dest);
        Empty(loctestnum, loctesterr, assign_dest, true);
        Size(loctestnum, loctesterr, move_dest, true, 3);
        Tip(loctestnum, loctesterr, move_dest, true, string("xyz"));
    }
    catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    
    cout << "End of PQ<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}


void MyFullTest2A(unsigned int & testnum, unsigned int & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    TestPQInt(loctestnum, loctesterr);
    TestPQDouble(loctestnum, loctesterr);
    TestPQString(loctestnum, loctesterr);

    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "My test for PQs (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}
}