//Main

#include <iostream>
#include "format.h"

using namespace std;

int main()
{
	size_t size;
	cout << "What would you like the width to be for your new format?" << endl;
	cin >> size;
	doIt(size);

	cout << endl << "Output sent to \"data.out\" " << endl << endl;

	return 0;
}
