
#include <iostream>
#include <random>
#include <cfloat>
#include <cmath>
#include <ctime>

#include "data.h"
#include "compare.h"

using namespace std;
using namespace db;

/*
void mydata::kmeans(int clusterNum)
{
    //determine k with no equations, just observation
    int k = clusterNum;

    //Initialization
    int initialGap = m_rowHeight_ * floor(m_rowNum_ / k); 
    int centroid = 0;
    vector<int> centroids;
    for(int i = 0; i < k; i++)
    {
        centroids.push_back(centroid);
        centroid += initialGap;
    }

    //Clustering
    bool isNoSol = true;
    int cnt = 0;
    while(isNoSol)
    {
        cnt++;
        //Initialization
        clusters_.clear();
        for(dbInst* inst : m_minorInsts_)
            inst->clearUserFlag1();
        for(int centroid_ : centroids)
        {
            instCluster cluster(centroid_);
            clusters_.push_back(cluster);
        }
        //Find minimum distance
        for(dbInst* inst : m_minorInsts_)
        {
            int x, y;
            inst->getLocation(x,y);
            int minDist = INT_MAX;
            int bestCluster;
            for(int i = 0; i < clusters_.size(); i++)
            {
                instCluster& clus = clusters_[i];
                int distance = abs((int)clus.getCentroid() - y);
                if(distance < minDist)
                {
                    minDist = distance;
                    bestCluster = i;
                }
            }
            clusters_[bestCluster].pushInst(inst);
        }

        //compute the centroid of each cluster
        vector<int> newCentroids;
        for(instCluster& clus : clusters_)
        {
            uint newCentroid = clus.calNewCentroid(m_rowHeight_);
            newCentroids.push_back(newCentroid);
        }
        sort(newCentroids.begin(), newCentroids.end());

        //compare old and new centroids
        if(newCentroids == centroids) isNoSol = false;
        else centroids = newCentroids;
    }
}
*/

void mydata::capKmeans(int clusterNum, int constraint)
{
    // determine K
    int dataSize = points_.size();
    int minimumNum = (dataSize % constraint == 0) ? dataSize / constraint : dataSize / constraint + 1;
    int maximumNum = max(clusterNum, minimumNum);

    cout << "DataSize: " << dataSize << endl;
    cout << "Constraint: " << constraint << endl;
    cout << "Min: " << minimumNum << endl;
    cout << "Max: " << maximumNum << endl;

    // initialization
    vector<Point> centroids;
    int initialGrid = ceil(sqrt(maximumNum));
    int gap = gridSize / (initialGrid + 1);

    cout << "initial grid: " << initialGrid << endl;
    cout << "gap: " << gap << endl;
    
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
            //Cluster cluster(initGridX, initGridY);
            //clusters_.push_back(cluster);
        }
        initGridY = 0;
        if(initCount > maximumNum)
            break;
    }
    sort(centroids.begin(), centroids.end(), lessXYPos);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(0, 255);
    for(Point& centroid_ : centroids)
    {
        Cluster cluster;
        clusters_.push_back(cluster);
        //set color for cluster
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
        //cout << "LOOP" << count << ": " << endl;
        //cluster clear
        //clusters_.clear();
        for(Point& pt : points_)
            pt.clearFlag1();
        //for(Point& centroid_ : centroids)
        //{
        //    //Cluster cluster(centroid_.getX(), centroid_.getY());
        //    //clusters_.push_back(cluster);
        //}
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
                    //double priority = (double)cellWidth / (double)minDist;
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
        double time = (double)(end - start)/CLOCKS_PER_SEC;
        cout << "Loop" << count << " : " << time << endl; 
    } //isNoSol
}

/*
void rdpManager::dpKmeans(int clusterNum)
{
    sort(m_minorInsts_.begin(), m_minorInsts_.end(), lessYPos);

    int n = m_minorInsts_.size();
    int k = clusterNum;

    // n+1 x k+1 dpTable
    int64_t **dpTable = new int64_t*[n+1];
    for(int i = 0; i < n+1; i++)
        dpTable[i] = new int64_t[k+1];

    int **idxTable = new int*[n+1];
    for(int i = 0; i < n+1; i++)
        idxTable[i] = new int[k+1];

    // initialize
    for(int i = 0; i < n+1; i++)
    {
        for(int j = 0; j < k+1; j++)
        {
            dpTable[i][j] = 0;
            idxTable[i][j] = -1;
        }
    }

    // DP table calculation
    for(int i = 0; i < n+1; i++)
    {
        for(int j = 0; j < k+1; j++)
        {
            if(i <= j || j == 0)
                continue;
            if(j == 1)
            {
                int64_t value = 0;
                int64_t avg = 0;
                for(int t = 1; t <= i; t++)
                {
                    int x, y;
                    m_minorInsts_[t-1]->getLocation(x, y);
                    avg += y;
                }
                avg /= i;
                //avg = avg / (int64_t)m_rowHeight_ * (int64_t)m_rowHeight_;
                for(int t = 1; t <= i; t++)
                {
                    int x, y;
                    m_minorInsts_[t-1]->getLocation(x, y);
                    value += abs(avg - y);
                }
                dpTable[i][j] = value;
                continue;
            }
            //dp table
            vector<int64_t> queue;
            for(int s = j; s <= i; s++)
            {
                int64_t value = dpTable[s-1][j-1];
                //x_s ... x_i
                int64_t avg = 0;
                for(int t = s; t <= i; t++)
                {
                    int x, y;
                    m_minorInsts_[t-1]->getLocation(x, y);
                    avg += y;
                }
                avg /= (i-s+1);
                //avg = avg / (int64_t)m_rowHeight_ * (int64_t)m_rowHeight_;
                for(int t = s; t <= i; t++)
                {
                    int x, y;
                    m_minorInsts_[t-1]->getLocation(x, y);
                    value += abs(avg - y);
                }
                queue.push_back(value);
            }
            auto minIter = min_element(queue.begin(), queue.end());
            dpTable[i][j] = *minIter;
            idxTable[i][j] = distance(queue.begin(), minIter) + j;
        }
    }
    
    // backtracking
    vector<int> clusterElements;
    int idx = n;
    for(int i = k; i > 1; i--)
    {
        idx = idxTable[idx][i];
        clusterElements.push_back(idx);
    }

    for(auto& i : clusterElements)
    {
        cout << i << " ";
    }
    cout << endl;

    for(int i = 0; i < n+1; i++)
        delete [] dpTable[i];
    delete [] dpTable;

    // make real instance cluster based on clusterElements index vector
    idx = clusterElements.back();
    clusterElements.pop_back();
    int cnt = 1;
    for(dbInst* inst : m_minorInsts_)
    {
        // make new cluster
        if(cnt == (idx+1) || cnt == 1)
        {
            if(cnt != 1 && clusterElements.size() != 0)
            {
                idx = clusterElements.back();
                clusterElements.pop_back();
            }
            instCluster cluster;
            cluster.pushInst(inst);
            clusters_.push_back(cluster);        
        }
        // insert to exist cluster
        else
        {
            clusters_.back().pushInst(inst);
        }
        cnt++;
    }

    for(instCluster& cluster : clusters_)
        cluster.calNewCentroid(m_rowHeight_);
}
*/

