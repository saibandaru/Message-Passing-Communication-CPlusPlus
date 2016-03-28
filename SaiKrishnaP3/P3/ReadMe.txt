Project 3
=========
Message-Passing Communication

Demonstration:
=============
Starting Client1, Client2, Server1 and Server2 simultaneously..
*First, Client1 and Client2 uploads files c1_TO_s1.pdf and c2_TO_s1.pdf to Server1 respectively. Then we are not interacting with Server1 so Client2 shutsdown Server1.
*Then Client1 disconnects from Server1 and connects to Server2 and uploads c1_TO_s2.pdf,c1_TO_s2.jpg files, at last Client1 ends Server2

Assumption:
==========

As advised in piazza, "the last client interacting with the server will end the server's sender for proper server termination". 


Functionality
=============

*Constructed Message class which has http message format.
*The communication between sender and receiver is carriedout using message class instances.
*Each Client and Server has its own sender and receiver for the communication of information.
*Client can upload file to server, server intern sends acknowledge message to client that the file has been uploaded to it.
*Two clients can upload files simultaneously to the same server.
*A client can send the information to one server and can disconnect and connect to another server for the communication.

****Help****
    ====
Client command line:  address:port folderlocation
Server command line:  address:port folderlocation

folder location is relative from Sockets/Debug directory

Client operations are given in properties_Client.txt in the that sholud be placed in folder location

commands
--------
UPLOAD to transfer command from client to server
DOWNLOAD to transfer command from srver to client
TERMINATE_SERVER to stop server's sender
TERMINATE to stop the client's sender

About properties_Client.txt 
===========================
command address:port filename








