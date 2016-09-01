#!/usr/bin/env python
#
# Copyright 2007 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
import webapp2
import datetime
import random
html =  """
<!doctype html>
<html lang="en">
	<head>
		<meta charset="utf-8"/>
		<title>Form Example</title>
	</head>
	<body>
	<center>
		<h1>REFRESH OR SUBMIT TO ENGAGE TELEPORTATION MECHANISM</h1>
		<br><br><br><br>
		
		<form action="http://vladis4661.appspot.com">
  RANDOM:<br>
  <input type="text" name="RANDOM" value="Submit"">
  <br>
  INPUT:<br>
  <input type="text" name="INPUT" value="meeee">
  <br><br>
  <input type="submit" value="Submit">
		</form>

<br><br><br><br>
	</body>
	</center>
</html>
"""
long = random.uniform(0, 90)
TheTime = datetime.datetime.strftime(datetime.datetime.now(), '%Y-%m-%d %H:%M:%S')
Link1 = '<img src="https://maps.googleapis.com/maps/api/staticmap?center='
Link2 = ',-73.998672&zoom=12&size=400x400&key=AIzaSyCegMqpUaZVkbVV_4-obbVtTUNLMOlu0cE">/'

Link3 = Link1 + str(long) + Link2
class MainHandler(webapp2.RequestHandler):
    def get(self):
	    
		self.response.write('<center>' +Link1 + str(random.uniform(0, 90)) + Link2)
		self.response.write(html)
		self.response.write(str(random.uniform(0, 90))) 
		self.response.write('<center><p>Meow Meow ' + str(datetime.datetime.utcnow()) + '</p></center>\r\n')
		self.response.write('Im frozen --->' + TheTime)

app = webapp2.WSGIApplication([
    ('/', MainHandler)
], debug=True)
