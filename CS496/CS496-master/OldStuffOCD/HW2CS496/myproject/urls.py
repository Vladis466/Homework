from django.conf.urls import patterns, include, url

urlpatterns = patterns('',
    url(r'^$', 'hello.views.home'),
	url(r'^time/$', 'hello.views.current_datetime'),
	url(r'^time/plus/(\d{1,2})/$', 'hello.views.hours_ahead'),
)

