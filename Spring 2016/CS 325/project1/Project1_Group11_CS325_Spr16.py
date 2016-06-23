# Written by Charles Bennett, Vlad Predovic, and Conrad Lewin
# This program runs four algorithms used to solve the maximun subarray problem 
# Data input: from file MSS_Problems.txt 

import random
import time

def writeLine(name, array, subarray, maxSum, time):
	return name + '\nOriginal: ' + str(array) + '\nSubarray: ' + str(subarray) + '\nMax Sum: ' + str(maxSum) + '\nRun time: ' + str(time) + '\n\n'
		

def enumeration_alg(arr):
	main_printlist = []
	main_maxlist = []

	t0 = time.time()			#start timer
	max_sum=0
	max_i=0
	mak_j=0
	for i in xrange(0, len(arr)):
		# print arr[i]
		for j in xrange(0, len(arr)):
			curr_sum=0

			for k in xrange(i, j+1):
				curr_sum+=arr[k]

			if(curr_sum > max_sum):
				max_sum = curr_sum
				max_i = i
				max_j = j
				result = {'name':'Algorithm 1 - Enumeration','array':arr, 'subarray':arr[i:j+1],'sum':max_sum, 'time':0} 

	t1 = time.time()				#end timer
	total = t1-t0
	result['time'] = total
	return result





def betterEnum_alg(arr):
	resultList = []

	startTime = time.time()
	maxSum = 0
	result = ()

	for i in xrange(0, len(arr)):
		start = end = i
		curSum = 0
		for j in xrange(i,len(arr)):
			curSum += arr[j]
			if curSum > maxSum:
				maxSum = curSum
				end = j
				result = {'name':'Algorithm 2 - Better Enumeration','array':arr, 'subarray':arr[start:end+1],'sum':maxSum, 'time':0 } 
				#result = (arr[start:end+1],maxSum)
	
	endTime = time.time() - startTime
	result['time'] = endTime
	#resultList.append(result)

	return result





def main():
	print "Max Subarray Algorithms"
	print "-----------------------"

	# list of lists in python. Like an array of arrays.
	data = []
	results = []

	print "Reading input file..."

	#remember to change file name
	#read file, format contents and save each array in a data list
	with open('MSS_TestProblems-1.txt') as inputfile:				
		for line in inputfile:
			newstr = line.replace("[", "").replace("]", "")		
			if newstr != '\n':				
				data.append(map(int,newstr.strip().split(',')))
	
	print "Items added to data list..."
	print "Creating 10 arrays of 100 random ints..."

	#generate 10 arrays with random numbers
	#and save them in the data list
	for i in xrange(10):
		randArray = []
		for j in xrange(100):
			num = random.randint(-500,500)
			randArray.append(num)
		
		data.append(randArray)
	
	print "Appending randomly generated arrays to data list..."
	print "Creating a results file..."

	#open the results file for writing
	resultFile = open('MSS_Results.txt', 'w')
	
	print "Running all four algorithms on arrays in the data list..."
	
	#run each algorithm, saving their results in a results list
	for array in data:
		results.append(betterEnum_alg(array))
		results.append(enumeration_alg(array))
		#other algorithms

	print "Writing results to the MSS_Results.txt..."
	#write the results of each algorithm to a results file
	for element in results:
		line = writeLine(element['name'],element['array'],element['subarray'],element['sum'],element['time'])
		resultFile.write(line)

	
		
	print "Closing MSS_Results.txt..."
	resultFile.close()

	print "End program..."











if __name__ == '__main__':
    main()

