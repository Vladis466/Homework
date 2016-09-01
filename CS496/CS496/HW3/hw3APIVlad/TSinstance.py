import webapp2
from google.appengine.ext import ndb
import db_models
import json
from datetime import datetime

class tsinstance(webapp2.RequestHandler):

	def json_serial(self, obj):
#"""JSON serializer for objects not serializable by default json code"""

	    if isinstance(obj, datetime):
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
		new_study = db_models.TSInstance()
		name = self.request.get('name', default_value = None)
		procs = self.request.get_all('procedures[]', default_value = None)
		user = self.request.get('user', default_value = 'Jerry')
		iteration = self.request.get('iter', default_value = 0)
		existCheck = db_models.TimeStudy.query(db_models.TimeStudy.name == name).fetch()
		
		#Make sure that the instance we are creating already exists as a timestudy.
		if existCheck:
			new_study.TSname = name
		else:
			self.response.status = 400
			self.response.status_message = 'Invalid request. Valid Name is required'
			return
		if procs:
			for proc in procs:
				new_study.procedures.append(ndb.Key(db_models.StudyProcedures, int(proc)))
		if user:
			new_study.user = user
		for proc in procs:
			print proc
		if iteration:
			new_study.iteration = int(iteration)
		key = new_study.put()
		out = new_study.to_dict()
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

		q = db_models.TSInstance.query()
		x = q.fetch()
		keys = q.fetch(keys_only = True)
		results = {'keys': [x.id() for x in keys]}
		#self.response.write(json.dumps(results))
		#self.response.write('<br><br>')
		for a in keys:
			Inst = a.get()
			self.response.write(Inst)
			self.response.write('<br><br>')





