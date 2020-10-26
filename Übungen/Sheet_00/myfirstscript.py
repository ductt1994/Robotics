import numpy as np
import matplotlib.pyplot as plt

# #Exercise 01

# def f_x(x):
#     #Calculate f(x) = cos(x) * exp(x)
#     ans = np.cos(x) * np.exp(x)
#     return(ans)

# #Exercise 02
# #Plot the function over -2*pi < x < +2*pi

# x = np.linspace((-2*np.pi), (+2*np.pi),100, endpoint=True)

# y = f_x(x)

# print(y)

# plt.plot(x,y)
# plt.ylabel('cos(x) * exp(x)')
# plt.xlabel('-2pi < x < 2pi')

# #Save as image
# plt.savefig('Ex_02.png')
# plt.show()

#Exercise 03
#a. Normal distribution
np.random.seed(0)

my = 5
sigma = 2
sz = 100000

norm_vec = np.random.normal(my,sigma,sz)

#b. Uniformal distribution
unif_vec = np.random.uniform(0,10,sz)

#c. Calc mean and standard deviation
print(np.mean(norm_vec), np.std(norm_vec))
print(np.mean(unif_vec), np.std(unif_vec))

#d. Plot data
# plt.hist()

# plt.figure()
# count, bins, ignored = plt.hist(unif_vec, 100, normed=True)
# plt.plot(bins, np.ones_like(bins)*0.1, linewidth=2, color='r')

# plt.figure()
# count, bins, ignored = plt.hist(norm_vec, 100, normed=True)
# plt.plot(bins, 1/(sigma * np.sqrt(2 * np.pi)) *
#                 np.exp( - (bins - my)**2 / (2 * sigma**2) ),
#          linewidth=2, color='r')

# plt.show()