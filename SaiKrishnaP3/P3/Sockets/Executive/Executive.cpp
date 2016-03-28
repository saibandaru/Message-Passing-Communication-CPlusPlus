/////////////////////////////////////////////////////////////////////////////
// Executive.cpp - To demonstrate the http message rwquirement             //
// Ver 1.1                                                                 //
// Sai Krishna, CSE#687 - Object Oriented Design, Spring 2015              //
// CST 4-187, Syracuse University, 832 940-8083, sbandaru@syr.edu 		   //
//-------------------------------------------------------------------------//
// Sai Krishna (c) copyright 2015                                          //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Application: Executive for Project #3, Communication Channel            //
// Platform:    Dell 2720, Win Pro 8.1, Visual Studio 2013                 //
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "../Display/Display.h"
#include "../Message/Message.h"
#ifdef TEST_EXECUTIVE
//----< test stub >------------------------------------------------------

int main()
{
	Message ms;
	std::string message = "general-purpose device that can be programmed";
	Display::displaytext( "\nDemonstrate Requirement (3):Constrution of message class\n");
	Display::displaytext("\nHEADER:\n");
	Display::displaytext("=======\n");
	Display::displaytext(ms.makeHeader("UPLOAD", "120.015.122.123:9098", "120.015.122.123:9098", message.size()));
	Display::displaytext("\nWHOLE MESSAGE:\n");
	Display::displaytext("==============\n");
	Display::displaytext(ms.makeMessage("UPLOAD", "120.015.122.123:9098", "120.015.122.123:9098", message.size(), message));
	Display::displaytext("\n\n\nFor Requirements (5),(6),(7) and (8)\n Demonstrating the following cases:\n");
	Display::displaytext("CASE 1: Client1(8090) and Client2(8080) connects to Server1(9000) and transfers file simultaneously\n");
	Display::displaytext("CASE 2:Then Client1(8090) disconnects from Server1(9000) and connects to Server2(9010) and transfers two files one after another\n");
	std::getchar();

	return 1;
}
#endif