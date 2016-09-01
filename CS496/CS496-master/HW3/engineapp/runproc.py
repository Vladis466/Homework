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
class runStudy(base_page.BaseHandler):
    #Overwrite init function(constructor fo class) to give empty dictionary
    def __init__(self, request, response):
        self.initialize(request, response)
        self.template_values = {}
        self.template_values['edit_url'] = blobstore.create_upload_url( '/runStudy/Pics' )

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
            if c.key in Study.procedures:
                c.startTime = time(0,0,0)
                c.endTime = time(0,0,0)
                c.put()
                
                
    def post(self):
        user = self.request.get('user')
        self.template_values['currentUser'] = user
        #self.response.write(cgi.escape("WAHOOOOO"))     #Used to error check
        Stamp = self.request.get('action','NOPE!')
    #request.get returns value of the POST/URL query
        study_key = ndb.Key(urlsafe=self.request.get('key'))
        study = study_key.get()
        self.template_values['study'] = study   
        iterNum = db_defs.TSInstance.query(db_defs.TSInstance.TSname == study.name).count()       
        #If type = TSinst create new instances
        #if self.request.get('type') == 'TSinst':

        procedures = db_defs.StudyProcedures.query(ancestor=ndb.Key(db_defs.StudyProcedures, 'default')).fetch()

        if study.endFigure:
            self.template_values['img_url'] = images.get_serving_url(study.endFigure, crop=True, size=256)

        #First we get the Instance were in by querying for the latest iteration using the Study Name (done above see IterNum)
        #We associate the new procedure if it was 'checked' giving it the same name as before but with a new 'datetimeStarted'
        #and the iteration linked with the current TSinstance.
        if self.request.get('newRun') == 'yes':
            self.response.write(cgi.escape("WAHOOOOO"))
            for c in procedures:                                                                                                                               
                if c.key in study.procedures:
                    k = ndb.Key(db_defs.StudyProcedures, 'default')
                    newProc = db_defs.StudyProcedures(parent=k)
                    newProc.Pname = c.Pname
                    newProc.iteration = iterNum
                    newProc.put()
                    

        #If we clicked the link on admin we assume the User is creating a new instance of studies.
        #Therefore we create a new iteration of the existing study. We then use this iteration to cycle
        #through instances of the existing procedures with this key iteration Number.
        if user:
            k = ndb.Key(db_defs.TSInstance, 'default')
            instance = db_defs.TSInstance(parent=k)
            instance.TSname = study.name
            instance.user = user
            instance.procedures = [ndb.Key(urlsafe=x) for x in self.request.get_all('studies[]')]
            instance.iteration = db_defs.TSInstance.query(db_defs.TSInstance.TSname == study.name).count() + 1
            instance.put()


        
        #If type = TS reset timers
        if self.request.get('type') == 'TS':
            self.resetTimes(procedures, study)
            
        if Stamp == 'start':
            proCedure_key = ndb.Key(urlsafe=self.request.get('chosenProc'))
            proCedure = proCedure_key.get()
            proCedure.startTime = datetime.today().time()
            proCedure.put()
            self.redirect('/runStudy?key=' + study_key.urlsafe() + '&user=' + user + '&type=TS1')
            
        if Stamp == 'end':
            proCedure = ndb.Key(urlsafe=self.request.get('chosenProc')).get()
            proCedure.endTime = datetime.today().time()
            proCedure.put()
                     
            
        proc_list = []
        for c in procedures:                                                                                                                                          
            if c.key in study.procedures:                                                                                                                                        #dis workin on subtracting times
                proc_list.append({'name':c.Pname, 'key':c.key.urlsafe(), 'start':str(c.startTime).split('.')
                                                    [0], 'end':str(c.endTime).split('.')[0], 'totTime': self.timeTot(c.startTime, c.endTime), 'checked': True})
            else:
                proc_list.append({'name':c.Pname, 'key':c.key.urlsafe(), 'checked': False})
        self.template_values['procedures'] = proc_list


            

        #calls render function of parent class. Done to render the page!
        self.template_values['message'] = 'Study: ' + str(study.name)
        self.render('runProc.html', self.template_values)
        self.response.write(str(Stamp)) 
        #self.response.write(str(class_boxes)) 


        
# key is reserves for a special property used to store the Model key. Each entity(object)
# is an instance of ndb.Model or a application-defined subclass of the former.