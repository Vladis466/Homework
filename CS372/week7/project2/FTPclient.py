import socket
import threading
import time
import sys


RECBUFF = 1024  #buffer size for recieving messages


#initialize the client. The idea for a class object was found on an online forum. (I thought it resulted in a much neater portrayal)
class FTPClient(object):
    def __init__(self, host, sport, command, dport, fname):
        self.serv_host = host
        self.serv_port = sport
        self.command = command
        self.file_name = fname
        self.rec_name = fname.split('.')[0] + '2.txt'
        self.sock = socket.socket()
        #Info for data
        self.sock2 = socket.socket()
        self.data_port = dport
        self.str_data_port = str(dport)
    # This function takes the users input initially and sends out a string to the server. It then calls recData
    def runFTP(self):
        self.sock.connect((self.serv_host, self.serv_port))

        self.sock.send(self.command+self.str_data_port+self.file_name); 
        self.recData()
        print "Transmission finished, closing main connection now, goodbye friend.\n\n"
        self.sock.close()
    # recData recieves the data from the server and displays output to the user depending on the command.
    def recData(self):
        import time
        file_out = []
        timeout = 0
        time.sleep(1)

        self.sock2.connect((self.serv_host,self.data_port))
        if self.command == "-l":
            data = self.sock2.recv(512)
            print "\n\n ****** Incoming directory ******* \n\n"
            print data
            print "\n\n ****** End directory ******* \n\n"
        elif self.command =="-g":
            print self.sock2.recv(512)
            start_time = time.time()
            timeout = 2
            with open(self.rec_name, "w") as text_file:
                #file closed automatically due to content manager (with)
                while True:
                    if time.time() - start_time > timeout:
                        break
                    data = self.sock2.recv(RECBUFF)
                    if data:
                        #file_out.append(data)
                        text_file.write(str(data))
                        #print data
                    else:
                        time.sleep(0.1)
            #Flush and close the connection
            self.sock2.recv(RECBUFF)
            time.sleep(2)

        print "\n\n Now closing data connection \n\n"

        self.sock2.close()



#program starts here.

if __name__ == "__main__":
    #Do a bit of error catching and snag all the necessary variables from the command line
    cmd_line_items = len(sys.argv)
    if cmd_line_items < 5 or not sys.argv[2].isdigit() or not sys.argv[4].isdigit() or cmd_line_items > 6:
        print "Use the following format separated by spaces to insert the commands"
        print "<SERVER_HOST>, <SERVER_PORT>, <COMMAND>, <DATA_PORT>, <FILENAME>"
        print "filename is optional depending on the command passed:"
        print "if -l, no filename is necessary"
    elif cmd_line_items > 5 and sys.argv[3] == "-l":
        print "No filename should appear when -l command is specified."
    else:
        serv_port = int(sys.argv[2])
        data_port = int(sys.argv[4])
        cmnd = sys.argv[3]
        filename = sys.argv[5] if cmd_line_items == 6 else ""
        host = sys.argv[1]
    #Intialize the client with all the variables. Then enter function runFTP once initialized.
        FTPClient(host,serv_port,cmnd,data_port,filename).runFTP()


#SOURCES


#http://stackoverflow.com/questions/17501131/sending-txt-file-to-server-from-client-using-python-sockets
#http://www.binarytides.com/receive-full-data-with-the-recv-socket-function-in-python/
#http://stackoverflow.com/questions/5214578/python-print-string-to-text-file
#http://stackoverflow.com/questions/23828264/how-to-make-a-simple-multithreaded-socket-server-in-python-that-remembers-client