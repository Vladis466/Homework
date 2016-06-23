import graph
from operator import itemgetter
from sys import argv,exit

#constants
CITY_ID = 0
X = 1
Y = 2

#------------------------------------------Euclidean TSP------------------------------------------------------------ 

def formSubgraph(gPrime,subGraph,treeEdges):
	for v in gPrime.getVertList():
		subGraph.vertList.append(v)

	for uv in treeEdges:
		subGraph.edgeList.append(subGraph.createEdge(uv[0],uv[1]))

	subGraph.createAdjList()

def makeTour(g,path,name):
	weight = 0
	path.append(path[0])

	for i in range(len(path) - 1):
		weight += g.getDistance(path[i],path[i+1])

	path.pop()
	tour = {'name':name,'len':weight,'certificate':tuple(path)} 

	return tour

def euclideanTSP(theMap):
	minWeight = float('inf')
	optimal = None
	mst = theMap.primMST(theMap.vertList[0])
	subGraph = graph.Graph()
	formSubgraph(theMap,subGraph,mst)
	path = subGraph.dfs()
	tour = makeTour(subGraph,path,'Euclidean TSP')
	return tour

#----------------------------------------End Euclidean TSP------------------------------------------------------------


#---------------------------------------Greedy TSP-------------------------------------------------------------------

def greedyTSP(theMap,source):
	minWeight = float('inf')
	path = [source]
	count = 0
	
	while count < len(theMap.vertList) - 1:
		for i in range(len(theMap.vertList)):
			isConnected = theMap.adjMatrix[int(source.getId())][i]
			if isConnected and theMap.getVertex(i) not in path:
				weight = theMap.getDistance(source,theMap.getVertex(i))
				if weight < minWeight:
					minWeight = weight
					newSource = theMap.getVertex(i)

		path.append(newSource)
		source = newSource
		count += 1
		minWeight = float('inf')

	return makeTour(theMap,path,'Greedy TSP')


#-------------------------------------End Greedy TSP------------------------------------------------------------------






#-------------------------------------Greedy 2-Opt--------------------------------------------------------------------

# vertices: list of all vertices
# currSol: the current order of the solution: Default is as input
# amt: The amount of vertices
def twoOptSwap(vertices, currSol, amt):

	biggest_change = 0 
	best_move = None

	# Gather the four nodes that will be compared.
	# This is done for every iteration
	for node1 in range(amt):
		for node3 in range(amt):
			node2 = (node1 + 1) % amt 														# node after node 1
			node4 = (node3 + 1) % amt 														# node after node 3

			#retrieve the locations for each cord.
			Anode1 = currSol[node1].getCords()
			Anode2 = currSol[node2].getCords()
			Anode3 = currSol[node3].getCords()
			Anode4 = currSol[node4].getCords()

			# print Anode1[0]

			len13 = int(round(sqrt(pow(Anode1[0] - Anode3[0],2) +  pow(Anode1[1] - Anode3[1],2))))
			len24 = int(round(sqrt(pow(Anode2[0] - Anode4[0],2) +  pow(Anode2[1] - Anode4[1],2))))
			len12 = int(round(sqrt(pow(Anode1[0] - Anode2[0],2) +  pow(Anode1[1] - Anode2[1],2))))
			len34 = int(round(sqrt(pow(Anode3[0] - Anode4[0],2) +  pow(Anode3[1] - Anode4[1],2))))

			# print "lens start======"
			# print len13
			# print len24
			# print len12
			# print len34
			# print "lens end-------"
			# Check to make sure not the same vertices. Would throw off calculations
			if node1 != node3 and node2 != node3 and node2 != node4:
				improv = (len12 + len34) - (len13 + len24)

				# If the result is better, then save the nodes.
				#print biggest_change
				if improv > biggest_change:
					biggest_change = improv
					best_move =  [node1,node2,node3,node4]

	if biggest_change > 0:
		newSol = range(0, amt)
		newSol[0] = currSol[best_move[0]]

		n = 1

		while best_move[2] != best_move[1]:
			newSol[n] = currSol[best_move[2]]
			best_move[2] = (best_move[2] - 1) % amt
			n += 1
		newSol[n] = currSol[best_move[1]]

		n += 1
		while best_move[3] != best_move[0]:
			newSol[n] = currSol[best_move[3]]
			best_move[3] = (best_move[3] + 1) % amt
			n += 1

		# print biggest_change
		return (True, newSol)
	else:
		return (False, currSol)


def twoOpt(theMap, source):

	minWeight = 0																			# create var

	for i in xrange(len(theMap.vertList)-1):												# Create the random starting path
		theMap.edgeList.append(theMap.createEdge(theMap.vertList[i],theMap.vertList[i+1]))	# calc distances
	for edg in theMap.edgeList:																# calculate total distance
		minWeight += edg.getEdgeWeight()

	#print minWeight
	
	currOrder = [x for x in theMap.vertList]												# creating starting sol
	status = True 

	while status:	# Keep running 2-opt while solution improves.
		(status, currOrder) = twoOptSwap(theMap.vertList, currOrder ,len(theMap.vertList))		
		# minWeight = 0
		# newMap = graph.Graph()
		# for i in xrange(len(currOrder)-1):														# Create the random starting path
		# 	newMap.edgeList.append(theMap.createEdge(currOrder[i],currOrder[i+1]))	# calc distances
		# for edg in newMap.edgeList:																# calculate total distance
		# 	minWeight += edg.getEdgeWeight()
		# print minWeight
		


	# print minWeight
	# vals = theMap.edgeList[1].getEdgeDesc()
	# print vals[1].getCords()

	return makeTour(theMap, currOrder, "Greedy 2-Opt")




#-------------------------------------End Greedy 2-Opt-----------------------------------------------------------------
	#run Vlad's algorithm
	print('Running Greedy 2-Opt...')
	tour = twoOpt(theMap,theMap.vertList[0]) #adjust parameter list
	results.append(tour)
	print('done...' + '\n')

def main():
	results = []
	theMap = graph.Graph()

	print('Creating graph...')
	print('adding verticies')
	with open(argv[1],'r') as inputFile:
		for line in inputFile:
			temp = line.split()
			theMap.addVertex(temp[CITY_ID],(int(temp[X]),int(temp[Y])))

	print('vertices added')
	#create graph
	print('creating adjacency matrix')
	theMap.createMatrix()
	print('adjacency matrix created')

	#run Conrad's aglorithm1
	print('Running Euclidean TSP...')
	tour = euclideanTSP(theMap)
	results.append(tour)
	theMap.reset()
	print('done...' + '\n')

	print('Running Greedy TSP...')
	tour = greedyTSP(theMap,theMap.vertList[0])
	results.append(tour)
	theMap.reset()
	print('done...' + '\n')

	print('Finding "optimal" solution...')
	optimal = sorted(results,key=itemgetter('len'))[0]

	print(optimal['name'] + ' produced optimal solution...' + '\n')

	print('Creating output file...')
	fd = argv[1].split()
	fd.append('.tour')
	fileName = ''.join(str(elem) for elem in fd)
	
	print('Writing result to ' + fileName + '...')

	with open(fileName, 'w') as outputFile:
		outputFile.write(str(optimal['len']) + '\n')
		cert = optimal['certificate']
		for c in cert:
			outputFile.write(c.getId() + '\n')

	print('End program...')

	return			






if __name__ == '__main__':
	try:
		arg = argv[1]
	except IndexError:
		print('Usage: python tsp.py <inputFile.txt>')
		exit(1)
	main()
