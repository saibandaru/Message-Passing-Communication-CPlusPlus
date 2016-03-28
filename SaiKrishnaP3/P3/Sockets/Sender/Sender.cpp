/////////////////////////////////////////////////////////////////////////////
// Sender.cpp - Defines the sender instance for each peer	               //
// Ver 1.0                                                                 //
// Sai Krishna, CSE#687 - Object Oriented Design, Spring 2015              //
// CST 4-187, Syracuse University, 832 940-8083, sbandaru@syr.edu	       //
//-------------------------------------------------------------------------//
// Sai Krishna (c) copyright 2015                                          //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Application: Sender for Project #3, Communication Channel               //
// Platform:    Dell 2720, Win Pro 8.1, Visual Studio 2013                 //
/////////////////////////////////////////////////////////////////////////////

#include "../Display/Display.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Sender.h"


using namespace ApplicationHelpers;

//----< test stub starts here >----------------------------------------------

struct Cosmetic1
{
	~Cosmetic1()
	{
		Display::displayString("  press key to exit : ");
		std::cin.get();
		std::cout << "\n\n";
	}
} aGlobalForCosmeticAction;

//----< To transfer file from sender to listner >--------------------------------------------------------------------------------

void Sender::fileUpload(Socket& si, std::string filename,std::string receiverAddr,std::string commandp,std::string path)
{
	Message block; std::ifstream myfile(path + filename, std::ios::in | std::ios::binary); char* c;
	if (!myfile.good()){
		
		if (commandp == "DOWNLOAD"){				//Request from server to upload
			c = block.makeMessage("NOFILE", this->address + ":" + std::to_string(this->port), receiverAddr, filename.size(), filename);
			si.send(block.getMessageSize(), c);
		}
		else
			Verbose::show("Doesn't have file with " + this->address + ":" + std::to_string(this->port));
		return;
	}
	size_t sizebolock; char  buf[1025]; bool endoffile = false;
	std::string   sender, reciver, body, command; int  i = 0; unsigned int size_stream;
	c = block.makeMessage(commandp, this->address + ":" + std::to_string(this->port), receiverAddr, filename.size(), filename);
	sizebolock = block.getMessageSize();
	si.send(sizebolock, c);																//send block first uploaf message
	myfile.seekg(0, myfile.end);	
	size_stream = (unsigned int)myfile.tellg();
	myfile.seekg(0, myfile.beg);
	while (true){													
		if (size_stream > 1024)	{
			myfile.read(buf, 1024); buf[1024] = '\0';
			c = block.makeHeader(commandp, this->address + ":" + std::to_string(this->port), receiverAddr, 1024);
			si.send(block.getHeaderSize(), c);si.send(1024, buf);
		}
		else{																			//for last block of message <=1024
			myfile.read(buf, size_stream); buf[size_stream] = '\0';
			c = block.makeHeader(commandp+"END", this->address + ":" + std::to_string(this->port), receiverAddr, size_stream);
			si.send(block.getHeaderSize(), c);si.send(size_stream, buf);endoffile = true;
		}
		if (endoffile == true) break;
		i += 1024;size_stream -= 1024;
	}
}

//----< File transfer request from sender to receiver >--------------------------------------------------------------------------------

void Sender::fileDownload(Socket& si, std::string filename, std::string receiverAddr)
{
	Message block;
	char* c = block.makeMessage("DOWNLOAD", this->address + ":" + std::to_string(this->port), receiverAddr, filename.size(), filename);
	si.send(block.getMessageSize(), c);
}

//----< File transfer request acknowledge after the operation based on the status >--------------------------------------------------------------------------------

void Sender::uploadfileAck(Socket& si, std::string filename, std::string receiverAddr,std::string command)
{
	Message block;
	char* c = block.makeMessage(command, this->address + ":" + std::to_string(this->port), receiverAddr, filename.size(), filename);
	si.send(block.getMessageSize(), c);
}

#ifdef TEST_SENDER
//----< test stub for sender >------------------------------------------------------

int main()
{
	title("Testing Socket Client", '=');

	try
	{
		Verbose v(true);
		SocketSystem ss;
		SocketConnecter si;
		Message msg;
		while (!si.connect("localhost", 9080))
		{
			Display::displayString("client waiting to connect");
			::Sleep(100);
		}

		title("File Upload");
		Sender CT(2020,"testport");
		CT.fileUpload(si, "Sender.pdf","dummy:2020","UPLOAD","");
		CT.fileDownload(si, "Pavan.txt","dummy:2020");
		si.shutDownSend();
	}
	catch (std::exception& ex)
	{
		Display::displayString("  Exception caught:");
		Display::displayString(std::string("\n  ") + ex.what() + "\n\n");
	}
}
#endif