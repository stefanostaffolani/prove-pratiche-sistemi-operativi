#!/usr/bin/python3

import os

tot = {}

for root, dirs, files in os.walk(".", topdown=False):
    for name in files:
        try:
            with open(os.path.join(root, name), 'r') as f:
                r1 = f.readline()   #prima riga
            #if r1.isascii():
                #print(r1)
                if r1[:2] == "#!":
                    #print("entroo")
                    paths = r1.split(" ")[0]
                    #print(paths)
                    if paths not in tot.keys():
                        tot[paths] = []
                    tot[paths].append(os.path.join(root, name))
        except UnicodeDecodeError:
            pass 

for i in tot.keys():
    print(i, ' '.join(tot[i]))



