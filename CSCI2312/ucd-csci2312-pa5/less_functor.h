//Dalton Burke
//less_functor.h

#ifndef PA5_LESS_FUNCTOR_H
#define PA5_LESS_FUNCTOR_H

#include<cstring>

namespace CS2312
{
    template <typename T>
    class less
    {
    public:
        bool operator()(const T &lhs, const T &rhs)
        { return (lhs < rhs); }
    };

    template<>
    class less<std::string>
    {
    public:
        bool operator() (const std::string &lhs, const std::string &rhs)
        { return (lhs < rhs);}
    };

    template<>
    class less<const char*>
    {
    public:
        bool operator() (const char* lhs, const char* rhs)
        { return (strcmp(lhs,rhs) < 0); }
    };
}

#endif //PA5_LESS_FUNCTOR_H
