#pragma once

#include <string>
#include <random>

#include "db.h"
#include "cluster.h"
#include "Painter.h"

class mydata
{
public:
    mydata();
    ~mydata();

    void parse(std::string fileName);

    void check();
    void clusterInfo();

    void kmeans(int clusterNum);
    void capKmeans(int clusterNum, int constraint);
    void dpKmeans(int clusterNum);

    void savePng(int step);

private:
    //std::mt19937 rdGen;
    //std::uniform_int_distribution<> distrib;

    gui::Painter* painter_;

    int gridSize;
    std::vector<db::Point> points_;
    std::unordered_map<int, db::Point*> pointMap_;

    std::vector<Cluster> clusters_;

    std::vector<std::vector<unsigned char>> colors_;

    void findGridSize(std::string fileName);
};
