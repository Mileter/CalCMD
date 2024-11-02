// CALCMD.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream> // for I/O into CIN/COUT
#include <vector>   // for parsing purposes
#include <regex>    // for splitString()
#include <string>   // for parsing purposes
#include <cmath>    // mathematical functions
#include <stack>    // for parsing purposes

#ifdef HAS_GRAPH_LIBS
// sdl
#elif defined(HAS_CURSES)
// curses
#endif

#define version   0.9
#define copyright 2024

using namespace std;

// String operations
vector<string> splitString(
	const string str,
    const string delimiter
);
vector<string> sliceString(
	const vector<string>& v, 
    int x,
    int legnth
);

// Shell
string getCommand();
void printAbout();
void printFunctions(
	vector<string> func = {"No functions have been defined."}
);
void printHelp(
	vector<string> func
);
int formattingError(
	string sender
);
/* 
int main();
*/

// Calculation
double computeExpression(
	string expression, 
	int inputFormat = 1
);

// Calculation helpers
int precedence(
	string op
);
double applyOperation(
	string op,
	double a,
	double b = 0.0
);
double evalulatePostfix(
	string expr
);
double infixToPostfix(
	string expr
);
double prefixToPostfix(
	string expr
);

// Function framework
void addUserFunction(
	string name,
	string expr,
	string testexpr=name+"()"
);
void removeFunction(
	string name
);
bool resolveFunction(
	string name,
	int argc
)
double computeFunction(
	string name,
	int argc,
	double ** argv
);