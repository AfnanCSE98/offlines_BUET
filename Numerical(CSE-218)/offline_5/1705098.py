# -*- coding: utf-8 -*-
"""
Created on Thu Aug 29 11:22:21 2019

@author: Sihat Afnan
"""
from math import sin, radians
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np


class myFloat( float ):
    def __str__(self):
        return "%.5f"%self 

def func( x, y ): 
    return (x+20*y)*(sin((x*y)))
def x_list(h):
    x=[]
    val=0;
    x.append(val)
    while val<10:
        val = myFloat(val + h)
        x.append(val)
    return x

def euler(x,y,h,xmax):
    y_list=[]
    y_list.append(y)
    while x < xmax:
        y = myFloat(y + h * func(x,y))
        #print(x)
        y_list.append(y)
        x = myFloat(x+h)
    return y_list

x1=x_list(0.01)
y1=euler(0,4,0.01,10)
plt.plot(x1,y1,label="step size = 0.01")

x2=x_list(0.05)
y2=euler(0,4,0.05,10)
plt.plot(x2,y2,label="step size = 0.05")

x3=x_list(0.1)
y3=euler(0,4,0.1,10)
plt.plot(x3,y3,label="step size = 0.1")

x4=x_list(0.5)
y4=euler(0,4,0.5,10)
plt.plot(x4,y4,label="step size = 0.5")

plt.legend()
plt.title("Euler's Method")
plt.show()

def RK_2ndorder_general(x,y,h,xmax,a2):
    a1=1-a2
    p = 1/(2*a2)
    q = 1/(2*a2)
    
   
    
    y_list=[]
    y_list.append(y)
    while x < xmax:
        k1 = func(x , y)
        k2 = func(x + p*h , y + q*k1*h)
        y = y + h*(a1*k1 + a2*k2)
        y_list.append(y)
        x = x + h
    return y_list
"""heun"""
x = x_list(0.01)
y = RK_2ndorder_general(0,4,0.01,10,0.5)
plt.plot(x,y,label="step size = 0.01")

x = x_list(0.05)
y = RK_2ndorder_general(0,4,0.05,10,0.5)
plt.plot(x,y,label="step size = 0.05")

x = x_list(0.1)
y = RK_2ndorder_general(0,4,0.1,10,0.5)
plt.plot(x,y,label="step size = 0.1")

x = x_list(0.5)
y = RK_2ndorder_general(0,4,0.5,10,0.5)
plt.plot(x,y,label="step size = 0.5")

plt.legend()
plt.title("heun's Method")
plt.show()

"""Midpoint method"""

x = x_list(0.01)
y = RK_2ndorder_general(0,4,0.01,10,1)
plt.plot(x,y,label="step size = 0.01")

x = x_list(0.05)
y = RK_2ndorder_general(0,4,0.05,10,1)
plt.plot(x,y,label="step size = 0.05")

x = x_list(0.1)
y = RK_2ndorder_general(0,4,0.1,10,1)
plt.plot(x,y,label="step size = 0.1")

x = x_list(0.5)
y = RK_2ndorder_general(0,4,0.5,10,1)
plt.plot(x,y,label="step size = 0.5")

plt.legend()
plt.title("Midpoint Method")
plt.show()

"""Ralston's Method"""

x = x_list(0.01)
y = RK_2ndorder_general(0,4,0.01,10,(2/3))
plt.plot(x,y,label="step size = 0.01")

x = x_list(0.05)
y = RK_2ndorder_general(0,4,0.05,10,(2/3))
plt.plot(x,y,label="step size = 0.05")

x = x_list(0.1)
y = RK_2ndorder_general(0,4,0.1,10,(2/3))
plt.plot(x,y,label="step size = 0.1")

x = x_list(0.5)
y = RK_2ndorder_general(0,4,0.5,10,(2/3))
plt.plot(x,y,label="step size = 0.5")

plt.legend()
plt.title("Ralston's Method")
plt.show()

def RK_4thOrder(x,y,h,xmax):
    
    y_list=[]
    y_list.append(y)
    while x < xmax:
        k1 = func(x , y)
        k2 = func(x +0.5*h, y + 0.5*k1*h)
        k3 = func(x + 0.5*h , y + 0.5*k2*h)
        k4 = func(x+h , y+k3*h)
        y = y + h*(k1 + 2*k2 + 2*k3 + k4)*(1/6)
        y_list.append(y)
        x = x + h
    return y_list

"""rk4"""
x = x_list(0.01)
y = RK_4thOrder(0,4,0.01 , 10)
plt.plot(x,y,label="step size = 0.01")

x = x_list(0.05)
y = RK_4thOrder(0,4,0.05 , 10)
plt.plot(x,y,label="step size = 0.05")

x = x_list(0.1)
y = RK_4thOrder(0,4,0.1 , 10)
plt.plot(x,y,label="step size = 0.1")

x = x_list(0.5)
y = RK_4thOrder(0,4,0.5 , 10)
plt.plot(x,y,label="step size = 0.5")

plt.legend()
plt.title("Range Kutta Method 4th Order")
plt.show()

"""Now for step size 0.01"""

x1=x_list(0.01)
y1=euler(0,4,0.01,10)
plt.plot(x1,y1,label="Euler's Method")

x = x_list(0.01)
y = RK_2ndorder_general(0,4,0.01,10,0.5)
plt.plot(x,y,label="Heun's Method")

x = x_list(0.01)
y = RK_2ndorder_general(0,4,0.01,10,1)
plt.plot(x,y,label="Midpoint Method")

x = x_list(0.01)
y = RK_2ndorder_general(0,4,0.01,10,(2/3))
plt.plot(x,y,label="Ralston's Method")

x = x_list(0.01)
y = RK_4thOrder(0,4,0.01 , 10)
plt.plot(x,y,label="Range Kutta(4th Order)")

plt.legend()
plt.title("step size = 0.01")
plt.show()


"""Now for step size 0.05"""

x1=x_list(0.05)
y1=euler(0,4,0.05,10)
plt.plot(x1,y1,label="Euler's Method")

x = x_list(0.05)
y = RK_2ndorder_general(0,4,0.05,10,0.5)
plt.plot(x,y,label="Heun's Method")

x = x_list(0.05)
y = RK_2ndorder_general(0,4,0.05,10,1)
plt.plot(x,y,label="Midpoint Method")

x = x_list(0.05)
y = RK_2ndorder_general(0,4,0.05,10,(2/3))
plt.plot(x,y,label="Ralston's Method")

x = x_list(0.05)
y = RK_4thOrder(0,4,0.05 , 10)
plt.plot(x,y,label="Range Kutta(4th Order)")

plt.legend()
plt.title("step size = 0.05")
plt.show()



"""Now for step size 0.1"""

x1=x_list(0.1)
y1=euler(0,4,0.1,10)
plt.plot(x1,y1,label="Euler's Method")

x = x_list(0.1)
y = RK_2ndorder_general(0,4,0.1,10,0.5)
plt.plot(x,y,label="Heun's Method")

x = x_list(0.1)
y = RK_2ndorder_general(0,4,0.1,10,1)
plt.plot(x,y,label="Midpoint Method")

x = x_list(0.1)
y = RK_2ndorder_general(0,4,0.1,10,(2/3))
plt.plot(x,y,label="Ralston's Method")

x = x_list(0.1)
y = RK_4thOrder(0,4,0.1 , 10)
plt.plot(x,y,label="Range Kutta(4th Order)")

plt.legend()
plt.title("step size = 0.1")
plt.show()



"""Now for step size 0.5"""

x1=x_list(0.5)
y1=euler(0,4,0.5,10)
plt.plot(x1,y1,label="Euler's Method")

x = x_list(0.5)
y = RK_2ndorder_general(0,4,0.5,10,0.5)
plt.plot(x,y,label="Heun's Method")

x = x_list(0.5)
y = RK_2ndorder_general(0,4,0.5,10,1)
plt.plot(x,y,label="Midpoint Method")

x = x_list(0.5)
y = RK_2ndorder_general(0,4,0.5,10,(2/3))
plt.plot(x,y,label="Ralston's Method")

x = x_list(0.5)
y = RK_4thOrder(0,4,0.5 , 10)
plt.plot(x,y,label="Range Kutta(4th Order)")

plt.legend()
plt.title("step size = 0.5")
plt.show()