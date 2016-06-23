import webapp2
from google.appengine.ext import ndb
import db_models
import json
from datetime import datetime
import hashlib

class userAuth(webapp2.RequestHandler):


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
        newUser = db_models.appUsers()
        Uname = self.request.get('userName', default_value = None)
        Upass = hashlib.md5(self.request.get('passWord', default_value = None)).hexdigest()
        Choice = self.request.get('Choice', default_value = None)
        existCheck = db_models.appUsers.query(db_models.appUsers.userName == Uname).fetch()
        logCheck = db_models.appUsers.query(db_models.appUsers.userName == Uname and db_models.appUsers.passWord == Upass).fetch()
        
        #Make sure that the instance we are creating doesn't allready exist as a user
        #Then proceed to login or register
        if Choice == 'Register':
            if existCheck:
                self.response.status = 400
                self.response.status_message = 'Invalid request. User already exists'
                self.response.write('nope')
            else:
                newUser.userName = Uname
                newUser.passWord = Upass
                key = newUser.put()
                out = newUser.to_dict()
                self.response.write('Registered')
        if Choice == 'Login':
            #make sure the name and password match
            if logCheck:
                self.response.write('yes')
                self.response.status_message = 'Succesfull Login!!'
            else:
                self.response.write('no')
                self.response.status_message = 'Bad credentials!!'
                return
        return



    def get(self, **kwargs):
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
            return

            #Were looking for id in keyword arguments. We make a key for the mod by passing it a type.
            #From the key we get the mod and turn it into a dictionary. We then dump that to a string and 
            #write that back as a response.

        q = db_models.appUsers.query()
        x = q.fetch()
        keys = q.fetch(keys_only = True)
        results = {'keys': [x.id() for x in keys]}
        #self.response.write(json.dumps(results))
        #self.response.write('<br><br>')
        for a in keys:
            Inst = a.get()
            self.response.write(Inst)
            self.response.write('<br><br>')





