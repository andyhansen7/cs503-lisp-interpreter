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

    class LispParser
    {
    public:
        LispParser();

        std::string parseCommand(std::string data);
        std::string evaluateAtom(std::string data);
    private:
        std::map<std::string, std::function<std::string(std::string,std::string)>> _operations;

        // Implementations
        static std::string addImplementation(std::string basicTypeA, std::string basicTypeB);
        static std::string subtractImplementation(std::string basicTypeA, std::string basicTypeB);
        static std::string multiplyImplementation(std::string basicTypeA, std::string basicTypeB);
        static std::string divideImplementation(std::string basicTypeA, std::string basicTypeB);

        static std::string greaterThanImplementation(std::string basicTypeA, std::string basicTypeB);
        static std::string equalToImplementation(std::string basicTypeA, std::string basicTypeB);
        static std::string lessThanImplementation(std::string basicTypeA, std::string basicTypeB);

        ParenthesisLocations getInnermostParenthesis(std::string data);
        ParenthesisLocations getOutermostParenthesis(std::string data);
        static bool isInteger(std::string str);
        static OperatorOperands getOperatorOperands(std::string data);
    };
}


#endif //CS503_LISP_INTERPRETER_LISPPARSER_HPP
