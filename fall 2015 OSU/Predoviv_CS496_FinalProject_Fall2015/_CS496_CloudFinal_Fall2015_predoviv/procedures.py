import webapp2
from google.appengine.ext import ndb
import db_models
import json
from datetime import datetime
from datetime import time

class studyProcs(webapp2.RequestHandler):

	def json_serial(self, obj):
#"""JSON serializer for objects not serializable by default json code"""

	    if isinstance(obj, datetime) or isinstance(obj, time):
	        serial = obj.isoformat()
	        return serial
	    raise TypeError ("Type not serializable")	

	def post(self):


		# create channel entity
		# POST body variables
		# name - required Channel name
		# procs[] - Array of procedure ids
		# user - current user running a study
		
		if 'application/json' not in self.request.accept:
			self.response.status = 406
			self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
			return
		new_Proc = db_models.StudyProcedures()
		name = self.request.get('name', default_value = None)
		iteration = self.request.get('iter', default_value = 0)
		if name:
			new_Proc.Pname = name
		else:
			self.response.status = 400
			self.response.status_message = 'Invalid request. Name is required'
		if iteration:
			new_Proc.iteration = int(iteration)
		key = new_Proc.put()
		out = new_Proc.to_dict()
		self.response.write(json.dumps(out, default=self.json_serial)) #lolwut?
		return



	def get(self, **kwargs):
		if 'application/json' not in self.request.accept:
			self.response.status = 406
			self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
			return

			#Were looking for id in keyword arguments. We make a key for the mod by passing it a type.
			#From the key we get the mod and turn it into a dictionary. We then dump that to a string and 
			#write that back as a response.

		q = db_models.StudyProcedures.query()
		x = q.fetch()
		keys = q.fetch(keys_only = True)
		results = {'keys': [x.id() for x in keys]}
		#self.response.write(json.dumps(results))
		#self.response.write('<br><br>')
		for a in keys:
			Inst = a.get()
			self.response.write(Inst)
			self.response.write('<br><br>')

