#include "calc.h"

/*
 * shell.cpp
 *
 * Copyright (c) 2024 Mileter
 *
 * Distributed under MIT License.
 * You should have recieved a license with this file.
 * If not, check the origin git page.
 *
 * shell.cpp handles all file operations, user I/O,
 * and includes the entry point.
 */

// define global defination externs
bool isRedirected;        // has CIN/I/SCANF been redirected from a file/program?
bool stopReading = false; // has the program reached end of input?

void printAbout()
{
	cout << product_name << "\n"
	     << "v" << version << " " << copyright << "\n";
}

void printFunctions()
{
	cout << "All defined functions: \n"
	     << "Name  : Comments";
	size_t size = funcComments.size();
	if (size == 0)
		cout << "(No functions are defined)";
	else
		for(map<string, string>::iterator i = funcComments.begin(); i != funcComments.end(); i++)
			printf("%-5s : %s", (i->first).c_str(), (i->second).c_str());
}

string getCommand()
{
	
	cout << "> " << "\n";
	string cmd;
	getline(cin, cmd);
	while(cmd[cmd.size()-1] == "\\") // check for escape character (for newline)
	{                                // other escape characters can be interpreted later
		string addon;
		getline(cin, cmd);
		cmd += addon;
	}
	return cmd;
}

void recordError(string sender, string message)
{
	cerr << "[ERR]" << sender << ": " << message << "\n";
}

int main(int argc, char **argv)
{
	isRedirected = !isatty(fileno(stdin)); // set isRedirected to the correct status
	
	// set up math calc
	usingRadians = false; // set to degress by default.
	                      // if on, all trig functions would need their inputs multiplied by 180/pi to make it degress before passing it on.
	
	while(!stopReading)
	{
		cout << "Not implemented\n"; // implement more when all the helper functions are done.
		stopReading = true;
	}
    return 0;
}