#ifndef DISPLAY
#define DISPLAY
/////////////////////////////////////////////////////////////////////////////
// Dsiplay.h - Display pacakage for the Project3			               //
// Ver 1.1                                                                 //
// Sai Krishna, CSE#687 - Object Oriented Design, Spring 2015              //
// CST 4-187, Syracuse University, 832 940-8083, sbandaru@syr.edu          //
//-------------------------------------------------------------------------//
// Sai Krishna (c) copyright 2015                                          //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Application: Display for Project #3, Communication Channel              //
// Platform:    Dell 2720, Win Pro 8.1, Visual Studio 2013                 //
/////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package provides:
*  - display functions for printing to output console
*
* Public Interface:
* =================
*void displayString(std::string)				static function which prints a text with mutex lock over output console
*
*void displayMessage(std::string)				static function which prints a message to output
*
*static void displaytitle(std::string)			static function which prints a text with mutex lock over output console with an underline
*
*void displaytext(std::string)					static function which prints a text without any formatting
*
*  Required Files:
*  ---------------
*  Sockets.h, Sockets.cpp
*  AppHelpers.h, AppHelpers.cpp, WindowsHelpers.h, WindowsHelpers.cpp
*
* Build Command:
*  --------------
*  devenv Sockets.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*  Version 1.0 April 15
*/
#include "../ApplicationHelpers/AppHelpers.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
/////////////////////////////////////////////////////////////////////////////
// Message class - manages loading and unloading Winsock library

class Display
{
public:
	static void displayString(std::string);
	static void displayMessage(std::string);
	static void displaytitle(std::string);
	static void displaytext(std::string);
};
#endif