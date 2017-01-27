//Dalton Burke
//main.cpp
//Driver functions to show functionality of the "Set" class
//CSCI 2421 HW 2

#include <iostream>
#include "ArrayBag.h"
#include "SetFunctions.h"

int main()
{

  Set set1, set2;

  std::ifstream fin("setInput.txt");

  //Bring the first two lines of the file to the sets
  set1.fileIn(fin);
  set2.fileIn(fin);

  fin.close();

  //print it all out
  std::cout << "Set 1:" << std::endl;
  std::cout << set1 << std::endl << std::endl;
  std::cout << "Set 2:" << std::endl;
  std::cout << set2 << std::endl << std::endl;
  std::cout << "Set 1 - Set 2:" << std::endl;
  std::cout << set1 - set2 << std::endl << std::endl;
  std::cout << "Set 2 - Set 1:" << std::endl;
  std::cout << set2 - set1 << std::endl << std::endl;
  std::cout << "Set 1 + Set 2:" << std::endl;
  std::cout << set1 + set2 << std::endl << std::endl;
}
