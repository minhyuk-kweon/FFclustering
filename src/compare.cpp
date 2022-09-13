
#include "compare.h"

using namespace std;
using namespace db;

bool greaterPriority(Point* a, Point* b)
{
    double aPriority = a->getPriority();
    double bPriority = b->getPriority();
    return aPriority > bPriority;
}

bool lessXYPos(Point& a, Point& b)
{
    if(a.getX() == b.getX())
        return a.getY() < b.getY();
    return a.getX() < b.getX();
}
