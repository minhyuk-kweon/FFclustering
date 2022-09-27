
import os
import argparse
import pointGeneration as pg

parser = argparse.ArgumentParser()
parser.add_argument("-n", "--pointNum", type=int, default=100, help="number of points")
parser.add_argument("-b", "--blockNum", type=int, default=5, help="number of obstacles (blocks)")
parser.add_argument("-g", "--gridSize", type=int, default=100, help="range of the points 0 ~ gridSize")
args = parser.parse_args()
    
pointFilePath = "../../points"

if not os.path.exists(pointFilePath):
    os.makedirs(pointFilePath)

for root, dirs, files in os.walk(pointFilePath):
    fileNumList = []
    for name in files:
        if(name[:5] == "point"):
            tokens = name.split("_")
            if(tokens[0][5:] == str(args.pointNum)):
                if(tokens[1].split("x")[0] == str(args.gridSize)):
                    fileNum = int(tokens[2].split(".")[0])
                    fileNumList.append(fileNum)

if(len(fileNumList) == 0):
    fileNum = 1
else:
    fileNum = max(fileNumList) + 1
fileName = "point" + str(args.pointNum) + "_" + str(args.gridSize) + "x" + str(args.gridSize) + "_" + str(fileNum) + ".pt"
fileName = os.path.join(pointFilePath, fileName)

## random number of points [low, high]
#low = high = args.pointNum
## number of point set
#num = 1
## grid size
#width = args.gridSize
#pointset = pg.point_generate(low, high, num, width)

pointset, obstacleset = pg.point_generate_with_obstacle(args.gridSize, args.pointNum, args.blockNum)
pg.generate_file(fileName, pointset, obstacleset)
