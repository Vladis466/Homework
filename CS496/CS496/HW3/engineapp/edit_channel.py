import webapp2
from google.appengine.ext import blobstore
from google.appengine.ext.webapp import blobstore_handlers
from google.appengine.ext import ndb
import db_defs

class EditChannel(blobstore_handlers.BlobstoreUploadHandler):
    def post(self):
        user = self.request.get('user', 'NOPE')
	#getting the object from the database using the extracted key from the url.
        Study_key = ndb.Key(urlsafe=self.request.get('key'))
        Study = Study_key.get()
        if self.request.get('image-action') == 'remove':
            Study.endFigure = None
        elif self.request.get('image-action') == 'change':
            upload_files = self.get_uploads('icon')
            if upload_files!= []:
                blob_info = upload_files[0]
                Study.endFigure = blob_info.key()
        Study.procedures = [ndb.Key(urlsafe = x) for x in self.request.get_all('procedures[]')]
        Study.put()
        self.redirect('/runStudy?key=' + Study_key.urlsafe() + '&user=' + user + '&type=TS')
        #study&user=' + user