//main

#include <iostream>
#include <fstream>
#include "set1.h"

using namespace main_savitch_3;
using std::cout;
using std::endl;


int main()
{
	cout << "Reading sets in from file..." << endl << endl <<  endl;

	set a, b, c, d, e;


	std::ifstream filein;
	filein.open("input.dat");

	int bfr;
	while(true)
	{
		filein >> bfr;
		a.insert(bfr);
		if(filein.peek() == '\n' || filein.eof())
			break;
	}

	while(true)
	{
		filein >> bfr;
		b.insert(bfr);
		if(filein.peek() == '\n' || filein.eof())
			break;
	}

	filein.close();


	cout << "First set from file, call it \'A\':" << endl;
	a.print();
	cout << endl << endl;

	cout << "Second set from file, call it \'B\':" << endl;
	b.print();
	cout << endl << endl;

	c = a + b;

	cout << "The union of A and B:" << endl;
	c.print();
	cout << endl << endl;

	d = a - b;

	cout << "A - B:" << endl;
	d.print();
	cout << endl << endl;

	e = b - a;

	cout << "B - A:" << endl;
	e.print();
	cout << endl << endl;

	return 0;
}
