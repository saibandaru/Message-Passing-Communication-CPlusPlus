/////////////////////////////////////////////////////////////////////////////
// Client.cpp   - Defines a  Client instance						       //
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

#include "../sockets/sockets.h"
#include "../ApplicationHelpers/AppHelpers.h"
#include "../Message/Message.h"
#include "../Display/Display.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include "Client.h"

using namespace ApplicationHelpers;

//----< helps client's sender to connect to requested address and port >------------------------------------------------------

void  Client::connectadd(SocketConnecter& si, std::string address, int port)
{
	while (!si.connect(address, port))
	{
		Display::displayString("client waiting to connect");
		::Sleep(100);
	}
	Display::displayString("Client connected to \"" + address + std::to_string(port) + "\"");
}

//----< Parse the property file of the client for the client operations >------------------------------------------------------

void Client::parse(std::string filename)
{
	std::ifstream file(path + filename, std::ios::in | std::ios::binary); std::string line, command, receiverI, filenameI, dummy;
	while (file.good())
	{
		std::getline(file,line);
		std::istringstream linestream(line);
		linestream >> command;
		linestream >> receiverI;
		linestream >> filenameI; Message msg;
		senderQ1.enQ(msg.makeMessage(command, this->address + std::to_string(this->port), receiverI, filenameI.size(), filenameI));
	}
}

//----< Client sender is started here and goes through the series of operations given in property file >------------------------------------------------------

void Client::sender()
{
	try	{
		Verbose v(true);
		SocketSystem ss;
		SocketConnecter si;
		Message msg,msgQparse;
		std::string popQ, addressR, filename, commandI, senderI, receiverI, bodyI; int portR = 0, pastportR = 0, contentLI;		//not using bodyI
		Sender CT(this->port, this->address);
		while (true){
			popQ = this->senderQ1.deQ();
			pastportR = portR;
			msgQparse.getMessage(&(*popQ.begin()), commandI, senderI, receiverI, contentLI, filename);
			portR =std::stoi(receiverI.substr((receiverI.find(':') + 1), receiverI.size()));
			addressR = receiverI.substr(0,receiverI.find(':'));
			if (commandI == "UPLOAD"){
				if (pastportR != portR){
					si.shutDownSend(); connectadd(si, addressR, portR);
				}
				CT.fileUpload(si, filename, receiverI, commandI,this->path);
			}
			else if (commandI == "DOWNLOAD"){
				if (pastportR != portR){
					si.shutDownSend(); connectadd(si, addressR, portR);
				}
				CT.fileDownload(si, filename, receiverI);
			}
			else if (commandI == "TERMINATE_SERVER"){
				char *C = msg.makeMessage("TERMINATE", this->address + ":" + std::to_string(this->port), addressR, 0, "");
				si.send(msg.getMessageSize(), C);
			}
			else{
				char *C = msg.makeMessage("ENDTHREAD", this->address + ":" + std::to_string(this->port), addressR, 0, "");
				si.send(msg.getMessageSize(), C);
				si.shutDownSend(); return;
			}
		}
	}
	catch (std::exception& ex){
		Display::displayString("  Exception caught:");
		Display::displayString(std::string("\n  ") + ex.what() + "\n\n");
	}
}

//----< Client receiver is started here and goes through the series of operations as the requests comes >------------------------------------------------------

void  Client::receiver()
{
	try
	{
		Verbose v(true);
		SocketSystem ss;
		SocketListener sl(port, Socket::IP6);
		Receiver cp(port, address,false,path);
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

//----< for enQ the sender's queue >------------------------------------------------------

void Client::push(std::string input)
{
	this->senderQ1.enQ(input);
}


#ifdef TEST_CLIENT
//----< demonstration >------------------------------------------------------

int main(int argc, char* argv[])
{
	if (argc < 2){
		Display::displayString("Should have atleast address and filepath"); return 0;
	}
	else{
		Client p1(argv[1], argv[2]);
		Message msg; std::string filename;
		Display::displaytitle("Client \n\nAddress:\t\t" + p1.peerAddress() + "\n\nLocated at path:\t" + p1.returnpath());
		std::thread Receiver(&Client::receiver, p1);
		std::thread Sender(&Client::sender, p1);
		p1.parse("properties_Client.txt");
		Sender.join();
		Receiver.join();
	}
}
#endif