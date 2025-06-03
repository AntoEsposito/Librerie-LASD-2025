#include "test.hpp"
#include "myvectorlist.cpp"
#include "myset.cpp"
#include "myheap.cpp"
#include "mypqheap.cpp"

/* ************************************************************************** */

#include <iostream>

using namespace std;

/* ************************************************************************** */

namespace mylasdtest {
void mytest() 
{
  cout << endl << "~*~#~*~ Welcome to my LASD Test Suite! ~*~#~*~ " << endl;

  uint loctestnum, loctesterr;
  uint stestnum = 0, stesterr = 0;

  loctestnum = 0; loctesterr = 0;
  MyFullTest1A(loctestnum, loctesterr);
  stestnum += loctestnum; stesterr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  MyFullTest1B(loctestnum, loctesterr);
  stestnum += loctestnum; stesterr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  MyFullTest2A(loctestnum, loctesterr);
  stestnum += loctestnum; stesterr += loctesterr;

  // loctestnum = 0; loctesterr = 0;
  // MyFullTest2B(loctestnum, loctesterr);
  // stestnum += loctestnum; stesterr += loctesterr;

  cout << endl << "MyTest (Errors/Tests: " << stesterr << "/" << stestnum << ")";

  cout << endl << "Goodbye!" << endl;
}
}
