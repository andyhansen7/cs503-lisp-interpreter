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

namespace parsers
{
    typedef struct
    {
        std::size_t _front;
        std::size_t _rear;
    } ParenthesisLocations;

    class LispParser
    {
    public:
        LispParser();

        std::string parse(std::string data);
    private:
        std::map<std::string, std::function<std::string(std::string,std::string)>> _operations;
        std::map<std::string, std::function<bool(std::string,std::string)>> _comparisons;

        // Implementations
        static std::string addImplementation(std::string basicTypeA, std::string basicTypeB);
        static std::string subtractImplementation(std::string basicTypeA, std::string basicTypeB);
        static std::string multiplyImplementation(std::string basicTypeA, std::string basicTypeB);
        static std::string divideImplementation(std::string basicTypeA, std::string basicTypeB);

        static bool greaterThanImplementation(std::string basicTypeA, std::string basicTypeB);
        static bool equalToImplementation(std::string basicTypeA, std::string basicTypeB);
        static bool lessThanImplementation(std::string basicTypeA, std::string basicTypeB);

        ParenthesisLocations getInnermostParenthesis(std::string data);
        static bool isInteger(std::string str);
    };
}


#endif //CS503_LISP_INTERPRETER_LISPPARSER_HPP
