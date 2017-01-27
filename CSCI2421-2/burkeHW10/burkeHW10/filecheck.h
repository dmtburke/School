//Dalton Burke 102279938
//filecheck.h
//contains function declaration for spell checking a file

#ifndef FILECHECK_H
#define FILECHECK_H

#include "dictionary.h"
#include <string>


// Checks file for misspelled words and outputs results
void checkFile(std::string filename, dictionary dict);

// Returns word after being converted to lower case, and stripped of punctuation at the beginning and end
std::string filter(std::string w);


#endif //FILECHECK_H
