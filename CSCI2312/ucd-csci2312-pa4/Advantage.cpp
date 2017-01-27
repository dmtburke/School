//Dalton Burke
//Advantage.cpp
//PA4

#include<iomanip>
#include"Advantage.h"

namespace Gaming
{
    const char Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity):
        Resource(g,p,capacity)
    {}

    Advantage::~Advantage()
    {}

    void Advantage::print(std::ostream &os) const
    { os  << ADVANTAGE_ID << std::left <<std::left <<  std::setw(4) << __id << std::setw(0); }

    double Advantage::getCapacity() const
    { return __capacity * ADVANTAGE_MULT_FACTOR; }

    double Advantage::consume()
    {
        double cons = getCapacity();
        __capacity = -1;
        finish();
        return cons;
    }

}
