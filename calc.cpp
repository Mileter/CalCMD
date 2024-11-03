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
map<string, tuple<int, vector<string>, string, int>> func;
                                  // (name, (argc, argv mappings, evaluation string, expression mode))
map<string, string> funcComments; // (name, comments)

// Trigonometry calculation setting
bool usingRadians;

bool addUserFunction(
	std::string name,
	int argc,
	std::string args[],     // names for which the arguments are called (valid positional variables)
	std::string expr,       // attempt to parse on add to check for formatting errors
	std::string comment = "No comment." ,
	int expression_mode = 1 // 1 is infix, 2 is postfix, 3 is prefix
)
{
	if(func.find(name) != func.end())
	{
		recordError("Function framework", "Cannot add function; `" + name + "` already exists.");
		throw ERR_ALREADY_EXIST;
	}
	else if (isInBindings(name))
	{
		recordError("Function framework", "Cannot add function; `" + name + "` has been reserved for a math binding.");
		throw ERR_ALREADY_RESERVED;
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
			}
		}
		vector<string> err;
		validityParse(argc, args, expr, err);
		
		if(err.size() > 0) // failed to parse
		{
			recordError("Function framework", "Errors occured when trying to add function `" + name + "`!");
			for(size_t i = 0; i < err.size(); i++)
				recordError("Function framework", "--> " + err[i]);
			throw ERR_NESTED_ERROR;
		}
		
		func[name] = make_tuple(argc, vector<string>(args, args + argc), expr, expression_mode);
		return true;
	}
	return false;
}

long double applyOperation(
	string op,
	int argc,
	long double argv[]
)
{
	try
	{
		if(isInBindings(op))
			return applyBindings(op, argc, argv);
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
	int argc_func = get<0>(func[op]);
	if(argc < argc_func) throw ERR_ARGC_LESS_THAN_OP;
	if(argc > argc_func) throw ERR_ARGC_MORE_THAN_OP;
	
	vector<string> & argv_map = get<1>(func[op]);
	string expr = get<2>(func[op]);
	int expr_mode = get<3>(func[op]);
	
	for(int i = 0; i < argc; i++)
	{
		// argv[i]:     the number to replace with
		// argv_map[i]: the thing to replace with number
		
		// find each occurance of argv[i] that is only surrounded by white space, comma, or brackets.
		// after that call on computeExpression(expr, expr_mode) to seal the deal.
	}
}