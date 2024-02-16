#include "calc.h"

/*
 * Copyright (c) Mileter 2024
 * TODO Add custom function support (e.g. f(x) = x + 1) @ applyOperation()
 * TODO Add multivarible function support (e.g. log(b, x) ) @ computeExpression()
 * TODO Add prefix and postfix @ computeExpression() & main() 
 */

using namespace std;

#define version   0.9
#define copyright 2024

vector<string> splitString(const string str,
                     const string delimiter) {
    regex regexz(delimiter);
    return {sregex_token_iterator(str.begin(), str.end(), regexz, -1),
            sregex_token_iterator()};
}

vector<string> sliceString(const vector<string>& v, 
                          int x,
                          int legnth)
{
  auto start = v.begin() + x;
  auto end = v.begin() + x + legnth;

  vector<string> result(x - legnth);

  copy(start, end, result.begin());

  return result;
}

string getCommand()
{
  cout << ">";
  string command;
  getline(cin, command);
  return command;
}

void printAbout()
{
  cout << "CALCMD Shell (v" << version << ")\n"
       << "Copyright (c) Miles R. Chang 2024-" << copyright;
}

void printFunctions(vector<string> func = {"No functions have been defined."})
{
  cout << "| Supported Functions\n";
  for (int i = 0; i < func.size(); i++)
  {
    if(i == func.size()-1)
    {
      cout << "| | " << func[i];
      break;
    }
    cout << "| | " << func[i] << endl;
  }
}

void printHelp(vector<string> func)
{
  printAbout();
  cout << "Summary\n"
       << "| Program Commands\n"
       << "| | help;    displays this message.\n"
       << "| | about    displays program information.\n"
       << "| | list;    lists which functions are defined.\n"
       << "| | input x; changes the input format to {prefix, infix, postfix}.\n"
       << "| | exit;    exits this program.\n"
       << "| | logout;  exits this program.\n";
       printFunctions(func); // None to mention at this moment
}

int precedence(string op)
{
  if(op == "+" || op == "-") return 1;
  if(op == "*" || op == "/") return 2;
  else                       return 3; // all other functions
}

double applyOperation(string op, double a, double b = 0.0)
{
  if (op == "+") return a + b;
  else if(op == "-") return a - b;
  else if(op == "*") return a * b;
  else if(op == "/")
  {
    if(b == 0) cout << "[!] Devision by zero is not acceptable.\n";
    return a/b;
  }
  else if(op == "^") return pow(a, b);
  else if(op == "%") return (int)a % (int)b;
  else if(op == "sin") return sin(a);
  else if(op == "cos") return cos(a);
  else if(op == "sqrt") return sqrt(a);
  else if(op == "cbrt") return cbrt(a);
  else if(op == "exp") return exp(a);
  else if(op == "logE") return log(a);
  else if(op == "log10") return log10(a);
  else if(op == "abs") return abs(a);
  else
  {
    // support for custom functions
    cout << "[!] " << op << " is not defined;\n"; // skips over custom function checking
    return 0.0;
  }
}

int formattingError(string sender)
{
  cout << "[" << sender << "] There was an error in parsing. Please check your command."\n;
  return 0;
}

double computeExpression(string expression, int inputFormat = 1)
{
  //vector<string> expressionVector = splitString(expression, " "); // gurenteed not to have whitespace
  // the line above is no longer nessecary, as it creates extra empty strings
  switch(inputFormat)
  {
    case 0: // prefix
    {
      string postfix;
      stack<string> operationStack;
      for(int i = 0; i < expression.size(); i++)
      {
        if(expression[i] == ' ') continue; // skip acceptable
        else if(isdigit(expression[i])) postfix.push_back(expression[i]); // no prentheses; one char number
        else if(expression[i] == '(') // multidigit number or decimal
        {
          postfix.push_back('(');
          while(i < expression.size())
          {
            if (expression[i] == ')')
            {
              postfix.push_back(')');
            }
            else if(!isdigit(expression[i]) && !(expression[i] == '.')) return formattingError("computeExpression:prefix");
            else postfix.push_back(expression[i]); // add digit or decimal point.
            i++;
          }
        }
      }
      return evalulatePostfix(postfix);
    }
    break;  // end of prefix
    case 2:
      return evalulatePostfix(expression);
    break;  // end of posfix
    default:// infix
    {       // infix scope
      int i;
      stack<double> operationStack;
      stack<string> numberStack;
      string postfix;
      return evalulatePostfix(postfix);
    }
  }
  return finalExpression;
}

double evalulatePostfix(string postfixExpression)
{
    string pE = postfixExpression;
}

int main() // no prototyping needed.
{
  cout << "Welcome to the CALCMD Shell" << endl << "Copyright (c) Miles R. Chang 2024";
  bool logout = false;
  double lastAnswer = 0;
  int inputFormat = 2; // 0 prefix, 1 infix, 2 postfix
  
  vector<string> functions =     {"sin",
                                  "cos",
                                  "sqrt",
                                  "cbrt",
                                  "exp",
                                  "logE",
                                  "log10",
                                  "abs"};

  while(!logout)
  {
    cout << "\n";
    string cmd = getCommand();
    if     (cmd == "exit") logout = true;
    else if(cmd == "logout") logout = true;
    else if(cmd == "list") printFunctions(functions);
    else if(cmd.substr(0, 5) == "input")
    {
      string x;
      try {
        cmd.substr(7);
      }
      catch (out_of_range) {
        cout << "[input] Invalid usage! {prefix, infix, postfix}."
      }
      if(x == "prefix") inputFormat = 0;
      else if(x == "infix") inputFormat = 1;
      else if(x == "postfix") inputFormat = 2;
      else cout << "[input] COMMAND FAILED. Run the `help` command for more information.";
    }
    else if(cmd == "help") printHelp(functions);
    else if(cmd == "about") printAbout();
    else {
      lastAnswer = computeExpression(cmd, inputFormat);
      cout << lastAnswer;
    }
  }
  return 0;
}
