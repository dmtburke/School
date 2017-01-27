//

#include <cmath>
#include "Point.h"

double computeArea(const Point &a, const Point &b, const Point &c);

double computeArea(const Point &a, const Point &b, const Point &c)
{
	double x = a.distanceTo(b);
	double y = b.distanceTo(c);
	double z = c.distanceTo(a);

	double area;

	//Heron's formula
	area = 0.25*(std::sqrt((x + y + z)*(-x + y + z)*(x - y + z)*(x + y - z)));

	return area;
}
