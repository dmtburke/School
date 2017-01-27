//csci 2421 hw 1
//member function definitions for class quadratic
//due feb 1 2016


#include <iostream>
using namespace std;
#include "quadratic.h"

quadratic::quadratic()
{
	__a = 0;
	__b = 0;
	__c = 0;
}

void quadratic::setA(double a)
{
	__a = a;
}

void quadratic::setB(double b)
{
	__b = b;
}

void quadratic::setC(double c)
{
	__c = c;
}

double quadratic::getA() const
{
	return __a;
}

double quadratic::getB() const
{
	return __b;
}

double quadratic::getC() const
{
	return __c;
}

void quadratic::setABC()
{
	cout << "Please enter the value for \"a\"" << endl;
	cin >> __a;

	cout << "Please enter the value for \"b\"" << endl;
	cin >> __b;

	cout << "Please enter the value for \"c\"" << endl;
	cin >> __c;
}

double quadratic::eval(double x) const
{
	return (__a*x + __b)*x + __c; //Just learned Horner's method in Numerical Analysis
}

void quadratic::print() const
{
	cout << __a << "*x^2 + " << __b << "*x + " << __c;
}

quadratic operator +(const quadratic& q1, const quadratic& q2)
{
	quadratic q3;
	q3.setA(q1.getA() + q2.getA());
	q3.setB(q1.getB() + q2.getB());
	q3.setC(q1.getC() + q2.getC());

	return q3;
}

quadratic operator*(double r, const quadratic& q)
{
	quadratic qnew;
	qnew.setA(r*q.getA());
	qnew.setB(r*q.getB());
	qnew.setC(r*q.getC());

	return qnew;
}
