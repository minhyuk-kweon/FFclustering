
#include "cluster.h"

using namespace std;

Cluster::Cluster() { }
Cluster::Cluster(int centroidX, int centroidY)
{
    centroidX_ = centroidX;
    centroidY_ = centroidY;
}
Cluster::~Cluster() { }

bool Cluster::pushInst(db::Point* pt)
{
    points_.push_back(pt);
    return true;
}

bool Cluster::popInst(db::Point*)
{
    return true;
}

int Cluster::size() { return points_.size(); }
//void Cluster::getCentroid(double& x, double& y)
void Cluster::getCentroid(int& x, int& y)
{
    x = centroidX_;
    y = centroidY_;
}
void Cluster::calNewCentroid()
{
    int64_t sumX = 0;
    int64_t sumY = 0;
    for(db::Point* pt : points_)
    {
        sumX += pt->getX();
        sumY += pt->getY();
    }
    
    //centroidX_ = (double)sumX / size();
    //centroidY_ = (double)sumY / size();
    centroidX_ = sumX / size();
    centroidY_ = sumY / size();
}
