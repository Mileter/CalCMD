#include "calc.h"

vector<string> funcReserved       // function names that connect to cmath bindings
  = {                             // TODO: implement all the bindingss into 
		"add", "sub", "mul", "div", "mod", "+", "-", "*", "/",  // standard operators
		"pow", "sqrt", "cbrt", "hypot",                         // extended standard
		"sin", "cos", "tan", "acos", "asin", "atan", "atan2",   // simple trig bindings
		"cosh", "sinh", "tanh", "acosh", "asinh", "atanh",      // hyperbolic functions
		"log", "log10", "log1p", "log2", "logb", "modf",        // log functions
		"scalbln", "exp", "frexp", "ldexp", "exp2", "expm1",    // exp functions
		"erf", "erfc",                                          // error functions
		"tgamma", "lgamma",                                     // gamma functions
		"ceil", "floor", "round", "trunc", "rint", "nearbyint", // rounding functions
		"fmod", "remainder", "remquo",                          // extended modulus functions
		"dim", "max", "min",                                    // min, max, difference_type
		"abs", "fabs", "fma",                                   // abs is actually fabs here
		"pi", "nan", "e", "ln2", "ln10", "egamma", "phi"        // constants
	};

using namespace std;

// Define method as a function pointer type that can point to the relevant functions
using method = std::variant<std::function<long double(long double)>, 
                            std::function<long double(long double, long double)>,
							std::function<long double(long double, long double, long double)>>;; // Adjusted for long double

map<string, pair<method, int>> funcMap = {
    {"add", [](long double a, long double b) { return a + b; }, 2},       // Custom add
    {"sub", [](long double a, long double b) { return a - b; }, 2},       // Custom sub
    {"mul", [](long double a, long double b) { return a * b; }, 2},       // Custom mul
    {"div", [](long double a, long double b) { return a / b; }, 2},       // Custom div
    {"mod", [](long double a, long double b) { return fmod(a, b); }, 2},  // Modulus
    {"+", [](long double a, long double b) { return a + b; }, 2},         // Operator +
    {"-", [](long double a, long double b) { return a - b; }, 2},         // Operator -
    {"*", [](long double a, long double b) { return a * b; }, 2},         // Operator *
    {"/", [](long double a, long double b) { return a / b; }, 2},         // Operator /

    {"pow", powl, 2},              // Power function using powl
    {"sqrt", sqrtl, 1},            // Square root
    {"cbrt", cbrtl, 1},            // Cube root
    {"hypot", hypotl, 2},          // Hypotenuse

    {"sin", sinl, 1},              // Sine
    {"cos", cosl, 1},              // Cosine
    {"tan", tanl, 1},              // Tangent
    {"acos", acosl, 1},            // Arc cosine
    {"asin", asinl, 1},            // Arc sine
    {"atan", atanl, 1},            // Arc tangent
    {"atan2", atan2l, 2},          // Arc tangent of two variables

    {"cosh", coshl, 1},            // Hyperbolic cosine
    {"sinh", sinhl, 1},            // Hyperbolic sine
    {"tanh", tanhl, 1},            // Hyperbolic tangent
    {"acosh", acoshl, 1},          // Inverse hyperbolic cosine
    {"asinh", asinhl, 1},          // Inverse hyperbolic sine
    {"atanh", atanhl, 1},          // Inverse hyperbolic tangent

    {"log", logl, 1},              // Natural logarithm
    {"log10", log10l, 1},          // Base-10 logarithm
    {"log1p", log1pl, 1},          // log(1 + x)
    {"log2", log2l, 1},            // Base-2 logarithm
    {"logb", logbl, 1},            // Binary exponent of a number
    {"modf", modfl, 2},            // Split float into integral and fractional parts

    {"scalbln", scalblnl, 2},      // Scale floating point number
    {"exp", expl, 1},              // Exponential function
    {"frexp", frexpl, 2},          // Break float into mantissa and exponent
    {"ldexp", ldexpl, 2},          // Combine mantissa and exponent
    {"exp2", exp2l, 1},            // Base-2 exponential
    {"expm1", expm1l, 1},          // exp(x) - 1

    {"erf", erfl, 1},              // Error function
    {"erfc", erfcl, 1},            // Complementary error function

    {"tgamma", tgammal, 1},        // Gamma function
    {"lgamma", lgammal, 1},        // Natural logarithm of gamma function

    {"ceil", ceill, 1},            // Round up
    {"floor", floorl, 1},          // Round down
    {"round", roundl, 1},          // Round to nearest integer
    {"trunc", truncl, 1},          // Truncate to integer
    {"rint", rintl, 1},            // Round to nearest integer
    {"nearbyint", nearbyintl, 1},  // Round to nearest integer (without raising overflow)

    {"fmod", fmodl, 2},            // Floating-point modulus
    {"remainder", remainderl, 2},  // Remainder of division
    {"remquo", remquol, 2},        // Remainder with quotient

    {"fdim", fdiml, 2},            // Positive difference
    {"fmax", fmaxl, 2},            // Maximum of two values
    {"fmin", fminl, 2},            // Minimum of two values

    {"abs", fabsl, 1},             // Absolute value (same as fabs)
    {"fabs", fabsl, 1},            // Absolute value for long double
    {"fma", fmal, 3},              // Fused multiply-add

    {"pi", M_PIl, 0},              // Constant pi
    {"nan", NAN, 0},               // NaN constant
    {"e", M_E, 0},                 // Euler's number (e)
    {"ln2", M_LN2, 0},             // Natural logarithm of 2
    {"ln10", M_LN10, 0},           // Natural logarithm of 10
    {"egamma", M_EULER, 0},        // Euler-Mascheroni constant
    {"phi", (1 + sqrtl(5)) / 2, 0} // Golden ratio
};

bool isInBindings(                 // checks if the function name is reserved.
	string name
)
{
	if(find(funcReserved.begin(), funcReserved.end(), name)
		!= funcReserved.end())
		return true;
	return false;
}

long double applyBindings(
	string name,
	int argc,
	long double argv[]
)
{
	
}