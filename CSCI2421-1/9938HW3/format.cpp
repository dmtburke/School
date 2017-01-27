
#include <cstdlib>
#include "format.h"

using namespace std;


reformat::reformat(size_t size)
{
	__line_size = size + 3;

	__line = new char[__line_size];
}

reformat::reformat()
{
	__line_size = 0;
	__line = NULL;
}

reformat::~reformat()
{
	delete [] __line;
}


void reformat::setSize(size_t size)
{
	__line_size = size + 3;
}

size_t reformat::getSize() const
{
	return __line_size;
}

void doIt(size_t size)
{
	ifstream fin;
	fin.open("data.txt");

	ofstream fout;
	fout.open("data.out");

	reformat fmt(size);

	char ch;

	size_t i;

	while(!fin.eof())
	{
		i = 0;
		while(!fin.eof() && i < fmt.getSize() -3)
		{

			//ignore every unprintable character (except for \n and \t)
			while(!isprint(fin.peek()) && fin.peek() != '\n' && fin.peek() != '\t' && !fin.eof())
				fin.ignore();

			//take in every character, I decide when whitespace matters
			fin >> noskipws >> ch;

			//homogenize white space
			if(ch == '\t' || ch == '\n')
				ch = ' ';

			//if we are seeing whitespace right now, get rid of any white space after it
			if(ch == ' ')
				while(fin.peek() == ' ' || fin.peek() == '\n' || fin.peek() == '\t')
					fin.ignore();

			//insert character into the line
			fmt.__line[i] = ch;
			i++;
		}

		//check if a word needs to be split with '-'
		if(ch == ' ' || fin.peek() == ' ')
		{
			fmt.__line[i] = '\n';
			fmt.__line[i+1] = '\0';
		}

		//place '-' at the end since word needs to be split
		else
		{
			fmt.__line[i] = '-';
			fmt.__line[i + 1] = '\n';
			fmt.__line[i+2] = '\0';
		}

		//send to file, and show what was sent.
		fout << fmt.__line;
		cout << fmt.__line;
	}

	//close files
	fin.close();
	fout.close();
}
