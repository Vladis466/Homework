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
import base_page
from google.appengine.ext import ndb
from google.appengine.api import images
from google.appengine.ext import blobstore
import db_defs
# here we import the base_page to extend it
class Edit(base_page.BaseHandler):
    #Overwrite init function(constructor fo class) to give empty dictionary
    def __init__(self, request, response):
        self.initialize(request, response)
        self.template_values = {}
        self.template_values['edit_url'] = blobstore.create_upload_url( '/edit/channel' )

        
    def get(self):
	#request.get returns value of the POST/URL query
        if self.request.get('type') == 'channel':
			#using the URL to reconstruct the key and then get the object.
            channel_key = ndb.Key(urlsafe=self.request.get('key'))
            channel = channel_key.get()
            if channel.icon:
                self.template_values['img_url'] = images.get_serving_url(channel.icon, crop=True, size=64)
            self.template_values['channel'] = channel
            classes = db_defs.ChannelClass.query(ancestor=ndb.Key(db_defs.ChannelClass, self.app.config.get('default-group'))).fetch()
            class_boxes = []
            for c in classes:
                if c.key in channel.classes:
                    class_boxes.append({'name':c.name, 'key':c.key.urlsafe(), 'checked': True})
                else:
                    class_boxes.append({'name':c.name, 'key':c.key.urlsafe(), 'checked': False})
            self.template_values['classes'] = class_boxes
        #calls render function of parent class. Done to render the page!
        self.render('edit.html', self.template_values)
    
# key is reserves for a special property used to store the Model key. Each entity(object)
# is an instance of ndb.Model or a application-defined subclass of the former.

