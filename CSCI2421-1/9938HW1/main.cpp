//Dalton Burke

#include <iostream>
#include "quadratic.h"
using namespace std;



//prototypes for overloaded operators

quadratic operator +( const quadratic& q1, const quadratic& q2);

quadratic operator*(double r, const quadratic& q);

int main()
{
	quadratic q1, q2, q3, q4; //quadratics to be used

	cout << "Please enter the information for the first quadratic" << endl;
	q1.setABC();//set all var for q1

	cout << "I have ";
	q1.print();
	cout << " for the first quadratic." << endl; //confirm input for q1

	cout << "Please enter the information for the second quadratic" << endl;
	q2.setABC(); //set all vars for q2

	cout << "I have ";
	q2.print();
	cout << " for the second quadratic." << endl; //confirm input for q2

	cout << "We will define the third quadratic as the sum of the first two" << endl;
	q3= q1+q2;
	cout << "We have ";
	q3.print();
	cout << " for the third quadratic." << endl;

	double bf; //buffer variable to take input and send it to functions
	cout << "Please enter an \"x\" that you would like the third quadratic to be evaluated at" << endl;
	cin >> bf;
	cout << "at x = " << bf << ", " << endl;
	q3.print();
	cout << " = " << q3.eval(bf) << endl;

	cout << "We will define the fourth quadratic as a number times the third. Please input the number we will use" << endl;
	cin >> bf;
	q4 = bf * q3;
	cout << "We have ";
	q4.print();
	cout << " for the fourth quadratic." << endl;
}
