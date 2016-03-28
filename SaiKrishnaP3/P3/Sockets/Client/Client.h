#ifndef CLIENT
#define CLIENT
/////////////////////////////////////////////////////////////////////////////
// Client.h   - Declares a  Client instance	     					       //
// Ver 1.0                                                                 //
// Sai Krishna, CSE#687 - Object Oriented Design, Spring 2015              //
// CST 4-187, Syracuse University, 832 940-8083, sbandaru@syr.edu	       //
//-------------------------------------------------------------------------//
// Sai Krishna (c) copyright 2015                                          //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Application: Client for Project #3, Communication Channel               //
// Platform:    Dell 2720, Win Pro 8.1, Visual Studio 2013                 //
/////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*-Can send file from the home location to given address and port
*
*-Can request a file from the given address 
* Public Interface:
* =================
*inline std::string peerAddress()						gives the address of the client
*
*inline std::string returnpath()						gives the home path of the clinet
*
*void sender()											starts sender module for the clinet
*
*void connectadd(SocketConnecter&, std::string, int)	helps sender to connevt to requested port address
*
*void receiver()										starts receiver module for the clinet
*
*void parse(std::string)								parse the properties file that is there in the home directory for the client operations
*
*void push(std::string)									enQ the sender queue with the properties file content
*
*  Required Files:
*  ---------------
*  Sockets.h, Sockets.cpp
*  AppHelpers.h, AppHelpers.cpp, WindowsHelpers.h, WindowsHelpers.cpp, Sender.h. Sender.cpp, Reveicer.h, Receiver.cpp, Display.h , Display.cpp,
*			Message.h and Message.cpp
*
*  Build Command:
*  --------------
*  devenv Sockets.sln /rebuild debug
*
*
*  Maintenance History:
*  --------------------
*  Version 1.0 April 15
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
// Client class - sends files to server and requests file from server

class Client
{
public:
	Client(std::string addressI = "localhost:8090", std::string pathI = "Client\\")
	{
		address = addressI.substr(0,addressI.find(':'));
		port = std::stoi(addressI.substr(addressI.find(':') + 1, addressI.size()));
		path = pathI;
	}
	~Client(){}
	inline std::string peerAddress(){ return (address + ":" + std::to_string(port)); }
	inline std::string returnpath(){ return (path); }
	void sender();
	void connectadd(SocketConnecter&, std::string, int);
	void receiver();
	void parse(std::string);
	void push(std::string);
	private:
	std::string path;														//Client home path
	std::string address;													//client ip address
	int port;																//client port address
	BlockingQueue<std::string> &senderQ1 = QServer<std::string, 4>().get();	//sender Queue
};
#endif