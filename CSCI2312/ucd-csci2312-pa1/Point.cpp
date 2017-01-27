//Implementation of Point class
#include <cmath>
#include "Point.h"


//constructors
Point::Point()
{
	__x = 0;
	__y = 0;
	__z = 0;
}

Point::Point(double x, double y, double z)
{
	__x = x;
	__y = y;
	__z = z;
}

//mutators
void Point::setX(double x)
{
	__x = x;
}

void Point::setY(double y)
{
	__y = y;
}

void Point::setZ(double z)
{
	__z = z;
}

//accessors
double Point::getX() const
{
	return __x;
}

double Point::getY() const
{
	return __y;
}

double Point::getZ() const
{
	return __z;
}

//others
double Point::distanceTo(const Point & p) const
{
	double d;
	//distance formula in 3-space
	d = std::sqrt(std::pow(this->__x - p.__x, 2)
	 		+ std::pow(this->__y - p.__y, 2)
			+ std::pow(this->__z - p.__z, 2));
	return d;
}
