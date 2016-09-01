import webapp2
import base_page
from google.appengine.ext import ndb
from google.appengine.ext import blobstore
import db_defs


# here we import the base_page to extend it
class Home(base_page.BaseHandler):
    # Overwrite init function(constructor fo class) to give empty dictionary
    def __init__(self, request, response):
        self.initialize(request, response)
        self.template_values = {}

    # render was overwritten, so now instead of rendering the template it does what is stated below
    def render(self, page):
        # python list comprehension: The query.fetch is how we get our channels that are stored in the database.
        # for each x in channels we want to make a dictionary with a name assoc with channel name
        # and key into a string we can pass to a site.
        self.template_values['Procedures'] = [{'name': x.Pname, 'key': x.key.urlsafe()} for x in
                                           db_defs.StudyProcedures.query().fetch()]
        self.template_values['Studies'] = [{'name': x.name, 'key': x.key.urlsafe()} for x in db_defs.TimeStudy.query(
            ancestor=ndb.Key(db_defs.TimeStudy, 'default')).fetch()]
        # Here is our original renderer on the base page. Now it does what it usually does.
        base_page.BaseHandler.render(self, page, self.template_values)

    def get(self):
        #user = self.request.get('Uname')
        #self.template_values['user'] = user
        #if user != "":
            #self.redirect('/admin?' + 'user=' + user)
        # calls render function of parent class. Done to render the page!
        self.render('home.html')

    def post(self):
        self.get()
