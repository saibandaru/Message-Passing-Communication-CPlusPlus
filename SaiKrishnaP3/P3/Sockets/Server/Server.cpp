/////////////////////////////////////////////////////////////////////////////
// Server.cpp   - Defines a  Server instance	   					       //
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

#include "../sockets/sockets.h"
#include "../ApplicationHelpers/AppHelpers.h"
#include "../Message/Message.h"
#include "../Display/Display.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include "Server.h"

using namespace ApplicationHelpers;

//----< helps sender of server to connect to required address >------------------------------------------------------

void  Server::connectadd(SocketConnecter& si, std::string address, int port)
{
	while (!si.connect(address, port))
	{
		Display::displayString("client waiting to connect");
		::Sleep(100);
	}
	//Display::displayString("Client connected to \"" + address + std::to_string(port) + "\"");
}

//----< starts sender module for the server and process requests depending on the enQ done by receiver >------------------------------------------------------

void Server::sender()
{
	try
	{
		Verbose v(true);
		SocketSystem ss;
		SocketConnecter si;
		Message msg, msgQparse;
		std::string popQ, addressR, filename, commandI, senderI, receiverI; int portR = 0, pastportR = 0, contentLI;
		Sender CT(this->port, this->address);
		BlockingQueue<std::string> &q1 = QServer<std::string, 1>().get();
		while (true){
			popQ = q1.deQ();
			pastportR = portR;
			msgQparse.getMessage(&(*popQ.begin()), commandI, senderI, receiverI, contentLI, filename);
			portR = std::stoi(senderI.substr((senderI.find(':') + 1), senderI.size()));
			addressR = senderI.substr(0, senderI.find(':'));
			if (commandI == "DOWNLOAD")	{
				if (pastportR != portR){
					si.shutDownSend();
					connectadd(si, addressR, portR); 
				}
				CT.fileUpload(si, filename, senderI, commandI,path); 
			}
			else if (commandI == "UPLOAD" || commandI == "UPLOADFAIL")
			{
				if (pastportR != portR){
					si.shutDownSend();
					connectadd(si, addressR, portR);
				}
				CT.uploadfileAck(si, filename, senderI, commandI);
			}
			else if (commandI == "TERMINATE")																		
			{
				//char *C = msg.makeMessage("TERMINATE", this->address + ":" + std::to_string(this->port), addressR, 0, "");
				si.shutDownSend();
				return;
			}
			else{
				return;
			}
		}
	}
	catch (std::exception& ex){
		Display::displayString("  Exception caught:");
		Display::displayString(std::string("\n  ") + ex.what() + "\n\n");
	}
}

//----< starts receiver module for the server and listens to requested sent to the server's address >------------------------------------------------------

void  Server::receiver()
{
	try
	{
		Verbose v(true);
		SocketSystem ss;
		SocketListener sl(port, Socket::IP6);
		Receiver cp(port, address,true,path);
		sl.start(cp);
		std::cout.flush();
		std::cin.get();
	}
	catch (std::exception& ex)
	{
		Display::displayString("  Exception caught:");
		Display::displayString(std::string("\n  ") + ex.what() + "\n\n");
	}
}

#ifdef TEST_SERVER
//----< demonstration >------------------------------------------------------

int main(int argc, char* argv[])
{
	if (argc < 2){
		Display::displayString("Should have atleast address and filepath"); return 0;
	}
	else{
		Server p1(argv[1], argv[2]); 
		Display::displaytitle("Server \n\nAddress:\t\t" + p1.peerAddress() + "\n\nLocated at path:\t" + p1.returnpath());
		std::thread Receiver(&Server::receiver, p1);
		std::thread Sender(&Server::sender, p1);
		Sender.join();
		Receiver.join();
	}
}
#endif