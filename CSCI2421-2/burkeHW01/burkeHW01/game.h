#include <iostream>
#include <vector>

struct number
{
  //this is to keep track of the number itself
  int num;
  //this is to keep track if this number has been counted
  bool used;
};

class Game
{
 public:
  int __size;
  int __max;
  number* __guess;
  number* __actual;
  //constructor, destructor. each game will depend on size and max, n and m
  Game(int size, int max);
  ~Game();
  //these functions give values to the arrays used for the game
  void inputGuess();
  void generateActual();
  //outputResult() tells the user how many they got correct, play will loop until this is true
  bool outputResult();
  //assess() determines the number of correct guesses
  int assess();
  //play drives the game
  void play();
};
