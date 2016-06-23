#defines an edge object
#description = a tuple of vertex objects that form the endpoints of the edge
#weight = integer edge weight
#next = self referential pointer used to connect links in an adjaceny list
class Edge:
	def __init__(self,desc,wght):
		self.description = desc
		self.weight = wght

	def getEdgeDesc(self):
		return self.description

	def getEdgeWeight(self):
		return self.weight