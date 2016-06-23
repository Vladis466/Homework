import maxSubArray as p1
import random, csv


def createArrays(numArrays,arraySize,scaleFactor):
	data = []

	#create 10 arrays with 100 random numbers
	for i in xrange(numArrays):
		for k in xrange(10):
			randArray = []
			for j in xrange(arraySize):
				num = random.randint(-1000,1000)
				randArray.append(num)
			data.append(randArray)
		arraySize += scaleFactor
	return data


def runTimeTest(outputFile,algo,dataSet):
	data = []
	with open(outputFile,'a') as dataFile:
		csvFile = csv.writer(dataFile)
	
		#run algo on array and write results to file
		for elem in dataSet:
			data.append(algo(elem))
		
		for i in xrange(0,100,10):
			csvFile.writerow([len(data[i]['array']),data[i+0]['time'],data[i+1]['time'],data[i+2]['time'],data[i+3]['time'],data[i+4]['time'], \
				data[i+5]['time'],data[i+6]['time'],data[i+7]['time'],data[i+8]['time'],data[i+9]['time']])
			avg = (data[i+0]['time'] + data[i+1]['time'] + data[i+2]['time'] + data[i+3]['time'] + data[i+4]['time'] + \
                                  data[i+5]['time'] + data[i+6]['time'] + data[i+7]['time'] + data[i+8]['time'] + data[i+9]['time']) / 10.0
			csvFile.writerow(['average speed',avg])

def main():
	valid = False

	while(valid == False):
		print '1) Enumeration Algorithm'
		print '2) Better Enumeration Algorithm'
		print '3) Divide and Conquer Algorithm'
		print '4) Linear Algorithm'
		print ''

		func = int(raw_input('Enter that number of the algorithm you wish to test: '))
		if(func >= 1 and func <= 4):
			valid = True 
		else:
			print 'Invalid entry. Enter a number between 1 and 4.\n'


	arraySize = int(raw_input('Enter size of the first array: '))
	scaleFactor = int(raw_input('Enter the the scale factor: '))
	numArrays = 10

	data = createArrays(numArrays,arraySize,scaleFactor)
	
	if(func == 1):
		runTimeTest('dataAlgo' + str(func) + '.csv',p1.enumeration_alg,data)	
	elif(func == 2):
		runTimeTest('dataAlgo' + str(func) + '.csv',p1.betterEnum_alg,data)	
	elif(func == 3):
		runTimeTest('dataAlgo' + str(func) + '.csv',p1.divAndConquer_alg,data)	
	elif(func == 4):
		runTimeTest('dataAlgo' + str(func) + '.csv',p1.linear_alg,data)




if __name__ == '__main__':
	main()
