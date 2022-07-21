import os,sys
import re
from tabulate import tabulate

pattern = r'^(Name:\s+.*)|(VmSize:\s+.*)'

processi = ['/proc/'+i for i in os.listdir("/proc/") if os.path.isdir('/proc/'+i) and str(os.stat('/proc/'+i).st_uid) == sys.argv[1]]
toprint = []

for i in processi:
	if(os.path.exists(i+'/status')):
		with open(i+'/status', 'r') as f:
			ll = f.read()
			res = re.findall(pattern, ll)
			toprint.append([res[0][0].strip().split('\t')[1],res[1][1].split('\t')[1].strip()])	


print(tabulate(toprint, headers=['Name','Vmsize']))

