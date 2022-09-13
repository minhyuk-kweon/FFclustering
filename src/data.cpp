
#include <fstream>
#include <iostream>
#include <random>

#include "data.h"
#include "Painter.h"

using namespace std;
using namespace gui;

mydata::mydata()
{
    //std::random_device rd;
    //rdGen(rd());
    //rdGen = new mt19937(rd());
    //distrib(0, 255);
    //distrib = new uniform_int_distribution<>(0, 255);

    //cout << distrib(rdGen) << endl;
    painter_ = new Painter();
}

mydata::~mydata()
{
    delete painter_;
}

void mydata::parse(string fileName)
{
    findGridSize(fileName);

    ifstream inputFile;
    inputFile.open(fileName, ifstream::in);
    
    string line;
    getline(inputFile, line);
    int pointNum = stoi(line);

    string delimiter = " ";
    for(int i = 0; i < pointNum; i++)
    {
        getline(inputFile, line);
        string token;
        size_t pos;
        
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        int x = (int)stod(token);
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        token = line.substr(0, pos);
        int y = (int)stod(token);
	
        db::Point pt(x, y);
        pt.setID(i);
        pt.setType("terminal");
        points_.push_back(pt);
    }

    for(auto& pt : points_)
        pointMap_.emplace(pt.id(), &pt);
}

void mydata::findGridSize(string fileName)
{
    string delimiter = "_";
    string token;
    size_t pos;

    pos = fileName.find(delimiter);
    token = fileName.substr(0, pos);
    fileName.erase(0, pos + delimiter.length());

    pos = fileName.find(delimiter);
    token = fileName.substr(0, pos);
    fileName.erase(0, pos + delimiter.length());
    
    string grid = token;
    delimiter = "x";

    pos = grid.find(delimiter);
    token = grid.substr(0, pos);
    grid.erase(0, pos + delimiter.length());
    
    gridSize = stoi(token);
}

void mydata::clusterInfo()
{
    for(Cluster& cluster : clusters_)
    {
        int x, y;
        //double x, y;
        cluster.getCentroid(x, y);
        cout << "Cluster (" << x << ", " << y << ") " << cluster.size() << endl;
    }
}

void mydata::check()
{
    //for(Point pt : points_)
    //{
    //    //cout << pt.getX() << " " << pt.getY() << endl;
    //    painter_->drawPoint(pt, gui::black);
    //}

    //cout << "total " << points_.size() << endl;
    //painter_->show();
}

void mydata::savePng(int step)
{
    //random_device rd;
    //mt19937 gen(rd());
    //uniform_int_distribution<int> distrib(0, 255);

    painter_->setWindow(800, 800);
    painter_->setBackground(gridSize, gridSize);

    //file name
    string fileName = "../png/" + to_string(step) + ".png";
    
    //draw points
    for(Cluster& cluster : clusters_)
    {
        const unsigned char color[] = {cluster.getR(), cluster.getG(), cluster.getB()};
        for(Point* pt : cluster.getPoints())
            painter_->drawPoint(pt->X(), pt->Y(), color);
    }
    //draw cluster centroids
    for(Cluster& cluster : clusters_)
    {
        int x, y;
        cluster.getCentroid(x, y);
        painter_->drawCentroid(x, y, gui::black);
    }
    //save png file
    painter_->save_png(fileName);
    painter_->destroy();
}
