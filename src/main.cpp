
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

#include "Painter.h"
#include "data.h"

using namespace std;
using namespace gui;

int main(int argc, char *argv[])
{
    bool isGui = false;
    string inputFileName;

    if(argc > 1)
    {
        inputFileName = string(argv[1]);
        if(argc > 2)
            if(string(argv[2]) == "gui")
                isGui = true;
    }
    else
    {
        cout << "Error: Invalid input arguments" << endl;
        cout << "   ./SteinerTree <fileName> <gui>" << endl;
        return 0;
    }

    mydata D;
    D.parse(inputFileName);
    
    D.capKmeans(169, 30);
    D.clusterInfo();

    D.check();
    
    return 0;
}
