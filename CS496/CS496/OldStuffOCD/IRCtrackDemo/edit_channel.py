import webapp2
from google.appengine.ext import blobstore
from google.appengine.ext.webapp import blobstore_handlers
from google.appengine.ext import ndb
import db_defs

class EditChannel(blobstore_handlers.BlobstoreUploadHandler):
    def post(self):
	#getting the object from the database using the extracted key from the url.
        channel_key = ndb.Key(urlsafe=self.request.get('key'))
        channel = channel_key.get()
        if self.request.get('image-action') == 'remove':
            channel.icon = None
        elif self.request.get('image-action') == 'change':
            upload_files = self.get_uploads('icon')
            if upload_files!= []:
                blob_info = upload_files[0]
                channel.icon = blob_info.key()
        channel.classes = [ndb.Key(urlsafe = x) for x in self.request.get_all('classes[]')]
        channel.put()
        self.redirect('/edit?key=' + channel_key.urlsafe() + '&type=channel')