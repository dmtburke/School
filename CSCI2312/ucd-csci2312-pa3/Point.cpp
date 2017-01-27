//Implementation of the Point class

#include <cmath> //for pow and sqrt
#include <cassert> //for assert()
#include <string> //for >> operator
#include <algorithm>
#include <sstream>

#include "Point.h"
#include "Exceptions.h"


using namespace Clustering;


unsigned int Point::__idGen = 0;

const char Point::POINT_VALUE_DELIM = ',';

Clustering::Point::Point(unsigned int dim)
{
    if(dim <= 0)
        throw ZeroDimensionsEx();
    __dim = dim;
    __values = new double[__dim];
    for(unsigned int i = 0; i < __dim; i++)
        __values[i] = 0;
    Point::__idGen++;
    __id = __idGen;
}

Point::Point(unsigned int dim, double* vals)
{
    __dim = dim;
    //don't know if I care, really.
}

Point::Point(const Point & p)
{
     __dim = p.__dim;
     __values = new double[__dim];
     for(unsigned int i = 0; i < __dim; i++)
        __values[i] = p.__values[i];
     __id = p.__id;
}

void Point::rewindIdGen()
{
    __idGen--;
}

Point & Point::operator=(const Point& p)
{
    if(__dim != p.__dim)
        throw DimensionalityMismatchEx(__dim, p.__dim);
    __id = p.__id;
    if(*this == p)
        return *this;

    for(unsigned int i = 0; i < __dim; i++)
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

unsigned int Point::getDims() const
{
     return __dim;
}

void Point::setValue(unsigned int pos, double value)
{
    if(pos >= __dim || pos < 0)
        throw OutOfBoundsEx(__dim, pos);
     __values[pos] = value;
}

double Point::getValue(unsigned int pos) const
{
    if(pos >= __dim || pos < 0)
        throw OutOfBoundsEx(__dim, pos);
     return __values[pos];
}

double Point::distanceTo(const Point &p) const
{
    if(p.__dim != __dim)
        throw DimensionalityMismatchEx(__dim, p.__dim);
    double sum = 0;
     for(unsigned int i = 0; i < __dim; i++)
          sum = sum + pow(__values[i] - p.__values[i], 2); //pythagorean theorem
     return sqrt(sum);
}

Point& Point::operator*=(double mult)
{
     for(unsigned int i = 0; i < __dim; i++)
         __values[i] = __values[i] * mult;
     return *this;
}

Point& Point::operator/=(double div)
{
    for(unsigned int i = 0; i < __dim; i++)
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

double& Point::operator[](unsigned int index)
{
    if( index >= __dim || index < 0)
        throw OutOfBoundsEx(__dim, index);
     return __values[index];
}

const double& Point::operator[](unsigned int index) const
{
    if(index > __dim)
        throw OutOfBoundsEx(__dim, index);
     return __values[index];
}

namespace Clustering //friends
{
    Point& operator+=(Point& p1, const Point& p2)
    {
        if( p1.__dim != p2.__dim )
            throw DimensionalityMismatchEx(p1.__dim, p2.__dim);

         for(unsigned int i = 0; i < p1.__dim; i++)
         {
            p1[i] = p1[i] + p2[i];
         }
         return p1;
    }

    Point& operator-=(Point& p1, const Point& p2)
    {
        if(p1.__dim != p2.__dim)
            throw DimensionalityMismatchEx(p1.__dim, p2.__dim);

         for(unsigned int i = 0; i < p1.getDims(); i++)
             p1[i] = p1[i] - p2[i];
         return p1;
    }

    const Point operator+(const Point& p, const Point& q)
    {
        Point r(p);
        r += q;
        return r;
    }

    const Point operator-(const Point& p, const Point& q)
    {
         Point r(p);
         r -= q;
         return r;
    }

    bool operator<(const Point& lhs, const Point& rhs)
    {
        if(lhs.__dim != rhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim, rhs.__dim);

        for(unsigned int i = 0; i < lhs.getDims(); i++)
            if(lhs[i] != rhs[i])
                return lhs[i] < rhs[i];
        return false;
    }

    bool operator>(const Point& lhs, const Point& rhs)
    {
        return rhs < lhs;
    }

    bool operator>=(const Point& lhs, const Point& rhs)
    {
         return !(lhs < rhs);
    }

    bool operator<=(const Point& lhs, const Point& rhs)
    {
         return !(rhs < lhs);
    }

    bool operator!=(const Point& lhs, const Point& rhs)
    {
         return !(rhs==lhs);
    }

    bool operator==(const Point& lhs, const Point& rhs)
    {
         if(lhs.__dim != rhs.__dim)
             throw DimensionalityMismatchEx(lhs.__dim, rhs.__dim);
         for(unsigned int i = 0; i < lhs.__dim; i++)
             if(lhs[i] != rhs[i])
                 return false;
         return lhs.__id == rhs.__id;
    }

    std::ostream& operator<<(std::ostream& os, const Point& p)
    {

        for(unsigned int i = 0; i < p.getDims() -1; i++)
            os << p[i] << Point::POINT_VALUE_DELIM << ' ';
        os << p[p.getDims()-1];

        return os;

    }

    std::istream & operator>>(std::istream& is, Point& p)
    {
         std::string input;
         std::getline(is, input, ':');
         unsigned int dims = (unsigned int) std::count(input.begin(), input.end(), Point::POINT_VALUE_DELIM) + 1;
         if(p.__dim != dims)
             throw DimensionalityMismatchEx(p.__dim, dims);

         std::stringstream ss(input);

         std::string str;
         for(unsigned int i = 0; i < p.__dim; i++)
         {
             std::getline(ss, str, Point::POINT_VALUE_DELIM);
             p[i] = std::stod(str);
         }
         return is;
    }
}



