//Dalton Burke

#include<iostream>
#include<fstream>

#include"Exceptions.h"
#include"Point.h"
#include"Cluster.h"
#include"KMeans.h"

namespace Clustering
{
    std::ostream &operator<<(std::ostream &os, const KMeans &kmeans);
}

using namespace Clustering;

KMeans::KMeans(unsigned int dim, unsigned int k, std::string filename, unsigned int maxIter) :
        __dimensionality(dim),
        __k(k)
{
    if(k == 0)
        throw ZeroClustersEx();

    __iFileName = filename;
    std::ifstream fin(__iFileName);
    if(filename == "" || !fin)
        throw DataFileOpenEx(__iFileName);

    __maxIter = maxIter;
    __numIter = 0;
    __numNonempty = 1;
    __numMovesLastIter = 1;

    __clusters = new Cluster*[k];
    for(unsigned int i = 0; i < k; i++)
        __clusters[i] = new Cluster(dim);
    fin >> *(__clusters[0]);//load it all into the first guy
    fin.close();//close the door behind you

    __initCentroids = new Point*[k];
    for(unsigned int i = 0; i < k; i++)
        __initCentroids[i] = new Point(__dimensionality);

    (*(__clusters[0])).pickCentroids(k, __initCentroids);


}

KMeans::~KMeans()
{
    for(unsigned int i = 0; i < __k; i++)
    {
        delete __clusters[i];
        delete __initCentroids[i];
    }
    delete[] __clusters;
    delete[] __initCentroids;
}

unsigned int KMeans::getMaxIter()
{
     return __maxIter;
}

unsigned int KMeans::getNumIters()
{
    return __numIter;
}

unsigned int KMeans::getNumNonemptyClusters()
{
     return __numNonempty;
}

unsigned int KMeans::getNumMovesLastIter()
{
    return __numMovesLastIter;
}

Cluster& KMeans::operator[](unsigned int u)
{
     return *(__clusters[u]);
}

const Cluster& KMeans::operator[](unsigned int u) const
{
    return *(__clusters[u]);
}

namespace Clustering
{
    std::ostream& operator<<(std::ostream &os, const KMeans &kmeans)
    {
         for(unsigned int i = 0; i < kmeans.__k; i++)
             os << kmeans[i];
         return os;
    }
}
void KMeans::run()
{
    unsigned int moves = 100, iter = 0, nearest = 0, nonempty = 0;
    LNode* pindex;
    while( moves > 0 && iter < __maxIter )
    {
        moves = 0;
        for(unsigned int i = 0; i < __k; i++) //looking at one cluster (i)
        {
             for(unsigned int j = 0; j < (*this)[i].getSize(); j++)//looking at one point (j) in one cluster (i)
             {
                 nearest = 0;
                 for(unsigned int k = 0; k < __k; k++)//find nearest centroid
                 {
                     if( (((*this)[i])[j]).distanceTo(*(__initCentroids[k])) < (((*this)[i])[j]).distanceTo(*(__initCentroids[nearest])))
                         nearest = k;
                 }

                 if(nearest != i)//the nearest centroid isn't in the cluster the point is currently in
                 {
                     Cluster::Move(((*this)[i])[j], (*this)[i], (*this)[nearest]).perform();//take it from i cluster and put it in "nearest" cluster
                    moves++;
                 }

             }
         nonempty = 0;
         for(unsigned int i = 0; i < __k; i++)
         {
             if(!(*this)[i].centroid.isValid())
                (*this)[i].centroid.compute();
             if((*this)[i].getSize() != 0)
                 nonempty++;
         }
         __numIter = iter;
         __numMovesLastIter = moves;
         __numNonempty = nonempty;
        }
    }
}
