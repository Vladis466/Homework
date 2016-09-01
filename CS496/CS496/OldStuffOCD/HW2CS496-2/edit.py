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
import re
import cgi
import webapp2
import base_page
from google.appengine.ext import ndb
from google.appengine.api import images
from google.appengine.ext import blobstore
import db_defs
from datetime import datetime, date, time
# here we import the base_page to extend it
class Edit(base_page.BaseHandler):
    #Overwrite init function(constructor fo class) to give empty dictionary
    def __init__(self, request, response):
        self.initialize(request, response)
        self.template_values = {}
        self.template_values['edit_url'] = blobstore.create_upload_url( '/edit/channel' )

    def get(self):
        self.post()

    def timeStart(self, value):
        startVal = datetime.now().time()
        
    def timeTot(self, enter, exit):
        Total = str(datetime.combine(date.today(), exit) - datetime.combine(date.today(), enter)).split('.')
        time_re = re.compile(r'([0-9]+):([0-5][0-9]):([0-5][0-9])')
        reTotal = re.search(time_re, str(Total))
        self.response.write(str(reTotal.group(0))) 
        return (str(reTotal.group(0)))
    
    def resetTimes(self, Procs, Study):
        for c in Procs:
            if c.key in Study.classes:
                c.startTime = time(0,0,0)
                c.endTime = time(0,0,0)
                c.put()
                
                
    def post(self):
        #self.response.write(cgi.escape(self.request.get('classes[]')))
        Stamp = self.request.get('action','NOPE!')
    #request.get returns value of the POST/URL query
        channel_key = ndb.Key(urlsafe=self.request.get('key'))
        channel = channel_key.get()
        self.template_values['channel'] = channel    
        

        if channel.icon:
            self.template_values['img_url'] = images.get_serving_url(channel.icon, crop=True, size=256)
        procedures = db_defs.ChannelClass.query(ancestor=ndb.Key(db_defs.ChannelClass, 'default')).fetch()
        
        if self.request.get('type') == 'channel':
            self.resetTimes(procedures, channel)
            
        if Stamp == 'start':
            proCedure_key = ndb.Key(urlsafe=self.request.get('chosenProc'))
            proCedure = proCedure_key.get()
            proCedure.startTime = datetime.today().time()
            proCedure.put()
            self.redirect('/edit?key=' + channel_key.urlsafe() + '&type=channel1')
            
        if Stamp == 'end':
            proCedure = ndb.Key(urlsafe=self.request.get('chosenProc')).get()
            proCedure.endTime = datetime.today().time()
            proCedure.put()
            
            #self.redirect('/edit?key=' + channel_key.urlsafe() + '&type=channel1')            
            
        class_boxes = []
        for c in procedures:                                                                                                                                                           #datetime.combine(date.today(), c.startTime) - datetime.combine(date.today(), c.endTime)
            if c.key in channel.classes:                                                                                                                                        #dis workin on subtracting times
                class_boxes.append({'name':c.name, 'key':c.key.urlsafe(), 'start':str(c.startTime).split('.')
                                                    [0], 'end':str(c.endTime).split('.')[0], 'totTime': self.timeTot(c.startTime, c.endTime), 'checked': True})
            else:
                class_boxes.append({'name':c.name, 'key':c.key.urlsafe(), 'checked': False})
        self.template_values['classes'] = class_boxes


            

        #calls render function of parent class. Done to render the page!
        self.template_values['message'] = 'Study: ' + str(channel.name)
        self.render('edit.html', self.template_values)
        self.response.write(str(Stamp)) 
        #self.response.write(str(class_boxes)) 


        
# key is reserves for a special property used to store the Model key. Each entity(object)
# is an instance of ndb.Model or a application-defined subclass of the former.