//
// Created by andyh on 2/2/22.
//

#ifndef LISP_INTERPRETER_FUNCTIONS_HPP
#define LISP_INTERPRETER_FUNCTIONS_HPP

// src
#include <functions/FunctionTypes.hpp>
#include <functions/ArithmeticOperators.hpp>
#include <basic_types/List.hpp>
#include <basic_types/Number.hpp>

// STl
#include <map>
#include <vector>
#include <functional>
#include <memory>

namespace functions
{

    /** Map of all valid functions to all valid identifiers
     */
    static std::map<std::string, std::function<std::unique_ptr<IReturnType>(FunctionParameterType)>> globalFunctions =
    {
        {"+", ArithmeticOperations::add}
    };
}


#endif //LISP_INTERPRETER_FUNCTIONS_HPP
