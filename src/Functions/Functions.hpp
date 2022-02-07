//
// Created by andyh on 2/2/22.
//

#ifndef LISP_INTERPRETER_FUNCTIONS_HPP
#define LISP_INTERPRETER_FUNCTIONS_HPP

// src
#include <Functions/FunctionTypes.hpp>
#include <Functions/ArithmeticOperators.hpp>
#include <Functions/ConditionalOperators.hpp>
#include <Functions/BooleanOperators.hpp>
#include <Functions/PrintOperator.hpp>
#include <Functions/ListOperators.hpp>
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
    static std::map<std::string, std::function<std::shared_ptr<IReturnType>(ArithmeticParameterType)>> arithmeticFunctions =
    {
        {"+", ArithmeticOperations::add},
        {"-", ArithmeticOperations::subtract},
        {"*", ArithmeticOperations::multiply},
        {"/", ArithmeticOperations::divide}
    };

    static std::map<std::string, std::function<std::shared_ptr<IReturnType>(ArithmeticParameterType)>> listFunctions =
    {
        {"cons", ListOperations::cons}
    };

    static std::map<std::string, std::function<std::shared_ptr<IReturnType>(ArithmeticParameterType)>> booleanFunctions =
    {
        {"<", BooleanOperations::lessThan},
        {"=", BooleanOperations::equalTo},
        {">", BooleanOperations::greaterThan}
    };

    static std::map<std::string, std::function<std::shared_ptr<IReturnType>(ConditionalParameterType)>> conditionalFunctions =
    {
        {"if", ConditionalOperations::ifThen}
    };

    static std::map<std::string, std::function<std::shared_ptr<IReturnType>(std::shared_ptr<basic_types::IBasicType>)>> printFunctions =
    {
        {"print", PrintOperator::print}
    };
}


#endif //LISP_INTERPRETER_FUNCTIONS_HPP
