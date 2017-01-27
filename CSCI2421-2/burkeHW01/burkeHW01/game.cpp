#include "game.h"
#include <stdlib.h>
#include <time.h>

Game::Game(int size, int max)
{
  __size = size;
  __max = max;
  __guess = new number[__size];
  __actual = new number[__size];
  for(int i = 0; i < __size; i++)
    {
      __guess[i].used = false;
      __actual[i].used = false;
    }
}

Game::~Game()
{
  delete[] __guess;
  delete[] __actual;
}

void Game::inputGuess()
{
  std::cout << "Please input " << __size << " guesses from 1 to " << __max << std::endl;
  for( int i = 0; i < __size; i++)
    std::cin >> __guess[i].num;
}

void Game::generateActual()
{
  std::srand(time(NULL));
  for(int i = 0; i < __size; i++)
  //generate a random number less than the max defined by the user
    __actual[i].num = 1 + (std::rand() % __max);
}

bool Game::outputResult()
{
  int correct = assess();
  if( correct == __size )
  {
    std::cout << "You are correct! ";
    return true;
  }

  std::cout << correct << " of your guesses are correct. ";
  return false;
}

int Game::assess()
{
  //the number of correct guesses
  int correct = 0;

  for(int i = 0; i < __size; i++)
    for(int j = 0; j < __size; j++)
      //if the guessed number and the actual number aren't used, and if they are equal,
      //mark them as used, and increment the number of correct guesses, then break to the next
      if( !__actual[i].used && !__guess[j].used && __actual[i].num == __guess[j].num )
      {
        __actual[i].used = true;
        __guess[j].used = true;
        correct++;
        break;
      }

  //reset the used flags to false for the next time;
  for(int i = 0; i < __size; i++)
  {
    __actual[i].used = false;
    __guess[i].used = false;
  }

  return correct;
}

void Game::play()
{
  //determine the random numbers
  generateActual();

  bool correct = false;

  //loop until the user gets all of the numbers correct
  //outputResult returns true if all numbers were correct
  while(true)
  {
    inputGuess();
    correct = outputResult();
    if(correct)
      break;
    std::cout << "Guess again." << std::endl;
  }
}



