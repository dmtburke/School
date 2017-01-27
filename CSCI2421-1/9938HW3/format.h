//class to read in an unformatted text and reformat it by column width
#ifndef REFORMAT
#define REFORMAT

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;


class reformat
{
private:
	char * __line;
	size_t __line_size;
public:
	reformat();
	reformat(size_t);
	~reformat();

	void setSize(size_t);

	size_t getSize() const;

	//doIt does it. (rereformats data and sends it to new file pass the size of the new column
	friend void doIt(size_t);

};

void doIt(size_t);

#endif //REFORMAT
