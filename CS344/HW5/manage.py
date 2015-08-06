import os		#for kage
import sys		#for exit
import errno
import signal
import socket
import optparse
import time
import select

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
	
def handleChild(sockConn):
    # read a line that tells us how many bytes to write
    #bytes = int(sock.recv(1024))
    # get our random bytes
    #data = os.urandom(bytes)

	print ('Connected! But I refuse to respond because I would rather keep you up all night')
    # send them all
    #sock.sendall(data)	
	data = sockConn.recv(1024)
	sockConn.sendall(data)

def babySitter(servSock):
	spawnCnt = 0
	# spawn a new child process for every request
	while True:
		try:
			conn, cliAddr = servSock.accept()
			
		#used for socket errors within exceptions(changed in 2.6, I know outraichous)
		except IOError as e:
			code, msg = e.args
			#if this is the error, retry, not actually broke. o/w you probs broke something
			if code == errno.EINTR:
				continue
			else:
				raise

		pid = os.fork()
		if pid == 0: # child
			spawnCnt += 1
			# close listening socket
			print ('Spawning: %d' %spawnCnt)
			servSock.close()
			handleChild(conn)
			os._exit(0)

		# parent - close connected socket
		conn.close()
	 
	#wait to accept a connection - blocking call
	#conn, addr = servSock.accept()
	#now keep talking with the client
	#while 1:
		
		#print ('Connected with ' + addr[0] + ':' + str(addr[1]))
		#now keep talking with the client
		#data = conn.recv(1024)
		#conn.sendall(data)







	

def main():

	
	srvSock = connect()
	babySitter(srvSock)
	#conn.close()
	srvSock.close()

	
	
if __name__ == '__main__':
    main()


	
	
	
#http://www.binarytides.com/python-socket-server-code-example/