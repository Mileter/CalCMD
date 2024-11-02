#include "calc.h"

/*
 * calc.cpp
 *
 * Copyright (c) 2024 Mileter
 *
 * Distributed under MIT License.
 * You should have recieved a license with this file.
 * If not, check the origin git page.
 *
 * calc.cpp handles all the calculations, function name resolutions,
 * user defined function name computation.
 *
 * Looking for the parser? See parse.cpp
 */
 
using namespace std;
 
// Function framework externs
map<string, tuple<int, vector<string>, string>> func;
                                  // (name, (argc, argv mappings, evaluation string))
map<string, string> funcComments; // (name, comments)
vector<string> funcReserved       // function names with custom handling
  = {
		"add", "sub", "mul", "div", "mod" // standard operators
		"sin", "cos", "tan", "acos", "asin", "atan" // simple trig
	};
// Trigonometry calculation setting
bool usingRadians;

bool addUserFunction(
	std::string name,
	int argc;
	std::string args[], // names for which the arguments are called (valid positional variables)
	std::string expr,   // attempt to parse on add to check for formatting errors
	std::string comment = "No comment." 
)
{
	if(func.find(name) != func.end())
	{
		recordError("Function framework", "Cannot add function; `" + name + "` already exists.");
		throw ERR_ALREADY_EXIST;
		return false;
	}
	else if(funcReserved.find(name) != funcReserved.end())
	{
		recordError("Function framework", "Cannot add function; `" + name + "` has been reserved for a special function.");
		throw ERR_ALREADY_RESERVED;
		return false;
	}
	else
	{
		for(size_t i = 0; i < name.size(); i++)
		{
			if(name[i] == '.' || name[i] >= '0' && name[i] <= '9')
			{
				recordError("Function framework", "Cannot add function; `" + name + "` is not a valid name. Names can not include decimal points, digits, brackets, asterisks, plus, comma, minus, nor escape characters.");
				recordError("Function framework", "--> See the manual for more information.");
				throw ERR_ILLEGAL_CHAR;
				return false;
			}
		}
		vector<string> err;
		validityParse(argc, args, expr, err);
		
		if(err.size() > 0) // failed to parse
		{
			recordError("Function framework", "Errors occured when trying to add function `" + name + "`!");
			for(size_t i = 0; i < err.size(); i++)
				recordError("Function framework", "--> " + err[i];
			throw ERR_NESTED_ERROR;
			return false;
		}
		
		func[name] = expr;
		return true;
	}
}

long double applyOperation(
	string op,
	int argc,
	std::string argv[]
)
{
	try
	{
		switch(op)
		{
			case "add":
			case "+":
			if(argc > 2) throw ERR_ARGC_MORE_THAN_OP;
			if(argc < 2) throw ERR_ARGC_LESS_THAN_OP
			return stold(argv[0]) + stold(argv[1]);
			break;
			
			case "sub":
			case "-":
			if(argc > 2) throw ERR_ARGC_MORE_THAN_OP;
			if(argc < 2) throw ERR_ARGC_LESS_THAN_OP;
			return stold(argv[0]) - stold(argv[1]);
			break;
			
			case "mul":
			case "*":
			if(argc > 2) throw ERR_ARGC_MORE_THAN_OP;
			if(argc < 2) throw ERR_ARGC_LESS_THAN_OP;
			return stold(argv[0]) * stold(argv[1]);
			break;
			
			case "div":
			case "/":
			if(argc > 2) throw ERR_ARGC_MORE_THAN_OP;
			if(argc < 2) throw ERR_ARGC_LESS_THAN_OP;
			if(stold(argv[1]) == 0.0) throw ERR_DIV_BY_ZERO;
			return stold(argv[0]) / stold(argv[1]);
			break;
			
			case "mod":
			case "%":
			if(argc > 2) throw ERR_ARGC_MORE_THAN_OP;
			if(argc < 2) throw ERR_ARGC_LESS_THAN_OP;
			if(stold(argv[1]) == 0.0) throw ERR_DIV_BY_ZERO;
			return stold(argv[0]) % stold(argv[1]);
			break;
		}
	}
	catch(invalid_argument const & e)
	{
		recordError("Operation computer", "Could not convert string to long double; input is not a long double.");
		throw ERR_NESTED_ERROR;
	}
	catch(out_of_range const & e)
	{
		recordError("Operation computer", "Input is too big to use with a long double.");
	}
	
	if(func.find[op] == func.end)
	{
		recordError("Function resolver", "Cannot resolve operation `" + op +"`.");
		throw ERR_CANNOT_RESOLVE;
	}
	int 
	vector<string> & argv_map = func[op].second;
	string expr = func[op].third;
}