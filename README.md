# FFclustering

This code conduct capacitated k-means clustering for randomly generated points.
Cmake is needed to build the executive, and numpy is needed for point generation.

## Usage

This repository contains clustering source code (C++) and point generation script (Python).

### Clustering (C++)
Clone the repository and conduct below commands to build and make binary file.
```
mkdir build
cd build
cmake ..
make
```
To execute, input file is needed. We provide several example files (FFclustering/points) and random point generation script (FFclustering/src/pointgen).

```
./ffclustering -f <input file>
```

There are other nonessential options.
```
-n <cluster num>      : Number of clusters
-c <maximum capacity> : Maximum capacity of each cluster
-v                    : verbose
```

### Point generation (Python)
The name of input file should be point<num>_<grid>x<grid>_<id>.pt , where <num> is number of points, <grid> is the size of region where points are located, <id> is the identical number of the .pt file. All points are generated with uniform distribution within the grid range.
```
cd src/pointgen
python main.py -n <num> -g <grid>
```
