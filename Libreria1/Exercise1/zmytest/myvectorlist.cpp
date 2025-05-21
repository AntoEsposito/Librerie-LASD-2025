#include <iostream>

/* ************************************************************************** */

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/traversable.hpp"

#include "../zlasdtest/vector/vector.hpp"
#include "../zlasdtest/list/list.hpp"

using namespace std;


// Vector Tests

void testVectorInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  
  cout << endl << "Begin Vector<int> Test:" << endl;
  
  try {
    {
      lasd::SortableVector<int> vec;
      Empty(loctestnum, loctesterr, vec, true);
      
      GetFront(loctestnum, loctesterr, vec, false, 0);
      GetBack(loctestnum, loctesterr, vec, false, 0);
      SetAt(loctestnum, loctesterr, vec, false, 0, 10);
      GetAt(loctestnum, loctesterr, vec, false, 0, 10);
      
      vec.Resize(1);
      Empty(loctestnum, loctesterr, vec, false);
      Size(loctestnum, loctesterr, vec, true, 1);
      
      SetAt(loctestnum, loctesterr, vec, true, 0, 10);
      GetFront(loctestnum, loctesterr, vec, true, 10);
      GetBack(loctestnum, loctesterr, vec, true, 10);
      
      vec.Resize(0);
      Empty(loctestnum, loctesterr, vec, true);
    }
    {
      lasd::SortableVector<int> vec(5);
      Size(loctestnum, loctesterr, vec, true, 5);
      Empty(loctestnum, loctesterr, vec, false);
      
      SetAt(loctestnum, loctesterr, vec, true, 0, 3);
      SetAt(loctestnum, loctesterr, vec, true, 1, 1);
      SetAt(loctestnum, loctesterr, vec, true, 2, 4);
      SetAt(loctestnum, loctesterr, vec, true, 3, 1);
      SetAt(loctestnum, loctesterr, vec, true, 4, 5);
      
      GetFront(loctestnum, loctesterr, vec, true, 3);
      GetBack(loctestnum, loctesterr, vec, true, 5);
      
      SetFront(loctestnum, loctesterr, vec, true, 9);
      SetBack(loctestnum, loctesterr, vec, true, 2);
      GetFront(loctestnum, loctesterr, vec, true, 9);
      GetBack(loctestnum, loctesterr, vec, true, 2);
      
      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 17);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 17);
      
      vec.Sort();
      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 1, 72);
    }
    {
      lasd::SortableVector<int> vec(4);
      SetAt(loctestnum, loctesterr, vec, true, 0, 7);
      SetAt(loctestnum, loctesterr, vec, true, 1, 8);
      SetAt(loctestnum, loctesterr, vec, true, 2, 9);
      SetAt(loctestnum, loctesterr, vec, true, 3, 10);
      
      vec.Resize(6);
      Size(loctestnum, loctesterr, vec, true, 6);
      GetAt(loctestnum, loctesterr, vec, true, 4, 0);
      GetAt(loctestnum, loctesterr, vec, true, 5, 0);
      
      SetAt(loctestnum, loctesterr, vec, true, 4, 11);
      SetAt(loctestnum, loctesterr, vec, true, 5, 12);
      
      vec.Resize(3);
      Size(loctestnum, loctesterr, vec, true, 3);
      GetAt(loctestnum, loctesterr, vec, true, 0, 7);
      GetAt(loctestnum, loctesterr, vec, true, 1, 8);
      GetAt(loctestnum, loctesterr, vec, true, 2, 9);
      
      GetAt(loctestnum, loctesterr, vec, false, 4, 0);
    }
    {
      lasd::SortableVector<int> vec(2);
      SetAt(loctestnum, loctesterr, vec, true, 0, 15);
      SetAt(loctestnum, loctesterr, vec, true, 1, 20);
      GetAt(loctestnum, loctesterr, vec, false, 2, 0);
      SetAt(loctestnum, loctesterr, vec, false, 5, 100);
    }
    {
      lasd::SortableVector<int> orig(3);
      SetAt(loctestnum, loctesterr, orig, true, 0, 2);
      SetAt(loctestnum, loctesterr, orig, true, 1, 4);
      SetAt(loctestnum, loctesterr, orig, true, 2, 6);
      
      lasd::SortableVector<int> copy(orig);
      Size(loctestnum, loctesterr, copy, true, 3);
      
      lasd::SortableVector<int> moved(std::move(orig));
      Size(loctestnum, loctesterr, moved, true, 3);
      Empty(loctestnum, loctesterr, orig, true);
      
      lasd::SortableVector<int> vecAssign(2);
      SetAt(loctestnum, loctesterr, vecAssign, true, 0, 99);
      SetAt(loctestnum, loctesterr, vecAssign, true, 1, 88);
      vecAssign = copy;
      Size(loctestnum, loctesterr, vecAssign, true, 3);
      
      lasd::SortableVector<int> moveAssignVec(4);
      moveAssignVec = std::move(copy);
      Size(loctestnum, loctesterr, moveAssignVec, true, 3);
    }
  }
  catch (...) {
    loctestnum++; 
    loctesterr++;
    cout << endl << "Unmanaged error!" << endl;
  }
  
  cout << "End of Vector<int> Test! (Errors/Tests: "<< loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testVectorDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<double> Test:" << endl;
  try {
    {
      lasd::SortableVector<double> vec; 
      Empty(loctestnum, loctesterr, vec, true);
      
      GetFront(loctestnum, loctesterr, vec, false, 0.0);
      GetBack(loctestnum, loctesterr, vec, false, 0.0);
      SetAt(loctestnum, loctesterr, vec, false, 0, 1.1);
      GetAt(loctestnum, loctesterr, vec, false, 0, 1.1);
      
      vec.Resize(1);
      Size(loctestnum, loctesterr, vec, true, 1);
      Empty(loctestnum, loctesterr, vec, false);
      GetFront(loctestnum, loctesterr, vec, true, 0.0);
      GetBack(loctestnum, loctesterr, vec, true, 0.0);
      
      SetAt(loctestnum, loctesterr, vec, true, 0, 2.2);
      GetFront(loctestnum, loctesterr, vec, true, 2.2);
      GetBack(loctestnum, loctesterr, vec, true, 2.2);
      
      vec.Resize(0);
      Empty(loctestnum, loctesterr, vec, true);
    }
    {
      lasd::SortableVector<double> vec(3);
      Empty(loctestnum, loctesterr, vec, false);
      Size(loctestnum, loctesterr, vec, true, 3);
      
      SetAt(loctestnum, loctesterr, vec, true, 0, 5.5);
      SetAt(loctestnum, loctesterr, vec, true, 1, 3.3);
      SetAt(loctestnum, loctesterr, vec, true, 2, 1.1);
      
      GetFront(loctestnum, loctesterr, vec, true, 5.5);
      GetBack(loctestnum, loctesterr, vec, true, 1.1);
      
      Exists(loctestnum, loctesterr, vec, true, 3.3);
      
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 0.0, 9.9);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<double>, 1.0, 19.965);
    }
    {
      lasd::SortableVector<double> vec(4);
      SetAt(loctestnum, loctesterr, vec, true, 0, 7.7);
      SetAt(loctestnum, loctesterr, vec, true, 1, 8.8);
      SetAt(loctestnum, loctesterr, vec, true, 2, 9.9);
      SetAt(loctestnum, loctesterr, vec, true, 3, 10.1);
      
      vec.Resize(6);
      Size(loctestnum, loctesterr, vec, true, 6);
      GetAt(loctestnum, loctesterr, vec, true, 4, 0.0);
      GetAt(loctestnum, loctesterr, vec, true, 5, 0.0);
      
      SetAt(loctestnum, loctesterr, vec, true, 4, 11.11);
      SetAt(loctestnum, loctesterr, vec, true, 5, 12.12);
      
      vec.Resize(3);
      Size(loctestnum, loctesterr, vec, true, 3);
      GetAt(loctestnum, loctesterr, vec, true, 0, 7.7);
      GetAt(loctestnum, loctesterr, vec, true, 1, 8.8);
      GetAt(loctestnum, loctesterr, vec, true, 2, 9.9);
      
      GetAt(loctestnum, loctesterr, vec, false, 4, 11.11);
    }
    {
      lasd::SortableVector<double> vec(2);
      SetAt(loctestnum, loctesterr, vec, true, 0, 15.15);
      SetAt(loctestnum, loctesterr, vec, true, 1, 20.2);

      GetAt(loctestnum, loctesterr, vec, false, 2, 0.0);
      SetAt(loctestnum, loctesterr, vec, false, 5, 100.1);

      SetFront(loctestnum, loctesterr, vec, true, 30.3);
      SetBack(loctestnum, loctesterr, vec, true, 40.4);
      GetFront(loctestnum, loctesterr, vec, true, 30.3);
      GetBack(loctestnum, loctesterr, vec, true, 40.4);
      
      vec.Sort();
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<double>, 1.0, 1224.12);
    }
    {
      lasd::SortableVector<double> orig(3);
      SetAt(loctestnum, loctesterr, orig, true, 0, 1.01);
      SetAt(loctestnum, loctesterr, orig, true, 1, 2.02);
      SetAt(loctestnum, loctesterr, orig, true, 2, 3.03);
    
      lasd::SortableVector<double> copy(orig);
      Size(loctestnum, loctesterr, copy, true, 3);
      
      lasd::SortableVector<double> moved(std::move(orig));
      Size(loctestnum, loctesterr, moved, true, 3);
      Empty(loctestnum, loctesterr, orig, true);
      
      lasd::SortableVector<double> assignTest(2);
      SetAt(loctestnum, loctesterr, assignTest, true, 0, 9.9);
      SetAt(loctestnum, loctesterr, assignTest, true, 1, 8.8);
      assignTest = copy;
      Size(loctestnum, loctesterr, assignTest, true, 3);
      
      lasd::SortableVector<double> moveAssign(4);
      moveAssign = std::move(copy);
      Size(loctestnum, loctesterr, moveAssign, true, 3);
    }
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error!" << endl;
  }
  cout << "End of Vector<double> Test! (Errors/Tests: "<< loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testVectorString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<string> Test:" << endl;
  try {
    {
      lasd::SortableVector<string> vec;
      Empty(loctestnum, loctesterr, vec, true);
      
      GetFront(loctestnum, loctesterr, vec, false, string(""));
      GetBack(loctestnum, loctesterr, vec, false, string(""));
      SetAt(loctestnum, loctesterr, vec, false, 0, string("Error"));
      GetAt(loctestnum, loctesterr, vec, false, 0, string("Error"));
      
      vec.Resize(3);
      Size(loctestnum, loctesterr, vec, true, 3);
      for (uint i = 0; i < 3; i++) GetAt(loctestnum, loctesterr, vec, true, i, string(""));
      
      SetAt(loctestnum, loctesterr, vec, true, 0, string("Primo"));
      SetAt(loctestnum, loctesterr, vec, true, 1, string("Secondo"));
      SetAt(loctestnum, loctesterr, vec, true, 2, string("Terzo"));
      GetFront(loctestnum, loctesterr, vec, true, string("Primo"));
      GetBack(loctestnum, loctesterr, vec, true, string("Terzo"));
      Exists(loctestnum, loctesterr, vec, true, string("Secondo"));
    }
    {
      lasd::SortableVector<string> vec(2);
      Empty(loctestnum, loctesterr, vec, false);
      Size(loctestnum, loctesterr, vec, true, 2);

      SetAt(loctestnum, loctesterr, vec, true, 0, string("A"));
      SetAt(loctestnum, loctesterr, vec, true, 1, string("B"));

      GetFront(loctestnum, loctesterr, vec, true, string("A"));
      GetBack(loctestnum, loctesterr, vec, true, string("B"));
      Exists(loctestnum, loctesterr, vec, true, string("A"));
      
      MapPreOrder(loctestnum, loctesterr, vec, true, [](string & str) {MapStringAppend(str, string(" "));});
      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<string>);
      
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XA B "));
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XB A "));
      
      Exists(loctestnum, loctesterr, vec, false, string("A"));
    }
    {
      lasd::SortableVector<string> vec(2);
      SetAt(loctestnum, loctesterr, vec, true, 0, string("Hello"));
      SetAt(loctestnum, loctesterr, vec, true, 1, string("World"));
      
      lasd::SortableVector<string> copvec(vec);
      EqualVector(loctestnum, loctesterr, vec, copvec, true);
      
      MapPreOrder(loctestnum, loctesterr, vec, true, [](string & str) {MapStringAppend(str, string("!"));});

      NonEqualVector(loctestnum, loctesterr, vec, copvec, true);
      
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("?"), string("?Hello!World!"));
      
      copvec = move(vec);
      FoldPreOrder(loctestnum, loctesterr, copvec, true, &FoldStringConcatenate, string("#"), string("#Hello!World!"));
    }
    {
      lasd::SortableVector<string> vec(3);
      SetAt(loctestnum, loctesterr, vec, true, 0, string("uno"));
      SetAt(loctestnum, loctesterr, vec, true, 1, string("due"));
      SetAt(loctestnum, loctesterr, vec, true, 2, string("tre"));
      
      lasd::SortableVector<string> movvec(move(vec));
      Empty(loctestnum, loctesterr, vec, true);
      
      FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?unoduetre"));

      movvec.Sort();
      FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?duetreuno"));
      
      movvec.Resize(2);
      Size(loctestnum, loctesterr, movvec, true, 2);
      FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?duetre"));
      
      movvec.Clear();
      Empty(loctestnum, loctesterr, movvec, true);
    }
  }
  catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Unmanaged error!" << endl;
  }
  cout << "End of Vector<string> Test! (Errors/Tests: "<< loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}


// List Tests

void testListInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<int> Test:" << endl;
  try {
    lasd::List<int> lst;

    InsertAtBack(loctestnum, loctesterr, lst, true, 10);
    InsertAtBack(loctestnum, loctesterr, lst, true, 20);
    InsertAtFront(loctestnum, loctesterr, lst, true, 5);
    InsertAtFront(loctestnum, loctesterr, lst, true, 1);

    Size(loctestnum, loctesterr, lst, true, 4);
    GetFront(loctestnum, loctesterr, lst, true, 1);
    GetBack(loctestnum, loctesterr, lst, true, 20);

    RemoveFromBack(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 3);
    GetBack(loctestnum, loctesterr, lst, true, 10);

    InsertAtBack(loctestnum, loctesterr, lst, true, 5);
    InsertAtFront(loctestnum, loctesterr, lst, true, 5);
    Size(loctestnum, loctesterr, lst, true, 5);

    Exists(loctestnum, loctesterr, lst, true, 5);

    lst.Clear();
    Empty(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 0);

    RemoveFromBack(loctestnum, loctesterr, lst, false);
    BackNRemove(loctestnum, loctesterr, lst, false, 0);

    InsertAtFront(loctestnum, loctesterr, lst, true, 42);
    GetFront(loctestnum, loctesterr, lst, true, 42);
    GetBack(loctestnum, loctesterr, lst, true, 42);

    lst.Clear();
    Empty(loctestnum, loctesterr, lst, true);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of List<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testListDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<double> Test:" << endl;
  try {
    lasd::List<double> lst;

    InsertAtBack(loctestnum, loctesterr, lst, true, 10.5);
    InsertAtBack(loctestnum, loctesterr, lst, true, 20.2);
    InsertAtFront(loctestnum, loctesterr, lst, true, 5.1);
    InsertAtFront(loctestnum, loctesterr, lst, true, 1.0);

    Size(loctestnum, loctesterr, lst, true, 4);
    GetFront(loctestnum, loctesterr, lst, true, 1.0);
    GetBack(loctestnum, loctesterr, lst, true, 20.2);

    RemoveFromBack(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 3);
    GetBack(loctestnum, loctesterr, lst, true, 10.5);

    InsertAtBack(loctestnum, loctesterr, lst, true, 5.1);
    InsertAtBack(loctestnum, loctesterr, lst, true, 5.1);
    Size(loctestnum, loctesterr, lst, true, 5);

    Exists(loctestnum, loctesterr, lst, true, 5.1);

    lst.Clear();
    Empty(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 0);

    RemoveFromBack(loctestnum, loctesterr, lst, false);
    BackNRemove(loctestnum, loctesterr, lst, false, 0.0);

    InsertAtFront(loctestnum, loctesterr, lst, true, 42.42);
    GetFront(loctestnum, loctesterr, lst, true, 42.42);
    GetBack(loctestnum, loctesterr, lst, true, 42.42);

    lst.Clear();
    Empty(loctestnum, loctesterr, lst, true);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of List<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testListString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<string> Test:" << endl;
  try {
    lasd::List<string> lst;

    Empty(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 0);
    GetFront(loctestnum, loctesterr, lst, false, string(""));
    GetBack(loctestnum, loctesterr, lst, false, string(""));
    RemoveFromFront(loctestnum, loctesterr, lst, false);
    RemoveFromBack(loctestnum, loctesterr, lst, false);
    FrontNRemove(loctestnum, loctesterr, lst, false, string(""));
    BackNRemove(loctestnum, loctesterr, lst, false, string(""));
    Exists(loctestnum, loctesterr, lst, false, string("notfound"));

    InsertAtFront(loctestnum, loctesterr, lst, true, string("A"));
    InsertAtBack(loctestnum, loctesterr, lst, true, string("B"));
    InsertAtFront(loctestnum, loctesterr, lst, true, string("C"));
    InsertAtBack(loctestnum, loctesterr, lst, true, string("D"));
    InsertAtBack(loctestnum, loctesterr, lst, true, string("B"));
    InsertAtFront(loctestnum, loctesterr, lst, true, string("A"));

    Size(loctestnum, loctesterr, lst, true, 6);
    GetFront(loctestnum, loctesterr, lst, true, string("A"));
    GetBack(loctestnum, loctesterr, lst, true, string("B"));
    Exists(loctestnum, loctesterr, lst, true, string("B"));
    Exists(loctestnum, loctesterr, lst, true, string("A"));
    Exists(loctestnum, loctesterr, lst, false, string("Z"));

    RemoveFromFront(loctestnum, loctesterr, lst, true);
    RemoveFromBack(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 4);

    FrontNRemove(loctestnum, loctesterr, lst, true, string("C"));
    BackNRemove(loctestnum, loctesterr, lst, true, string("D"));
    FrontNRemove(loctestnum, loctesterr, lst, true, string("A"));
    BackNRemove(loctestnum, loctesterr, lst, true, string("B"));
    Empty(loctestnum, loctesterr, lst, true);

    RemoveFromFront(loctestnum, loctesterr, lst, false);
    RemoveFromBack(loctestnum, loctesterr, lst, false);

    InsertAtFront(loctestnum, loctesterr, lst, true, string("X"));
    InsertAtBack(loctestnum, loctesterr, lst, true, string("Y"));
    InsertAtBack(loctestnum, loctesterr, lst, true, string("Z"));

    GetAt(loctestnum, loctesterr, lst, true, 0, string("X"));
    GetAt(loctestnum, loctesterr, lst, true, 1, string("Y"));
    GetAt(loctestnum, loctesterr, lst, true, 2, string("Z"));
    GetAt(loctestnum, loctesterr, lst, false, 3, string(""));

    SetAt(loctestnum, loctesterr, lst, true, 1, string("YY"));
    SetFront(loctestnum, loctesterr, lst, true, string("XX"));
    SetBack(loctestnum, loctesterr, lst, true, string("ZZ"));
    GetAt(loctestnum, loctesterr, lst, true, 0, string("XX"));
    GetAt(loctestnum, loctesterr, lst, true, 1, string("YY"));
    GetAt(loctestnum, loctesterr, lst, true, 2, string("ZZ"));

    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<string>);
    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<string>);
    MapPreOrder(loctestnum, loctesterr, lst, true, [](string & str) { MapStringAppend(str, string("!")); });
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string(""), string("XX!YY!ZZ!"));
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string(""), string("ZZ!YY!XX!"));

    lasd::List<string> coplst(lst);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    MapPreOrder(loctestnum, loctesterr, coplst, true, [](string & str) { MapStringAppend(str, string("?")); });
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    lasd::List<string> movlst(move(lst));
    Size(loctestnum, loctesterr, movlst, true, 3);
    Empty(loctestnum, loctesterr, lst, true);

    movlst.Clear();
    Empty(loctestnum, loctesterr, movlst, true);
    Size(loctestnum, loctesterr, movlst, true, 0);

    InsertAtFront(loctestnum, loctesterr, movlst, true, string("front"));
    GetFront(loctestnum, loctesterr, movlst, true, string("front"));
    GetBack(loctestnum, loctesterr, movlst, true, string("front"));
    InsertAtBack(loctestnum, loctesterr, movlst, true, string("back"));
    GetBack(loctestnum, loctesterr, movlst, true, string("back"));

    movlst.Clear();
    Empty(loctestnum, loctesterr, movlst, true);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of List<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}


// Vector/List Tests

void testVectorListInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector/List<int> Test:" << endl;
  try {
    lasd::SortableVector<int> vec(5);
    SetAt(loctestnum, loctesterr, vec, true, 0, 10);
    SetAt(loctestnum, loctesterr, vec, true, 1, 20);
    SetAt(loctestnum, loctesterr, vec, true, 2, 30);
    SetAt(loctestnum, loctesterr, vec, true, 3, 40);
    SetAt(loctestnum, loctesterr, vec, true, 4, 50);

    lasd::List<int> lst;
    InsertAtBack(loctestnum, loctesterr, lst, true, 10);
    InsertAtBack(loctestnum, loctesterr, lst, true, 20);
    InsertAtBack(loctestnum, loctesterr, lst, true, 30);
    InsertAtBack(loctestnum, loctesterr, lst, true, 40);
    InsertAtBack(loctestnum, loctesterr, lst, true, 50);

    EqualLinear(loctestnum, loctesterr, vec, lst, true);

    lasd::SortableVector<int> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);

    lasd::List<int> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);

    SetAt(loctestnum, loctesterr, copvec, true, 2, 99);
    NonEqualVector(loctestnum, loctesterr, vec, copvec, true);

    InsertAtFront(loctestnum, loctesterr, lst, true, 5);
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    copvec.Resize(3);
    Size(loctestnum, loctesterr, copvec, true, 3);
    copvec.Sort();
    TraversePreOrder(loctestnum, loctesterr, copvec, true, &TraversePrint<int>);

    SetAt(loctestnum, loctesterr, copvec, false, 5, 0);
    GetAt(loctestnum, loctesterr, copvec, false, 5, 0);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector/List<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testVectorListDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of my Vector/List<double> Test:" << endl;
  try {
    lasd::SortableVector<double> vec(4);
    SetAt(loctestnum, loctesterr, vec, true, 0, 1.1);
    SetAt(loctestnum, loctesterr, vec, true, 1, 2.2);
    SetAt(loctestnum, loctesterr, vec, true, 2, 3.3);
    SetAt(loctestnum, loctesterr, vec, true, 3, 4.4);

    lasd::List<double> lst;
    InsertAtFront(loctestnum, loctesterr, lst, true, 4.4);
    InsertAtFront(loctestnum, loctesterr, lst, true, 3.3);
    InsertAtFront(loctestnum, loctesterr, lst, true, 2.2);
    InsertAtFront(loctestnum, loctesterr, lst, true, 1.1);

    EqualLinear(loctestnum, loctesterr, vec, lst, true);

    lasd::SortableVector<double> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);

    lasd::List<double> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);

    SetAt(loctestnum, loctesterr, copvec, true, 0, 9.9);
    NonEqualVector(loctestnum, loctesterr, vec, copvec, true);

    InsertAtBack(loctestnum, loctesterr, lst, true, 5.5);
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    copvec.Resize(2);
    Size(loctestnum, loctesterr, copvec, true, 2);
    copvec.Sort();
    TraversePreOrder(loctestnum, loctesterr, copvec, true, &TraversePrint<double>);

    SetAt(loctestnum, loctesterr, copvec, false, 4, 0.0);
    GetAt(loctestnum, loctesterr, copvec, false, 4, 0.0);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector/List<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void testVectorListString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector/List<string> Test:" << endl;
  try {
    // let's see if i remember greek letters
    lasd::SortableVector<string> vec(4);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("alpha"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("beta"));
    SetAt(loctestnum, loctesterr, vec, true, 2, string("gamma"));
    SetAt(loctestnum, loctesterr, vec, true, 3, string("delta"));

    lasd::List<string> lst;
    InsertAtBack(loctestnum, loctesterr, lst, true, string("alpha"));
    InsertAtBack(loctestnum, loctesterr, lst, true, string("beta"));
    InsertAtBack(loctestnum, loctesterr, lst, true, string("gamma"));
    InsertAtBack(loctestnum, loctesterr, lst, true, string("delta"));

    EqualLinear(loctestnum, loctesterr, vec, lst, true);

    lasd::SortableVector<string> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);

    lasd::List<string> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);

    SetAt(loctestnum, loctesterr, copvec, true, 1, string("epsilon"));
    NonEqualVector(loctestnum, loctesterr, vec, copvec, true);

    InsertAtFront(loctestnum, loctesterr, lst, true, string("omega"));
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    copvec.Resize(2);
    Size(loctestnum, loctesterr, copvec, true, 2);
    copvec.Sort();
    TraversePreOrder(loctestnum, loctesterr, copvec, true, &TraversePrint<string>);

    SetAt(loctestnum, loctesterr, copvec, false, 5, string(""));
    GetAt(loctestnum, loctesterr, copvec, false, 5, string(""));
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector/List<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}


// Test Functions

void testVector(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  testVectorInt(loctestnum, loctesterr);
  testVectorDouble(loctestnum, loctesterr);
  testVectorString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "Vector (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

void testList(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  testListInt(loctestnum, loctesterr);
  testListDouble(loctestnum, loctesterr);
  testListString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "List (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

void testVectorList(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    testVectorListInt(loctestnum, loctesterr);
    testVectorListDouble(loctestnum, loctesterr);
    testVectorListString(loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "Vector/List (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

void MyFullTestA(unsigned int & testnum, unsigned int & testerr){
    uint loctestnum = 0, loctesterr = 0;
    testVector(loctestnum, loctesterr);
    testList(testnum, loctesterr);
    testVectorList(testnum, testerr);

    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "My test (Vector and Lists) (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}