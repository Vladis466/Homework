This client-server program allows you to send either the current directory 
of the server which will be displayed in the command prompt for the client. 
Additionally it has an option for sending a text file to the client.

NOTE: The recieved file will have a '2' at the end of the file name. This was hardcoded in to illustrate that the file was copied in case you are 
running this program within the same folder (since otherwise it would just be overwritten).

NOTE2: If you try to run the client program back to back instantly it will fail on the data port if sending a text file. 
If you wait about 15 seconds before running the next iteration it works...I was not able to figure out why.

Directions:

First compile and start the server:
gcc FTPserver.c -o serv

Then start it with an arbitrary port number:
serv 4455 

Then start the client in a separate window as shown below, If an incorrect number of arguments is added, 
the program will let you know how to correct this:
If wanting to display the server's directory the following format is used:

<SERVER_HOST>, <SERVER_PORT>, <COMMAND>, <DATA_PORT>


If wanting to copy a text file the following format is used:


<SERVER_HOST>, <SERVER_PORT>, <COMMAND>, <DATA_PORT>, <FILENAME>


An example for each can be found below:

python FTPclient.py flip3.engr.oregonstate.edu 4455 -l 3344

python FTPclient.py flip3.engr.oregonstate.edu 4455 -g 3344 sample.txt  


