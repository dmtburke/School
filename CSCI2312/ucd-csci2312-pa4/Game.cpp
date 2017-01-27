//Dalton Burke
//Game.cpp
//PA4

#include<iomanip>

#include"Exceptions.h"
#include"Game.h"
#include"Simple.h"
#include"Strategic.h"
#include"Food.h"
#include"Advantage.h"


namespace Gaming
{
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;

    PositionRandomizer Game::__posRandomizer = PositionRandomizer();

    const unsigned Game::MIN_WIDTH = 3, Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    void Game::populate() //save for later
    {
        int __numInitAgents = (__width * __height )/NUM_INIT_AGENT_FACTOR;
        int __numInitResources = (__width * __height)/NUM_INIT_RESOURCE_FACTOR;
        unsigned numStrategic = __numInitAgents/2;
        unsigned numSimple = __numInitAgents - numStrategic;
        unsigned numAdvantages = __numInitResources/4;
        unsigned numFoods = __numInitResources - numAdvantages;

        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height -1);

        //Populate Strategics
        while(numStrategic > 0)
        {
            int i = d(gen);
            if(__grid[i] == NULL)
            {
                 Position pos(i / __width, i % __width);
                 __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                 numStrategic--;
            }
        }

        //Populate Simples
        while(numSimple > 0)
        {
            int i = d(gen);
            if(__grid[i] == NULL)
            {
                 Position pos(i / __width, i % __width);
                 __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                 numSimple--;
            }
        }

        //Populate Advantages
        while(numAdvantages > 0)
        {
            int i = d(gen);
            if(__grid[i] == NULL)
            {
                 Position pos(i / __width, i % __width);
                 __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                 numAdvantages--;
            }
        }

        //Populate Foods
        while(numFoods > 0)
        {
            int i = d(gen);
            if(__grid[i] == NULL)
            {
                 Position pos(i / __width, i % __width);
                 __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                 numFoods--;
            }
        }
    }

    Game::Game():
        __width(Game::MIN_WIDTH),
        __height(Game::MIN_HEIGHT),
        __status(NOT_STARTED),
        __verbose(false),
        __round(0)
    {
        for(unsigned int i = 0; i < __width*__height; i++)
            __grid.push_back(NULL);
    }

    Game::Game(unsigned int width, unsigned int height, bool manual):
        __width(width),
        __height(height),
        __status(NOT_STARTED),
        __verbose(false),
        __round(0)
    {
         if(height < Game::MIN_HEIGHT || width < Game::MIN_WIDTH)
             throw InsufficientDimensionsEx(Game::MIN_WIDTH, Game::MIN_HEIGHT, width, height);

         for(unsigned int i = 0; i < width*height; i++)
             __grid.push_back(NULL);

         if(!manual)
             populate();
    }

    Game::~Game()
    {
        for(auto rm = __grid.begin(); rm != __grid.end(); ++rm)
            if(*rm != NULL)
                delete *rm;
    }


    unsigned int Game::getNumPieces() const
    {
        unsigned int num = 0;
        for(auto ctr = __grid.begin(); ctr != __grid.end(); ctr++)
            if(*ctr != NULL)
                num++;
        return num;
    }

    unsigned int Game::getNumAgents() const
    {
         unsigned int num = 0;
         for(auto ctr = __grid.begin(); ctr != __grid.end(); ctr++)
         {
             Agent* test = dynamic_cast<Agent*>(*ctr);
             if(test)
                 num++;
         }
         return num;
    }

    unsigned int Game::getNumSimple() const
    {
         unsigned int num = 0;
         for(auto ctr = __grid.begin(); ctr != __grid.end(); ctr++)
         {
             Simple* test = dynamic_cast<Simple*>(*ctr);
             if(test)
                 num++;
         }
         return num;
    }

    unsigned int Game::getNumStrategic() const
    {
         unsigned int num = 0;
         for(auto ctr = __grid.begin(); ctr != __grid.end(); ++ctr)
         {
             Strategic* test = dynamic_cast<Strategic*>(*ctr);
             if(test)
                 num++;
         }
         return num;
    }

    unsigned int Game::getNumResources() const
    {
         unsigned int num = 0;
         for(auto ctr = __grid.begin(); ctr != __grid.end(); ++ctr)
         {
             Resource* test = dynamic_cast<Resource*>(*ctr);
             if(test)
                 num++;
         }
         return num;
    }

    const Piece* Game::getPiece(unsigned int x, unsigned int y) const
    {
         if(__width <= y || __height <= x)
             throw OutOfBoundsEx(__height, __width, x, y);

         unsigned int index = __width*x + y;

         if(__grid[index] == NULL)
             throw PositionEmptyEx(x,y);

         return __grid[index];
    }

    void Game::addSimple(const Position &position)
    {
         if(__width <= position.y || __height <= position.x)
             throw OutOfBoundsEx(__height, __width, position.x, position.y);

         unsigned int index = position.x * __width + position.y;

         if(__grid[index] != NULL)
             throw PositionNonemptyEx(position.x, position.y);

         __grid[index] = new Simple(*this, position, Game::STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(const Position &position, double energy)
    {
         if(__width <= position.y || __height <= position.x)
             throw OutOfBoundsEx(__height, __width, position.x, position.y);

         unsigned int index = position.x * __width + position.y;

         if(__grid[index] != NULL)
             throw PositionNonemptyEx(position.x, position.y);

         __grid[index] = new Simple(*this, position, energy);
    }

    void Game::addSimple(unsigned int x, unsigned int y)
    {
         if(__width <= y || __height <= x)
             throw OutOfBoundsEx(__height, __width, x, y);

         unsigned int index = x * __width + y;

         if(__grid[index] != NULL)
             throw PositionNonemptyEx(x, y);

         Position position;
         position.x = x;
         position.y = y;

         __grid[index] = new Simple(*this, position, Game::STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(unsigned int x, unsigned int y, double energy)
    {
         if(__width <= y || __height <= x)
             throw OutOfBoundsEx(__height, __width, x, y);

         unsigned int index = x * __width + y;

         if(__grid[index] != NULL)
             throw PositionNonemptyEx(x, y);

         Position position;
         position.x = x;
         position.y = y;

         __grid[index] = new Simple(*this, position, energy);

    }

    void Game::addStrategic(const Position &p, Strategy *s)
    {
         if(__width <= p.y || __height <= p.x)
             throw OutOfBoundsEx(__height, __width, p.x, p.y);

         unsigned int index = p.x * __width + p.y;

         if(__grid[index] != NULL)
             throw PositionNonemptyEx(p.x, p.y);

         __grid[index] = new Strategic(*this, p, Game::STARTING_AGENT_ENERGY, s);
    }

    void Game::addStrategic(unsigned int x, unsigned int y, Strategy *s)
    {
         if(__width <= y || __height <= x)
             throw OutOfBoundsEx(__height, __width, x, y);

         unsigned int index = x * __width + y;

         if(__grid[index] != NULL)
             throw PositionNonemptyEx(x, y);

         Position position;
         position.x = x;
         position.y = y;

         __grid[index] = new Strategic(*this, position, Game::STARTING_AGENT_ENERGY, s);
    }

    void Game::addFood(const Position &p)
    {
        if(__width <= p.y || __height <= p.x)
             throw OutOfBoundsEx(__height, __width, p.x, p.y);

         unsigned int index = p.x * __width + p.y;

         if(__grid[index] != NULL)
             throw PositionNonemptyEx(p.x, p.y);

         __grid[index] = new Food(*this, p, Game::STARTING_RESOURCE_CAPACITY);
    }


    void Game::addFood(unsigned int x, unsigned int y)
    {
        if(__width <= y || __height <= x)
             throw OutOfBoundsEx(__height, __width, x, y);

         unsigned int index = x * __width + y;

         if(__grid[index] != NULL)
             throw PositionNonemptyEx(x, y);

         Position position;
         position.x = x;
         position.y = y;

         __grid[index] = new Food(*this, position, Game::STARTING_RESOURCE_CAPACITY);
    }


    void Game::addAdvantage(const Position &p)
    {
        if(__width <= p.y || __height <= p.x)
             throw OutOfBoundsEx(__height, __width, p.x, p.y);

         unsigned int index = p.x * __width + p.y;

         if(__grid[index] != NULL)
             throw PositionNonemptyEx(p.x, p.y);

         __grid[index] = new Advantage(*this, p, Game::STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(unsigned x, unsigned y)
    {
        if(__width <= y || __height <= x)
             throw OutOfBoundsEx(__height, __width, x, y);

         unsigned index = x * __width + y;

         if(__grid[index] != NULL)
             throw PositionNonemptyEx(x, y);

         Position position;
         position.x = x;
         position.y = y;

         __grid[index] = new Advantage(*this, position, Game::STARTING_RESOURCE_CAPACITY);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings s;
        int x = pos.x, y = pos.y;

        for(int i = 0; i < 9; ++i)
            s.array[i] = EMPTY;
        for(int row = -1; row < 2; row++)
            for(int col = -1; col < 2; col++)
            {
                if(x + row < 0 || x + row >=  __height || y + col < 0 || y + col >= __width)
                    s.array[col + 3*row + 4] = INACCESSIBLE;
                else if(__grid[y + col + __width*(x + row)])
                    s.array[col + 3*row + 4] = __grid[y + col + __width*(x + row)]->getType();
            }

        s.array[4] = SELF;
        return s;
    }

    //static stuff
    const ActionType Game::reachSurroundings(const Position &from, const Position &to)
    {
        int x = to.x - from.x, y = to.y - from.y;

        if(x == -1 && y == -1)
            return NW;
        if(x == -1 && y == 0)
            return N;
        if(x == -1 && y == 1)
            return NE;
        if(x == 0 && y == -1)
            return W;
        if(x == 0 && y == 1)
            return E;
        if(x == 1 && y == -1)
            return SW;
        if(x == 1 && y == 0)
            return S;
        if(x == 1 && y == 1)
            return SE;
        return STAY;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const
    {
        int x = pos.x, y = pos.y;

        switch(ac)
        { //each case is the position in the surroundings array, checking to see if the moves leave you inside of the __grid
            case NW: x--; y--; break;
            case N: x--; break;
            case NE: x--; y++; break;
            case W: y--; break;
            case STAY: return true; //ac == STAY, totally cool
            case E: y++; break;
            case SW: x++; y--; break;
            case S: x++; break;
            case SE: x++; y++; break;
        }
        return (x >= 0 && x < __height && y >= 0 && y < __width);
    }

    const Position Game::move(const Position &pos, const ActionType &ac) const
    {
        if(!isLegal(ac, pos))
            return pos;
        int x = pos.x, y = pos.y;
        switch(ac)
        { //each case is the position in the surroundings array, and since it has to be valid, we will move
            case NW: x--; y--; break;
            case N: x--; break;
            case NE: x--; y++; break;
            case W: y--; break;
            case STAY: return pos; //don't change the position
            case E: y++; break;
            case SW: x++; y--; break;
            case S: x++; break;
            case SE: x++; y++; break;
        }
        return Position(x,y);
    }

    void Game::round()
    {
         __status = PLAYING;
         for(int i = 0; i < __grid.size(); ++i)
             if(__grid[i] != NULL && !(__grid[i]->getTurned()))
             {
                 __grid[i]->setTurned(true);
                 ActionType ac = __grid[i]->takeTurn(getSurroundings(__grid[i]->getPosition()));

                 if(ac == STAY)
                     continue;

                 Position moved = move(__grid[i]->getPosition(), ac);
                 int j = moved.x * __width + moved.y;
                 if(__grid[j] != NULL)
                 {
                     __grid[i]->operator*(*__grid[j]);
                     if(__grid[i]->isViable())
                     {
                          delete __grid[j];
                          __grid[j] = __grid[i];
                          __grid[i]->setPosition(moved);
                          __grid[i] = NULL;
                     }
                     else if(__grid[j]->isViable())
                     {
                         delete __grid[i];
                         __grid[i] = NULL;
                     }
                     else
                     {
                          delete __grid[i];
                          delete __grid[j];
                          __grid[i] = NULL;
                          __grid[j] = NULL;
                     }
                 }
                 else
                 {
                      __grid[i]->setPosition(moved);
                      __grid[j] = __grid[i];
                      __grid[i] = NULL;
                 }
             }

         for(int i = 0; i < __grid.size(); ++i)
            if(__grid[i] != NULL)
            {
                __grid[i]->setTurned(false);
                __grid[i]->age();
                if(!__grid[i]->isViable())
                {
                    delete __grid[i];
                    __grid[i] = NULL;
                }
            }
         __round++;
    }


    void Game::play(bool verbose)
    {
        __status = PLAYING;
        if(verbose)
        {
             __verbose = true;
             while(getNumResources())
             {
                 std::cout << *this << std::endl;
                 round();
             }
            __status = OVER;
            std::cout << *this << std::endl;
        }
        else
        {
            while(getNumResources())
                round();
            __status = OVER;
        }
    }

    std::ostream& operator<<(std::ostream &os, const Game &game)
    {
        os << "Round " << game.__round << std::endl;
        int i = 0;
        for(auto ctr = game.__grid.begin(); ctr != game.__grid.end(); ++ctr)
        {
            os << '[';
            if(!*ctr)
                os << "     ";
            else
                os << **ctr;
            os << ']';
            i++;
            if(i == game.__width)
            {
                os << std::endl;
                i = 0;
            }

        }
         os  << "Status: ";

         switch(game.__status)
         {
             case(Game::Status::NOT_STARTED): os << "Not Started"; break;
             case(Game::Status::PLAYING): os << "Playing..."; break;
             case(Game::Status::OVER): os << "Over!"; break;
         }
         return os;
    }


}
