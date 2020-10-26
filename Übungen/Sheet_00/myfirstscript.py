import numpy as np
import matplotlib.pyplot as plt

#Exercise 01

def f_x(x):
    #Calculate f(x) = cos(x) * exp(x)
    ans = np.cos(x) * np.exp(x)
    return(ans)

#Exercise 02
#Plot the function over -2*pi < x < +2*pi

x = np.linspace((-2*np.pi), (+2*np.pi),100, endpoint=True)

y = f_x(x)

print(y)

plt.plot(x,y)
plt.ylabel('cos(x) * exp(x)')
plt.xlabel('-2pi < x < 2pi')

#Save as image
plt.savefig('Ex_02.png')
plt.show()