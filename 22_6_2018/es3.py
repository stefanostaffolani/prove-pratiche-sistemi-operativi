import subprocess

while True:
	try:
		print(subprocess.run([ i for i in input('$').strip().split(' ') if i ], capture_output=True, shell=False).stdout.strip().decode('utf-8')) 
	except:
		break
