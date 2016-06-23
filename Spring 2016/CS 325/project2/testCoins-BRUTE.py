import coins as p2
from csv import writer
# ONLY USED DATA FROM TEST 1 <---------------------------------------------------------------------------

#constants
CHANGE = 1
NUM_COINS = 2
TIME = 3
NUM_DENOM = 0
AVG_TIME = 1



def baseTest(algo):
	result = []

	denom1 = [1,2,4,8]
	denom2 = [1,3,7,12]

	amnt1 = 15
	amnt2 = 29
	amnt3 = 31

	result.append(algo(denom1,amnt1))
	result.append(algo(denom2,amnt2))
	result.append(algo(denom2,amnt3))

	print 'Base Test'
	print '---------'

	print 'Coins: ' + str(denom1) + '\n' + 'Amount: ' + str(amnt1) + '\n' + 'Change: ' + str(result[0][CHANGE]) \
		+ '\n' + 'Number of Coins: ' + str(result[0][NUM_COINS]) + '\n'

	print 'Coins: ' + str(denom2) + '\n' + 'Amount: ' + str(amnt2) + '\n' + 'Change: ' + str(result[1][CHANGE]) \
		+ '\n' + 'Number of Coins: ' + str(result[1][NUM_COINS]) + '\n'

	print 'Coins: ' + str(denom2) + '\n' + 'Amount: ' + str(amnt3) + '\n' + 'Change: ' + str(result[2][CHANGE]) \
		+ '\n' + 'Number of Coins: ' + str(result[2][NUM_COINS]) + '\n'



def test1(algo,outputFile):
	result = []
	sumTime = 0
	avgTime = 0

	denom = [1,5,10,25]
	amnt = list(xrange(30,31,1))
	# amnt = list(xrange(30,70,5))		# Changed this out for my second test
	for i in xrange(len(amnt)):
		print amnt[i]
		result.append(algo(denom,amnt[i]))

	with open(outputFile,'w') as dataFile:
		csvFile = writer(dataFile)
		csvFile.writerow(['Amount','Num Coins','Time'])

		for i in xrange(len(result)):
			csvFile.writerow([amnt[i],result[i][NUM_COINS],result[i][TIME]])
			sumTime += result[i][TIME]

	avgTime = sumTime / len(result)


	print avgTime

	return (len(denom),avgTime)



def test2(algo,outputFile):
	result1 = []
	result2 = []
	data = []
	sumTime = 0
	avgTime = 0

	denom1 = [1, 2, 6, 12, 24, 48, 60]
	denom2 = [1, 6, 13, 37, 150]

	amnt = list(xrange(15,32))

	for i in xrange(len(amnt)):
		print amnt[i]
		result1.append(algo(denom1,amnt[i]))
		result2.append(algo(denom2,amnt[i]))

	with open(outputFile,'w') as dataFile:
		csvFile = writer(dataFile)

		csvFile.writerow(['Coins',denom1])
		csvFile.writerow(['Amount','Num Coins','Time'])

		for i in xrange(len(result1)):
			csvFile.writerow([amnt[i],result1[i][NUM_COINS],result1[i][TIME]])
			sumTime += result1[i][TIME]
		
		avgTime = sumTime / len(result1)
		data.append((len(denom1),avgTime))
		sumTime = 0

		csvFile.writerow([])
		csvFile.writerow(['Coins',denom2])
		csvFile.writerow(['Amount','Num Coins','Time'])

		for i in xrange(len(result2)):
			csvFile.writerow([amnt[i],result2[i][NUM_COINS],result2[i][TIME]])
			sumTime += result2[i][TIME]
		
		avgTime = sumTime / len(result2)
		data.append((len(denom2),avgTime))

	return data



def test3(algo,outputFile):
	result = []
	sumTime = 0
	avgTime = 0

	denom = [1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32]

	amnt = list(xrange(10,27))

	for i in xrange(len(amnt)):
		print amnt[i]
		result.append(algo(denom,amnt[i]))

	with open(outputFile,'w') as dataFile:
		csvFile = writer(dataFile)
		csvFile.writerow(['Amount','Num Coins','Time'])

		for i in xrange(len(result)):
			csvFile.writerow([amnt[i],result[i][NUM_COINS],result[i][TIME]])
			sumTime += result[i][TIME]
		
		avgTime = sumTime / len(result)

	return (len(denom),avgTime)



def main():
	data = []
	valid = False
	auxTestFile = ''

	while(valid == False):
		print '1) Brute Force Algorithm'
		print '2) Greedy Algorithm'
		print '3) Dynamic Algorithm'
		print ''

		func = int(raw_input('Enter that number of the algorithm you wish to test: '))
		if(func >= 1 and func <= 3):
			valid = True 
		else:
			print 'Invalid entry. Enter a number between 1 and 3.\n'
	
	if(func == 1):
		auxTestFile = 'slowTest_Q8.csv'
		baseTest(p2.changeslow)
		data.append(test1(p2.changeslow,'slowTest_Q4.csv'))
		data.append(test2(p2.changeslow,'slowTest_Q5.csv'))
		data.append(test3(p2.changeslow,'slowTest_Q6.csv'))
	elif(func == 2):
		auxTestFile = 'greedyTest_Q8.csv'
		baseTest(p2.changegreedy)
		data.append(test1(p2.changegreedy,'greedyTest_Q4.csv'))
		data.append(test2(p2.changegreedy,'greedyTest_Q5.csv'))
		data.append(test3(p2.changegreedy,'greedyTest_Q6.csv'))
	elif(func == 3):
		auxTestFile = 'dpTest_Q8.csv'
		baseTest(p2.changedp)
		data.append(test1(p2.changedp,'dpTest_Q4.csv'))
		data.append(test2(p2.changedp,'dpTest_Q5.csv'))
		data.append(test3(p2.changedp,'dpTest_Q6.csv'))

	with open(auxTestFile,'w') as auxTest:
		csvFile = writer(auxTest)

		csvFile.writerow(['Num Denominations','Avg Run Time'])
		
		for i in xrange(len(data)):
			if(isinstance(data[i],list)):
				csvFile.writerow([data[i][0][NUM_DENOM],data[i][0][AVG_TIME]])
				csvFile.writerow([data[i][1][NUM_DENOM],data[i][1][AVG_TIME]])
			else:
				csvFile.writerow([data[i][NUM_DENOM],data[i][AVG_TIME]])

	print 'Other tests written to csv files in the current directory.'





if __name__ == '__main__':
	main()
	
