#!/usr/bin/python
import os
import MDAnalysis
import MDAnalysis.coordinates

import matplotlib as mpl
mpl.use('Agg')
import mpl_toolkits.mplot3d
from mpl_toolkits.mplot3d import Axes3D
import math
import numpy as np
import pylab

import matplotlib.pyplot as plt

import pickle as pl
from operator import itemgetter
import scipy.stats




def read_coord(frame):
    f="ub_0_stride10.dcd"

    u=MDAnalysis.coordinates.reader(f)
    print(u)

    i=0
    for timestep in u[:]:
      i=i+1
      #print("i is")
      #print(i)
      #print("frame is")
      #print(frame)
      if int(i)==int(frame):
        #for i in range(1,len(u)+1):
        #print(np.size(u))   
        #print("THIS IS THE TIMESTEP")
        #print(timestep)
        walk=[]
        for j in range(1,76+1,1):
            if j==1: 
               k1=timestep[1]
               v=[]
               v.append(k1[0]) #k1[3*l+1][0])
               v.append(k1[1]) #data[k][0][3*l+1][1])
               v.append(k1[2]) #data[k][0][3*l+1][2])
               walk.append(v)
           
               for u in range(1,17+1,1):
                   k1=timestep[4+(u-1)*5+2-1]
                   v=[]
                   v.append(k1[0]) #k1[3*l+1][0])
                   v.append(k1[1]) #data[k][0][3*l+1][1])
                   v.append(k1[2]) #data[k][0][3*l+1][2])
                   walk.append(v)
            if j==19:
               k1=timestep[(4+17*5)+1]
               v=[]
               v.append(k1[0]) #k1[3*l+1][0])
               v.append(k1[1]) #data[k][0][3*l+1][1])
               v.append(k1[2]) #data[k][0][3*l+1][2])
               walk.append(v)
               for u in range(1,17+1,1):
                   k1=timestep[93+(u-1)*5+2-1]
                   v=[]
                   v.append(k1[0]) #k1[3*l+1][0])
                   v.append(k1[1]) #data[k][0][3*l+1][1])
                   v.append(k1[2]) #data[k][0][3*l+1][2])
                   walk.append(v)
            if j==37:
               k1=timestep[(4+24*5+4)+1]
               v=[]
               v.append(k1[0]) #k1[3*l+1][0])
               v.append(k1[1]) #data[k][0][3*l+1][1])
               v.append(k1[2]) #data[k][0][3*l+1][2])
               walk.append(v)
            if j==38:
               k1=timestep[(4+24*5+2*4)+1]
               v=[]
               v.append(k1[0]) #k1[3*l+1][0])
               v.append(k1[1]) #data[k][0][3*l+1][1])
               v.append(k1[2]) #data[k][0][3*l+1][2])
               walk.append(v)
               for u in range(1,36+1,1):
                   k1=timestep[186+(u-1)*5+2-1]
                   v=[]
                   v.append(k1[0]) #k1[3*l+1][0])
                   v.append(k1[1]) #data[k][0][3*l+1][1])
                   v.append(k1[2]) #data[k][0][3*l+1][2])
                   walk.append(v)
            if j==75:
               k1=timestep[(4+60*5+3*4)+1]
               v=[]
               v.append(k1[0]) #k1[3*l+1][0])
               v.append(k1[1]) #data[k][0][3*l+1][1])
               v.append(k1[2]) #data[k][0][3*l+1][2])
               walk.append(v)
               k1=timestep[372-1]
               v=[]
               v.append(k1[0]) #k1[3*l+1][0])
               v.append(k1[1]) #data[k][0][3*l+1][1])
               v.append(k1[2]) #data[k][0][3*l+1][2])
               walk.append(v)
      else:
         d=0
         auxwalk=[]  
    return walk



for i in range(1,9701): 
        
        protein = read_coord(i) 
        #protein has the CA atoms of ubiquitin at tilmestep I
        #you can use this protein to calculate the local topological free energy

        
