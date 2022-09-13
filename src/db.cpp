#include "db.h"

namespace db {

using namespace std;

// Rect

Rect::Rect() { }
Rect::~Rect() { }
void Rect::init(int x1, int y1, int x2, int y2)
{
    ll_x = x1;
    ll_y = y1;
    ur_x = x2;
    ur_y = y2;
}

///// Point   

Point::Point() { }
Point::Point(int x, int y) : x_(x), y_(y) { }
Point::~Point() { }

void Point::setX(int x) {x_ = x;}
void Point::setY(int y) {y_ = y;}
void Point::setXY(int x, int y) {x_ = x; y_ = y;}
void Point::setID(int id) {id_ = id;}
void Point::setType(string type) {type_ = type;}
void Point::addAdjNode(Point* point) {adjPoints_.push_back(point);}

int Point::getX() {return x_;}
int Point::getY() {return y_;}
int Point::id() {return id_;}
string Point::getType() {return type_;}
vector<Point*> Point::getAdjPoints() {return adjPoints_;}

///// Edge

Edge::Edge() { }
Edge::Edge(int src, int tgt) : src_(src), tgt_(tgt) { }
Edge::~Edge() { }

int Edge::src() { return src_; }
int Edge::tgt() { return tgt_; }

void Edge::setLType() { ifL_ = true; }
bool Edge::ifL() { return ifL_; }


///// GCell

GCell::GCell() { }
GCell::GCell(Rect bbox) : BBox_(bbox) { }
GCell::GCell(double llx, double lly, double urx, double ury) : xMin_(llx), yMin_(lly), xMax_(urx), yMax_(ury) { }
GCell::~GCell() { }

GCell* GCell::getAncestor() { return ancestor_; }
vector<Point*> GCell::getPoints() { return points_; }
vector<GCell*> GCell::getChilds() { return childs_; }
Rect GCell::getBBox() { return BBox_; }
double GCell::getXMin() { return xMin_; }
double GCell::getYMin() { return yMin_; }
double GCell::getXMax() { return xMax_; }
double GCell::getYMax() { return yMax_; }
double GCell::dx() { return xMax_ - xMin_; }
double GCell::dy() { return yMax_ - yMin_; }
void GCell::pushPoint(Point* point) { points_.push_back(point); }
void GCell::setAncestor(GCell* gcell) { ancestor_ = gcell; }
void GCell::addChild(GCell* gcell) { childs_.push_back(gcell); }

void GCell::initCount()
{
    numBoundaryCrossings_ = numConnectedComponents_ = 0;
}
int GCell::getCrossingNum() { return numBoundaryCrossings_; }
int GCell::getCC() { return numConnectedComponents_; }
void GCell::incrCrossingNum() { numBoundaryCrossings_++; }
void GCell::incrCC() { numConnectedComponents_++; }

} //namespace
