#!/usr/bin/python3

import os

tot = {}

for root, dirs, files in os.walk(".", topdown=False):
    for name in files:
        filename = os.path.join(root,name)
        inode = os.stat(filename).st_ino 
        if inode not in tot.keys():
            tot[inode] = []
        tot[inode].append(filename)

l = list(tot.keys())
#print(tot)
#print([i for i in l if len(l)>1])

for i in l:
    if len(tot[i]) > 1:
        print(" ".join(tot[i]))


