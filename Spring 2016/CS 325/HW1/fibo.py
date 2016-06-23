import time

def fiboIterative(x):
	num1 = 0
	num2 = 1
	temp = 0

	if x == 0:
		return 0
	elif x == 1:
		return 1
	else:
		for i in xrange(2, x):
			temp = num2
			num2 += num1
			num1 = temp
	
	return num2


def fiboRecursive(x):
	if x == 0:
		return 0
	elif x == 1:
		return 1
	else:
		return fiboRecursive(x-1) + fiboRecursive(x-2)

def in_the_forest(duck):
    print(duck.quack())

def main():
	print "insert a number representing the index of the fibbonacci number to iterate up to please"
	num = int(raw_input())

	print "insert i for iterative or r for recursive"
	choice = raw_input()

	if choice == 'i':
		start_time = time.time()
		ans = fiboIterative(num)
	if choice == 'r':
		start_time = time.time()
		ans = fiboRecursive(num)

	print("--- %s seconds ---" % (time.time() - start_time))



if __name__ == "__main__": main()