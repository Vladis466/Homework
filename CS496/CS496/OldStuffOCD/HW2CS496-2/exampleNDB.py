from google.appengine.ext import ndb
#database definitions
class TimeStudy
    name = ndb.StringProperty(required = True)  
    
class TSInstance(ndb.Model):
    TSname = ndb.StringProperty(required = True)  
    user = ndb.StringProperty(required = True)  
    Procedures = ndb.KeyProperty(repeated = True)
    dateStarted = ndb.DateTimeProperty(required = True)
    endFigure = ndb.BlobKeyProperty()

class StudyProcedure(ndb.Model):
    Pname = ndb.StringProperty(required = True)
    startTime = ndb.TimeProperty(auto_now_add = True)
    endTime = ndb.TimeProperty(auto_now_add = True)
    iteration =  ndb.IntegerProperty(required = True)
