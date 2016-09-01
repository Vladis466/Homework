from google.appengine.ext import ndb
#database definitions
class Message(ndb.Model):
    channel = ndb.StringProperty(required = True)
    date_time = ndb.DateTimeProperty(required = True)
    count = ndb.IntegerProperty(required = True)
    
class Channel(ndb.Model):
    name = ndb.StringProperty(required = True)
    classes = ndb.KeyProperty(repeated = True)
    active = ndb.BooleanProperty(required = True)
    icon = ndb.BlobKeyProperty()

class ChannelClass(ndb.Model):
    name = ndb.StringProperty(required = True)

#channel has a name(string), a list of associated classes(list of strings), and whether or not channel is active(bool)
# these are our models....
