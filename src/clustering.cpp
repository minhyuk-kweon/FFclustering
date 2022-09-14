
#include <iostream>
#include <random>
#include <cfloat>
#include <cmath>
#include <ctime>

#include "data.h"
#include "compare.h"

using namespace std;
using namespace db;

void mydata::capKmeans(int clusterNum, int constraint)
{
    // determine K
    int dataSize = points_.size();
    int minimumNum = (dataSize % constraint == 0) ? dataSize / constraint : dataSize / constraint + 1;
    int maximumNum = max(clusterNum, minimumNum);

    if(verbose_)
    {
        cout << "DataSize: " << dataSize << endl;
        cout << "Maximum capacity: " << constraint << endl;
        cout << "Min: " << minimumNum << endl;
        cout << "Max: " << maximumNum << endl;
    }

    // initialization
    vector<Point> centroids;
    int initialGrid = ceil(sqrt(maximumNum));
    int gap = gridSize / (initialGrid + 1);

    if(verbose_)
    {
        cout << "initial grid: " << initialGrid << endl;
        cout << "gap: " << gap << endl;
    }
    
    int initGridX = 0;
    int initGridY = 0;
    int initCount = 0;
    for(int i = 0; i < initialGrid; i++)
    {
        initGridX += gap;
        for(int j = 0; j < initialGrid; j++)
        {
            initCount++;
            initGridY += gap;
            if(initCount > maximumNum)
                break;
            Point pt(initGridX, initGridY);
            centroids.push_back(pt);
        }
        initGridY = 0;
        if(initCount > maximumNum)
            break;
    }
    sort(centroids.begin(), centroids.end(), lessXYPos);

    //set color for each cluster
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(0, 255);
    for(Point& centroid_ : centroids)
    {
        Cluster cluster;
        clusters_.push_back(cluster);
        unsigned char r = (unsigned char)distrib(gen);
        unsigned char g = (unsigned char)distrib(gen);
        unsigned char b = (unsigned char)distrib(gen);
        cluster.setColor(r, g, b);
    }

    // clustering
    // if true there is no clustering solution, if false the clustering
    // solution converges.
    bool isNoSol = true;
    // if true there are not assigned cells to cluster, if false all cells are
    // assigned to the clusters.
    bool isNotAsgd = true;

    vector<Point> origCentroids = centroids;

    int count = 0;
    while(isNoSol)
    {
        clock_t start, end;
        start = clock();

        count++;
        for(Point& pt : points_)
            pt.clearFlag1();
        for(int i = 0; i < origCentroids.size(); i++)
        {
            Cluster& cluster = clusters_[i];
            Point& centroid = origCentroids[i];
            //set centroid for cluster
            cluster.setCentroid(centroid.X(), centroid.Y());
            //clear pointset for cluster
            cluster.clearInst();
        }

        isNotAsgd = true;
        //assign each point to the nearest centroid (and redefine the cluster)
        while(isNotAsgd)  
        {
            //initialize pointMap
            unordered_map<int, vector<Point*>> pointMap;
            for(int i = 0; i < clusters_.size(); i++)
            {
                vector<Point*> temp;
                pointMap.emplace(i, temp);
            }
    
            //first set trial cluster label based on minimum distance
            //then set priority of the instance (cell width) / (distance)
            for(Point& pt : points_)
            {
                if(pt.getFlag1()) continue;
                int x = pt.getX();
                int y = pt.getY();
                //int minDist = INT_MAX;
                double minDist = DBL_MAX;
                int minIdx = -1;
                for(int i = 0; i < clusters_.size(); i++)
                {
                    Cluster& cluster = clusters_[i];
                    if(cluster.size() >= constraint) continue;
                    int cx, cy;
                    //double cx, cy;
                    cluster.getCentroid(cx, cy);
                    //int distance = abs(cx - x) + abs(cy - y);
                    double distance = sqrt(abs(cx-x)*abs(cx-x) + abs(cy-y)*abs(cy-y));
                    if(distance < minDist)
                    {
                        minDist = distance;
                        minIdx = i;
                    }
                }
                if(minIdx == -1)
                    cout << "ERROR" << endl;
                if(pointMap.find(minIdx) != pointMap.end())
                {
                    double priority = 1 / (double)minDist;
                    pt.setPriority(priority);
                    pointMap.at(minIdx).push_back(&pt);
                }
            }

            //put cells into the clusters with capacity constraint
            for(int i = 0; i < clusters_.size(); i++)
            {
                //sort temp cluster by priority
                vector<Point*>& points = pointMap.at(i);
                sort(points.begin(), points.end(), greaterPriority);
                
                //put cells into clusters considering row capacity
                for(Point* pt : points)
                {
                    if(clusters_[i].size() + 1 <= constraint)
                    {
                        pt->setFlag1();
                        clusters_[i].pushInst(pt);
                    }
                }
            }
        
            //iterate while there are no assigned cells (UserFlag1 = False)
            isNotAsgd = false;
            int cnt = 0;
            for(auto pt : points_)
                if(!pt.getFlag1())
                {
                    isNotAsgd = true;
                    cnt++;
                }
        } //isNotAsgd
    
        savePng(count);

        //compute the centroid of each cluster
        vector<Point> newCentroids;
        for(Cluster& clus : clusters_)
        {
            clus.calNewCentroid();
            int x, y;
            //double x, y;
            clus.getCentroid(x, y);
            Point pt(x, y);
            newCentroids.push_back(pt);
        }
        origCentroids = newCentroids;
        sort(newCentroids.begin(), newCentroids.end(), lessXYPos);
        
        //compare old and new centroids
        if(newCentroids == centroids || count == 100) isNoSol = false;
        else centroids = newCentroids;

        end = clock();
        if(verbose_)
        {
            double time = (double)(end - start)/CLOCKS_PER_SEC;
            cout << "Loop" << count << " : " << time << endl; 
        }
    } //isNoSol
}

