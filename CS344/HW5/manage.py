import os		#for kage
import sys		#for exit
import errno
import signal
import socket
import optparse
import time
import select
import string

HOST = ''   # Symbolic name, meaning all available interfaces
PORT = 6969 # Arbitrary non-privileged port
LOG = 5		#backlog

def connect():

	#AF_INET: addr domain of socket connects to IPv4 SOCK_STREAM = TCP protocol connection
	#create an internet-based socket
	try:
		sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	except:
		print ('Failed to create socket. Error code: ' + str(msg[0]) + ' , Error message : ' + msg[1])
		sys.exit()
	
	print ('Socket created')
	 
	#reusable port set 
	sockfd.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	
	#Bind socket to local host and port
	try:
		sockfd.bind((HOST, PORT))
	except socket.error as msg:
		print ('Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1])
		sys.exit()
		 
	print ('Socket bind complete')
	 
	#Start listening on socket
	sockfd.listen(LOG)
	print ('Socket now listening on port %d' % PORT)
	
	return sockfd
	
def handleProc(sockConn):
    # read a line that tells us how many bytes to write
    #bytes = int(sock.recv(1024))
    # get our random bytes
    #data = os.urandom(bytes)

	print ('Connected! But I refuse to respond because I would rather keep you up all night')
    # send them all
    #sock.sendall(data)	
	data = sockConn.recv(1024)
	print('data');
	sockConn.sendall(data)

def babySitter(servSock):
	msg = []
	#servSock.close()
	#handleProc(conn)
	# parent - close connected socket
	#conn.close()
	 
	#wait to accept a connection - blocking call
	
	#now keep talking with the client
	
	while 1:
		conn, addr = servSock.accept()
		print ('Connected with ' + addr[0] + ':' + str(addr[1]))
		#now keep talking with the client
		data = conn.recv(15)
		# sending the data to evaluate the size we must reach for performance calc
		print("number: ", data);
		num =  int(data);
		print('Number: ', num);
		msg.append('5')
		msg.append(data)
		conn.sendall(msg[1])



	

def main():

	
	srvSock = connect()
	babySitter(srvSock)
	#conn.close()
	srvSock.close()

	
	
if __name__ == '__main__':
    main()
	

	
	
	
#http://www.binarytides.com/python-socket-server-code-example/