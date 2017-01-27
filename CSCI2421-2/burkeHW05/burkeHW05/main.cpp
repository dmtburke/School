//Dalton Burke
//main.cpp
//contains testing for StringOfNodes class
//burkeHW05 CSCI2421

#include <iostream>
#include "StringOfNodes.h"

using namespace burke;

int main()
{
  StringOfNodes str1;

//Testing insert functions
  std::cout << "str1 = \'" << str1 << '\'' <<  std::endl;

  str1.insertBack('l');
  std::cout << "str1.insertBack('l'):\t" << str1 << std::endl;

  str1.insertFront('e');
  std::cout << "str1.insertFront('e'):\t" << str1 << std::endl;

  str1.insert('F', -1);
  std::cout << "str1.insert('F', -1):\t" << str1 << std::endl;

  str1.insert('l', 1);
  std::cout << "str1.insert('l', 1):\t" << str1 << std::endl;

  str1.insert('o', 3);
  std::cout << "str1.insert('o', 3):\t" << str1 << std::endl;

  str1.insert('&', 5);
  std::cout << "str1.insert('&', 5):\t" << str1 << std::endl;

  str1.insert('H', 0);
  std::cout << "str1.insert('H', 0):\t" << str1 << std::endl;

  std::cout << "str1 = \'" << str1 << '\'' <<  std::endl << std::endl;

  StringOfNodes str2;
  str2.insertBack(' ');

  StringOfNodes str3;
  str3.insertBack('W');
  str3.insertBack('o');
  str3.insertBack('r');
  str3.insertBack('l');
  str3.insertBack('d');
  str3.insertBack('!');

//Testing size()
  std::cout << "Size of str1 = " << str1.size() << std::endl << std::endl;

//Testing addition
  std::cout << "str1 = 'Hello' , str2 = ' ' , str3 = 'World!'" << std::endl;
  std::cout << "str1 + str2 + str3 = '" << str1 + str2 + str3 << '\'' << std::endl << std::endl;

//Testing subscript
  for(int i = 0; i < str3.size(); i++)
    std::cout << "data at str3[" << i << "] = " << str3[i]->__data << std::endl;

}
