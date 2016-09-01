import webapp2
from google.appengine.ext import ndb
import db_models
import json
from datetime import datetime


class tsinstance(webapp2.RequestHandler):
    def json_serial(self, obj):
        # """JSON serializer for objects not serializable by default json code"""

        if isinstance(obj, datetime):
            serial = obj.isoformat()
            return serial
        raise TypeError("Type not serializable")

    def post(self):

        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
            return
        choice = self.request.get('choice', default_value='add')
        name = self.request.get('name', default_value=None)
        existCheck = db_models.TimeStudy.query(db_models.TimeStudy.name == name).get(deadline=5)

        # Make sure that the instance we are creating already exists as a timestudy.
        # Get the iteration number by counting how many times this study has been ran.
        # get the key and throw it in the dictionary with the term 'TimeStudyKey'
        if existCheck:
            if choice == 'add':
                self.new_instance(name, existCheck)
            elif choice == 'updatetime':
                meep = self.request.get('procTimes', default_value="batch")
                datajson = json.loads(meep)
                self.update_instance(datajson)
            elif choice == 'getAllCoords':
                studies_query = db_models.TSInstance.query(db_models.TSInstance.TSname == name).fetch()
                self.getallCoords(studies_query, name)

            else:
                self.response.status = 400
                self.response.status_message = 'Invalid request. Stop curling me.'
                self.response.write("Error within existcheck")
                return
        else:
            self.response.status = 400
            self.response.status_message = 'Invalid request. Time Study does not exist'
            self.response.write("TSDNE")
            return

        # key = new_studyRun.put()
        # out = new_studyRun.to_dict()
        # self.response.write(json.dumps(out, default=self.json_serial)) #Done to jsonify it. Cant because date-time
        return

    # program to
    def getallCoords(self, inst_qris, study_name):
        loc_dict = {'study_name': study_name, 'value_sets': {}}
        for aentity in inst_qris:
            if aentity.location in loc_dict['value_sets']:
                if aentity.datetimeStarted > loc_dict['value_sets'][aentity.location][0]:
                    temparr = [aentity.datetimeStarted, aentity.user]
                    loc_dict['value_sets'][aentity.location] = temparr
            else:
                temparr = [aentity.datetimeStarted, aentity.user]
                loc_dict['value_sets'][aentity.location] = temparr

        loc_dictJSON = json.dumps(loc_dict, default=self.json_serial)
        self.response.write(loc_dictJSON)


        # update the instance with the times recorded for the study.
        # python time is in seconds, javascript in miliseconds (divide by 1000).
    def update_instance(self, instance):
        studyrun = db_models.TSInstance.get_by_id(instance['instanceKey'])
        for prockey in studyrun.procedures:
            currentproc = prockey.get()
            # self.response.write(currentproc)
            # self.response.write(instance['instanceProcs']['startTime' + currentproc.Pname])
            starti = float(instance['instanceProcs']['startTime' + currentproc.Pname]) / 1000.0
            endi = float(instance['instanceProcs']['endTime' + currentproc.Pname]) / 1000.0
            currentproc.startTime = datetime.fromtimestamp(starti).time()
            self.response.write('\n')
            self.response.write('\n')
            self.response.write('\n')
            self.response.write('\n')
            self.response.write('Entity before alteration \n')
            self.response.write(currentproc)
            self.response.write('\n')
            self.response.write('Input new time for end \n')
            self.response.write(datetime.fromtimestamp(endi).time())
            self.response.write('\n')
            self.response.write('current actial procedure end time \n')
            self.response.write(currentproc.endTime)
            currentproc.endTime = datetime.fromtimestamp(endi).time()
            self.response.write('\n')
            self.response.write('Current actual procedure end time after change \n')
            self.response.write(currentproc.endTime)
            self.response.write('\n')
            self.response.write('Entity after alteration\n')
            currentproc.put()
            self.response.write(currentproc)
        studyrun.put()
        return

    def new_instance(self, tsname, tsblueprint):
        new_studyRun = db_models.TSInstance()
        user = self.request.get('user', default_value='Anon')
        geoLocation = self.request.get('location', default_value=None)
        new_Dict = {'studyName': tsname}
        # procedures go in layered dict for obhect creation(javascript)
        new_Dict['instanceProcs'] = {}
        new_studyRun.TSname = tsname
        new_studyRun.user = user
        new_studyRun.iteration = (db_models.TSInstance.query(db_models.TSInstance.TSname == tsname and db_models.TSInstance.user == user).count() + 1)
        new_studyRun.location = geoLocation
        # Get all procedures of the existing time study instance.
        # For each one create a new procedure instance with the given
        # iteration number and the same stats. The timestamp will also serve to identify them.
        # Don't need to add date time because since they are all added at same time, will have the same stamp.
        for procKey in tsblueprint.procedures:
            currProc = procKey.get()
            # Error code 5 means that one of the root studies does not exist.
            if currProc is None:
                self.response.status_message = 'Invalid request. The associated procedure key does not exist.'
                return "5"

            new_studyProc = db_models.StudyProcedures()
            new_studyProc.Pname = currProc.Pname
            new_studyProc.iteration = new_studyRun.iteration
            new_studyProc_key = new_studyProc.put()
            new_studyRun.procedures.append(ndb.Key(db_models.StudyProcedures, int(new_studyProc_key.id())))
            self.response.status_message = 'Succesfully added procedure.'
            # add proc to dict in dict
            new_Dict['instanceProcs'][new_studyProc.Pname] = new_studyProc_key.id()
        # study instances and associated procedures into a dictionary with the name and key.
        # Only need the name and key for the procedures and TS instance. This method is temporary as it
        # forces the user to create a new instance every time. Cannot edit previous results....Which makes sense.
        key = new_studyRun.put()
        new_Dict['instanceKey'] = key.id()
        self.response.write(json.dumps(new_Dict))
        return

    def get(self):
        user = self.request.get('user', default_value='Anon')

        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = 'Not Acceptable, API only supports application/json MIME type'
            return

            # Were looking for id in keyword arguments. We make a key for the mod by passing it a type.
            # From the key we get the mod and turn it into a dictionary. We then dump that to a string and
            # write that back as a response.

        # Retrieve all existing instances for that specific user, if no user provided, retrieve all.
        if user == 'Anon':
            q = db_models.TSInstance.query()
        else:
            q = db_models.TSInstance.query(db_models.TSInstance.user == user)

        x = q.fetch()
        keys = q.fetch(keys_only=True)
        # build a list with all the keys, and then we can turn it into JSON..Easily Transform to javascript object.
        # Use this to set up the studies by fetching all the procedure keys??
        results = {'keys': [x.id() for x in keys]}
        # self.response.write(json.dumps(results))
        # self.response.write('<br><br>')
        for a in keys:
            Inst = a.get()
            self.response.write(Inst)
            self.response.write('<br><br>')
