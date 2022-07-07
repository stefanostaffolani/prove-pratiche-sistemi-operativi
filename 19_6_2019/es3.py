import os

def conta(fl):
	sum = 0
	for root, dirs, files in os.walk(".", topdown=False):

		for name in files:
			if name[-len(fl):].lower() == fl.lower():
				with open(os.path.join(root,name), "r") as f:
					l = len(f.readlines())
					sum += l
					print(os.path.join(root, name), l)
	
	print(f"tot {fl}:", sum)
	return sum

def main():
	s1 = conta(".c")
	s2 = conta(".h")
	s3 = conta("Makefile")
	print("totale: ", s1+s2+s3)

if __name__ == "__main__":
	main()


	
