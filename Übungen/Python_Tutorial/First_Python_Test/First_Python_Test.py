import numpy as np
import math
import matplotlib.pyplot as plt

def cos_exp(x):
    return(math.cos(x)*math.exp(x))

#######################################
min = 2 * (-np.pi)
max = 2 * (+np.pi)

#Create 50 elements
pi_vals = np.linspace(min, max, 50)
x_vals = pi_vals
#Reshape 1D-array into 50 rows and 1 col
x_vals = x_vals.reshape(-1,1)
#Create corresponding y-values
num_elems = len(x_vals)

y_vals = np.zeros((num_elems,1))
e_vals = np.zeros((num_elems,1))

idx = 0

for elem in x_vals:
    y_vals[idx] = cos_exp(elem)
    e_vals[idx] = math.exp(elem)
    idx = idx + 1

plt.plot(x_vals,y_vals)
plt.plot(x_vals,e_vals)
#plt.plot(pi_vals)

plt.show()