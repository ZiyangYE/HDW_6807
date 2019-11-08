# -*- coding: utf-8 -*-
"""
Created on Fri Nov  8 02:52:56 2019

@author: jack
"""
def rev(n):
    bits="{:0>8b}".format(n)
    return int(bits[::-1],2)

def tohex(n):
    a=hex(n)
    if(len(a)==3):
        a='0x0'+a[-1]
    return a

def conv(a):
    a=a.split(',')
        
    for i in range(0,14):
        a[i]=tohex(rev(int(a[i],16)))
    
    b=""
    b=b+a[0]
    for i in range(2,14,2):
        b=b+","+a[i]
    
    for i in range(1,14,2):
        b=b+","+a[i]
 
    return b

f=open('t.C')
t=f.read()
f.close()
tl=t.split('\n')
to=''
to=to+tl[0]
for line in tl[1:]:
    if(len(line)<3):
        to=to+'\n'+line
    else:
        if(line[0]=='\t' and line[1]=='\t'):
            linep=conv(line[2:-1])
            linep='\t\t'+linep
            linep=linep+','
            to=to+'\n'+linep
        else:
            to=to+'\n'+line