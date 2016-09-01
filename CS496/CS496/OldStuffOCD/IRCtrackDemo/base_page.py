import webapp2
import os
import jinja2


# loads the files at the directory where this __file__ is in + the templates directory.
# It looks for the templates directory.
class BaseHandler(webapp2.RequestHandler):
    @webapp2.cached_property  # made it a cached property, First time calculate value, then just return value(calculated)
    def jinja2(self):  # Any time it gets a get request(typical) will always look for get request and route it there..
        return jinja2.Environment(
            loader=jinja2.FileSystemLoader(os.path.dirname(__file__) + '/templates'),
            extensions=['jinja2.ext.autoescape'],
            autoescape=True
        )

    #   this func takes in the template to be rendered and it's vars(defaults to empty)
    def render(self, template, template_variables={}):
        template = self.jinja2.get_template(template)
        self.response.write(template.render(template_variables))

# in post we defined the variable form content. For every element i that was submitted, create a new entry
# Create a dictionary with [i] = username and message keys and then get the value of these in the self.request.get
