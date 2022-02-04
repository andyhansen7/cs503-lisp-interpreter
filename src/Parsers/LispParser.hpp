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
    typedef struct parenthesisLocations
    {
        std::size_t _front;
        std::size_t _rear;
    } ParenthesisLocations;

    typedef struct allParenthesisLocations
    {
        std::vector<ParenthesisLocations> _pairs;
    } AllParenthesisLocations;

    typedef struct operatorOperands
    {
        std::string _operation;
        std::vector<std::string> _operands;
    } OperatorOperands;

    typedef struct functionDefinition
    {
        std::string _name;
        std::string _inputs;
        std::vector<std::string> _lines;
    } FunctionDefinition;

    typedef struct evaluationReturn
    {
        std::string returnValue = "";
        bool parameterWasList = false;
    } EvaluationReturn;

    class LispParser
    {
    public:
        LispParser();

        std::string parseCommand(std::string data);
        std::string evaluateAtom(std::string data);
        std::string evaluateList(std::string data);
    private:
        // Map of all functions to their corresponding string names
        std::map<std::string, std::function<std::string(std::vector<std::string>)>> _atomOperations;

        // Same as above, but for functions of lists
        std::map<std::string, std::function<std::string(std::vector<std::string>)>> _listOperations;

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
        static std::string consImplentation(std::vector<std::string> operands);
        std::string ifImplementation(std::vector<std::string> operands);

        // Allow users to define
        std::string setqImplementation(std::vector<std::string> operands);

        // Returns indices of innermost (last) pair of parenthesis
        static ParenthesisLocations getInnermostParenthesis(std::string data);

        // Returns indices of outermost (first) pair of parenthesis
        static ParenthesisLocations getOutermostParenthesis(std::string data);

        static AllParenthesisLocations getAllParenthesisLocations(std::string data);
        static AllParenthesisLocations orderParenthesisLocations(AllParenthesisLocations locations);
        static bool compareLocations(const ParenthesisLocations& a, const ParenthesisLocations& b);

        // Returns true if string contains integer - no period
        static bool isInteger(std::string str);

        // Returns true if string is a list - period separating each entry
        bool isList(std::string str);

        // Returns true if all items in string are integers
        static bool allOperandsAreIntegers(std::vector<std::string> operands);

        // Returns true if all items in string are lists
        bool allOperandsAreLists(std::vector<std::string> operands);

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
