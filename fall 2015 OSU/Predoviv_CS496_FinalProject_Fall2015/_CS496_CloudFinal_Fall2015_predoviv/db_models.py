from google.appengine.ext import ndb

#A key cannot be JSONified.
#We have to pull out the ID. 
#So we call the super, override to_dict method.
class Model(ndb.Model):
    def to_dict(self):
        d = super(Model, self).to_dict()
        d['key'] = self.key.id()
        return d
        
class TimeStudy(ndb.Model):
    name = ndb.StringProperty(required = True)  
    procedures = ndb.KeyProperty(repeated = True) 
    endFigure = ndb.BlobKeyProperty()
    #dictionary overrides
    def to_dict(self):
        d = super(TimeStudy, self).to_dict()
        d['procedures'] = [m.id() for m in d['procedures']]
        return d

class TSInstance(ndb.Model):
    TSname = ndb.StringProperty(required = True)  
    user = ndb.StringProperty(required = True)  
    procedures = ndb.KeyProperty(repeated = True)
    datetimeStarted = ndb.DateTimeProperty(auto_now_add = True)
    iteration =  ndb.IntegerProperty(required = False)
    location = ndb.StringProperty(required = False)

class StudyProcedures(ndb.Model):
    Pname = ndb.StringProperty(required = True)
    startTime = ndb.TimeProperty(auto_now = True)
    endTime = ndb.TimeProperty(auto_now = True)
    datetimeStarted = ndb.DateTimeProperty(auto_now_add = True)
    iteration =  ndb.IntegerProperty(required = True)  #The TSInstance iteration Number


class appUsers(ndb.Model):
    userName = ndb.StringProperty(required = True)
    passWord = ndb.StringProperty(required = True)

    