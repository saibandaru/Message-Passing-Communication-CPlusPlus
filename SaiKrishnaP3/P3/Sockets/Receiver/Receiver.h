#ifndef RECEIVERTEST
#define RECEIVERTEST
/////////////////////////////////////////////////////////////////////////////
// Receiver.h   - Defines a  Receiver instance for each peer               //
// Ver 1.0                                                                 //
// Sai Krishna, CSE#687 - Object Oriented Design, Spring 2015              //
// CST 4-187, Syracuse University, 832 940-8083, sbandaru@syr.edu	       //
//-------------------------------------------------------------------------//
// Sai Krishna (c) copyright 2015                                          //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Application: Receiver for Project #3, Communication Channel             //
// Platform:    Dell 2720, Win Pro 8.1, Visual Studio 2013                 //
/////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package provides sender operations listed below:
*  - can process and make files uploaded into the Peer sent by the sender.
*  - can process and send files for download request sent by the sender.
*  - can store and give the operations it performed when the sender asks for
*
* Public Interface:
* =================
* void operator()									Callable object which is called by the accept thread when the new connect request comes to listner
*
*void serverOperations(Socket&)						Server side receiver/listner operations are here.
*
*void clientOperations(Socket&)						Client side receiver/listner operations are handled here.
*
*bool upload(Socket& , std::string,std::string)		Sends the file information from server to client whenever download requests received.
*
*  Required Files:
*  ---------------
*  Receiver.cpp, Receiver.h
*  Sockets.h, Sockets.cpp, AppHelpers.h, AppHelpers.cpp, Message.h, Message.cpp , Display.h and Display.cpp
*
*  Build Command:
*  --------------
*  devenv Sockets.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*  ver 1.0 : 06 Apr 15

*  - first release
*/
#include "../sockets/sockets.h"
#include "../ApplicationHelpers/AppHelpers.h"
#include "../QServer/Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"
#include "../QServer/QServer/QServer.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
/////////////////////////////////////////////////////////////////////////////////
// Receiver class - Manages all the listner operations of both client and server

class Receiver
{
public:
	Receiver(int portI, std::string addressI, bool client_serverI,std::string pathI)
		:port(portI), address(addressI), client_server(client_serverI),path(pathI){}
	void operator()(Socket& );
	bool upload(Socket& , std::string,std::string);
	void serverOperations(Socket&);
	void clientOperations(Socket&);
private:
	bool client_server;															//client=false, server=true
	std::string path;															//home path of the listner
	std::string address;														//Listner ip address
	int port;																	//Listner port
	BlockingQueue<std::string> &q1 = QServer<std::string, 1>().get();			//Receiver Queue 
};
#endif