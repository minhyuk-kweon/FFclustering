# FFclustering

This code conduct capacitated k-means clustering for randomly generated points.

## Usage

This repository contains clustering source code (C++) and point generation script (python).

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
