#pragma once

#include "db.h"

class Cluster
{
public:
    Cluster();
    Cluster(int centroidX, int centroidY);
    ~Cluster();
 
    bool pushInst(db::Point*);
    bool popInst(db::Point*);
    void clearInst() { points_.clear(); }

    int size();
    //void getCentroid(double& x, double& y);
    void getCentroid(int& x, int& y);
    void calNewCentroid();
    void setCentroid(int x, int y) { centroidX_ = x; centroidY_ = y; }

    std::vector<db::Point*> getPoints() { return points_; }

    void setColor(unsigned char r, unsigned char g, unsigned char b)
    {
        r_ = r;
        g_ = g;
        b_ = b;
    }
    unsigned char getR() { return r_; }
    unsigned char getG() { return g_; }
    unsigned char getB() { return b_; }

protected:
    //double centroidX_, centroidY_;
    int centroidX_, centroidY_;
    std::vector<db::Point*> points_;
    unsigned char r_;
    unsigned char g_;
    unsigned char b_;
    
};
