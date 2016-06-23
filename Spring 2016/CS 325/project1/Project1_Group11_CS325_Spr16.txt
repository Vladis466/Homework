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
	startTime = time.time()
	maxSum = 0
	result = {'name':'Algorithm 2 - Better Enumeration','array':arr}

	for i in xrange(0, len(arr)):
		start = end = i
		curSum = 0
		for j in xrange(i,len(arr)):
			curSum += arr[j]
			if curSum > maxSum:
				maxSum = curSum
				end = j
				result.update({'subarray':arr[start:end+1],'sum':maxSum})

	endTime = time.time() - startTime
	result.update({'time':endTime }) 
	return result

	
def maxCrossSum(list,start,middle,end):
    	leftSum = float('-inf')
    	curSum = 0
    	startIndex = endIndex = None

    	for i in xrange(middle,start-1,-1):
        	curSum += list[i]
        	if(curSum > leftSum):
            		leftSum = curSum
            		startIndex = i
    
    	rightSum = float('-inf')
    	curSum = 0
                    
    	for j in xrange(middle + 1, end+1):
        	curSum += list[j]
        	if(curSum > rightSum):
            		rightSum = curSum
            		endIndex = j
    
    	return (startIndex,endIndex,leftSum + rightSum)         

	
def recDivAndConquer(list,start,end):
    	START_INDEX = 0
    	END_INDEX = 1
    	SUM_DATA = 2

    	if(start == end):
        	return (start,end,list[start])
    
    	middle = (start + end) // 2

    	leftSum = recDivAndConquer(list,start,middle)
    	rightSum = recDivAndConquer(list,middle + 1, end)
    	crossSum = maxCrossSum(list,start,middle,end)

    	if(leftSum[SUM_DATA] >= rightSum[SUM_DATA] and leftSum[SUM_DATA] >= crossSum[SUM_DATA]):
        	return leftSum
    	elif(rightSum[SUM_DATA] >= leftSum[SUM_DATA] and rightSum[SUM_DATA] >= crossSum[SUM_DATA]):
        	return rightSum
    	else:
        	return crossSum
   

def divAndConquer_alg(list):
    	START_INDEX = 0
    	END_INDEX = 1
    	SUM_DATA = 2
	
	startTime = time.time()
    	data = recDivAndConquer(list,0,len(list)-1)
	endTime = time.time() - startTime
    	return {'name':'Algorithm 3 - Divide and Conquer','array':list,'subarray':list[data[START_INDEX]:data[END_INDEX] + 1],'sum':data[SUM_DATA],'time':endTime}
	
	
def linear_alg(arr):
	result = {'name':'Algorithm 4 - Linear','array':arr}
	startTime = time.time()
	
	size = len(arr)
	maxSum = float('-inf')
	endHereSum = float('-inf')
	low = high = 0

	for i in xrange(size):
		endHereHigh = i
		if(endHereSum > 0):
			endHereSum = endHereSum + arr[i]
		else:
			endHereLow = i
			endHereSum = arr[i]
		if(endHereSum > maxSum):
			maxSum = endHereSum
			low = endHereLow
			high = endHereHigh			
	endTime = time.time() - startTime
	result.update({'subarray':arr[low:high+1],'sum':maxSum, 'time':endTime})
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
	with open('MSS_Problems.txt') as inputfile:				
		for line in inputfile:
			newstr = line.replace("[", "").replace("]", "")		
			if newstr != '\n':				
				data.append(map(int,newstr.strip().split(',')))
	
	print "Items added to data list..."

	print "Creating a results file..."

	#open the results file for writing
	resultFile = open('MSS_Results.txt', 'w')
	
	print "Running all four algorithms on arrays in the data list..."
	
	#run each algorithm, saving their results in a results list
	for array in data:
		results.append(enumeration_alg(array))	
		results.append(betterEnum_alg(array))
		results.append(divAndConquer_alg(array))
		results.append(linear_alg(array))

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

