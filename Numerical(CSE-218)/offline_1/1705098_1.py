# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import numpy as np
import numpy.linalg as LA
import numpy.random
import matplotlib.pyplot as plt
def error(a,b):
    return abs((a-b)/(a))*100
def calculate_ln(x,n):
    sign=1
    i=1
    result=0
    tmp=x/i
    while i<=n:
        result=result+tmp*sign
        i+=1
        tmp=(x*tmp)/i
        sign*=-1
    return result

#x_val=input("enter the value of x: ")
#no_of_iteration=input("enter the number of iteration:")
x_val=0.2
no_of_iteration=1000

print(calculate_ln(float(x_val),int(no_of_iteration)))

plt.style.use('fivethirtyeight') 
fig = plt.figure(figsize=(10,20)) 
plt1 = fig.add_subplot(221) 
plt2 = fig.add_subplot(222) 
plt3 = fig.add_subplot(223) 

#1b

x=np.arange(-1,1,0.1)
y=np.log(1+x)
plt1.plot(x,y,label="ln(1+x)" , linewidth=1, marker = 'o', markerfacecolor = 'black', markersize = '5')

#1c
iteration = [1,3,5,20,50]
ara=[]
z=[]
for n in iteration:
    for i in x:
        ara.append(calculate_ln(i,n))
    z.append(np.array(ara))
    ara.clear()    

plt2.plot(x,y,label="Main Function" , linewidth=1, marker = 'o', markerfacecolor = 'black', markersize = '5')

plt2.plot(x,z[0],linewidth = 1, label="Iteartion 1",marker = 'o', markerfacecolor = 'black', markersize = '5')
plt2.plot(x,z[1],linewidth = 1, label="Iteartion 3",marker = 'o', markerfacecolor = 'black', markersize = '5')
plt2.plot(x,z[2],linewidth = 1, label="Iteartion 5",marker = 'o', markerfacecolor = 'black', markersize = '5')
plt2.plot(x,z[3],linewidth = 1, label="Iteartion 20",marker = 'o', markerfacecolor = 'black', markersize = '5')
plt2.plot(x,z[4],linewidth = 1, label="Iteartion 50",marker = 'o', markerfacecolor = 'black', markersize = '5')
#1d 
n=2
x=np.arange(2,51)
y=[]
while n<=50:
    curr=calculate_ln(0.5,n)
    old=calculate_ln(0.5,n-1)
    err=error(curr,old)
    y.append(err)
    n+=1
plt3.plot(x,y,linewidth = 1,label="Error vs Iteration",marker = 'o', markerfacecolor = 'black', markersize = '5')
fig.subplots_adjust(hspace=.5,wspace=0.5) 
plt1.legend()
plt2.legend()
plt3.legend()
plt.show()
    
    