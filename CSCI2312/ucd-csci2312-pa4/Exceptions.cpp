//Dalton Burke
//Exceptions.cpp
//PA4

#include"Exceptions.h"

namespace Gaming
{
    //GamingException stuff
    void GamingException::setName(std::string name)
    {
        __name = name;
    }

    std::ostream& operator<<(std::ostream &os, const GamingException &ex)
    {
        os << ex.getName() << std::endl;
        ex.__print_args(os);
        return os;
    }

    //DimensionEx stuff
    DimensionEx::DimensionEx(unsigned int expWidth, unsigned int expHeight, unsigned int width, unsigned int height):
        __exp_width(expWidth),
        __exp_height(expHeight),
        __width(width),
        __height(height)
    { setName("DimensionEx"); }

    unsigned int DimensionEx::getExpWidth() const
    { return __exp_width; }

    unsigned int DimensionEx::getExpHeight() const
    { return __exp_height; }

    unsigned int DimensionEx::getWidth() const
    { return __width; }

    unsigned int DimensionEx::getHeight() const
    { return __height; }

    //InsufficientDimensionsEx stuff
    void InsufficientDimensionsEx::__print_args(std::ostream &os) const
    {
        os << "minWidth: " << getExpWidth() << ", minHeight: " << getExpHeight() <<
            std::endl << "Width: " << getWidth() << ", Height: " << getHeight() << std::endl;
    }

    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned int minWidth, unsigned int minHeight, unsigned int width, unsigned int height):
        DimensionEx(minWidth, minHeight, width, height)
    { setName("InsufficientDimensionsEx"); }

    //OutOfBoundsEx stuff
    void OutOfBoundsEx::__print_args(std::ostream &os) const
    {
         os << "maxWidth: " << getExpWidth() << ", maxHeight: " << getExpHeight() <<
             std::endl << "Width: " << getWidth() << ", Height: " << getHeight() << std::endl;
    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height):
        DimensionEx(maxWidth, maxHeight, width, height)
    { setName("OutOfBoundsEx"); }

    //PositionEx stuff
    void PositionEx::__print_args(std::ostream &os) const
    { os << "x: " << __x << ", y: " << __y << std::endl; }

    PositionEx::PositionEx(unsigned x, unsigned y):
        __x(x),
        __y(y)
    { setName("PositionEx"); }

    //PositionNonemptyEx stuff
    PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y):
        PositionEx(x,y)
    { setName("PositionNonemptyEx"); }

    //PositionEmptyEx stuff
    PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y):
        PositionEx(x,y)
    { setName("PositionEmptyEx"); }

    //PosVectorEmptyEx stuff
    void PosVectorEmptyEx::__print_args(std::ostream &os) const
    {}

    PosVectorEmptyEx::PosVectorEmptyEx()
    { setName("PosVectorEmptyEx"); }


}
