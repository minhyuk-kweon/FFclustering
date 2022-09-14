
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <unistd.h>

#include "painter.h"
#include "data.h"

using namespace std;
using namespace gui;

int main(int argc, char *argv[])
{
    string inputFileName;
    int clusterNum = 169;
    int capacity = 30;
    bool verbose = false;

    int opt;
    while((opt = getopt(argc, argv, ":f:n:c:v")) != -1)
    {
        switch(opt)
        {
            case 'f':
                inputFileName = string(optarg);
                break;
            case 'n':
                clusterNum = atoi(optarg);
                break;
            case 'c':
                capacity = atoi(optarg);
                break;
            case 'v':
                verbose = true;
                break;
            case '?':
                cout << "unknown option: " << char(optopt) << endl;
                break;
        }
    }

    //Argument summary
    if(!inputFileName.empty())
        cout << "Input File: " << inputFileName << endl;
    else
        cout << "ERROR: no input file" << endl;
    cout << "Perform capacitated k means clustering" << endl;
    cout << "    Cluster number " << clusterNum << " with maximum capacity " << capacity << endl;

    mydata D(verbose);
    D.parse(inputFileName);
    D.capKmeans(clusterNum, capacity);
    D.clusterInfo();

    return 0;
}
