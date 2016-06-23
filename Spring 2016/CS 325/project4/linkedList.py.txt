import edge
import copy

#very basic linked list blueprint
class LinkedList:
	def __init__(self):
		self.firstLink = None

	def isEmpty():
		return self.firstLink == None

	#v = a dictionary of this form {'vertex':vertex obj,'weight':int}
	def addLink(self,v):
		v['vertex'].setNext(self.firstLink)
		self.firstLink = copy.copy(v)
		
