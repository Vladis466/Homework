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
        new_studyRun = db_models.TSInstance()
        name = self.request.get('name', default_value = None)
        user = self.request.get('user', default_value = 'Anon')
        geoLocation = self.request.get('location', default_value = None)
        existCheck = db_models.TimeStudy.query(db_models.TimeStudy.name == name).get(deadline=5)
        
        #Make sure that the instance we are creating already exists as a timestudy.
        #Get the iteration number by counting how many times this study has been ran.
        if existCheck:
            new_studyRun.TSname = name
            new_studyRun.user = user
            new_studyRun.iteration = (db_models.TSInstance.query(db_models.TSInstance.TSname == name).count() + 1)
            new_studyRun.location = geoLocation
        #Get all procedures of the existing time study instance. For each one create a new procedure instance with the given 
        #iteration number and the same stats. The timestamp will also serve to identify them.
        #Don't need to add date time because since they are all added at same time, will have the same stamp.
            for procKey in existCheck.procedures:
                currProc = procKey.get()
                new_studyProc = db_models.StudyProcedures()
                new_studyProc.Pname = currProc.Pname
                new_studyProc.iteration = new_studyRun.iteration
                new_studyProc_key = new_studyProc.put()
                new_studyRun.procedures.append(ndb.Key(db_models.StudyProcedures, int(new_studyProc_key.id()))) 

        else:
            self.response.status = 400
            self.response.status_message = 'Invalid request. Valid Name is required'
            return


            
        key = new_studyRun.put()
        out = new_studyRun.to_dict()
        #self.response.write(json.dumps(out, default=self.json_serial)) #lolwut?
        return



    def get(self, **kwargs):
        user = self.request.get('user', default_value = 'Anon')

        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
            return

            #Were looking for id in keyword arguments. We make a key for the mod by passing it a type.
            #From the key we get the mod and turn it into a dictionary. We then dump that to a string and 
            #write that back as a response.
        q = db_models.TSInstance.query()
        #Retrieve all existing instances for that specific user, if no user provided, retrieve all.
        if user == 'Anon':
            q = db_models.TSInstance.query()
        else:
            q = db_models.TSInstance.query(db_models.TSInstance.user == user)

        x = q.fetch()
        keys = q.fetch(keys_only = True)
        #build a list with all the keys, and then we can turn it into JSON..Easily Transform to javascript object.
        #Use this to set up the studies by fetching all the procedure keys??
        results = {'keys': [x.id() for x in keys]}
        #self.response.write(json.dumps(results))
        #self.response.write('<br><br>')
        for a in keys:
            Inst = a.get()
            self.response.write(Inst)
            self.response.write('<br><br>')





