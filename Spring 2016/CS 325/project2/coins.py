from sys import argv,exit
import time


def changeslow(coins,amount):

	start = time.time()

	def mincoins(coinArr, amt):
		
		# create a list to hold amt of coins
		coinTally = [0 for c in coinArr]
		# start value used for comparison and check coin val
		coinTally[0] = amt                             
		for each in coinArr:
			# if the coin is less than or equal to the current amt
			if each <= amt: 
			# find amt to make change subtraction 1 of given coin                           
				temp = mincoins(coinArr, amt - each)
				# add 1 of that coin each time you search for amount w/out it
				temp[coinArr.index(each)] += 1         
				# if the sum at the given level of all coins used is greater than
				# the brute force temp result found, temp result is now new smallest      
				if sum(coinTally) > sum(temp):             
					coinTally = temp                   

		return coinTally
	
	minlist = mincoins(coins, amount)

	end = time.time() - start

	numCoins = sum(minlist)
	return ('Algorithm bruteforce', minlist, numCoins, end)




	


	# result = cnt(coins, size-1, amount) + cnt(arr, size, amount - arr[size-1])
	# cntmem[size-1][amount] = result
	# return result
	# return ('Algorithm changegreedy', result, numCoins, end)



def changegreedy(coins,amount):
	start = time.time()

	maxIndex = len(coins) - 1
	result = [0] * len(coins)
	numCoins = 0

	while(amount > 0):
		if(coins[maxIndex] <= amount):
			result[maxIndex] = amount // coins[maxIndex]
			amount -= coins[maxIndex] * result[maxIndex]
			numCoins += result[maxIndex]
		
		maxIndex -= 1
	
	end = start - time.time()

	return ('Algorithm changegreedy', result, numCoins, end)


def dpchange(coins,amount):
	return;


def main():

	print 'Making Change - Project 2'
	print '-------------------------'
	
	# parallel lists
	coinDenoms = []
	amounts = []
	
	print 'Reading input file...'

	with open(argv[1],'r') as inputFile:
		lineCount = 1
		for line in inputFile:
			if(lineCount % 2 != 0):
				newstr = line.replace('[', '').replace(']', '')		
				if(newstr != '\n'):				
					coinDenoms.append(map(int,newstr.strip().split(',')))
			else:
				amnt = int(line)
				amounts.append(amnt)
			lineCount += 1

	print 'Data collected...'
	print 'Running algorithms...'

	# list of alogorithm results
	results = []
# , len(coinDenoms[i])
	for i in xrange(len(coinDenoms)):
		results.append(changeslow(coinDenoms[i],amounts[i]))
		results.append(changegreedy(coinDenoms[i],amounts[i]))
		# changedp algorithm goes here

	# create output file
	fd = argv[1].split('.txt')
	fd.append('change.txt')
	fileName = ''.join(str(elem) for elem in fd)
	
	print 'Writing results to ' + fileName + '...'

	with open(fileName,'w') as outputFile:
		for elem in results:
			outputFile.write(elem[0] + '\n')
			outputFile.write(str(elem[1]) + '\n')
			outputFile.write(str(elem[2]) + '\n')

			# outputFile.write(str(elem[3]) + '\n\n')                 # JUST FOR TESTING
	
	print 'Closing output file...'
	print 'End program...'




if __name__ == '__main__':
	try:
		arg = argv[1]
	except IndexError:
		print 'Usage: python coins.py <inputFile.txt>'
		exit(1)
	main()






