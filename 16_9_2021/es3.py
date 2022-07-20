#!/usr/bin/python3

import os
import sys

tot = {}

for root, dirs, files in os.walk(sys.argv[1], topdown=False):
	for name in files:
		if name not in tot.keys():
			tot[name] = []
			tot[name].append(root)
		else:
			tot[name].append(root)

for i in tot.keys():
	print(i, ': ', ' '.join(tot[i]))

