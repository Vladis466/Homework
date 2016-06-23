import vertex
import edge
import linkedList
import Queue as Q
from math import sqrt,pow
from operator import attrgetter

#constants
X = 0
Y = 1

#defines a complete graph
#vertList = list of vertex objects that make up the graph
#edgeList = list of edge objects that connect vertices in the graph
#adjList = list of linked lists. the index of the list corresponds to a vertex id.
#the linked lists at each index represent the graph connectivity. all vertices and edges
#in the adjacency list are shallow copies of their counterparts
class Graph:
	def __init__(self):
		self.vertList = []
		self.edgeList = []
		self.adjMatrix = None
		self.adjList = []

	#-------------getters--------------------------------------------------------------------------

	#get vertex by id
	def getVertex(self,id):
		if int(id) >= 0 and int(id) <= len(self.vertList):
			return self.vertList[int(id)]
		else:
			return None

	#get adjacency matrix
	def getAdjMatrix(self):
		return self.adjMatrix

	#get adjacency list
	def getAdjList(self):
		return self.adjList

	#get vertex list
	def getVertList(self):
		return self.vertList

	#--------end getters------------------------------------------------------------------------------------



	#creates a single graph vertex
	def addVertex(self,id,cords):
		vert = vertex.Vertex(id,cords)
		self.vertList.append(vert)

	def createEdge(self,v1,v2):
		return edge.Edge((v1,v2),self.getDistance(v1,v2))

	#only creates adjacency matrix for a complete graph
	#should only be used to initialize a complete graph
	def createMatrix(self):
		self.adjMatrix = [[1 for v in range(len(self.vertList))] for row in range(len(self.vertList))]
		for i in range(len(self.vertList)):
			self.adjMatrix[i][i] = 0

	#creates and adjaceny list for the graph
	#requires a graph with a valid edge list
	#this function may be useful for creating subgraphs from the main graph (theMap)
	def createAdjList(self):
		for vert in self.vertList:
			id = vert.getId()
			newList = linkedList.LinkedList()
			self.adjList.append(newList)
			for e in self.edgeList:
				edgeName = e.getEdgeDesc()
				if edgeName[0].getId() == id:
					newList.addLink({'vertex':edgeName[1],'weight':e.getEdgeWeight()})
				elif edgeName[1].getId() == id:
					newList.addLink({'vertex':edgeName[0],'weight':e.getEdgeWeight()})


	#calculate edge weight
	#firstVert = first vertex object
	#secondVert = second vertex object
	def getDistance(self,firstVert, secondVert):
			x1 = firstVert.getCords()[X]
			x2 = secondVert.getCords()[X]
			y1 = firstVert.getCords()[Y]
			y2 = secondVert.getCords()[Y]
			dist = sqrt(pow(x1 - x2,2) +  pow(y1 - y2,2))
			return int(round(dist))

	#prim's algorithm
	#root = source vertex object
	def primMST(self,root):
		root.key = 0
		pq = Q.PriorityQueue()
		tree = []

		for vert in self.vertList:
			pq.put(vert)

		while not pq.empty():
			u = pq.get()
			id = int(u.getId())

			for i in range(len(self.vertList)):
				isConnected = self.adjMatrix[id][i]
				if isConnected:
					v = self.getVertex(i)
					weight = self.getDistance(u, v)
					if v in pq.queue and weight < v.key:
						v.setKey(weight)
						v.setPredecessor(u)

		for vert in self.vertList:
			if vert != root:
				tree.append((vert,vert.getPredecessor()))

		return tree
		
	#dfs algorithm straigh out of the book
	#retuns the path it took, ommits backtracking
	def dfs(self):
		self.reset()
		path = []
		for u in self.vertList:
			if u.color == 'white':
				path = self.__dfsVisit(u,path)

		return path

	#dfs algorithm straigh out of the book
	def __dfsVisit(self,u,path):
		u.color = 'gray'
		
		v = self.adjList[int(u.getId())].firstLink
		while v != None:
			if v['vertex'].getColor() == 'white':
				v['vertex'].setPredecessor(u)
				self.__dfsVisit(v['vertex'],path)
			v = v['vertex'].getNext()
		
		
		u.setColor('black')
		path.append(u)
		
		return path

	#resets the vertex information for all verticies in the graph's vertex list
	#does not affect the vertex id or coordinates
	def reset(self):
		for v in self.vertList:
			v.reset()
			
