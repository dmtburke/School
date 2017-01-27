# 9938HW5
Dalton Burke 102279938

Homework #5, CSCI2412

This program implements a doubly linked circular list in order to solve the following problem.

A travel agent selects n customers to compete in the finals of a contest for a free world cruise. The agent places the customer in a circle and then draws a number m(1<= m <= n) from a hat. The game is played by having the agent walk clockwise and counter-clockwise around a circle, stopping at every mth contestant. At an odd turn, the agent walk clockwise, and at an even turn the agent walk counter clockwise, alternatively. The agent asks the selected person to leave the game and then continues the walk. Over time, the number of remaining contestants dwindles until only one survivor remains. The person is the winner of the world cruise.

This program was developed and tested on Gentoo GNU/Linux with GCC 4.9.3

to use:

unzip the archive, and you should see these files:

main.cpp, makefile, node1.cpp, node1.h, README.md

"make" gives you the executable "cruise", and to run it, "./cruise" 

"make clean" to delete object files and executable.
