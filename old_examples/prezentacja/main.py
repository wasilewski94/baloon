import pylab as plt
import numpy as np
import time

data = []
t = []
first = False
first_val = 0
fpath = "./testfile"

def interpret_line(l):
    t = l.split(";")
    if not first:
        first = True
        first_val = int(t[1])
    return  float(int(t[1]) - first_val)+float(t[2])/1000000, int(t[1])

def refresh():
    data = []
    t = []
    first = False
    with open(fpath, "r") as f:
        for line in f.readlines():
            o = interpret_line(line)
            data.append(o[0])
            t.append(o[1])

refresh()
plt.ion()
graph = plt.plot(data,time)[0]

while True:
    graph.set_xdata(time)
    graph.set_ydata(data)
    plt.draw()
    time.sleep(0.5)
    refresh()
