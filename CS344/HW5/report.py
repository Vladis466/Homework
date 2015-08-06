import socket   #for sockets
import sys  #for exit
HOST = 'localhost'
PORT = 6969 

#TCP socket create, get host IP, connect
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ip = socket.gethostbyname( HOST ) 
print 'Ip address of ' + HOST + ' is ' + ip
s.connect((remote_ip , PORT))
 
print 'Socket Connected to ' + HOST + ' on ip ' + ip

data = s.recv(1024)
print >>sys.stderr, '%s: received "%s"' % (s.getsockname(), data)
if not data:
	print >>sys.stderr, 'closing socket', s.getsockname()
	s.close()