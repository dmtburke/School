//Implementation of the Point class

#include <cmath> //for pow and sqrt
#include <cassert> //for assert()
#include <string> //for >> operator
#include "Point.h"



using namespace Clustering;


unsigned int Point::__idGen = 0;


Point::Point(int dim)
{
    __dim = dim;
    __values = new double[__dim];
    for(int i = 0; i < __dim; i++)
        __values[i] = 0;
    Point::__idGen++;
    __id = __idGen;
}

Point::Point(int dim, double* vals)
{
    __dim = dim;
    //don't know if I care, really.
}

Point::Point(const Point & p)
{
     __dim = p.__dim;
     __values = new double[__dim];
     for(int i = 0; i < __dim; i++)
        __values[i] = p.__values[i];
     __id = p.__id;
}

Point & Point::operator=(const Point& p)
{
    __dim = p.__dim;
    if(*this == p)
        return *this;

    for(int i = 0; i < __dim; i++)
        this->__values[i] = p[i];
    return *this;
}

Point::~Point()
{
     delete [] __values;
}

int Point::getId() const
{
     return __id;
}

int Point::getDims() const
{
     return __dim;
}

void Point::setValue(int pos, double value)
{
     __values[pos] = value;
}

double Point::getValue(int pos) const
{
     return __values[pos];
}

double Point::distanceTo(const Point &p) const
{
     assert(__dim == p.__dim);
     double sum = 0;
     for(int i = 0; i < __dim; i++)
          sum = sum + pow(__values[i] - p.__values[i], 2); //pythagorean theorem
     return sqrt(sum);
}

Point& Point::operator*=(double mult)
{
     for(int i = 0; i < __dim; i++)
         __values[i] = __values[i] * mult;
     return *this;
}

Point& Point::operator/=(double div)
{
    for(int i = 0; i < __dim; i++)
         __values[i] = __values[i] / div;

     return *this;
}

const Point Point::operator*(double mult) const
{
     Point p(*this);
     p *= mult;
     return p;
}

const Point Point::operator/(double div) const
{
     Point p(*this);
     p /= div;
     return p;
}

double& Point::operator[](int index)
{
     return __values[index];
}

const double& Point::operator[](int index) const
{
     return __values[index];
}

Point& Clustering::operator+=(Point& p1, const Point& p2)
{
     assert(p1.__dim == p2.__dim);

     for(int i = 0; i < p1.__dim; i++)
     {
        p1[i] = p1[i] + p2[i];
     }
     return p1;
}

Point& Clustering::operator-=(Point& p1, const Point& p2)
{
     assert(p1.getDims() == p2.getDims());

     for(int i = 0; i < p1.getDims(); i++)
         p1[i] = p1[i] - p2[i];
     return p1;
}

const Point Clustering::operator+(const Point& p, const Point& q)
{
    Point r(p);
    r += q;
    return r;
}

const Point Clustering::operator-(const Point& p, const Point& q)
{
     Point r(p);
     r -= q;
     return r;
}

bool Clustering::operator<(const Point& lhs, const Point& rhs)
{
    bool less = false;
    for(int i = 0; i < lhs.getDims(); i++)
        if(lhs[i]!=rhs[i])
        {
            if(lhs[i] < rhs[i])
                return true;
            else
                return false;
        }
    return false;
}

bool Clustering::operator>(const Point& lhs, const Point& rhs)
{
    return rhs < lhs;
}

bool Clustering::operator>=(const Point& lhs, const Point& rhs)
{
     return !(lhs < rhs);
}

bool Clustering::operator<=(const Point& lhs, const Point& rhs)
{
     return !(rhs < lhs);
}

bool Clustering::operator!=(const Point& lhs, const Point& rhs)
{
     return (lhs < rhs || rhs < lhs || rhs.__id != lhs.__id);
}

bool Clustering::operator==(const Point& lhs, const Point& rhs)
{
     return !(rhs!=lhs);
}

std::ostream& Clustering::operator<<(std::ostream& os, const Point& p)
{

    for(int i = 0; i < p.getDims() -1; i++)
        os << p[i] << ',' << ' ';
    os << p[p.getDims()-1] << std::endl;

    return os;

}

std::istream & Clustering::operator>>(std::istream& is, Point& p)
{
     std::string s;
     for(int i = 0; i < p.__dim; i++)
     {
         std::getline(is, s, ',');
         p[i] = std::stod(s);
     }
     return is;
}


