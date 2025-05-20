#include "test.hpp"
#include "myvectorlist.cpp"
#include "myset.cpp"

/* ************************************************************************** */

#include <iostream>

using namespace std;

/* ************************************************************************** */

void mytest() 
{
  cout << endl << "~*~#~*~ Welcome to my LASD Test Suite ~*~#~*~ " << endl;

  uint loctestnum, loctesterr;
  uint stestnum = 0, stesterr = 0;

  loctestnum = 0; loctesterr = 0;
  MyFullTestA(loctestnum, loctesterr);
  stestnum += loctestnum; stesterr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  // MyFullTestB(loctestnum, loctesterr);
  stestnum += loctestnum; stesterr += loctesterr;

  cout << endl << "MyTest (Errors/Tests: " << stesterr << "/" << stestnum << ")";

  cout << endl << "Goodbye!" << endl;
}
