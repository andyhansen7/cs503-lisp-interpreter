//
// Created by andyh on 2/3/22.
//

#ifndef LISP_INTERPRETER_PARSER_HPP
#define LISP_INTERPRETER_PARSER_HPP

// src
#include <basic_types/List.hpp>
#include <basic_types/Number.hpp>
#include <basic_types/Conditional.hpp>
#include <error/ErrorHandle.hpp>
#include <parser/ParenthesisUtils.hpp>
#include <functions/Functions.hpp>

// STL
#include <string>
#include <map>

using namespace functions;
using namespace basic_types;
using namespace parsers;

namespace parsers
{
    typedef struct operator_operands
    {
        std::string operation;
        std::vector<std::string> operands;
    } OperatorOperands;

    typedef struct operator_parameters
    {
        std::string operation;
        FunctionParameterType params;
    } OperatorParameters;

    class Parser
    {
    public:
        Parser();
        ~Parser() = default;

        std::string parse(const std::string& text);
    private:
        std::map<std::string, std::unique_ptr<IBasicType>> _userVariables;

        // Evaluate an object by applying an operation and returning a string
        std::string evaluate(const std::string& data);

        OperatorOperands getOperatorOperands(const std::string& data);

        OperatorParameters getOperatorParameters(OperatorOperands ops);

        // Evaluate user variables in operands
        std::vector<std::string> evaluateUserVars(std::vector<std::string> operands);

        // Error log call
        void error(const std::string& message);
    };
}


#endif //LISP_INTERPRETER_PARSER_HPP
