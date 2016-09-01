import webapp2
from google.appengine.ext import ndb
import db_models
import json

#Methods that specifically handle POST or GET or PUT or DELETE
#In a move to be RESTful only give back what user provides
class Mod(webapp2.RequestHandler):
	def post(self):
		# creates a Mod entity
		# nick - required nickname
		# email - email address
		# name - real name
		
		#Client has to ask for application JSON representation in the accept of the header.
		if 'application/json' not in self.request.accept:
			self.response.status = 406
			self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
			return

		new_mod = db_models.Mod()
		nick = self.request.get('nick', default_value = None)
		email = self.request.get('email', default_value = None)
		name = self.request.get('name', default_value = None)
		if nick:
			new_mod.nick = nick
		else:
			self.response.status = 400
			self.response.status_message = 'Invalid request. Nickname is required'
		if email:
			new_mod.email = email
		if name:
			new_mod.name = name
		#Email and name are optional
		#Save in database and return the thing we made.
		key = new_mod.put()
		out = new_mod.to_dict()  #Returns the properties values in dictionary form
		self.response.write(json.dumps(out))
		
		#kwargs = keywordarguments
	def get(self, **kwargs):
		if 'application/json' not in self.request.accept:
			self.response.status = 406
			self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
			return

			#Were looking for id in keyword arguments. We make a key for the mod by passing it a type.
			#From the key we get the mod and turn it into a dictionary. We then dump that to a string and 
			#write that back as a response.
		if 'id' in kwargs:
			out = ndb.Key(db_models.Mod, int(kwargs['id'])).get().to_dict()
			self.response.write(json.dumps(out))

			#If there isnt an 'id' in the keyword arguments, we return all the IDs.
		else:
			q = db_models.Mod.query()
			keys = q.fetch(keys_only = True)
			results = {'keys': [x.id() for x in keys]}
			self.response.write(json.dumps(results))
			
class ModSearch(webapp2.RequestHandler):
	# should be get not post
	def post(self):
		# search for moderators
		# POST body variables:
		# nick - String nickname
		# email - String email address
		
		if 'application/json' not in self.request.accept:
			self.response.status = 406
			self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
			return
		q = db_models.Mod.query()
		if self.request.get('nick', None):
			q = q.filter(db_models.Mod.nick == self.request.get('nick'))
		if self.request.get('email', None):
			q = q.filter(db_models.Mod.email == self.request.get('email'))
		keys = q.fetch(keys_only = True)
		results = {'keys': [x.id() for x in keys]}
		self.response.write(json.dumps(results))