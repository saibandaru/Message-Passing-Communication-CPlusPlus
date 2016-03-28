#ifndef MESSAGE_H
#define MESSAGE_H
/////////////////////////////////////////////////////////////////////////////
// Message.h   - Defines a  Message class for http message                 //
// Ver 1.0                                                                 //
// Sai Krishna, CSE#687 - Object Oriented Design, Spring 2015              //
// CST 4-187, Syracuse University, 832 940-8083, sbandaru@syr.edu	       //
//-------------------------------------------------------------------------//
// Sai Krishna (c) copyright 2015                                          //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Application: Message for Project #3, Communication Channel	           //
// Platform:    Dell 2720, Win Pro 8.1, Visual Studio 2013                 //
/////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*-Can make message as well as the header part thatdont have body
*
*-Can parse message and header bocks
*
*-Can return the message and header lengths
*
* Public Interface:
* =================
*int getMaxsize()															gives the maxomum size of the body that a message can send
*
*int getMessageSize()														gives the message size after naking the message
*
*char* makeMessage(std::string, std::string, std::string, int, std::string) returns the character pointer adter making the message 
*
*char* makeHeader(std::string , std::string , std::string , int )			returns the character pointer adter making the header
*
*void  getMessage(char*,std::string&,  std::string&, std::string&, int&, std::string&) parses the whole message based on the character pointer input
*
*void  getHeader(char* ch, std::string& command, std::string& sender, std::string& reciver, int& content_length) parses the header based on the character pointer input
*
*void  getBody(std::string, std::string& body)								returns the parsed body of the message block
*
*inline const int getHeaderSize()											returns the header size
*
*  Required Files:
*  ---------------
*  Receiver.cpp, Receiver.h
*  Sockets.h, Sockets.cpp, AppHelpers.h, AppHelpers.cpp
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


#include <iostream>
#include <string>
#include <sstream>
/////////////////////////////////////////////////////////////////////////////
// Message class constructs and parses the http message

class Message
{
public:
	Message(){};
	~Message(){};
	int getMaxsize();
	int getMessageSize();
	char* makeMessage(std::string, std::string, std::string, int, std::string);
	char* makeHeader(std::string command, std::string sender, std::string reciver, int content_length);
	void  getMessage(char*,std::string&,  std::string&, std::string&, int&, std::string&);
	void  getHeader(char* ch, std::string& command, std::string& sender, std::string& reciver, int& content_length);
	void  getBody(std::string, std::string& body);						
	inline const int getHeaderSize(){ return headSize; };
private:
	std::string  command;
	std::string sender;
	std::string reciver;
	int content_length;
	std::string body;
	int maxSize = 1024;
	int headSize = 100;
	std::string message;
};
#endif