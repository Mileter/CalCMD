// CALCMD.h : Include file for standard system include files,
// or project specific include files.

#pragma once

/*
 * calc.h
 *
 * Copyright (c) 2024 Mileter
 *
 * Distributed under MIT License.
 * You should have recieved a license with this file.
 * If not, check the origin git page.
 *
 * calc.h defines all functions that should be implemented.
 */

#include <iostream>  // for I/O into CIN/COUT
#include <cstdio>    // (more I/O)
#include <vector>    // for parsing purposes
#include <regex>     // for splitString()
#include <string>    // for parsing purposes
#include <cmath>     // mathematical functions
#include <stack>     // for parsing purposes
#include <stdexcept> // handle bad arguments

#ifdef _WIN32       // get access to isatty()
	#include <io.h>
#else
	#include <unistd.h>
#endif

#if defined(HAS_CURSES) // stay in console if possible
// curses
#elif defined(HAS_SDL2)
// sdl
#endif

#define version   1.0
#define copyright "Copyright (c) 2024 Mileter"
#define product_name "CalCMD Shell"

// global definations

// shell
extern bool isRedirected; // has CIN/I/SCANF been redirected from a file/program?
extern bool stopReading;  // has the program reached end of input?
// calculation
extern std::map<std::string, std::string> func; // (name, evaluation string)
extern std::map<std::string, std::string> funcComments; // (name, comments)
// trig
extern bool usingRadians;

// String operations
std::vector<std::string> splitString(
	const std::string str,
    const std::string delimiter
);
std::vector<std::string> sliceString(
	const std::vector<std::string>& v, 
    int x,
    int legnth
);

// shell.cpp
// Shell
#ifndef BUILD_LIBRARY
string getCommand();
void printAbout();
void printFunctions();
void printHelp();
void recordError(
	std::string sender,
	std::string message
);

int main(
	int argc, 
	char **argv
);
#endif

// parse.cpp
// Calculation parsers
double evalulatePostfix(
	std::string expr
);
double infixToPostfix(
	std::string expr
);
double prefixToPostfix(
	std::string expr
);
double computeExpression(
	std::string expression, 
	int inputFormat = 1
);
void validityParse(
	int argc,
	std::string pre[],   // predefined variables that are known to exist
	std::string expr,
	std::vector<std::string> & errors // return errors with parse
);

// calc.cpp
// Calculation helpers
int precedence(
	string op
);
double applyOperation(
	string op,
	int argc,
	std::string argv[]
);

// Function framework
bool addUserFunction(
	std::string name,
	int argc;
	std::string args[], // names for which the arguments are called (valid positional variables)
	std::string expr  // attempt to parse on add to check for formatting errors
);
void removeFunction(
	std::string name
);
bool resolveFunction(
	std::string name
);
double computeFunction(
	std::string name,
	int argc,
	double ** argv
);
std::string getEvaluationExpr(
	std::string name
);
