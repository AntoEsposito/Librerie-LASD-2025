#include <iostream>

/* ************************************************************************** */

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/traversable.hpp"

#include "../zlasdtest/vector/vector.hpp"
#include "../zlasdtest/list/list.hpp"
#include "../zlasdtest/set/set.hpp"

#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"

/* ************************************************************************** */

using namespace std;

//IMPORTANT: in the float test, there are not fold with add functions due to the fact that due to floating point precision
// the result of the fold is not always correct.

/* ************************************************************************** */

// testSetInt test

void mytestSetInt(lasd::Set<int> & set, uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    try {
        Empty(loctestnum, loctesterr, set, false);
        Size(loctestnum, loctesterr, set, true, 10);
        
        Exists(loctestnum, loctesterr, set, true, -10);
        Exists(loctestnum, loctesterr, set, true, 5);
        Exists(loctestnum, loctesterr, set, true, 15);
        Exists(loctestnum, loctesterr, set, false, 100);
        Exists(loctestnum, loctesterr, set, false, -100);
        Exists(loctestnum, loctesterr, set, false, 6);
        
        Min(loctestnum, loctesterr, set, true, -10);
        Max(loctestnum, loctesterr, set, true, 15);
        
        Remove(loctestnum, loctesterr, set, true, 0);
        Size(loctestnum, loctesterr, set, true, 9);
        Exists(loctestnum, loctesterr, set, false, 0);
        
        InsertC(loctestnum, loctesterr, set, true, 0);
        Size(loctestnum, loctesterr, set, true, 10);
        Exists(loctestnum, loctesterr, set, true, 0);
        
        InsertC(loctestnum, loctesterr, set, false, 5);
        InsertC(loctestnum, loctesterr, set, false, -5);
        Size(loctestnum, loctesterr, set, true, 10);
        
        RemoveMin(loctestnum, loctesterr, set, true);
        Min(loctestnum, loctesterr, set, true, -7);
        
        RemoveMax(loctestnum, loctesterr, set, true);
        Max(loctestnum, loctesterr, set, true, 10);
        
        Size(loctestnum, loctesterr, set, true, 8);
        
        Predecessor(loctestnum, loctesterr, set, true, 0, -5);
        Successor(loctestnum, loctesterr, set, true, 0, 2);
        Predecessor(loctestnum, loctesterr, set, true, 10, 7);
        Successor(loctestnum, loctesterr, set, false, 10, 0);
        Predecessor(loctestnum, loctesterr, set, false, -7, 0);
        
        Predecessor(loctestnum, loctesterr, set, false, -100, 0);
        Successor(loctestnum, loctesterr, set, false, 100, 0);
        
        PredecessorNRemove(loctestnum, loctesterr, set, true, 3, 2);
        Size(loctestnum, loctesterr, set, true, 7);
        SuccessorNRemove(loctestnum, loctesterr, set, true, 3, 5);
        Size(loctestnum, loctesterr, set, true, 6);
        
        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        
        FoldPreOrder(loctestnum, loctesterr, set, true, &FoldAdd<int>, 0, 8);
        FoldPostOrder(loctestnum, loctesterr, set, true, &FoldMultiply<int>, 1, 0);
        
        set.Clear();
        Empty(loctestnum, loctesterr, set, true);
        Size(loctestnum, loctesterr, set, true, 0);
        
        InsertC(loctestnum, loctesterr, set, true, 42);
        Size(loctestnum, loctesterr, set, true, 1);
        Min(loctestnum, loctesterr, set, true, 42);
        Max(loctestnum, loctesterr, set, true, 42);
        
        RemoveMin(loctestnum, loctesterr, set, true);
        Empty(loctestnum, loctesterr, set, true);
    }
    catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of my Set<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void mytestSetInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of my Set<int> Test" << endl;
    try {
        lasd::Vector<int> vec(10);
        SetAt(loctestnum, loctesterr, vec, true, 0, -10);
        SetAt(loctestnum, loctesterr, vec, true, 1, -5);
        SetAt(loctestnum, loctesterr, vec, true, 2, 0);
        SetAt(loctestnum, loctesterr, vec, true, 3, 5);
        SetAt(loctestnum, loctesterr, vec, true, 4, 10);
        SetAt(loctestnum, loctesterr, vec, true, 5, 15);
        SetAt(loctestnum, loctesterr, vec, true, 6, 3);
        SetAt(loctestnum, loctesterr, vec, true, 7, 7);
        SetAt(loctestnum, loctesterr, vec, true, 8, -7);
        SetAt(loctestnum, loctesterr, vec, true, 9, 2);

        cout << endl << "Begin of SetVec<int> Test:" << endl;
        lasd::SetVec<int> setvec(vec);
        mytestSetInt(setvec, loctestnum, loctesterr);
        
        lasd::SetVec<int> setvecCopy(setvec);
        EqualSetVec(loctestnum, loctesterr, setvec, setvecCopy, true);
        setvecCopy.Insert(99);
        NonEqualSetVec(loctestnum, loctesterr, setvec, setvecCopy, true);
        
        lasd::SetVec<int> setvecAssign;
        setvecAssign = setvecCopy;
        EqualSetVec(loctestnum, loctesterr, setvecCopy, setvecAssign, true);
        
        lasd::SetVec<int> setvecMove(std::move(setvecAssign));
        Empty(loctestnum, loctesterr, setvecAssign, true);
        Exists(loctestnum, loctesterr, setvecMove, true, 99);

        cout << endl << "Begin of SetLst<int> Test:" << endl;
        lasd::SetLst<int> setlst(vec);
        mytestSetInt(setlst, loctestnum, loctesterr);
        
        lasd::SetLst<int> setlstCopy(setlst);
        EqualSetLst(loctestnum, loctesterr, setlst, setlstCopy, true);
        setlstCopy.Insert(-99);
        NonEqualSetLst(loctestnum, loctesterr, setlst, setlstCopy, true);
        
        lasd::SetLst<int> setlstAssign;
        setlstAssign = setlstCopy;
        EqualSetLst(loctestnum, loctesterr, setlstCopy, setlstAssign, true);
        
        lasd::SetLst<int> setlstMove(std::move(setlstAssign));
        Empty(loctestnum, loctesterr, setlstAssign, true);
        Exists(loctestnum, loctesterr, setlstMove, true, -99);

        setvec.Clear();
        setlst.Clear();
        
        setvec.InsertAll(vec);
        setlst.InsertAll(vec);
        Size(loctestnum, loctesterr, setvec, true, 10);
        Size(loctestnum, loctesterr, setlst, true, 10);
        
        for (int i = 0; i < 10; ++i) 
        {
            Remove(loctestnum, loctesterr, setvec, true, vec[i]);
            Remove(loctestnum, loctesterr, setlst, true, vec[i]);
        }
        Empty(loctestnum, loctesterr, setvec, true);
        Empty(loctestnum, loctesterr, setlst, true);
        
        setvec.InsertAll(vec);
        setlst.InsertAll(vec);
        EqualLinear(loctestnum, loctesterr, setvec, setlst, true);
        
        setvec.Clear();
        setlst.Clear();
        EqualLinear(loctestnum, loctesterr, setvec, setlst, true);
        
        setvec.Insert(42);
        NonEqualLinear(loctestnum, loctesterr, setvec, setlst, true);
        setlst.Insert(42);
        EqualLinear(loctestnum, loctesterr, setvec, setlst, true);
    }
    catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of my Set<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}


// testSetFloat test

void mytestSetFloat(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of my Set<float> Test" << endl;
    try {
        lasd::List<float> lst;
        InsertAtFront(loctestnum, loctesterr, lst, true, 0.0f);
        InsertAtBack(loctestnum, loctesterr, lst, true, -2.5f);
        InsertAtFront(loctestnum, loctesterr, lst, true, 3.14f);
        InsertAtBack(loctestnum, loctesterr, lst, true, 2.1f);
        InsertAtFront(loctestnum, loctesterr, lst, true, 1.1f);
        InsertAtBack(loctestnum, loctesterr, lst, true, 5.3f);
        InsertAtFront(loctestnum, loctesterr, lst, true, -100.0f);
        InsertAtBack(loctestnum, loctesterr, lst, true, 100.0f);

        TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<float>);

        /* ********************************************************************** */

        lasd::SetVec<float> setvec1(lst);

        Empty(loctestnum, loctesterr, setvec1, false);
        Size(loctestnum, loctesterr, setvec1, true, 8);

        TraversePreOrder(loctestnum, loctesterr, setvec1, true, &TraversePrint<float>);
        TraversePostOrder(loctestnum, loctesterr, setvec1, true, &TraversePrint<float>);

        lasd::SetVec<float> setvec2;

        InsertC(loctestnum, loctesterr, setvec2, true, 2.1f);
        InsertC(loctestnum, loctesterr, setvec2, true, 0.0f);
        InsertC(loctestnum, loctesterr, setvec2, true, 1.1f);
        InsertC(loctestnum, loctesterr, setvec2, true, 3.14f);
        InsertC(loctestnum, loctesterr, setvec2, true, 5.3f);
        InsertC(loctestnum, loctesterr, setvec2, true, -2.5f);
        InsertC(loctestnum, loctesterr, setvec2, true, -100.0f);
        InsertC(loctestnum, loctesterr, setvec2, true, 100.0f);

        EqualSetVec(loctestnum, loctesterr, setvec1, setvec2, true);
        NonEqualSetVec(loctestnum, loctesterr, setvec1, setvec2, false);

        Remove(loctestnum, loctesterr, setvec2, true, 3.14f);
        Exists(loctestnum, loctesterr, setvec2, false, 3.14f);
        InsertC(loctestnum, loctesterr, setvec2, true, 3.14f);
        Exists(loctestnum, loctesterr, setvec2, true, 3.14f);

        InsertC(loctestnum, loctesterr, setvec2, false, 3.14f);
        Remove(loctestnum, loctesterr, setvec2, false, 999.9f);

        Min(loctestnum, loctesterr, setvec2, true, -100.0f);
        Max(loctestnum, loctesterr, setvec2, true, 100.0f);

        FoldPostOrder(loctestnum, loctesterr, setvec2, true, &FoldMultiply<float>, 1.0f, 0.0f);

        setvec1.Clear();
        setvec2.Clear();

        InsertC(loctestnum, loctesterr, setvec1, true, 0.5f);
        InsertC(loctestnum, loctesterr, setvec1, true, -0.5f);
        InsertC(loctestnum, loctesterr, setvec1, true, 1.5f);

        InsertC(loctestnum, loctesterr, setvec2, true, 1.5f);
        InsertC(loctestnum, loctesterr, setvec2, true, -0.5f);
        InsertC(loctestnum, loctesterr, setvec2, true, 0.5f);

        EqualSetVec(loctestnum, loctesterr, setvec1, setvec2, true);

        /* ********************************************************************** */

        lasd::SetLst<float> setlst1(lst);

        Empty(loctestnum, loctesterr, setlst1, false);
        Size(loctestnum, loctesterr, setlst1, true, 8);

        TraversePreOrder(loctestnum, loctesterr, setlst1, true, &TraversePrint<float>);
        TraversePostOrder(loctestnum, loctesterr, setlst1, true, &TraversePrint<float>);

        lasd::SetLst<float> setlst2;

        InsertC(loctestnum, loctesterr, setlst2, true, 2.1f);
        InsertC(loctestnum, loctesterr, setlst2, true, 0.0f);
        InsertC(loctestnum, loctesterr, setlst2, true, 1.1f);
        InsertC(loctestnum, loctesterr, setlst2, true, 3.14f);
        InsertC(loctestnum, loctesterr, setlst2, true, 5.3f);
        InsertC(loctestnum, loctesterr, setlst2, true, -2.5f);
        InsertC(loctestnum, loctesterr, setlst2, true, -100.0f);
        InsertC(loctestnum, loctesterr, setlst2, true, 100.0f);

        EqualSetLst(loctestnum, loctesterr, setlst1, setlst2, true);
        NonEqualSetLst(loctestnum, loctesterr, setlst1, setlst2, false);

        Remove(loctestnum, loctesterr, setlst2, true, 5.3f);
        Exists(loctestnum, loctesterr, setlst2, false, 5.3f);
        InsertC(loctestnum, loctesterr, setlst2, true, 5.3f);
        Exists(loctestnum, loctesterr, setlst2, true, 5.3f);

        InsertC(loctestnum, loctesterr, setlst2, false, 5.3f);
        Remove(loctestnum, loctesterr, setlst2, false, -999.9f);

        Min(loctestnum, loctesterr, setlst2, true, -100.0f);
        Max(loctestnum, loctesterr, setlst2, true, 100.0f);

        FoldPostOrder(loctestnum, loctesterr, setlst2, true, &FoldMultiply<float>, 1.0f, 0.0f);

        setlst1.Clear();
        setlst2.Clear();

        InsertC(loctestnum, loctesterr, setlst1, true, 0.5f);
        InsertC(loctestnum, loctesterr, setlst1, true, -0.5f);
        InsertC(loctestnum, loctesterr, setlst1, true, 1.5f);

        InsertC(loctestnum, loctesterr, setlst2, true, 1.5f);
        InsertC(loctestnum, loctesterr, setlst2, true, -0.5f);
        InsertC(loctestnum, loctesterr, setlst2, true, 0.5f);

        EqualSetLst(loctestnum, loctesterr, setlst1, setlst2, true);

        /* ********************************************************************** */

        EqualLinear(loctestnum, loctesterr, setvec1, setlst2, true);
        NonEqualLinear(loctestnum, loctesterr, setlst2, setvec2, false);

        setvec1.Clear();
        setlst1.Clear();
        Empty(loctestnum, loctesterr, setvec1, true);
        Empty(loctestnum, loctesterr, setlst1, true);
    }
    catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of my Set<float> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}


// testSetString test

void mytestSetString(lasd::Set<string> & set, uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    try {
        set.Clear();
        Empty(loctestnum, loctesterr, set, true);

        InsertC(loctestnum, loctesterr, set, true, string("A"));
        InsertC(loctestnum, loctesterr, set, true, string("AB"));
        InsertC(loctestnum, loctesterr, set, true, string("XY"));
        InsertC(loctestnum, loctesterr, set, true, string("CD"));
        InsertC(loctestnum, loctesterr, set, true, string("EF"));
        InsertC(loctestnum, loctesterr, set, true, string("GH"));
        InsertC(loctestnum, loctesterr, set, true, string("IJ"));
        InsertC(loctestnum, loctesterr, set, true, string("KL"));
        InsertC(loctestnum, loctesterr, set, true, string("MN"));
        InsertC(loctestnum, loctesterr, set, true, string("OP"));

        InsertC(loctestnum, loctesterr, set, false, string("A"));
        InsertC(loctestnum, loctesterr, set, false, string("AB"));

        Exists(loctestnum, loctesterr, set, true, string("A"));
        Exists(loctestnum, loctesterr, set, false, string("QR"));

        Remove(loctestnum, loctesterr, set, true, string("XY"));
        Remove(loctestnum, loctesterr, set, false, string("XY"));
        Remove(loctestnum, loctesterr, set, false, string("ZZ"));

        Min(loctestnum, loctesterr, set, true, string("A"));
        Max(loctestnum, loctesterr, set, true, string("OP"));

        RemoveMin(loctestnum, loctesterr, set, true);
        RemoveMax(loctestnum, loctesterr, set, true);

        Predecessor(loctestnum, loctesterr, set, true, string("CD"), string("AB"));
        Successor(loctestnum, loctesterr, set, true, string("CD"), string("EF"));
        Predecessor(loctestnum, loctesterr, set, false, string("AB"), string(""));
        Successor(loctestnum, loctesterr, set, false, string("OP"), string(""));

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        FoldPreOrder(loctestnum, loctesterr, set, true, &FoldStringConcatenate, string("!"), string("!ABCDEFGHIJKLMN"));
        FoldPostOrder(loctestnum, loctesterr, set, true, &FoldStringConcatenate, string("!"), string("!MNKLIJGHEFCDAB"));

        InsertC(loctestnum, loctesterr, set, true, string(""));
        InsertC(loctestnum, loctesterr, set, true, string(" "));
        InsertC(loctestnum, loctesterr, set, true, string("123"));
        InsertC(loctestnum, loctesterr, set, true, string("!@#"));
        InsertC(loctestnum, loctesterr, set, true, string("abc"));

        Exists(loctestnum, loctesterr, set, true, string(""));
        Exists(loctestnum, loctesterr, set, true, string(" "));
        Exists(loctestnum, loctesterr, set, true, string("123"));
        Exists(loctestnum, loctesterr, set, true, string("!@#"));
        Exists(loctestnum, loctesterr, set, true, string("abc"));
        Exists(loctestnum, loctesterr, set, false, string("ABC"));

        Remove(loctestnum, loctesterr, set, true, string(""));
        Remove(loctestnum, loctesterr, set, true, string(" "));
        Remove(loctestnum, loctesterr, set, true, string("123"));
        Remove(loctestnum, loctesterr, set, true, string("!@#"));
        Remove(loctestnum, loctesterr, set, true, string("abc"));

        set.Clear();
        Empty(loctestnum, loctesterr, set, true);
        Size(loctestnum, loctesterr, set, true, 0);

        InsertC(loctestnum, loctesterr, set, true, string("ZZ"));
        Exists(loctestnum, loctesterr, set, true, string("ZZ"));
        set.Clear();

        Empty(loctestnum, loctesterr, set, true);
        Size(loctestnum, loctesterr, set, true, 0);
    } 
    catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of my Set<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}
void mytestSetString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of my Set<string> Test" << endl;
    try {
        lasd::Vector<string> vec(10);
        SetAt(loctestnum, loctesterr, vec, true, 0, string("AA"));
        SetAt(loctestnum, loctesterr, vec, true, 1, string("AB"));
        SetAt(loctestnum, loctesterr, vec, true, 2, string("AC"));
        SetAt(loctestnum, loctesterr, vec, true, 3, string("AD"));
        SetAt(loctestnum, loctesterr, vec, true, 4, string("AE"));
        SetAt(loctestnum, loctesterr, vec, true, 5, string("AF"));
        SetAt(loctestnum, loctesterr, vec, true, 6, string("AG"));
        SetAt(loctestnum, loctesterr, vec, true, 7, string("AH"));
        SetAt(loctestnum, loctesterr, vec, true, 8, string("AI"));
        SetAt(loctestnum, loctesterr, vec, true, 9, string("AJ"));

        cout << endl << "Begin of SetVec<string> Test:" << endl;
        lasd::SetVec<string> setvec(vec);
        lasd::SetVec<string> vectotest(vec);
        mytestSetString(vectotest, loctestnum, loctesterr);

        InsertC(loctestnum, loctesterr, setvec, false, string("AA"));
        InsertC(loctestnum, loctesterr, setvec, true, string(""));
        InsertC(loctestnum, loctesterr, setvec, true, string(" "));
        InsertC(loctestnum, loctesterr, setvec, true, string("123"));
        InsertC(loctestnum, loctesterr, setvec, true, string("!@#"));
        InsertC(loctestnum, loctesterr, setvec, true, string("aa"));
        InsertC(loctestnum, loctesterr, setvec, false, string("aa"));

        Exists(loctestnum, loctesterr, setvec, true, string("AA"));
        Exists(loctestnum, loctesterr, setvec, true, string(""));
        Exists(loctestnum, loctesterr, setvec, false, string("AK"));

        Remove(loctestnum, loctesterr, setvec, true, string("AC"));
        Remove(loctestnum, loctesterr, setvec, false, string("AC"));
        Remove(loctestnum, loctesterr, setvec, true, string(""));
        Remove(loctestnum, loctesterr, setvec, false, string("ZZ"));

        Min(loctestnum, loctesterr, setvec, true, string(" "));
        Max(loctestnum, loctesterr, setvec, true, string("aa"));

        Predecessor(loctestnum, loctesterr, setvec, true, string("AD"), string("AB"));
        Successor(loctestnum, loctesterr, setvec, true, string("AD"), string("AE"));
        Predecessor(loctestnum, loctesterr, setvec, false, string("AB"), string(""));
        Successor(loctestnum, loctesterr, setvec, false, string("aa"), string(""));

        TraversePreOrder(loctestnum, loctesterr, setvec, true, &TraversePrint<string>);
        FoldPreOrder(loctestnum, loctesterr, setvec, true, &FoldStringConcatenate, string("!"), string("! !@#123AAABADAEAFAGAHAIAJaa"));

        lasd::SetVec<string> setvecCopy(setvec);
        EqualSetVec(loctestnum, loctesterr, setvec, setvecCopy, true);
        setvecCopy.Insert(string("AK"));
        NonEqualSetVec(loctestnum, loctesterr, setvec, setvecCopy, true);

        lasd::SetVec<string> setvecMove(std::move(setvecCopy));
        Empty(loctestnum, loctesterr, setvecCopy, true);
        Size(loctestnum, loctesterr, setvecMove, true, setvec.Size() + 1);

        setvec = setvec;
        EqualSetVec(loctestnum, loctesterr, setvec, setvec, true);
        EqualSetVec(loctestnum, loctesterr, setvec, setvecMove, false);

        setvec.Clear();
        Empty(loctestnum, loctesterr, setvec, true);

        cout << endl << "Begin of SetLst<string> Test:" << endl;
        lasd::SetLst<string> setlst(vec);
        lasd::SetLst<string> lsttotest(vec);
        mytestSetString(lsttotest, loctestnum, loctesterr);

        InsertC(loctestnum, loctesterr, setlst, false, string("AA"));
        InsertC(loctestnum, loctesterr, setlst, true, string(""));
        InsertC(loctestnum, loctesterr, setlst, true, string(" "));
        InsertC(loctestnum, loctesterr, setlst, true, string("123"));
        InsertC(loctestnum, loctesterr, setlst, true, string("!@#"));
        InsertC(loctestnum, loctesterr, setlst, true, string("aa"));
        InsertC(loctestnum, loctesterr, setlst, false, string("aa"));

        Exists(loctestnum, loctesterr, setlst, true, string("AA"));
        Exists(loctestnum, loctesterr, setlst, true, string(""));
        Exists(loctestnum, loctesterr, setlst, false, string("AK"));

        Remove(loctestnum, loctesterr, setlst, true, string("AC"));
        Remove(loctestnum, loctesterr, setlst, false, string("AC"));
        Remove(loctestnum, loctesterr, setlst, true, string(""));
        Remove(loctestnum, loctesterr, setlst, false, string("ZZ"));

        Min(loctestnum, loctesterr, setlst, true, string(" "));
        Max(loctestnum, loctesterr, setlst, true, string("aa"));

        Predecessor(loctestnum, loctesterr, setlst, true, string("AD"), string("AB"));
        Successor(loctestnum, loctesterr, setlst, true, string("AD"), string("AE"));
        Predecessor(loctestnum, loctesterr, setlst, false, string("AB"), string(""));
        Successor(loctestnum, loctesterr, setlst, false, string("aa"), string(""));

        TraversePreOrder(loctestnum, loctesterr, setlst, true, &TraversePrint<string>);
        FoldPreOrder(loctestnum, loctesterr, setlst, true, &FoldStringConcatenate, string("!"), string("! !@#123AAABADAEAFAGAHAIAJaa"));

        lasd::SetLst<string> setlstCopy(setlst);
        EqualSetLst(loctestnum, loctesterr, setlst, setlstCopy, true);
        setlstCopy.Insert(string("AK"));
        NonEqualSetLst(loctestnum, loctesterr, setlst, setlstCopy, true);

        lasd::SetLst<string> setlstMove(std::move(setlstCopy));
        Empty(loctestnum, loctesterr, setlstCopy, true);
        Size(loctestnum, loctesterr, setlstMove, true, setlst.Size() + 1);

        setlst = setlst;
        EqualSetLst(loctestnum, loctesterr, setlst, setlst, true);
        EqualSetLst(loctestnum, loctesterr, setlst, setlstMove, false);

        setlst.Clear();
        Empty(loctestnum, loctesterr, setlst, true);

        /* ********************************************************************** */

        lasd::SetVec<string> setvec2(vec);
        lasd::SetLst<string> setlst2(vec);
        EqualLinear(loctestnum, loctesterr, setvec2, setlst2, true);

        setvec2.Insert(string("AK"));
        NonEqualLinear(loctestnum, loctesterr, setvec2, setlst2, true);
        setlst2.Insert(string("AK"));
    }
    catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of my Set<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void MyFullTest1B(uint & testnum, uint & testerr) {
    mytestSetInt(testnum, testerr);
    mytestSetFloat(testnum, testerr);
    mytestSetString(testnum, testerr);
    cout << endl << "My test for Sets (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}