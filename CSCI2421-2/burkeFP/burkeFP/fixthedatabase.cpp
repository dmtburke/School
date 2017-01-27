//Dalton Burke
//Quick fix for the database problem
//Adds zeros to the end of short IDs then saves to a new file

#include <iostream>
#include <fstream>
#include <string>

int main()
{
  std::ifstream fin("databaselarge.txt");
  std::ofstream fout("databaselarge0.txt");

  std::string bufferold = "", buffernew = "";

  while(fin.good())
    {
      std::getline(fin, buffernew);
      if(!fin.good())
        break;
      if(bufferold[0] == '|')
        while(buffernew.length() != 9)
          {
            std::cout << buffernew << std::endl;
            buffernew.push_back('0');
          }
      fout << buffernew << std::endl;

      bufferold = buffernew;
    }

  fout.close();
  fin.close();
}
