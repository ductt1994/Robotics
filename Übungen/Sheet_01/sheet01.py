#Import libs
import numpy as np
import matplotlib.pyplot as plot

#Robot senses object at position (-2,2)
#Vehicle coordinate system

#Transform to global coordinate system
#Global to Robot
#Rotation by +90 °
#Translation by [0,1] in global coordinate system

#Matrix product of Translation -> Rotation

#T(trans) x T(rot):
delta_x = 0
delta_y = 1
theta = np.deg2rad(90)

T = np.array([[np.cos(theta),  -np.sin(theta),    delta_x],
              [np.sin(theta),   np.cos(theta),    delta_y],
              [0,               0,                1      ]])

p1 = np.array([[2,-2,1]]).transpose()

p2 = T.dot(p1)

print(p2)
