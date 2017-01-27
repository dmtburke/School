#include <iostream>
#include "game.h"

int main()
{
  int n, m;
  char yn;
  while(true)
  {
    std::cout << "Amount of numbers to guess: ";
    std::cin >> n;
    std::cout << "Generate " << n << " numbers from 1 to ";
    std::cin >> m;

    Game g(n,m);
    g.play();
    std::cout << "Play again? (y/n): ";
    std::cin >> yn;
    if(yn == 'n')
      break;
  }

  std::cout << "Goodbye!" << std::endl;
}
