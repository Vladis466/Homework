import os       #for kage
import sys      #for exit
import errno
import signal
import socket
import optparse
import time
import select
import string
from threading import *


HOST = ''   # Symbolic name, meaning all available interfaces
PORT = 6969 # Arbitrary non-privileged port
RECBUFF = 4096  #buffer size for recieving messages
LOG = 5     #backlog


def babySitter(servSock, conn_list):
    alias = raw_input("Name: ")
    prompt = raw_input("< " + alias + " >   ")
    while prompt != "quit":
        # Get the list sockets which are ready to be read through select
        read_sockets,write_sockets,error_sockets = select.select(conn_list,[],[])
 
        for sock in read_sockets:
             
            #New connection
            if sock == servSock:
                # Handle the case in which there is a new connection recieved through servSock
                sockfd, addr = servSock.accept()
                conn_list.append(sockfd)
                print "Client (%s, %s) connected" % addr
                 
            #Some incoming message from a client
            else:
                # Data recieved from client, process it
                try:
                    #In Windows, sometimes when a TCP program closes abruptly,
                    # a "Connection reset by peer" exception will be thrown
                    data = sock.recv(RECBUFF)
                    print('Client sent:', sock.recv(1024).decode())
                    # echo back the client message
                    if data:
                        # print data
                        sock.send(prompt + data) 
                # client disconnected, so remove from socket list
                except:
                    print "Client (%s, %s) is offline" % addr
                    sock.close()
                    conn_list.remove(sock)
                    continue
            prompt = raw_input("< " + alias + " >   ")                
         
def connect(connection_list):
    #AF_INET: addr domain of socket connects to IPv4 SOCK_STREAM = TCP protocol connection       #create an internet-based socket
    sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print ('Socket created')
    #reusable port set 
    sockfd.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    #Bind socket to local host and port
    try:
        sockfd.bind((HOST, PORT))
    except socket.error as msg:
        print ('Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1])
        sys.exit()
    #Start listening on socket
    sockfd.listen(LOG)
    print ('Socket now listening on port %d' % PORT)
    connection_list.append(sockfd)
    
    babySitter(sockfd, connection_list)

    servSock.close()

if __name__ == '__main__':

    conn_list = []
    srvSock = connect(conn_list)
    babySitter(srvSock, conn_list)
    #conn.close()
    srvSock.close()
    

    
    
    
#http://www.binarytides.com/python-socket-server-code-example/