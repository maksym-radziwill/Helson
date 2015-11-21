#!/usr/bin/python

## Might want to add support for better precision than 0.01

import re
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np

def read(string):
    f = open(string)
    a = f.read()
    return a

def round(flt):
    integer = int(100*flt)
    approx = float(integer)/100
    if(flt - approx > 0.005):
        return float(integer+1)/100
    else:
        return approx

def gen_plot(string,plt, name):
    a = read(string)
    b = a.splitlines()
    
    x = []
    y = []

    for d in b:

        c = re.search('[-.\d]+', d)
        
        if(float(c.group(0)) > 4 or float(c.group(0)) < -4):
            continue
        if(abs(float(c.group(0))) == 0):
            continue
        
        x.append(float(c.group(0)))
        y.append(int(d.split('=')[1]))

    # ------------
    # Compute sample size as a small sanity check
        
    i = 0
    for l in y:
        i = i + l

    print "Sample size: " + str(i)

    # -------------

#    patch = mpatches(label=name)
#    plt.legend(handles=patch)
    plt.plot(x,y, label=name)

    return

gen_plot("helson.out.re",plt,"Real part RMF")
#gen_plot("helson.out.im",plt,"Imaginary part RMF")
gen_plot("helson.out.abs",plt,"Absolute value RMF")
gen_plot("helson.out.normal",plt,"Normal")
gen_plot("helson.out.normal.abs",plt,"Abs value cplx normal")
plt.legend()
plt.show()

