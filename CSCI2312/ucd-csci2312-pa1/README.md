###ucd-csci2312-pa1

*******************************************************
	Name    :	Dalton Burke
	SID 	:	102279938  
	Class   :	CSCI - 2312 - 001
	PA#     :	1
	Due		:	2016-02-07

*******************************************************


###Read Me


####Description of the program
*******************************************************
Contains a class, and the implementation of that class, made to store a point in
 three-space. Also contains a test suite to ensure correct functioning of the class.
 The class contains functions also to determine the distance between points and to
 calculate the area of a triangle formed by three points.


####Source files
*******************************************************
Name:  area.cpp

Contains implementation of a function "computeArea" which takes three points as
 parameters and computes the area of the triangle that they make.

Name: ErrorContext.cpp

Contains implementation of class used to test the Point class

Name: ErrorContext.h

Contains definition of the class used to test the Point class

Name:  main.cpp

Contains main, which calls all of the tests for the functionality of the point class

Name:	Point.h

Contains class definition for "Point" class

Name:	Point.cpp

Contains implementation "Point" class

The point class stores an ordered triple, the coordinates for a point
in three-space. Along with standard accessors and mutators, the member function
 "distanceTo" calculates the distance to another point in three-space.

Name: PointTests.cpp

Contains functions for the tests of the point class

Name: PointTests.h

Contains function prototypes for the tests of point class


####Status of program
*******************************************************

The program runs successfully, scores 56/56.  

The program was developed, compiled and tested on Arch Linux using g++.


####How to build and run the program
*******************************************************


1. Build the program.

	Change to the directory that contains the file by:
        `cd [directory_name]`

	Compile the program by:
        `make`

2. Run the program by:
   `./ucd-csci2312-pa1`

3. Delete the obj files, executables, and core dump by
   `make clean`
