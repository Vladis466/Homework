import socket
import threading
import time
import sys

HOST = ''   # Symbolic name, meaning all available interfaces
RECBUFF = 1024  #buffer size for recieving messages
LOG = 45    #backlog


#initialize the server. The idea for a class object was found on an online forum. (I thought it resulted in a much neater portrayal)
class ThreadedServer(object):
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind((socket.gethostname(), self.port))
        #self.sock.setblocking(0)
        self.tLock = threading.Lock()

    # Thread is spawned whose sole purpose is to read in and print the client's messages
    def listenToClient(self, client, address,alias):
        while True:
            try:
                data = client.recv(RECBUFF)
                if data:
                    if data == "\quit\n":
                        print "Client has closed the connection. Type in ok and press enter to continue"
                        client.close()
                        return False
                        
                    else:
                        print "\n" + data
                else:
                    raise error('Client disconnected')
            except:
                client.close()
                return False


    # This function takes the users input initially and gives back the hostname
    def listen(self):
        alias = raw_input("Name: ")
        print "Welcome " + alias
        print "Your hostname is " + socket.gethostname()

        # listen for a client. When found spawn a thread to recieve the clients messages
        while True:
            print "Listening for a client....."
            self.sock.listen(10)
            client, address = self.sock.accept()
            prompt = "client connected on port " + str(self.port)
            client.settimeout(LOG)
            threading.Thread(target = self.listenToClient,args = (client,address,alias)).start()
            while True:
                #The thread allows us to accept and send messages autonomously.
                #Search for keyword \quit, appart from that just send messages when the prompt is filled.
                if prompt == "\quit":
                    print "Disconnecting from client..."
                    print "OVER HEE ----->" + prompt
                    client.send("\n" + prompt + "\n")
                    break
                if prompt != '':
                    try:
                        client.send("\n < " + alias + " >  " + prompt + "\n")
                    except:
                        #client disconnected
                        break
                prompt = str(raw_input("< " + alias + " >   "))
                time.sleep(.2)

            client.close()
            print "Connection ended"



#program starts here.

if __name__ == "__main__":
    port_num = int(sys.argv[1])
    ThreadedServer(HOST,port_num).listen()