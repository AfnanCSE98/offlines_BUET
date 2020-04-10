# -*- coding: utf-8 -*-
"""
Created on Wed Jul 10 18:57:43 2019

@author: Sihat Afnan
"""

import numpy as np
import numpy.linalg as LA
import numpy.random
lo=[]
up=[]
class myFloat( float ):
    def __str__(self):
        return "%.4f"%self 

def Backward_substitution(A,b):
    n = len(A)
  
    x = [[0]for j in range(n)]
    for i in range(n-1,-1,-1): 
        for j in range(i+1,n):
            
            b[i][0] = b[i][0] - A[i][j]*x[j][0]
        x[i][0] = b[i][0]/A[i][i]

    return x

def Forward_Substitution(L,B):
    n=len(B)
    y=[[0]for j in range(n)]
    
    y[0][0] = B[0][0]/L[0][0]
   
    for i in range(n):
        sum=0
       
        for j in range(i):
            sum=sum+L[i][j]*y[j][0]
            
        y[i][0] = (B[i][0] - sum)
    return y 

 
def LU_Decomposition(A):
    
    n=len(A[0])
    """set all to zeros"""
    Lower = np.zeros([n,n])
    Upper = np.zeros([n, n])
    
    for i in range(n):
        Lower[i][i]=1
        if (i==0):
            Upper[0][0] = A[0][0]
            for j in range(1,n):
                Upper[0][j]=A[0][j]
                Lower[j][0]=A[j][0]/Upper[0][0]
        else:
                for j in range(i, n):#U
                    temp=0
                    for k in range(0, i):
                        temp = temp+Lower[i][k] * Upper[k][j]
                    Upper[i][j]=A[i][j]-temp
                for j in range(i+1, n):#L
                    temp = 0
                    for k in range(0, i ):
                        temp = temp + Lower[j][k] * Upper[k][i]
                    Lower[j][i] = (A[j][i] - temp)/Upper[i][i]
    return Lower,Upper


    
    
 
      
"""driver code"""

A=[]
a=[]
b=[]
B=[]    
file_handle=open("in1.txt" , "r")
n=int(file_handle.readline())

file_handle.seek(0)
lines_list = file_handle.readlines()

my_data = [[float(val) for val in line.split()] for line in lines_list[1:]]

for i in range(n):
    for j in range(n):
        a.append(my_data[i][j])
       
    A.append(list(a))
    a.clear()


for i in range(n,2*n):
    b.append(my_data[i][0])
    B.append(list(b))
    b.clear()

file_handle.close()
lo,up = LU_Decomposition(A ) 
of= open("out1.txt","w")  
for i in range(n):
    for j in range(n):
        x=myFloat(lo[i][j])
        of.write(str(x) )
        of.write(" ")
    of.write("\n")    
of.write("\n")   
for i in range(n):
    for j in range(n):
        x=myFloat(up[i][j])
        of.write(str(x) )
        of.write(" ")
    of.write("\n")           
of.write("\n")  
"""checking unique soln""" 
hoise=0 
for i in range(n):
    cnt=0
    for j in range(n):
        if(up[i][j]==0):
            cnt=cnt+1
            
        if(cnt==n):
            of.write("No unique solution")
            hoise=1
            #exit()  
if(hoise==0):
    Y=Forward_Substitution(lo,B)  
    
    for i in range(n):
        x=myFloat(Y[i][0])
        of.write(str(x))
        of.write("\n")
    of.write("\n")      
        
    X=Backward_substitution(up , Y)
    
    for i in range(n):
        x=myFloat(X[i][0])
        of.write(str(x))
        of.write("\n")
    of.write("\n")  

of.close()  
                   