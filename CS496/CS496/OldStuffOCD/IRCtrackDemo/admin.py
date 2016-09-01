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
            ancestor=ndb.Key(db_defs.Channel, self.app.config.get('default-group'))).fetch()]
        # Here is our original renderer on the base page. Now it does what it usually does.
        base_page.BaseHandler.render(self, page, self.template_values)

    def get(self):
        # calls render function of parent class. Done to render the page!
        self.render('admin.html')

    def post(self):
        #returns value of a queryURL or POST argument with the given name.
        action = self.request.get('action')
        if action == 'add_channel':
            k = ndb.Key(db_defs.Channel, self.app.config.get('default-group'))
            chan = db_defs.Channel(parent=k)
            chan.name = self.request.get('channel-name')
            # construct a key from a URL safe string
            chan.classes = [ndb.Key(urlsafe=x) for x in self.request.get_all('classes[]')]
            chan.active = True
            chan.put()  # How to save a channel!
            self.template_values['message'] = 'Added time study ' + chan.name + ' to the database'
        elif action == 'add_class':
            k = ndb.Key(db_defs.ChannelClass, self.app.config.get('default-group'))
            c = db_defs.ChannelClass(parent=k)
            c.name = self.request.get('class-name')
            c.put()
            self.template_values['message'] = 'Added class ' + c.name + 'to the database.'
        elif action == 'del_class':
            k = ndb.Key(db_defs.ChannelClass, self.app.config.get('default-group'))
            c = db_defs.ChannelClass(parent=k)
            c.name = self.request.get('class-name')
            self.template_values['message'] = 'Deleted Procedure ' + c.name + ' from the database'
            db_defs.ChannelClass(parent=k).key.delete()
        else:
            self.template_values['message'] = 'Action ' + action + ' is unknown'
        self.render('admin.html')


        # a key is defined as a type and identifier. SO we make a parent key for all of the channels.
        # The type is a channel (db_defs.channel).
        # The id comes from main with the name base-data(arbitrary name) stored in the config var. We get it out through
        # self.app.config.get() although we could have just hardcoded that string. THIS GENERATES A KEY.

        # db_defs.Channel is the constructor for channels. We call this constructor from db_defs.py
        # we set the chan.name to be whatever we get from the request(html form) and chan.put saves it and the key.
        # Then we render the page and say that the channel was added, else we display an error message.
