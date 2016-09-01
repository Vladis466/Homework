import webapp2

class MainHandler(webapp2.RequestHandler):
	def get(self):
		self.response.write('hello from some random URL! <br> Here is a picture of a turtle: <br><img src="/img/Turtles.jpg">')

class CatchAllHandler(webapp2.RequestHandler):
	def get(self):
		self.response.write('hello from some random URL after /one/')
	
app = webapp2.WSGIApplication([
	('/one/?', MainHandler),
	('/one.*', CatchAllHandler)
	
], debug=True)


