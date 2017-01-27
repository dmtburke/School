//csci 2421 hw 1
//matrix class definition


#ifndef H_QUADRATIC
#define H_QUADRATIC

class quadratic
{
private:
	double __a, __b, __c; // using __ to denote the actual private member
public:
	quadratic(); //constructor sets all to 0

	//mutators
	void setA(double a);
	void setB(double b);
	void setC(double c);

	//accessors
	double getA() const; //const because I don't want these to change the private members ever
	double getB() const;
	double getC() const;

	void setABC(); //user is prompted to define all constants

	double eval(double x) const; //evaluate at given x

	void print() const; //display the function
	//side note, I thought of making this output a string to make some
	//lines of code look better later, but I decided that adding the entire string
	//library was not worth making the code look a little bit prettier
};

#endif
