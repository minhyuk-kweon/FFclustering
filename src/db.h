#pragma once

#include <string>
#include <vector>
#include <utility>

namespace db {

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

} //namespace
