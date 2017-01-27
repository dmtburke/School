//Dalton Burke 102279938
//dictionary.cpp
//contains implimentation of dictionary class

#include "dictionary.h"
#include <string>

SNode::SNode(std::string word, SNode* next) : //constructor because it's convenient
    word(word),
    next(next)
{}

SNode::~SNode()
{
  if(next)
    delete next;
}

bool SNode::contains(std::string w)
{
  SNode* cursor = this;

  while(cursor) // check everyone in the bucket
    {
      if(w == cursor->word)
        return true;         // we found it! the word was in the dictionary
      cursor = cursor->next;
    }
  return false;
}

dictionary::dictionary(std::string filename, int __buckets)
{
  words = 0;
  buckets = __buckets;
  table = new SNode*[buckets];

  std::hash<std::string> hashFn;
  std::ifstream fin(filename);

  for(int i =0; i < buckets; i++)
      table[i] = nullptr;

  //placeholders to bring in the data
  std::string w;          //this one is to hold the input from the file
  unsigned int pos;       //this one is so that I only need compute the hash once

  while(fin >> w)
  {
    words++;
    pos = hashFn(w) % buckets; //only want to compute this once

    //add new word at the front of the linked list
    table[pos] = new SNode(w, table[pos]);
  }

  fin.close();
}

dictionary::~dictionary()
{
  //carefully deconstructing my magic castle of pointers
  for(int i = 0; i < buckets; i++)
    if(table[i])
      delete table[i];

  delete[] table;
}

int dictionary::getWords()
{
  return words;
}


bool dictionary::contains(std::string w)
{
  if(w.empty())        // This happens if we get something like '--', it comes out empty
    return false;      // and that word wouldn't be in the dictionary, so just return false here

  std::hash<std::string> hashFn;
  int pos = hashFn(w) % buckets;  // Find out which bucket the word would go in

  return table[pos]->contains(w);
}
