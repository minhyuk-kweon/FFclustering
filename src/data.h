#pragma once

#include <string>
#include <random>

#include "db.h"
#include "cluster.h"
#include "painter.h"

class mydata
{
public:
    mydata();
    mydata(bool verbose);
    ~mydata();

    void parse(std::string fileName);

    void clusterInfo();

    void capKmeans(int clusterNum, int constraint);

    void savePng(int step);

private:
    bool verbose_;

    gui::Painter* painter_;

    int gridSize;
    std::vector<db::Point> points_;
    std::unordered_map<int, db::Point*> pointMap_;
    std::vector<Cluster> clusters_;

    void findGridSize(std::string fileName);
};
