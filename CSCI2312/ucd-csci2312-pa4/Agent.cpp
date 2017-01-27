//Agent.cpp
//Dalton Burke
//PA4

#include"Food.h"
#include"Advantage.h"
#include"Agent.h"

namespace Gaming
{
    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) :
        Piece(g,p),
        __energy(energy)
    {}

    Agent::~Agent()
    {}

    void Agent::age()
    { __energy -= AGENT_FATIGUE_RATE; }

    Piece& Agent::operator*(Piece &other)
    {
        if(dynamic_cast<Resource*>(&other))
            interact(dynamic_cast<Resource*>(&other));
        else
            interact(dynamic_cast<Agent*>(&other));

        if(!isFinished())
            setPosition(other.getPosition());

        return *this;

    }

    Piece& Agent::interact(Agent *enemy)
    {
        if(__energy >= enemy->__energy)
            enemy->finish();
        if (__energy <= enemy->__energy)
            finish();
        return *this;
    }

    Piece& Agent::interact(Resource *res)
    {
        __energy += res->consume();
        return *this;
    }

}
