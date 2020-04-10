# -*- coding: utf-8 -*-
"""
Created on Tue May 21 14:15:51 2019

@author: Sihat Afnan
"""

#•	Uses graphical model to estimate the value.					[5]
#•	Uses Secant method and False Position method to estimate the value for εs=0.5%. Report the number of iterations for each  method  while achieving the expected result.						    [7.5+7.5=15]
import numpy as np
import matplotlib.pyplot as plt



K=0.05
pt=3

TBLUE=  '\033[34m' 
TCYAN=  '\033[36m' 
TRED=   '\033[31m' 
def f(x):
    return (x/(1-x))*np.sqrt(2*pt/(2+x))- K
def error(a,b):
    return abs((a-b)/(a))*100


def secant(f,a,b,Es,max_iteration):
    count=0
    if(f(a)*f(b)>=0):
        print(TRED+"secant method failed")
        #return None
  
    for n in range(1,max_iteration+1):
        count+=1
        ans = a-(f(a)*(b-a))/(f(b)-f(a))
        if(error(ans,b)<=Es):
            print(TCYAN+"solution found")
            return (ans,count)
        a=b
        b=ans
        
    return (a,count)
        
def False_Position_Method(f,a,b,Es,max_iteration):
    old_ans=0
    count=0
    if(f(a)*f(b)>=0):
        print(TRED+"False Position Method failed")
        #return None

    for n in range(1,max_iteration+1):
        count+=1
        ans = a-(f(a)*(b-a))/(f(b)-f(a))
       
        if(error(ans,old_ans)<=Es):
            print(TBLUE+"solution found")
            return (ans,count)
        if(f(a)*f(ans)<0):
            b=ans
            old_ans=b
        elif(f(b)*f(ans)<0):
            a=ans
            old_ans=a
        elif(f(ans)==0):
            return (ans,count)
        else:
            print("False Position Method failed")
            return None
    
    return (a-(f(a)(b-a))/(f(b)-f(a)),count)
        

    
x=np.arange(-0.5,0.5,0.0001)

y=(x/(1-x))*np.sqrt(2*pt/(2+x))- K
plt.figure(figsize=(14,8))
plt.plot(x,y)
z=x*0
plt.plot(x,z,color="green")
idx = np.argwhere(np.diff(np.sign(y-z))).flatten()
plt.plot(x[idx],y[idx],"ro")

plt.legend() 
plt.xlabel("xx")
plt.ylabel("yy")
plt.title("Graphical Method")
plt.grid()
plt.show()

print("the graphically estimated solution is %.5f" %x[idx])
plt.savefig("graphical_Method.pdf")

first_in_guess = input("Enter first initial guess of secant method ")
second_in_guess = input("Enter second initial guess of secant method ")
max_itr =  input("Enter maximum no of iteration")
sec_ans , no_of_iteration = secant(f,float(first_in_guess),float(second_in_guess),0.005,int(max_itr))
print(TCYAN+"Solution by secant method is ",sec_ans)
print(TCYAN+"No of iterations in secant method",no_of_iteration)

first_in_guess = input("Enter first initial guess of false position method ")
second_in_guess = input("Enter second initial guess of false position method ")
max_itr = input("Enter maximum no of iteration")
fpm_ans , no_of_iteration = False_Position_Method(f,float(first_in_guess),float(second_in_guess),0.005,int(max_itr))
print(TBLUE+"Solution by False Position Method is ",fpm_ans)
print(TBLUE+"No of iterations in False Position Method ",no_of_iteration)