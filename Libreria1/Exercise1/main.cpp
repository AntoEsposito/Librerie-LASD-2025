
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() 
{
  std::cout << "Hello! Welcome to my LASD libraries (2024/2025)" << std::endl;
  std::cout << "Student: Antonio Esposito, N86005375." << std::endl;
  while (true)
  {
    std::cout << "Press 1 to run the Professor's tests, or 2 to run my tests." << std::endl;
    std::cout << "Press any other key to exit." << std::endl;
    char choice;
    std::cin >> choice;

    if (choice == '1') lasdtest();
    else if (choice == '2') mytest();
    else break;
  }
  std::cout << "Thank you for using my libraries!" << std::endl;
  return 0;
}
