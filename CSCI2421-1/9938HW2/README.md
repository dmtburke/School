###9938HW1

*******************************************************
	Name    :	Dalton Burke
	SID 	:	102279938  
	Class   :	CSCI - 2421
	HW#     :	2
	Due		:	2016-02-08

*******************************************************


###Read Me


#####Description of the program
*******************************************************
Creates two sets based on the "input.dat" file, the sets must be separated by a newline character.
The set is implemented in the "set" class, which can only contain one of a single number at a time.



#####Source files
*******************************************************

Name:  main.cpp

Contains main, and operations made on the two sets

Name:	set1.h

Contains class definition for set class

Name:	set1.cpp

Contains implementation set class, including overloading operators + and - for
union and set difference respectively



#####Status of program
*******************************************************

The program runs successfully.

Member function performance:

find: it loops until it finds the element. if the element isn't in the set, it takes n
loops to find that out (max n iterations)

erase: if the array has "n" elements, then erase takes exactly n iterations to finish (always n iterations)

insert: it runs find, and if it doesn't find it, it adds it in at the end. (max n iterations)

contains: runs find, and if it is found then it returns true, same as find (max n iterations)

+: runs insert n times for the first set, and m times for the second set, (n^2 + m^2 max)

-: runs insert n times for the first set, erase m times for second set, (n^2 + m^2 max)

print: prints each element to console, iterates exactly n times (always n iterations)


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

set1.cpp

set1.h

2. Build the program.

	Change to the directory that contains the file by:
        `cd [directory_name]`

	Compile the program by:
        `make`

3. Run the program by:
   `./sets`

4. Delete the obj files, executables, and core dump by
   `make clean`
