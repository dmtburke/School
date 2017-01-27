//Dalton Burke
//DefaultAgentStrategy.cpp
//PA4

#include<vector>
#include"Game.h"
#include"DefaultAgentStrategy.h"

namespace Gaming
{
    DefaultAgentStrategy::DefaultAgentStrategy()
    {}

    DefaultAgentStrategy::~DefaultAgentStrategy()
    {}

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const
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

        if(adv.size())
            return Game::reachSurroundings(pos, Game::randomPosition(adv));
        if(food.size())
            return Game::reachSurroundings(pos, Game::randomPosition(food));
        if(empt.size())
            return Game::reachSurroundings(pos, Game::randomPosition(empt));
        if(simp.size())
            return Game::reachSurroundings(pos, Game::randomPosition(simp));
        return STAY;

    }
}
