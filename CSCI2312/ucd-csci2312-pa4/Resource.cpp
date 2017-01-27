//Dalton Burke
//Resource.cpp
//PA4

#include"Resource.h"

namespace Gaming
{
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity):
        Piece(g,p),
        __capacity(capacity)
    {}

    Resource::~Resource()
    {}

    double Resource::consume()
    {
        double cons = getCapacity();
        __capacity = -1;
        finish();
        return cons;
    }

    void Resource::age()
    {
        __capacity -= RESOURCE_SPOIL_FACTOR;
        if (__capacity <= 0)
            finish();
    }

    ActionType Resource::takeTurn(const Surroundings &s) const
    { return STAY; }//resources don't move

    Piece& Resource::operator*(Piece &other)
    { return other; }

    Piece& Resource::interact(Agent *a)
    {}

    Piece& Resource::interact(Resource *)
    { return *this; }

}
