//
// Created by andyh on 2/4/22.
//

#ifndef LISP_INTERPRETER_PRINTOPERATOR_HPP
#define LISP_INTERPRETER_PRINTOPERATOR_HPP

// src
#include <Functions/FunctionTypes.hpp>
#include <BasicTypes/IBasicType.hpp>

// STL
#include <memory>
#include <string>

namespace functions
{
    class PrintOperator
    {
    public:
        static std::shared_ptr<StringReturnType> print(std::shared_ptr<basic_types::IBasicType> data)
        {
            return std::make_shared<StringReturnType>(data->str());
        }
    };
}

#endif //LISP_INTERPRETER_PRINTOPERATOR_HPP
