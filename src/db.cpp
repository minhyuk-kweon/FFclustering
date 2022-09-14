#include "db.h"

namespace db {

using namespace std;

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

} //namespace
