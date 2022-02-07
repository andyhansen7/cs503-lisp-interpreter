//
// Created by andyh on 2/3/22.
//

#ifndef LISP_INTERPRETER_PARSER_HPP
#define LISP_INTERPRETER_PARSER_HPP

// src
#include <BasicTypes/List.hpp>
#include <BasicTypes/Number.hpp>
#include <BasicTypes/Conditional.hpp>
#include <Output/ErrorHandle.hpp>
#include <Output/Debug.hpp>
#include <Parsers/OperatorOperands.hpp>
#include <Parsers/ParenthesisUtils.hpp>
#include <Functions/Functions.hpp>

// STL
#include <string>
#include <vector>
#include <map>

using namespace functions;
using namespace basic_types;
using namespace parsers;

namespace parsers
{
    typedef struct evaluation_return
    {
        std::string data = "";
        bool dataWasList = false;
    } EvaluationReturn;

    class Parser
    {
    public:
        Parser();
        ~Parser() = default;

        // Parse a single command
        std::string parse(const std::string& text);

        friend class List;
    private:
        std::map<std::string, std::shared_ptr<IBasicType>> _userVariables;

        // Evaluate an object by applying an operation and returning a string
        EvaluationReturn evaluate(const std::string& data);

        ArithmeticParameterType getArithmeticParameterType(const OperatorOperands& ops);
        ConditionalParameterType getConditionalParameterType(const OperatorOperands& ops);

        // Evaluate user variables in operands
        std::vector<std::string> evaluateUserVars(std::vector<std::string> operands);

        // Error log call
        static void error(const std::string& message);

        // Debug log call
        static void debug(const std::string& message);
    };
}


#endif //LISP_INTERPRETER_PARSER_HPP
