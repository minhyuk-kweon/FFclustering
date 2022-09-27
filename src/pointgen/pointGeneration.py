import numpy as np
import random
import os

def point_generate(low, high, num, width):
    L = []
    for k in range(num):
        n = random.randint(low, high)
        S = np.zeros((n,2))
        for i in range(n):
            p = random.random()
            point = np.floor(np.random.uniform(0, width, size=(1, 2)))
            S[i] = point
        L.append(S)
    return L

def point_in_obstacle(pt, obstacles):
    pt_x = pt[0]
    pt_y = pt[1]
    for obs in obstacles:
        obs_llx = obs[0]
        obs_lly = obs[1]
        obs_urx = obs[2]
        obs_ury = obs[3]
        if obs_llx <= pt_x and pt_x <= obs_urx and \
           obs_lly <= pt_y and pt_y <= obs_ury:
            return True
    return False

def point_generate_with_obstacle(width, ptNum, obsNum):
    # obstacles (llx, lly, urx, ury)
    O = np.zeros((obsNum, 4))
    for n in range(obsNum):
        #lower left point
        ll = np.floor(np.random.uniform(0, width, size=(1, 2)))
        #width and height
        wh = np.floor(np.random.uniform(0, width/4, size=(1, 2)))
        #upper right point
        ur = ll + wh
        for i in range(ur.shape[0]):
            for j in range(ur.shape[1]):
                ur[i][j] = max(0, min(width, ur[i][j]))
        points = np.hstack((ll, ur))
        O[n] = points

    # random points (x, y)
    S = np.zeros((ptNum,2))
    for n in range(ptNum):
        pt = np.floor(np.random.uniform(0, width, size=(1, 2)))
        while point_in_obstacle(pt[0], O):
            pt = np.floor(np.random.uniform(0, width, size=(1, 2)))
        S[n] = pt

    return S, O

def generate_file(filePath, points, obstacles):
    wfile = open(filePath, 'w')
    num_str = "%d\n" % (len(obstacles)) 
    wfile.write(num_str)
    for obs in obstacles:
        obs_str = "%d %d %d %d\n" % (obs[0], obs[1], obs[2], obs[3])
        wfile.write(obs_str)
    num_str = "%d\n" % (len(points)) 
    wfile.write(num_str)
    for point in points:
        point_str = "%d %d\n" % (point[0], point[1])
        wfile.write(point_str)
    wfile.close()
    return

points, obstacles = point_generate_with_obstacle(100, 10, 2)
generate_file("./test.pt", points, obstacles)
