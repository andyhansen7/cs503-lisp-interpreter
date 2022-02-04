//
// Created by andyh on 2/2/22.
//

#ifndef LISP_INTERPRETER_FUNCTIONS_HPP
#define LISP_INTERPRETER_FUNCTIONS_HPP

// src
#include <Functions/FunctionTypes.hpp>
#include <Functions/ArithmeticOperators.hpp>
#include <Functions/ConditionalOperators.hpp>
#include <BasicTypes/List.hpp>
#include <BasicTypes/Number.hpp>

// STl
#include <map>
#include <vector>
#include <functional>
#include <memory>

namespace functions
{

    /** Map of all valid functions to all valid identifiers
     */
    static std::map<std::string, std::function<std::unique_ptr<IReturnType>(FunctionParameterType)>> arithmeticFunctions =
    {
        {"+", ArithmeticOperations::add},
        {"-", ArithmeticOperations::subtract},
        {"*", ArithmeticOperations::multiply},
        {"/", ArithmeticOperations::divide}
    };

    static std::map<std::string, std::function<std::unique_ptr<IReturnType>(ConditionalParameterType)>> conditionalFunctions =
    {
        {"if", ConditionalOperations::ifThen}
    };
}


#endif //LISP_INTERPRETER_FUNCTIONS_HPP
