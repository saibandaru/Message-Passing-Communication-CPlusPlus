/////////////////////////////////////////////////////////////////////////////
// Message.cpp - Test passing strings, blocks, and buffers                 //
// Ver 1.1                                                                 //
// Sai Krishna, CSE#687 - Object Oriented Design, Spring 2015              //
// CST 4-187, Syracuse University, 832 940-8083, sbandaru@syr.edu          //
//-------------------------------------------------------------------------//
// Sai Krishna (c) copyright 2015                                          //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Application: Message for Project #3, Communication Channel              //
// Platform:    Dell 2720, Win Pro 8.1, Visual Studio 2013                 //
/////////////////////////////////////////////////////////////////////////////

#include "Message.h"
#include <vector>

//----< returns the character pointer after construction of message  >------------------------------------------------------

char* Message::makeMessage(std::string commandI,  std::string senderI, std::string reciverI, int content_lengthI, std::string bodyI)
{
	this->command = "COMMAND:" + commandI;
	this->sender = "SENDER:"+senderI;
	this->reciver = "RECEIVER:" + reciverI;
	this->content_length = content_lengthI;
	this->body = bodyI;
	message = command + "\n" + sender + "\n" + reciver + "\n" + "CONTENTLENGTH:"+std::to_string(content_length) + "\n\n";
	if (message.size() < 100)
	{
		while (message.size() != 100)
		{
			message += ' ';
		}
	}
	message += body;
	return(&(*message.begin()));
}

//----< returns the character pointer after construction of header  >------------------------------------------------------

char* Message::makeHeader(std::string commandI, std::string senderI, std::string reciverI, int content_lengthI)
{
	this->command = "COMMAND:" + commandI;
	this->sender = "SENDER:" + senderI;
	this->reciver = "RECEIVER:" + reciverI;
	this->content_length = content_lengthI;
	this->body = body;
	message = command + "\n" + sender + "\n" + reciver + "\n" + "CONTENTLENGTH:" + std::to_string(content_length) + "\n\n";
	if (message.size() < 100)
	{
		while (message.size() != 100)
		{
			message += ' ';
		}
	}
	return(&(*message.begin()));
}

//----< returns the maximum size of block that it can send >------------------------------------------------------

int Message::getMaxsize()
{
	return(maxSize);
}

//----< parses the header based on cahracter pointer >------------------------------------------------------

void  Message::getHeader(char* ch, std::string& command, std::string& sender, std::string& reciver, int& content_length)
{
	std::istringstream iss(ch);
	int length = 0;
	std::string sub;
	std::vector<std::string> header;
	while (length != 4)
	{
		iss >> sub;
		header.push_back(sub);
		++length;
	}this->command = command = header[0].substr(header[0].find(':') + 1, header[0].size());
	this->sender = sender = header[1].substr(header[1].find(':') + 1, header[1].size());
	this->reciver = reciver = header[2].substr(header[2].find(':') + 1, header[2].size());
	this->content_length = content_length = std::stoi(header[3].substr(header[3].find(':') + 1, header[3].size()));
}

//----< parses the message based on cahracter pointer >------------------------------------------------------

void  Message::getMessage(char* ch, std::string& command, std::string& sender, std::string& reciver, int& content_length, std::string& body)
{
	std::istringstream iss(ch);
	int length = 0;
	std::string sub;
	std::vector<std::string> header;
	while (length != 4)
	{
		iss >> sub;
		if (sub != "\n")
		{
			header.push_back(sub);
		}
		++length;
	}this->command = command = header[0].substr(header[0].find(':') + 1, header[0].size());
	this->sender = sender = header[1].substr(header[1].find(':') + 1, header[1].size());
	this->reciver = reciver = header[2].substr(header[2].find(':') + 1, header[2].size());
	this->content_length = content_length = std::stoi(header[3].substr(header[3].find(':') + 1, header[3].size()));
	sub = std::string(ch);
	this->body=body=sub = sub.substr(100);
}

//----< parses the body only, after parsing the message >------------------------------------------------------

void  Message::getBody(std::string ch, std::string& body)
{
	this->body=body = ch;
}

//----< returns the body size>------------------------------------------------------

int Message::getMessageSize()
{
	
	return(message.size());
}
#ifdef TEST_MESSAGE
//----< test stub >------------------------------------------------------

int main()
{
	Message ms;
	int size_http = ms.getMaxsize();
	std::string MessageBody = "Upload.txt";
	int size_body = MessageBody.size();
	char * ch = ms.makeMessage("UPLOAD", "120.015.122.123:9098", "120.015.122.123:9098", size_body, MessageBody);
	std::string command;
	std::string fileOrTest;
	std::string sender;
	std::string reciver;
	int content_length;
	std::string body;
	ms.getHeader(ch, command, sender, reciver, content_length);
	std::cout << "Command:" << command << "\n" << "Sender:" << sender << "\n"
		<< "Reciver:" << reciver << "\n" << "Content length:" << content_length << "\n\n\n";
	ms.getMessage(ch, command, sender, reciver, content_length, body);

	std::cout << "Command:" << command << "\n"  << "Sender:" << sender << "\n"
		<< "Reciver:" << reciver << "\n" << "Content length:" << content_length << "\n" << "Body:" << body << "\n";

	std::cout << "Header Length:" << ms.getMessageSize() - size_body<<"\n";

	return 1;
}
#endif

