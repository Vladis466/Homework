import webapp2
import os
import jinja2

#loads the files at the directory where this __file__ is in + the templates directory. It looks for the templates directory.
JINJA_ENVIRONMENT = jinja2.Environment(
    loader = jinja2.FileSystemLoader(os.path.dirname(__file__) + '/templates'),
    extensions = ['jinja2.ext.autoescape'],
    autoescape = True
    )


class HelloWorld(webapp2.RequestHandler):
    template_variables = {}
    
    def get(self):      #Any time it gets a get request(typical) will always look for get request and route it there..
        template = JINJA_ENVIRONMENT.get_template('helloworld.html')
        self.response.write(template.render())
     #in post we defined the variable form content. For every element i that was submitted, create a new entry
#Create a dictionary with [i] = username and message keys and then get the value of these in the self.request.get
    def post(self):
        self.template_variables['form_content'] = {}
        template = JINJA_ENVIRONMENT.get_template('helloworld.html')
        for i in self.request.arguments():
            self.template_variables['form_content'][i] = self.request.get(i)
        self.response.write(template.render(self.template_variables))

    


