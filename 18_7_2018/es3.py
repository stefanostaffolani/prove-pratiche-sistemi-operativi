import subprocess

while True:
    print(subprocess.run([ i for i in input('$').strip().split(' ') if i ], capture_output=True, shell=False).stdout.strip().decode())
