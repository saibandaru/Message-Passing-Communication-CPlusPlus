/////////////////////////////////////////////////////////////////////////////
// Display.cpp - Display pacakage for the Project3			               //
// Ver 1.1                                                                 //
// Sai Krishna, CSE#687 - Object Oriented Design, Spring 2015              //
// CST 4-187, Syracuse University, 832 940-8083, sbandaru@syr.edu	       //
//-------------------------------------------------------------------------//
// Sai Krishna (c) copyright 2015                                          //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Application: Display for Project #3, Communication Channel              //
// Platform:    Dell 2720, Win Pro 8.1, Visual Studio 2013                 //
/////////////////////////////////////////////////////////////////////////////
#include "../ApplicationHelpers/AppHelpers.h"
#include "../Message/Message.h"
#include <iostream>
#include "Display.h"

using namespace ApplicationHelpers;

//----< Display a s string with endl at starting and ending with mutex lock >------------------------------------------------------

void Display::displayString(std::string text)
{
	Verbose::show(text, always);
}

//----< Display a http message >------------------------------------------------------

void Display::displayMessage(std::string message)
{
	std::string text;
	text = message.substr(100, message.size());
	message = message.substr(0, message.find("\n\n")+2);
	message += text;
	Verbose::show(message, always);
	Verbose::show("\n", always);
}

//----< Display text as a title >------------------------------------------------------

void Display::displaytitle(std::string title)
{
	::title(title);
}

//----< Display text without formatting >------------------------------------------------------

void Display::displaytext(std::string text)
{
	std::cout << text;
}
#ifdef TEST_DISPLAY
//----< test stub >------------------------------------------------------

int main()
{
	std::string text = "Message class demonstration";
	int size = text.size();
	Message msg;
	Display::displayString("Display text demonstration");
	std::string message = msg.makeMessage("UPLOAD", "localhost:9000", "localhost:8090", text.size(), text);
	Display::displayMessage(message);

}
#endif