//Dalton Burke
//AggressiveAgentStrategy.cpp
//PA4

#include"Game.h"
#include"AggressiveAgentStrategy.h"

namespace Gaming
{
    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy):
        __agentEnergy(agentEnergy)
    {}

    AggressiveAgentStrategy::~AggressiveAgentStrategy()
    {}

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const
    {
        std::vector<int> simp, strat, adv, food, empt;
        Position pos(1,1);
        for(unsigned i = 0; i < 9; ++i)
            switch(s.array[i])
            {
                case SIMPLE: simp.push_back(i); break;
                case STRATEGIC: strat.push_back(i); break;
                case ADVANTAGE: adv.push_back(i); break;
                case FOOD: food.push_back(i); break;
                case EMPTY: empt.push_back(i); break;
            }
        if(simp.size() && __agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD)
            return Game::reachSurroundings(pos, Game::randomPosition(simp));
        if(adv.size())
            return Game::reachSurroundings(pos, Game::randomPosition(adv));
        if(food.size())
            return Game::reachSurroundings(pos, Game::randomPosition(food));
        return STAY;
    }

}
