//
// Created by andyh on 2/3/22.
//

#ifndef LISP_INTERPRETER_CONDITIONALOPERATORS_HPP
#define LISP_INTERPRETER_CONDITIONALOPERATORS_HPP

// src
#include "FunctionTypes.hpp"

// STL
#include <memory>

using namespace functions;

namespace functions
{
    class ConditionalOperations
    {
    public:
        static std::shared_ptr<IReturnType> ifThen(ConditionalParameterType params)
        {
            if(params.condition)
            {
                return std::make_shared<StringReturnType>(params.trueExpression);
            }
            else
            {
                return std::make_shared<StringReturnType>(params.falseExpression);
            }
        }
    };
}

#endif //LISP_INTERPRETER_CONDITIONALOPERATORS_HPP
