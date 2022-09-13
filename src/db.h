#pragma once

#define S_SHAPE 0
#define L_SHAPE 1


#include <string>
#include <vector>
#include <utility>

namespace db {

class Rect
{
public:
    Rect();
    ~Rect();
    
    void init(int x1, int y1, int x2, int y2);
    int xMin() { return ll_x; }
    int yMin() { return ll_y; }
    int xMax() { return ur_x; }
    int yMax() { return ur_y; }
    uint dx() { return (uint)(ur_x - ll_x); }
    uint dy() { return (uint)(ur_y - ll_y); }

protected:
    int ll_x, ll_y, ur_x, ur_y;

};

class Point
{
public:
    Point();
    Point(int, int);
    ~Point();
    
    void setX(int);
    void setY(int);
    void setXY(int, int);
    void setID(int);
    void setType(std::string);
    void addAdjNode(Point*);

    int getX();
    int getY();
    int id();
    std::string getType();
    std::vector<Point*> getAdjPoints();

    double getPriority() { return priority_; }
    void setPriority(double priority) { priority_ = priority; }

    bool getFlag1() { return flag1_; }
    void setFlag1() { flag1_ = true; }
    void clearFlag1() { flag1_ = false; }

    //operator overloading ==
    friend bool operator==(const Point& lhs, const Point& rhs)
    {
        return (lhs.X() == rhs.X()) && (lhs.Y() == rhs.Y());    
    }
    int X() const {return x_;}
    int Y() const {return y_;}

protected:
    int id_;
    int x_, y_;
    std::string type_; //terminal or steiner
    std::vector<Point*> adjPoints_;

    double priority_;
    bool flag1_;
};


class Edge
{
public:
    Edge();
    Edge(int, int);
    ~Edge();
    
    int src();
    int tgt();

	void setLType();
	bool ifL();

protected:
	bool ifL_ = false;
    int src_, tgt_;

};

class GCell
{
public:
    GCell();
    GCell(Rect bbox);
    GCell(double llx, double lly, double urx, double ury);
    ~GCell();

    GCell* getAncestor();
    Rect getBBox();
    double getXMin();
    double getYMin();
    double getXMax();
    double getYMax();
    double dx();
    double dy();
    std::vector<Point*> getPoints();
    std::vector<GCell*> getChilds();

    void pushPoint(Point*);
    void setAncestor(GCell*);
    void addChild(GCell*);

    void initCount();
    int getCrossingNum();
    int getCC();
    void incrCrossingNum();
    void incrCC();

protected:
    GCell* ancestor_;
    Rect BBox_;
    double xMin_;
    double yMin_;
    double xMax_;
    double yMax_;

    std::vector<Point*> points_;
    std::vector<GCell*> childs_;

    int numBoundaryCrossings_;
    int numConnectedComponents_;

};

} //namespace
