#defines a vertex object
#id = city id (string).
#cords = tuple of integers representing x and y coordinates
#set = integer id used in Kruskal's algorithm to define sets of vertices
#visited = boolean that indicates whether or not a vertex has been visited

class Vertex:
	def __init__(self,name,pos):
		self.id = name
		self.cords = pos
		self.set = set()
		self.color = 'white'
		self.key = float('inf')
		self.predecessor = None
		self.next = None

	#---------------getters and setters------------------------------------------------------------------------------------------

	def getId(self):
		return self.id

	def getCords(self):
		return self.cords

	def getSet(self):
		return self.set

	def setSet(self,s):
		self.set = s

	def getNext(self):
		return self.next

	def setNext(self,v):
		self.next = v

	def setColor(self,c):
		self.color = c

	def getColor(self):
		return self.color

	def getPredecessor(self):
		return self.predecessor

	def setPredecessor(self,p):
		self.predecessor = p

	def getKey(self):
		return self.key

	def setKey(self,k):
		self.key = k

	#------------------------end getters and setters------------------------------------------------------------------------------


	#-----------------------------overloaded operators--------------------------------------------------------------------------
	
	def __lt__(self,other):
		return self.key < other.key

	def __le__(self,other):
		return self.key <= other.key 

	def __gt__(self,other):
		return self.key > other.key

	def __ge__(self,other):
		return self.key >= other.key

	#def __eq__(self,other):
	#	return self.key == other.key

	#def __ne__(self,other):
	#	return self.key != other.key

	#---------------------------end overloaded operators--------------------------------------------------------------------------

	#resets a single vertex (only the mutable data)
	def reset(self):
		self.set = None
		self.color = 'white'
		self.key = float('inf')
		self.predecessor = None

	