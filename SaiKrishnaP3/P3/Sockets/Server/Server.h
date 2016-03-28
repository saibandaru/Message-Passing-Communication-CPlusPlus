#ifndef SERVER
#define SERVER
/////////////////////////////////////////////////////////////////////////////
// Server.h   - Declares a  Server instance		  					       //
// Ver 1.0                                                                 //
// Sai Krishna, CSE#687 - Object Oriented Design, Spring 2015              //
// CST 4-187, Syracuse University, 832 940-8083, sbandaru@syr.edu	       //
//-------------------------------------------------------------------------//
// Sai Krishna (c) copyright 2015                                          //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Application: Server for Project #3, Communication Channel               //
// Platform:    Dell 2720, Win Pro 8.1, Visual Studio 2013                 //
/////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*-Can accept file that is sent by the client
*
*-Can process the file request by sending the file back to requested client
*
* Public Interface:
* =================
*inline std::string peerAddress()						gives the address of the server
*
*inline std::string returnpath()						gives the home path of the server
*
*void sender()											starts sender module for the server
*
*void connectadd(SocketConnecter&, std::string, int)	helps sender to connevt to requested port address
*
*void receiver()										starts receiver module for the server	
*
*  Required Files:
*  ---------------
*  Sockets.h, Sockets.cpp
*  AppHelpers.h, AppHelpers.cpp, WindowsHelpers.h, WindowsHelpers.cpp, Sender.h. Sender.cpp, Reveicer.h, Receiver.cpp, Display.h , Display.cpp,
*			Message.h and Message.cpp
*
*  Maintenance History:
*  --------------------
*  Version 1.0 10 April 15
*/

#include "../sockets/sockets.h"
#include "../ApplicationHelpers/AppHelpers.h"
#include "../QServer/Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"
#include "../QServer/QServer/QServer.h"
#include "../Sender/Sender.h"
#include "../Receiver/Receiver.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
/////////////////////////////////////////////////////////////////////////////
// Server class - sends files to client and accepts file from client

class Server
{
public:
	Server(std::string addressI = "localhost:9000", std::string pathI = "Server\\")
	{
		address = addressI.substr(0, addressI.find(':'));
		port = std::stoi(addressI.substr(addressI.find(':') + 1, addressI.size()));
		this->path = pathI;
	}
	~Server(){}
	inline std::string peerAddress(){ return (address + ":" + std::to_string(port)); }
	inline std::string returnpath(){ return this->path; }
	void sender();
	void connectadd(SocketConnecter&, std::string, int);
	void receiver();
private:
	std::string path;
	std::string address;
	int port;
	BlockingQueue<std::string> senderQ1 = QServer<std::string, 4>().get();
};
#endif