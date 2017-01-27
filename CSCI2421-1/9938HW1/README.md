###9938HW1

*******************************************************
	Name    :	Dalton Burke
	SID 	:	102279938  
	Class   :	CSCI - 2421
	HW#     :	1
	Due		:	2016-02-01

*******************************************************


###Read Me


#####Description of the program
*******************************************************
Creates 4 quadratic functions based on user input. The first two from coefficients provided by user, the third is the sum of those two, and the fourth is a constant multiple of the third. Demonstrates operation overloading with class objects.



#####Source files
*******************************************************

Name:  main.cpp

Contains main

Name:	quadratic.h

Contains class definition for quadratic class

Name:	quadratic.cpp

Contains implementation quadratic class



#####Status of program
*******************************************************

The program runs successfully.  

The program was developed, compiled and tested on Arch Linux using g++


#####How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands
       `% unzip [homework_filename]`

Now you should see a directory named homework with the files:

main.cpp

makefile

README.md

quadratic.cpp

quadratic.h

2. Build the program.

	Change to the directory that contains the file by:
        `cd [directory_name]`

	Compile the program by:
        `make`

3. Run the program by:
   `./quadratic`

4. Delete the obj files, executables, and core dump by
   `make clean`
