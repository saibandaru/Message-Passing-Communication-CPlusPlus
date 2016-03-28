/////////////////////////////////////////////////////////////////////////////
// Receiver.cpp - Defines the Receiver/Listner instance for each peer      //
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

#include "../sockets/sockets.h"
#include "../ApplicationHelpers/AppHelpers.h"
#include "../Message/Message.h"
#include "../Display/Display.h"
#include "Receiver.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

using namespace ApplicationHelpers;

//----< Handle the client side listner requests  >----------------------------------------------------------------------------------------

void Receiver::clientOperations(Socket& socket_)
{
	while (true){
		Socket::byte buffbyte[100]; Message msg;							//block.Headersize();
		bool headerr = socket_.recv(msg.getHeaderSize(), buffbyte);
		if (!headerr){
			socket_.shutDown();
			socket_.close();
		}
		std::string   sender, reciver, body, command,  message, substr; int  content_length;
		msg.getHeader(buffbyte, command, sender, reciver, content_length);
		Socket::byte buffbyteB[1024];
		headerr = socket_.recv(content_length, buffbyteB);
		substr = message = buffbyteB;
		substr = substr.substr(0, content_length);
		message += substr;
		msg.getBody(substr, body);
		if (command == "DOWNLOAD"){
			if (upload(socket_, body,command))
				Display::displayString("File \"" + substr + "\" downloaded successed from  to \"" + sender + "\"");
			else
				Display::displayString("File \"" + substr + "\" downloaded failed at client side from  to \"" + sender + "\"");
		}
		else if (command == "UPLOAD"){ 
			Display::displayString("File \"" + substr + "\" uploaded successfully to \"" + sender+"\"");
		}
		else if (command == "UPLOADFAIL"){
			Display::displayString("File \"" + substr + "\" couldn't upload to \"" + sender + "\"");
		}
		else if (command == "NOFILE"){
			this->q1.enQ(message);
			Display::displayString("Download request failed! file \"" + substr + "\" doesn't existe with server\"" + sender + "\"");
		}
		else{
			break;
		}
	}
}

//----< Handle the Server side listner requests  >----------------------------------------------------------------------------------------

void Receiver::serverOperations(Socket& socket_)
{
	bool display = false;
	while (true	){
		Socket::byte buffbyte[100]; Message msg;							//block.Headersize();
		bool headerr = socket_.recv(msg.getHeaderSize(), buffbyte); Socket::byte buffbyteB[1024];
		std::string   sender, reciver, command, message, substr; int  content_length;
		msg.getHeader(buffbyte, command, sender, reciver, content_length);
		if (display == false)
		{Display::displayString("Server connected to \"" + sender + "\""); display = true;}
		if (!headerr){
			socket_.shutDown();	socket_.close();
			Display::displayString("Server closed connection with \"" + sender + "\"");//"Client " + sender + " connection destroyed");
		}
		message = buffbyte;
		message = message.substr(0, 100);
		headerr = socket_.recv(content_length, buffbyteB);
		substr =  buffbyteB;
		substr = substr.substr(0, content_length);
		message += substr;
		if (command == "UPLOAD"){
			if (!upload(socket_, substr, command)){
				message = msg.makeMessage("UPLOADFAIL", sender, reciver, substr.size(), substr);
				this->q1.enQ(message);												//enQ UPLOAD FAIL
				
			}
			else{
				this->q1.enQ(message);												//enQ UPLOAD SUCCESS
			}
		}
		else if (command == "DOWNLOAD"){
			
			this->q1.enQ(message);													//enQ DOWNLOAD
		}
		else if (command == "TERMINATE"){
			this->q1.enQ(message);													//enq TERMINATE message
		}
		else{
			Display::displayString("Server closed connection with \"" + sender + "\"");
			return;
		}
	}
}
//----< Callable object which is called by the accept thread when the new connect request comes to listner  >----------------------------------------------------------------------------------------

void Receiver::operator()(Socket& socket_)
{
	if (client_server == true)
		serverOperations(socket_);														//for server operations
	else
		this->clientOperations(socket_);												//for client operations
}

//----< Responds to upload file request and grabs the information that is required to copy the file  >----------------------------------------------------------------------------------------

bool Receiver::upload(Socket& socket_, std::string filename,std::string commandp)
{
	Message msg;
	std::ofstream myfile(this->path+filename, std::ios::out | std::ios::binary | std::ios::ate);
	if (!myfile.good())
		return false;
	std::string   sender, reciver, command, body; int  content_length;
	Socket::byte buffbyte[100], buffbyteB[1024];
	while (true){
		bool headerr = socket_.recv(msg.getHeaderSize(), buffbyte);
		msg.getHeader(buffbyte, command, sender, reciver, content_length);
		headerr = socket_.recv(content_length, buffbyteB);
		for (int i = 0; i < content_length; i++)
			myfile << buffbyteB[i];
		if (command == (commandp+"END"))												//for end of the file
			break;
	}
	myfile.close();
	return true;
}


//----< test stub starts here >----------------------------------------------

struct Cosmetic
{
	~Cosmetic()
	{
		std::cout << "\n  press key to exit: ";
		std::cin.get();
		std::cout << "\n\n";
	}
} aGlobalForCosmeticAction;

#ifdef TEST_RECEIVER
//----< Receiver test stub >------------------------------------------------------

int main()
{
	title("Testing Socket Server", '=');

	try
	{
		Verbose v(true);
		SocketSystem ss;
		SocketListener sl(9080, Socket::IP6);
		Receiver cp(9080, "localhost",true,"");
		sl.start(cp);

		Verbose::show("press key to exit: ", always);
		std::cout.flush();
		std::cin.get();
	}
	catch (std::exception& ex)
	{
		Display::displayString("  Exception caught:");
		Display::displayString(std::string("\n  ") + ex.what() + "\n\n");
	}
}
#endif
