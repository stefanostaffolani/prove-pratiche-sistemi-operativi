import subprocess
import os, sys

tot = { k:[] for k in set([''.join(subprocess.run(['file', i], capture_output=True).stdout.decode().split(':')[1:]).strip() for i in os.listdir(sys.argv[1])]) }

for i in os.listdir(sys.argv[1]):
    tot[''.join(subprocess.run(['file', i], capture_output=True).stdout.decode().split(':')[1:]).strip()].append(i)

for i in tot.keys():
    print(i, end=': ')
    print(','.join(tot[i]))




