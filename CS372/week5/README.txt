testing servers:
flip1.engr.oregonstate.edu
flip2.engr.oregonstate.edu

To start the server:
python serv.py 'port'

To compile the client:
gcc client.c -o cli -pthread

To run the client:
cli



This program allows for a client to connect to a server and for messages to be sent back and forth between them. 
Entering '\quit' on either the client or server will result in the client disconnecting. The server will then 
default to listening for a new client.

How to run:
Start the server first, don't forget to enter the port number. 
Type in a username and press enter.
The server will now listen for a client.

Now start the client.
Type in the port you entered for the server.
Type in the hostname you entered for the server.
Type in a username for yourself.

Assuming no errors, both programs will now connect and you will be able to chat. 