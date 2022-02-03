//
// Created by andyh on 2/3/22.
//

#ifndef LISP_INTERPRETER_CONDITIONALOPERATORS_HPP
#define LISP_INTERPRETER_CONDITIONALOPERATORS_HPP

// src
#include <functions/FunctionTypes.hpp>

using namespace functions;

namespace functions
{
    class ConditionalOperations
    {
    public:
        static std::unique_ptr<IReturnType> ifThen(ConditionalParameterType params)
        {
            if(params.condition)
            {
                return std::make_unique<StringReturnType>(params.trueExpression);
            }
            else
            {
                return std::make_unique<StringReturnType>(params.falseExpression);
            }
        }
    };
}

#endif //LISP_INTERPRETER_CONDITIONALOPERATORS_HPP
