# -*- coding: utf-8 -*-
"""
Created on Fri Aug  9 23:36:46 2019

@author: Sihat Afnan
"""

import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np
from sys import exit



def isclose(a, b, rel_tol=1e-09, abs_tol=0.0):
    return abs(a-b) <= max(rel_tol * max(abs(a), abs(b)), abs_tol)


class myFloat( float ):
    def __str__(self):
        return "%.5f"%self 

def simp_13(h, f0 , f1 , f2):
    return (2*h*(f0+4*f1+f2))/6

def simp_38(h, f0 , f1 , f2 , f3):
    return (3*h*(f0+3*(f1+f2)+f3))/8


def trap(h , f0 , f1):
    return h*(f0+f1)/2       

file_handle=open("input.txt" , "r")
no_of_points = int(file_handle.readline())
lines_list = file_handle.readlines()

my_data = [[float(val) for val in line.split()] for line in lines_list[0:]]
#print(no_of_points)
#print(my_data)
x_list = [row[0] for row in my_data]
y_list = [row[1] for row in my_data]

ans = 0
i=0
s13=0
tp=0
s38=0
x=[]
y=[]
hoise = 0
if(no_of_points==2):
    parthokko = myFloat(x_list[1] - x_list[0])
    ans = trap(parthokko , y_list[0] , y_list[1])
    tp=1
    plt.fill_between(x_list , y_list , color='#FF3C33',alpha = 0.3 , label="trapezoidal")
    ans = myFloat(ans)
    print("Trapezoid : "+str(tp))
    print("1/3 Rule : "+str(s13))
    print("3/8 Rule : "+str(s38))
    print("Integral value : "+str(ans))        
    
    a = mpatches.Patch(color='#52FF33', label='Simpson 1/3')
    b = mpatches.Patch(color='#334FFF', label='Simpson 3/8')
    c = mpatches.Patch(color='#FF3C33', label='Trapezoidal')                    
    plt.legend(handles=[a,b,c])
    
    plt.plot(x_list , y_list)
    plt.xlabel('x - axis') 
    plt.ylabel('y - axis')  
    for i in range(no_of_points):
        #plt.axvline(x=x_list[i] , ymax = y_list[i] , ymin = 0)
        plt.vlines(x_list[i], ymin=0, ymax=y_list[i])
    
    plt.title('Numerical Integration using Newtons Cotes Formula') 
    plt.show()
    exit()

    
while i<=(no_of_points-2):
    dif1 = myFloat(x_list[i+1] - x_list[i])
    if(i+2<no_of_points):
        dif2 = myFloat( x_list[i+2] - x_list[i+1])
    if(i+3<no_of_points):
        dif3 = myFloat(x_list[i+3] - x_list[i+2])
    if(i+4 < no_of_points):
        dif4 = myFloat(x_list[i+4] - x_list[i+3])
    if(i+5 < no_of_points):
        dif5 = myFloat(x_list[i+5] - x_list[i+4])
    
    if (i+5) < no_of_points and isclose(dif1,dif2) and isclose(dif2,dif3) and isclose(dif3,dif4) and isclose(dif4,dif5)==0:
        
        
         # if (((i+5) < no_of_points) and isclose(dif4,dif5)==0) or ((i+5)==no_of_points):
        ans = ans + simp_13(dif1 , y_list[i] , y_list[i+1], y_list[i+2])
        x = x_list[i:i+3]
        y = y_list[i:i+3]
        i = i+2
        s13 = s13+2
        plt.fill_between(x , y , color = '#52FF33',alpha = 0.3 , label="simpson1/3")
         
         
        ans = ans + simp_13(dif3 , y_list[i] , y_list[i+1], y_list[i+2])
        x = x_list[i:i+3]
        y = y_list[i:i+3]
        i = i+2
        s13 = s13+2
        plt.fill_between(x , y , color = '#52FF33',alpha = 0.3 , label="simpson1/3")
       # hoise = 0
         #else:
           #  hoise = 1
    
    elif ((i+3) < no_of_points) and isclose(dif1,dif2) and isclose(dif2,dif3):
        ans = ans + simp_38(dif3 , y_list[i] , y_list[i+1], y_list[i+2], y_list[i+3])
        x = x_list[i:i+4]
        y = y_list[i:i+4]
        s38 = s38+3
        i = i+3
        #print("3/8: "+str(ans))
        
        
       # print(x)
        plt.fill_between(x , y , color='#334FFF',alpha = 0.3 , label="simpson3/8")
    elif isclose(dif1,dif2) and (i+2)<no_of_points:
        ans = ans + simp_13(dif1 , y_list[i] , y_list[i+1], y_list[i+2])
        x = x_list[i:i+3]
        y = y_list[i:i+3]
        i = i+2
        s13 = s13+2
        #print("1/3: "+str(ans))
        
        
        plt.fill_between(x , y , color = '#52FF33',alpha = 0.3 , label="simpson1/3")
    else:
        ans = ans + trap(dif1 , y_list[i] , y_list[i+1])
        x = x_list[i:i+2]
        y = y_list[i:i+2]
        i = i+1
        tp = tp+1
        #print("trap: "+str(ans))
        
       
        plt.fill_between(x , y , color='#FF3C33',alpha = 0.3 , label="trapezoidal")
    
ans = myFloat(ans)
print("Trapezoid : "+str(tp))
print("1/3 Rule : "+str(s13))
print("3/8 Rule : "+str(s38))
print("Integral value : "+str(ans))        

a = mpatches.Patch(color='#52FF33', label='Simpson 1/3')
b = mpatches.Patch(color='#334FFF', label='Simpson 3/8')
c = mpatches.Patch(color='#FF3C33', label='Trapezoidal')                    
plt.legend(handles=[a,b,c])

plt.plot(x_list , y_list)
plt.xlabel('x - axis') 
plt.ylabel('y - axis')  
for i in range(no_of_points):
    #plt.axvline(x=x_list[i] , ymax = y_list[i] , ymin = 0)
    plt.vlines(x_list[i], ymin=0, ymax=y_list[i])

plt.title('Numerical Integration using Newtons Cotes Formula') 
plt.show()


