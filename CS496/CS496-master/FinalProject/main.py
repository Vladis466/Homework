import webapp2
from google.appengine.api import oauth

# resource based but not RESTful. Missing cache properties and uri based.

app = webapp2.WSGIApplication([
#takes us to mod class as a handler where we can do to get or post to get a list of mods or get new mods.
	('TimeStudies', 'TimeStudies.timestudies')
	], debug = True)



#Search based on name.
app.router.add(webapp2.Route(r'/TimeStudies', 'TimeStudies.timestudies'))
#Search based on name.
app.router.add(webapp2.Route(r'/TSinstance', 'TSinstance.tsinstance'))
#Search based on name.
app.router.add(webapp2.Route(r'/studyProcedures', 'procedures.studyProcs'))
#Search based on name.
app.router.add(webapp2.Route(r'/UserAuth', 'UserAuth.userAuth'))
#TimeStudies has a list of procedures. This is how we add procs to a timestudy (Via PUT) or lookup a proc.
app.router.add(webapp2.Route('/TimeStudies/<sid:[0-9]+>/proc/<pid:[0-9]+><:/?>', 'TimeStudies.studyProcs'))