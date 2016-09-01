import webapp2
from google.appengine.api import oauth

# resource based but not RESTful. Missing cache properties and uri based.

app = webapp2.WSGIApplication([
#takes us to mod class as a handler where we can do to get or post to get a list of mods or get new mods.
	('/mod', 'mod.Mod')
	], debug = True)

#takes a mod and then an id which is a string of integers. This will look up an individual mod
									#ID is the variable name of the argument to be passed. The [0-9] is the argument to be passed
app.router.add(webapp2.Route(r'/mod/<id:[0-9]+><:/?>', 'mod.Mod'))
#Search based on name.
app.router.add(webapp2.Route(r'/mod/search', 'mod.ModSearch'))
#Effectively same thing as /mod
app.router.add(webapp2.Route(r'/channel', 'channel.Channel'))
#Channel has a list of mods. This is how we add mods to channel (Via PUT) or lookup a mod.
app.router.add(webapp2.Route('/channel/<cid:[0-9]+>/mod/<mid:[0-9]+><:/?>', 'channel.ChannelMods'))
	
