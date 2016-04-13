import socket   #for sockets
import sys  #for exit
HOST = 'localhost'
PORT = 6969 

#TCP socket create, get host IP, connect
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ip = socket.gethostbyname( HOST ) 
print ('Ip address of ' + HOST + ' is ' + ip)
sock.connect((ip , PORT))
 
print ('Socket Connected to ' + HOST + ' on ip ' + ip)
sock.send(b'hello')
data = sock.recv(1024)
print ("\n\n\n" + data.decode())
#print ('received "%s"' % (sock.getsockname(), data))
if not data:
	print('closing socket', sock.getsockname())
	sock.close()