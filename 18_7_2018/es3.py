import subprocess

while True:
	cmd = input("$")
	lcmd = cmd.strip().split(' ')
	result = subprocess.run(lcmd, capture_output=True, shell=False)
	print(result.stdout.strip().decode('utf-8'))
