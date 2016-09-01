from django import http
from django.shortcuts import render
import datetime
import cgi
import urllib
from google.appengine.api import users
from google.appengine.ext import ndb
import webapp2


def home(request):
    return http.HttpResponse('Hello World, this is vlad!')

def current_datetime(request):
    now = datetime.datetime.now()
    return render(request, 'current_datetime.html', {'current_date': now})
	
def hours_ahead(request, offset):
    try:
        offset = int(offset)
    except ValueError:
        raise Http404()
    dt = datetime.datetime.now() + datetime.timedelta(hours=offset)
    html = "<html><body>In %s hour(s), it will be %s.</body></html>" % (offset, dt)
    return http.HttpResponse(html)