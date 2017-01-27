//Cluster implementation


#include<fstream>
#include<sstream>
#include<algorithm>
#include"Cluster.h"
#include"Point.h"

using namespace Clustering;

LNode::LNode(const Point& p, LNodePtr n) : point(p)
{
    next = n;
}

Cluster::Cluster()
{
    __size = 0;
    __points = NULL;
}

Cluster::Cluster(const Cluster& c)
{
    __points = NULL;
    __size = 0;
    for(int i = 0; i < c.__size; i++)
        this->add(c[i]);
    for(int i = 0; i < __size; i++)
    {
    }
}

Cluster& Cluster::operator=(const Cluster& c)
{
    if(*this == c)
        return *this;

    for(int i = 0; i <= __size +1; i++)//remove all points from what it used to be
        this->remove((*this)[0]);
    for(int i = 0; i < c.__size; i++)//add in all the points from the new guy
        this->add(c[i]);

    return *this;
}

Cluster::~Cluster()
{
     LNodePtr index, keeper;
     index = __points;

     for(int i = 0; i < __size; i++)
     {
         keeper = index->next;
         delete index;
         index = keeper;
     }
}

int Cluster::getSize() const
{
     return __size;
}

void Cluster::add(const Point& p)
{
    if(this->contains(p))//don't add it if it's already here
        return void();
    if(__size==0)//if the list is empty, put p at the start
    {
        LNodePtr node;
        node = new LNode(p, NULL);
        __points = node;
    }

    else if(p <= (*this)[0])//if the point belongs at the start of the list
    {
        LNodePtr node;
        node = new LNode(p, __points);
        __points = node;
    }

    else //anywhere else
    {
        LNodePtr index = __points; //we know that it's not going to be less than the first spot
        LNodePtr back;
        while(p > index->point)
        {
             if(index->next == NULL)
                 break;
             back = index;
             index = index->next;
        }
         LNodePtr node;
        if(index->next == NULL)//end of the list
        {
             node = new LNode(p, NULL);
             index->next = node;
        }
        else
        {
             node = new LNode(p, index);
             back->next = node;
        }


    }

    ++__size;
}

const Point &Cluster::remove(const Point& p)
{
    if(this->contains(p)) //it's in the list somewhere, we have work to do
    {
        LNodePtr killer = __points; //this will be used to delete the pointers found guilty of harboring the point we are looking for
        if(p.getId() == __points->point.getId())
        {
            __points = __points->next;
            delete killer;
            __size--;
        }
        else
        {
                LNodePtr back;
             while(p.getId() != killer->point.getId())
             {
                 back = killer;
                 killer = killer->next;
             }
             back->next = killer->next;
             delete killer;
             __size--;
        }
    }//if the if statement was false, there would be nothing to do, and we would just return the input anyways
    return p;
}

bool Cluster::contains(const Point& p) const
{
     for(int i = 0; i < __size; i++)
         if(p == (*this)[i])
            return true;

     return false;
}

const Point& Cluster::operator[](unsigned int index) const
{
    LNodePtr holder;
    holder = __points;
    for(int i = 0; i < index; i++)
        holder = holder->next;
    return holder->point;
}

Cluster& Cluster::operator+=(const Point& p)
{
    this->add(p);
    return *this;
}

Cluster& Cluster::operator-=(const Point& p)
{
    this->remove(p);
    return *this;
}

Cluster& Cluster::operator+=(const Cluster& c)
{

     for(int i = 0; i < c.__size; i++)
         this->add(c[i]);
     return *this;
}

Cluster& Cluster::operator-=(const Cluster& c)
{

     for(int i = 0; i < c.__size; i++)
         this->remove(c[i]);
     return *this;
}

std::ostream& Clustering::operator<<(std::ostream& os, const Cluster& c)
{
     for(int i = 0; i < c.__size; i++)
         os << c[i];
     return os;
}

std::istream& Clustering::operator>>(std::istream& is, Cluster& c)
{
    //count the commas in each line then make a point with that numbr of dims and copy them in
    std::string str;
    while( getline(is, str))
    {
        std::stringstream ss(str);
        int dims = (int) std::count(str.begin(), str.end(), ',') + 1;
        Point * p = new Point(dims);
        ss >> *p;
        c.add(*p);
    }
    return is;
}

bool Clustering::operator==(const Cluster& c, const Cluster& d)
{
    bool eq = true;

    if(c.__size != d.__size)
        return false;
    for(int i = 0; i < d.__size; i++)
    {
        eq = eq && c.contains( d[i] ) && d.contains( c[i] );
    }

    return eq;
}

bool Clustering::operator!=(const Cluster& c, const Cluster& d)
{
    return !(c == d);
}

const Cluster Clustering::operator+(const Cluster& c, const Cluster& d)
{
     Cluster e(c);
     e+=d;
     return e;
}

const Cluster Clustering::operator-(const Cluster& c, const Cluster& d)
{
     Cluster e(c);
     e-=d;
     return e;
}


const Cluster Clustering::operator+(const Cluster& c, const Point& p)
{
     Cluster e(c);
     e += p;
     return e;
}


const Cluster Clustering::operator-(const Cluster& c, const Point& p)
{
     Cluster e(c);
     e-=p;
     return e;
}


