import os, shlex, subprocess, time, sys


	
	
def prodPrint():

	num = '\
73167176531330624919225119674426574742355349194934\
96983520312774506326239578318016984801869478851843\
85861560789112949495459501737958331952853208805511\
12540698747158523863050715693290963295227443043557\
66896648950445244523161731856403098711121722383113\
62229893423380308135336276614282806444486645238749\
30358907296290491560440772390713810515859307960866\
70172427121883998797908792274921901699720888093776\
65727333001053367881220235421809751254540594752243\
52584907711670556013604839586446706324415722155397\
53697817977846174064955149290862569321978468622482\
83972241375657056057490261407972968652414535100474\
82166370484403199890008895243450658541227588666881\
16427171479924442928230863465674813919123162824586\
17866458359124566529476545682848912883142607690042\
24219022671055626321111109370544217506941658960408\
07198403850962455444362981230987879927244284909188\
84580156166097919133875499200524063689912560717606\
05886116467109405077541002256983155200055935729725\
71636269561882670428252483600823257530420752963450'

	temp, maxi, i = 0, 0, 0

	while i < len(num) - 4:
		prod =  int(num[i]) *  int(num[i+1]) * int(num[i+2]) * int(num[i+3]) * int(num[i+4])
		if prod > maxi: maxi = prod
		i = i + 1 

	print(maxi)



def namesCost():
	c = 0
	total = 0
	cost = []
	
	dic = {'"': 0,'A': 1, 'C': 3, 'B': 2, 'E': 5, 'D': 4, 'G': 7, 'F': 6, 'I': 9, 'H': 8, 'K': 11, 'J': 10, 'M': 13, 'L': 12, 'O': 15, 'N': 14, 'Q': 17, 'P': 16, 'S': 19, 'R': 18, 'U': 21, 'T': 20, 'W': 23, 'V': 22, 'Y': 25, 'X': 24, 'Z': 26}
	f = open('names.txt') 		
	lines = f.read().split(',')		#Successfully reads in the list of names.
	f.close()

	lines.sort()
#	print(lines[937])			#check 938th is Colin!

	while c < len(lines):
		temp = 0
		for x in lines[c]:
			temp += dic[x]	
		cost.append(temp)
		

		c = c + 1

#	print(cost[937])
	

	for i, c in enumerate(cost):		#Enumerating and printing total value of text file.
		total += (i+1)*c
	print(total)
	







def dirPath():

	path = '/nfs/stak/students/p/predoviv'
	dirList = []

	for rt, dirs, files in os.walk(path):
	    for name in dirs:       
		    filename = os.path.join(rt, name)
		    sys.stdout.write('')
		    dirList.append(filename)
		   
	def pathLine(path):    
		x = 0
		head = tail = path
		while head and tail:
			head, tail = os.path.split(head)
			x +=1
		return x

	def find_Longest( emptyList ):
		return max(emptyList, key=pathLine)



		   
	print(find_Longest(dirList))	


def main():
	choice = 4

	while choice != 0:
		choice = int(input('1 for prodPrint, 2 for namesCost, 3 for dirPath, 0 to exit.'))
		
		if choice == 1: prodPrint()
		
		if choice == 2: namesCost()

		if choice == 3: dirPath()


if __name__ == "__main__":
    main()
