import webapp2
from google.appengine.ext import ndb
import db_models
import json
from datetime import datetime
from datetime import time

class timestudies(webapp2.RequestHandler):

    def post(self):


        # create Timestudy entity
        # POST body variables
        # name - required Channel name
        # procs[] - Array of procedure ids
        # user - current user running a study
        
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
            return
        new_Study = db_models.TimeStudy()
        name = self.request.get('name', default_value = None)
        procedures = self.request.get('procedures[]', default_value = 0).split(',')
        existCheck = db_models.TimeStudy.query(db_models.TimeStudy.name == name).fetch()
        if existCheck:
            self.response.status = 400
            self.response.status_message = 'Invalid request. TimeStudy already exists'
            return
        if name:
            new_Study.name = name
        else:
            self.response.status = 400
            self.response.status_message = 'Invalid request. Name is required'
        if procedures:
            for i in procedures:
                new_Study.procedures.append(ndb.Key(db_models.StudyProcedures, int(i)))


        key = new_Study.put()
        out = new_Study.to_dict()
        self.response.write(json.dumps(out)) #lolwut?
        return



    def get(self, **kwargs):
        self.response.write('<meta http-equiv="Cache-control" content="public">')
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
            return

            #Were looking for id in keyword arguments. We make a key for the mod by passing it a type.
            #From the key we get the mod and turn it into a dictionary. We then dump that to a string and 
            #write that back as a response.

        q = db_models.TimeStudy.query()
        x = q.fetch()
        keys = q.fetch(keys_only = True)
        results = {'keys': [x.id() for x in keys]}
        #self.response.write(json.dumps(results))
        #self.response.write('<br><br>')
        for a in keys:
            Inst = a.get()
            self.response.write(Inst)
            self.response.write('<br><br>')





    def delete(self, **kwargs):
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
            return
        if self.request.get('name'):
            q = db_models.TimeStudy.query(db_models.TimeStudy.name == self.request.get('name')).fetch()
            studyProcs = q[0].procedures
            for s in studyProcs:
                self.response.write(s.get())
                s = s.get()
                s.key.delete()
                self.response.write('   DELETED \n\n')
            studyInsts = db_models.TSInstance.query(db_models.TSInstance.TSname == self.request.get('name')).fetch()
            for z in studyInsts:
                self.response.write(z)
                self.response.write('   DELETED \n\n')
                z.key.delete()
            q[0].key.delete() #In case we have duplicates for testing
            self.response.write('\nTimeStudy Deleted, associated instances and procedures deleted')
            return



class studyProcs(webapp2.RequestHandler):
    
    def put(self, **kwargs):
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
            return
        if 'sid' in kwargs:
            Study = ndb.Key(db_models.TimeStudy, int(kwargs['sid'])).get()
            if not Study:
                self.response.status = 404
                self.response.status_message = 'Study not found'
                return
        if 'pid' in kwargs:
            proc = ndb.Key(db_models.StudyProcedures, int(kwargs['pid']))
            if not proc: # NOT Study ??
                self.response.status = 404
                self.response.status_message = 'Procedure not found'
                return  
        if proc not in  Study.procedures:
            Study.procedures.append(proc)
            Study.put()
        self.response.write(json.dumps(Study.to_dict()))
        return          


