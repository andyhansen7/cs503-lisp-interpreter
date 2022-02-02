//
// Created by andyh on 1/31/22.
//

#ifndef CS503_LISP_INTERPRETER_LISPPARSER_HPP
#define CS503_LISP_INTERPRETER_LISPPARSER_HPP

// String
#include <string>
#include <map>
#include <functional>
#include <exception>
#include <vector>

namespace parsers
{
    typedef struct
    {
        std::size_t _front;
        std::size_t _rear;
    } ParenthesisLocations;

    typedef struct
    {
        std::string _operation;
        std::vector<std::string> _operands;
    } OperatorOperands;

    typedef struct
    {
        std::string _name;
        std::string _inputs;
        std::vector<std::string> _lines;
    } FunctionDefinition;

    class LispParser
    {
    public:
        LispParser();

        std::string parseCommand(std::string data);
        std::string evaluateAtom(std::string data);
    private:
        // Map of all functions to their corresponding string names
        std::map<std::string, std::function<std::string(std::vector<std::string>)>> _operations;

        // Map of all variables declared using setq and their corresponding values
        std::map<std::string, std::string> _userVariables;

        // Map of all defined functions to function types to corresponding objects
        std::map<std::string, FunctionDefinition> _userFunctions;

        // Basic operators
        static std::string addImplementation(std::vector<std::string> operands);
        static std::string subtractImplementation(std::vector<std::string> operands);
        static std::string multiplyImplementation(std::vector<std::string> operands);
        static std::string divideImplementation(std::vector<std::string> operands);

        // Comparison operators
        static std::string greaterThanImplementation(std::vector<std::string> operands);
        static std::string equalToImplementation(std::vector<std::string> operands);
        static std::string lessThanImplementation(std::vector<std::string> operands);

        // Other operators
         std::string ifImplementation(std::vector<std::string> operands);

        // Allow users to define
        std::string setqImplementation(std::vector<std::string> operands);

        // Returns indices of innermost (last) pair of parenthesis
        static ParenthesisLocations getInnermostParenthesis(std::string data);

        // Returns indices of outermost (first) pair of parenthesis
        static ParenthesisLocations getOutermostParenthesis(std::string data);

        // Returns true if string contains integer - no period
        static bool isInteger(std::string str);

        // Returns true if all items in string are integers
        static bool allOperandsAreIntegers(std::vector<std::string> operands);

        // Returns the operator to be applied to a string, and a vector of all operands in the string
        static OperatorOperands getOperatorOperands(std::string data);

        // Evaluate user variables in operands
        std::vector<std::string> evaluateUserVars(std::vector<std::string> operands);

        // Prints a message to cout if __DEBUG is defined
        static void debugLog(std::string message);

        // Prints an error message to cout
        static void errorLog(std::string message);
    };
}


#endif //CS503_LISP_INTERPRETER_LISPPARSER_HPP
