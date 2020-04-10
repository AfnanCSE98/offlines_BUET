# -*- coding: utf-8 -*-
"""
Created on Thu Jul 25 11:28:52 2019

@author: Sihat Afnan
"""

import matplotlib.pyplot as plt
import numpy as np
import numpy.linalg as LA
import numpy.random

file_handle=open("data.txt" , "r")


file_handle.seek(0)
lines_list = file_handle.readlines()

my_data = [[float(val) for val in line.split()] for line in lines_list[0:]]
num_lines = len(my_data)
#print(num_lines)
A=[]
B=[]

x_list = [row[0] for row in my_data]
y_list = [row[1] for row in my_data]

sum_x = sum(x_list)
sum_y = sum(y_list)
sum_x2 = sum(i**2 for i in x_list)
sum_x3 = sum(i**3 for i in x_list)
sum_x4 = sum(i**4 for i in x_list)
sum_x5 = sum(i**5 for i in x_list)
sum_x6 = sum(i**6 for i in x_list)
sum_xy = sum(i*j for i,j in zip(x_list , y_list))
sum_x2y = sum((i**2)*j for i,j in zip(x_list , y_list))
sum_x3y = sum((i**3)*j for i,j in zip(x_list , y_list))
y_avg = sum_y/num_lines;
st = sum((i - y_avg)**2 for i in y_list)

"""first order"""
A=[[num_lines , sum_x] , [sum_x , sum_x2]]
B=[sum_y,sum_xy]
solution = LA.solve(A , B)

sr = sum((i - solution[0] - solution[1]*j)**2 for i,j in zip( y_list , x_list))
rc = ((st-sr)/st)**(1/2)

print("First Order :")
print("\t",end='')
for i in range(len(solution)):
    print("a"+str(i)+":",end=" ")
    print(solution[i])
    print("\t",end='')
print("Regression Coefficient : "+ str(rc))
x1=np.arange(12)
y1 = solution[0] + x1*solution[1]

"""second order"""
A.clear()
B.clear()

A=[[num_lines , sum_x , sum_x2] , [sum_x , sum_x2 , sum_x3] , [sum_x2 , sum_x3 , sum_x4]]
B=[sum_y , sum_xy , sum_x2y]
solution = LA.solve(A , B)

sr = sum((i - solution[0] - solution[1]*j - solution[2]*j**2)**2 for i,j in zip( y_list , x_list))
rc = ((st-sr)/st)**(1/2)

print("Second Order :")
print("\t",end='')
for i in range(len(solution)):
    print("a"+str(i)+":",end=" ")
    print(solution[i])
    print("\t",end='')
print("Regression Coefficient : "+ str(rc))
x2=np.arange(12)
y2 = solution[0] + x2*solution[1] + solution[2]*(x2**2)


"""third order"""
A.clear()
B.clear()

A=[[num_lines , sum_x , sum_x2 , sum_x3] , [sum_x , sum_x2 , sum_x3 , sum_x4] , [sum_x2 , sum_x3 , sum_x4 , sum_x5] , [sum_x3 , sum_x4 , sum_x5 , sum_x6]]
B = [sum_y , sum_xy , sum_x2y , sum_x3y]
solution = LA.solve(A , B)
sr = sum((i - solution[0] - solution[1]*j - solution[2]*j**2 - solution[3]*j**3)**2 for i,j in zip( y_list , x_list))
rc = ((st-sr)/st)**(1/2)

print("Third Order :")
print("\t",end='')
for i in range(len(solution)):
    print("a"+str(i)+":",end=" ")
    print(solution[i])
    print("\t",end='')
print("Regression Coefficient : "+ str(rc))
x3=np.arange(12)
y3 = solution[0] + x3*solution[1] + solution[2]*(x3**2) + solution[3]*(x3**3)


plt.figure(figsize=(12,5))
plt.scatter(x_list , y_list , s=1,c='#B533FF')
plt.plot(x1,y1,label="1st Order")
plt.plot(x2,y2,label="2nd Order")
plt.plot(x3,y3, label="3rd Order")
plt.legend()

