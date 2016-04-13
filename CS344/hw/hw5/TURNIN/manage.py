import os		#for kage
import sys		#for exit
import errno
import signal
import socket
import optparse
import time
import select
import string
import random
import re

HOST = ''   # Symbolic name, meaning all available interfaces
PORT = 6969 # Arbitrary non-privileged port
LOG = 5		#backlog
CONNECTION_LIST = []    # list of socket clients
RECV_BUFFER = 256


#This parser will prepare JSON responses according to what is received.
def Jparser(line):
	#How to extract a number: r'(?<=Performance:)\d+'
	
	#Search for only transmitted performance. If found, prepare a JSON string with send back info
	#Including where to start searching
	searchObj = re.search( r'(^\"Performance\":)\d+$', line, re.I)
	if searchObj:
		print ("searchObj.group() : " + searchObj.group())
		start = random.randint(1, 10000)
		print("Random: ", start)
		Instructions = "{" + line + ',"Start":' + str(start) + "}"
		#Instructions = ' '.join("{", line, ',"start":', str(start), "}")
		
		print("Number Encoded: ", Instructions);
		#print("Random: ", start)
		return Instructions
	#else:
		#print ("not found: " + line)

		
		
#Handles the encoding and decoding of the information, 
#Keeps it out of socket behaviour		
def info(dataRec): 
	performance = dataRec.decode()
	JSONSend = Jparser(performance)
	#print("Random: ", start)

	
	JSONSend = JSONSend.encode()

	#data = b"help"
	return JSONSend




	

def babySitter(servSock):
	
	while CONNECTION_LIST:
        #Attempt at implementing concurrent servers...
		read_sockets,write_sockets,error_sockets = select.select(CONNECTION_LIST,[],[])

		for conn in read_sockets:
			 
			#New connection
			if conn == servSock:
				# Handle the case in which there is a new connection recieved through server_socket
				sockfd, addr = servSock.accept()
				CONNECTION_LIST.append(sockfd)
				#print 'Client (%s, %s) connected' % addr
				 
			#Some incoming message from a client
			else:
				# Data recieved from client, process it
				try:
					print ('Connected with ' + addr[0] + ':' + str(addr[1]))

					data = conn.recv(256)
					if(data == b'hello'):
						conn.send(data2)
						wait(1)
					# echo back the client message
					elif data:
						result = info(data)
						#print ('Here it is: ' result)
						conn.send(result)
						#time.sleep(1)

					data2 = conn.recv(256)
					print(data2)
					if data2:
						result2 = info(data2)
						#print ('Here it is: ' result)
						#conn.sendall(result)
						#wait(5)
                        
				# client disconnected, so remove from socket list
				except:
					#broadcast_data(conn, "Client (%s, %s) is offline" % addr)
					#print "Client (%s, %s) is offline" % addr
					conn.close()
					CONNECTION_LIST.remove(conn)
					continue
                    	 
	servSock.close()

	
#Description: Simple function that takes care of all the initial server socket setup and puts
# it into listening mode with a max client line of LOG
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
    
	CONNECTION_LIST.append(sockfd);
	
	return sockfd














	

def main():

	
	srvSock = connect()
	babySitter(srvSock)
	#conn.close()
	srvSock.close()

	
	
if __name__ == '__main__':
    main()
	

	
	
	
#http://www.binarytides.com/python-socket-server-code-example/