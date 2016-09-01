import webapp2
from google.appengine.ext import ndb
import db_models
import json
from datetime import datetime
from datetime import time

class studyProcs(webapp2.RequestHandler):

    def json_serial(self, obj):
    # """JSON serializer for objects not serializable by default json code"""

        if isinstance(obj, datetime) or isinstance(obj, time):
            serial = obj.isoformat()
            return serial
        raise TypeError ("Type not serializable")

    def post(self):

        # Creates a new autonomous procedure, taking in the procedure name from the user.
        # Ideally, these should be highly personalized names like BoeingEMC3rdLineBoltCutter

        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
            return
        name = self.request.get('name', default_value = None)

        existCheck = db_models.StudyProcedures.query(db_models.StudyProcedures.Pname == name).get(deadline=5)
        if existCheck:
            self.response.write("PnameIssue")
        else:
            new_Proc = db_models.StudyProcedures()
            new_Proc.iteration = 0
            new_Proc.Pname = name
            new_Proc.put()
            # out = new_Proc.to_dict()
            #self.response.write(json.dumps(out, default=self.json_serial)) #lolwut?
            return



    def get(self, **kwargs):
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
            return

            # Were looking for id in keyword arguments. We make a key for the mod by passing it a type.
            # From the key we get the mod and turn it into a dictionary. We then dump that to a string and
            # write that back as a response.

        q = db_models.StudyProcedures.query()
        # x = q.fetch()
        keys = q.fetch(keys_only=True)
        # results = {'keys': [x.id() for x in keys]}
        # self.response.write(json.dumps(results))
        # self.response.write('<br><br>')
        for a in keys:
            Inst = a.get()
            self.response.write(Inst)
            self.response.write('<br><br>')

# i seem to have really brute forced this solution. Could have gotten a dictionary of the keys and names. then
# sent it on it's way instead of sending much more data and leaving the bulk of the processing power to the app.
