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
        self.template_values['StudyProcedures'] = [{'name': x.Pname, 'key': x.key.urlsafe()} for x in db_defs.StudyProcedures.query().fetch()]
        self.template_values['TSInstance'] = [{'name': x.TSname, 'key': x.key.urlsafe()} for x in db_defs.TSInstance.query().fetch()]
        self.template_values['TimeStudies'] = [{'name': x.name, 'key': x.key.urlsafe()} for x in db_defs.TimeStudy.query(ancestor=ndb.Key(db_defs.TimeStudy, 'default')).fetch()]
        # Here is our original renderer on the base page. Now it does what it usually does.
        base_page.BaseHandler.render(self, page, self.template_values)

    def get(self):
        # calls render function of parent class. Done to render the page!
        self.render('admin.html')

    def post(self):
        #returns value of a queryURL or POST argument with the given name.
        user = self.request.get('Uname','NOPE!')
        self.template_values['currentUser'] = user
        
        action = self.request.get('action')
        #Create our instance with the userif he does not exist.

        if action == 'add_study':
            k = ndb.Key(db_defs.TimeStudy, 'default')
            Study = db_defs.TimeStudy(parent=k)
            Study.name = self.request.get('study-name')
            # construct a key from a URL safe string
            if Study.name == "":
                self.template_values['message'] = 'Invalid Value, Please try again.'
            else:
                Study.procedures = [ndb.Key(urlsafe=x) for x in self.request.get_all('studies[]')]
                Study.put() 
                self.template_values['message'] = 'Added time study ' + Study.name + ' to the database'
 

 
 
 
        elif action == 'del_study':
            self.template_values['TimeStudy'] = [{'name': x.name, 'key': x.key.urlsafe()} for x in db_defs.TimeStudy.query(ancestor=ndb.Key(db_defs.TimeStudy, 'default')).fetch()]
            Tkey = [d['key'] for d in self.template_values['TimeStudy'] if d['name'] == self.request.get('study-name')]
            if Tkey:
                self.template_values['message'] = 'Succesfully deleted'
                ndb.Key(urlsafe=str(Tkey)).delete()
            else:
                self.template_values['message'] = 'Procedure not found. Deletion failed.'
            
            
            
            #
            #
            #
        elif action == 'add_proc':
            k = ndb.Key(db_defs.StudyProcedures, 'default')
            c = db_defs.StudyProcedures(parent=k)
            c.Pname = self.request.get('proc-name')
            c.iteration = 0
            if c.Pname == "":
                self.template_values['message'] = 'Invalid Value, Please try again.'
            else:
                self.template_values['message'] = 'Added procedure ' + c.Pname + ' to the database.'
                c.put()           
                self.redirect('/admin')
            #Query all the different procedures currently in the database
            #Isolate the entity matching the class name selected
            #Delete that entity
        elif action == 'del_proc':
            self.template_values['StudyProcedures'] = [{'name': x.Pname, 'key': x.key.urlsafe()} for x in
                                           db_defs.StudyProcedures.query().fetch()]
            Tkey = [d['key'] for d in self.template_values['StudyProcedures'] if d['name'] == self.request.get('proc-name')]
            if Tkey:
                self.template_values['message'] = 'Succesfully deleted'
                ndb.Key(urlsafe=str(Tkey)).delete()
            else:
                self.template_values['message'] = 'Procedure not found. Deletion failed.'
                


        elif action == 'login':
            self.template_values['message'] = 'Welcome! ' + user
        else:
            self.template_values['message'] = ' '# + action + ' is unknown'

        self.render('admin.html')