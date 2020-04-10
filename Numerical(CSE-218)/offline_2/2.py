# -*- coding: utf-8 -*-
"""
Created on Thu Jul 11 22:10:02 2019

@author: Sihat Afnan
"""

import matplotlib.pyplot as plt
import numpy as np

TBLUE=  '\033[34m' 
TCYAN=  '\033[36m' 
TRED=   '\033[31m' 

def next_round(tab , col):
    for i in range(col):
        if(tab[0][i]<0):
            return 1
    return 0    
def piv_col(tab):
    a = list(tab[0])
    idx = np.argmin(a)
    return idx
def piv_row(tab,row,col):
    pc = piv_col(tab)
    a=[]
    for i in range(1,row):
        try:
            tmp = tab[i][col-1]/tab[i][pc]
        except ZeroDivisionError:
            tmp=0
        if(tmp <= 0):
            a.append('INF')
        if(tmp>0):
            a.append(tmp)
        
    idx = np.argmin(a)
    print(a)
    return idx+1

def find_pivot(tab,row,col):
    c=piv_col(tab)
    r=piv_row(tab,row,col) 
    return tab[r][c]
def divide_by_pivot(tab,row,col):
    pvt = find_pivot(tab,row,col)
    pvt_row = piv_row(tab,row,col)
    for i in range(col):
        tab[pvt_row][i] /= pvt
    print(TBLUE+"Step 1:")
    printtable(tab,row,col)
    print("Step 2:")
    
def modify_table(tab,row,col):
    pvt_row = piv_row(tab,row,col)
    pvt_col = piv_col(tab)
    divide_by_pivot(tab,row,col)
    
    for i in range(row):
       # print(tab[i][pvt_col])
        tmp = tab[i][pvt_col]
        if(i==pvt_row):
            continue
        for j in range(1,col):
           # print(tab[pvt_row][j])
            tab[i][j] = tab[i][j] - tmp*tab[pvt_row][j]
class myFloat( float ):
    def __str__(self):
        return "%.2f"%self

def find_var(tab,row,col):
    b=[]
    global var
    v=var
    
    for i in range(1,v+1):
        cnt=0
        cnt1=0
        for j in range(row):
            if(tab[j][i]==0):
                cnt=cnt+1
            if(tab[j][i]==1):
                idx = j
                cnt1=cnt1+1
        if(cnt==row-1 and cnt1==1):
            b.append(tab[idx][col-1])
        else:
            b.append(0)
            
    return b        
def printtable(tab,row,col):
    global var
    print("Z",end="\t")
    
    for i in range(1,var+1):
        print("X"+str(i),end="\t")
    for i in range(1,col-var-1):
        print("S"+str(i),end="\t")
    print("Solution")
    
    for i in range(row):
        for j in range(col):
            if(isInt(tab[i][j])):
                print(int(tab[i][j]),end="\t")
                
            else:
                x=myFloat(tab[i][j])
                print(x , end ="\t")
        print(" \n")        
             
            
def find_optimal_solution(tab,col):
    return tab[0][col-1]



"""driver code"""



i_file = open("in2.txt" , "r")
lines_list = i_file.readlines()
my_data = [[float(val) for val in line.split()] for line in lines_list[0:]]
var = len(my_data[0])
slack_var = len(my_data)-1


"""table making"""
row = slack_var+1
col = slack_var+var+2

tab = np.zeros((row , col))
#print(tab)
tab[0][0] = 1

for i in range(1,var+1):
    tab[0][i] = my_data[0][i-1]*(-1)
for j in range(1,row):
    for i in range(1,var+1):
        tab[j][i] = my_data[j][i-1]

for i in range(1,row):
    tab[i][col-1] = my_data[i][var]
j=var+1
for i in range(1,row):
    tab[i][j] = 1
    j=j+1
print(TBLUE+"initial table")
printtable(tab,row,col)
it=1

while(next_round(tab,col)):
    
    print(TBLUE+"Iteration No ",str(it))
    modify_table(tab,row,col)
    printtable(tab,row,col)
    it=it+1

print(TBLUE+"The optimal solution is : ",end=" ")
print(myFloat(find_optimal_solution(tab,col)))
""" finding corresponding variables' values"""

print(TBLUE+"The value of the corresponding variables are :")
b = find_var(tab,row,col)
for i in range(len(b)):
    som=myFloat(b[i])
    print(som)

#"""drawing area
if(var==2):
    x = np.linspace(0, 20, 50)
    l=[]
    for i in range(1,len(my_data)):
       # print(my_data[i][0]/my_data[i][1])
        try:
            y=-(my_data[i][0]/my_data[i][1])*x + my_data[i][2]/my_data[i][1]
        except ZeroDivisionError:
            y=0
        l.append(y)

    ymin = l[0]
    for i in range(slack_var):
        ymin = np.minimum(ymin , l[i])    
    y=0*x
#plt.plot(x,y,label="x axis")
    plt.xlim((0, 450))
    plt.ylim((0, 450))
    for i in range(slack_var):
        plt.plot(x,l[i],label="y"+str(i+1))
    plt.fill_between(x, y, ymin, where=ymin>y, color='grey', alpha=0.5)
    plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
    plt.show()

    

        



