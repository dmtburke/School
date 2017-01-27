//Dalton Burke
//dictionary.cpp
//contains implementation for "dictionary" class member functions
//burkeHW06

#include "dictionary.h"
#include <iostream>
#include <fstream>

dictionary::dictionary()
{

}

int dictionary::searchForward(list<DictEntry> &wordList, wordType findString)
{
  int counter = 1;
  //start from the front of the list and go until you see the word you want
  for(list<DictEntry>::iterator wordPtr = wordList.begin(); wordPtr != wordList.end(); wordPtr++)
  {
    if(wordPtr->getWord() == findString)
      return counter;
    counter++;
  }
  return -1;
}

int dictionary::searchBackward(std::list<DictEntry> &wordList, wordType findString)
{
  int counter = 1;
  //start from the end of the list and go until you see the word you want
  for(list<DictEntry>::reverse_iterator wordPtr = wordList.rbegin(); wordPtr != wordList.rend(); wordPtr++)
    {
      if(wordPtr->getWord() == findString)
        return counter;
      counter++;
    }

  return -1;
}


void dictionary::revPrintList(std::ostream &output, list<DictEntry> &wordList)
{
  //send each word into the ostream that we asked for, from the back to the front.
  for(list<DictEntry>::reverse_iterator wordPtr = wordList.rbegin(); wordPtr != wordList.rend(); wordPtr++)
    {
      output << wordPtr->getWord() << std::endl;
    }

}
