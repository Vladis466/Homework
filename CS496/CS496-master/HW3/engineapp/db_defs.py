from google.appengine.ext import ndb
#database definitions
class TimeStudy(ndb.Model):
    name = ndb.StringProperty(required = True)  
    procedures = ndb.KeyProperty(repeated = True) 
    endFigure = ndb.BlobKeyProperty()



class TSInstance(ndb.Model):
    TSname = ndb.StringProperty(required = True)  
    user = ndb.StringProperty(required = True)  
    procedures = ndb.KeyProperty(repeated = True)
    datetimeStarted = ndb.DateTimeProperty(auto_now_add = True)
    iteration =  ndb.IntegerProperty(required = True)

class StudyProcedures(ndb.Model):
    Pname = ndb.StringProperty(required = True)
    startTime = ndb.TimeProperty(auto_now_add = True)
    endTime = ndb.TimeProperty(auto_now_add = True)
    datetimeStarted = ndb.DateTimeProperty(auto_now_add = True)
    iteration =  ndb.IntegerProperty(required = True)  #The TSInstance iteration Number






class Message(ndb.Model):
    channel = ndb.StringProperty(required = True)
    date_time = ndb.DateTimeProperty(required = True)
    count = ndb.IntegerProperty(required = True)