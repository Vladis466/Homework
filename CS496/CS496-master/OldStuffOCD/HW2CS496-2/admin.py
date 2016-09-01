import webapp2
import base_page
from google.appengine.ext import ndb
from google.appengine.ext import blobstore
import db_defs


# here we import the base_page to extend it
class Admin(base_page.BaseHandler):
    # Overwrite init function(constructor fo class) to give empty dictionary
    def __init__(self, request, response):
        self.initialize(request, response)
        self.template_values = {}
        self.template_values['upload_url'] = blobstore.create_upload_url('/channel/add')

    # render was overwritten, so now instead of rendering the template it does what is stated below
    def render(self, page):
        # python list comprehension: The query.fetch is how we get our channels that are stored in the database.
        # for each x in channels we want to make a dictionary with a name assoc with channel name
        # and key into a string we can pass to a site.
        self.template_values['classes'] = [{'name': x.name, 'key': x.key.urlsafe()} for x in
                                           db_defs.ChannelClass.query().fetch()]
        self.template_values['channels'] = [{'name': x.name, 'key': x.key.urlsafe()} for x in db_defs.Channel.query(
            ancestor=ndb.Key(db_defs.Channel, 'default')).fetch()]
        # Here is our original renderer on the base page. Now it does what it usually does.
        base_page.BaseHandler.render(self, page, self.template_values)

    def get(self):
        # calls render function of parent class. Done to render the page!
        self.render('admin.html')

    def post(self):
        #returns value of a queryURL or POST argument with the given name.
        action = self.request.get('action')
        if action == 'add_channel':
            k = ndb.Key(db_defs.Channel, 'default')
            chan = db_defs.Channel(parent=k)
            chan.name = self.request.get('channel-name')
            # construct a key from a URL safe string
            if chan.name == "":
                self.template_values['message'] = 'Invalid Value, Please try again.'
            else:
                chan.classes = [ndb.Key(urlsafe=x) for x in self.request.get_all('classes[]')]
                chan.active = True
                chan.put()  # How to save a channel!
                self.template_values['message'] = 'Added time study ' + chan.name + ' to the database'
 

 
 
 
        elif action == 'del_channel':
            self.template_values['channels'] = [{'name': x.name, 'key': x.key.urlsafe()} for x in db_defs.Channel.query(
                                        ancestor=ndb.Key(db_defs.Channel, 'default')).fetch()]
            Tkey = [d['key'] for d in self.template_values['channels'] if d['name'] == self.request.get('channel-name')]
            if Tkey:
                self.template_values['message'] = 'Succesfully deleted'
                ndb.Key(urlsafe=str(Tkey)).delete()
            else:
                self.template_values['message'] = 'Procedure not found. Deletion failed.'
            
            
            
            #
            #
            #
        elif action == 'add_class':
            k = ndb.Key(db_defs.ChannelClass, 'default')
            c = db_defs.ChannelClass(parent=k)
            c.name = self.request.get('class-name')
            if c.name == "":
                self.template_values['message'] = 'Invalid Value, Please try again.'
            else:
                self.template_values['message'] = 'Added procedure ' + c.name + ' to the database.'
                c.put()           
            
            #Query all the different procedures currently in the database
            #Isolate the entity matching the class name selected
            #Delete that entity
        elif action == 'del_class':
            self.template_values['classes'] = [{'name': x.name, 'key': x.key.urlsafe()} for x in
                                           db_defs.ChannelClass.query().fetch()]
            Tkey = [d['key'] for d in self.template_values['classes'] if d['name'] == self.request.get('class-name')]
            if Tkey:
                self.template_values['message'] = 'Succesfully deleted'
                ndb.Key(urlsafe=str(Tkey)).delete()
            else:
                self.template_values['message'] = 'Procedure not found. Deletion failed.'
                
        elif action == 'login':
            self.template_values['message'] = 'Welcome!'
        else:
            self.template_values['message'] = ' '# + action + ' is unknown'
        self.render('admin.html')


        # a key is defined as a type and identifier. SO we make a parent key for all of the channels.
        # The type is a channel (db_defs.channel).
        # The id comes from main with the name base-data(arbitrary name) stored in the config var. We get it out through
        # self.app.config.get() although we could have just hardcoded that string. THIS GENERATES A KEY.

        # db_defs.Channel is the constructor for channels. We call this constructor from db_defs.py
        # we set the chan.name to be whatever we get from the request(html form) and chan.put saves it and the key.
        # Then we render the page and say that the channel was added, else we display an error message.
