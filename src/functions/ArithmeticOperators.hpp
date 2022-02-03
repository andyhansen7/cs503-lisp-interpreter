//
// Created by andyh on 2/2/22.
//

#ifndef LISP_INTERPRETER_ARITHMETICOPERATORS_HPP
#define LISP_INTERPRETER_ARITHMETICOPERATORS_HPP

// src
#include <basic_types/Number.hpp>
#include <basic_types/List.hpp>
#include <functions/FunctionTypes.hpp>

// STL
#include <string>
#include <vector>
#include <memory>

using namespace basic_types;
using namespace functions;

namespace functions
{
    class ArithmeticOperations
    {
    public:
        static std::unique_ptr<NumberReturnType> add(FunctionParameterType params)
        {
            assert(params.listOperands.size() == 0);
            assert(params.numberOperands.size() == 0);

            const bool resultIsInt = basic_types::Number::allAreIntegers(params.numberOperands);
            double val = 0.0f;

            for(auto it : params.numberOperands)
            {
                val += it.get();
            }

            Number num(resultIsInt ? static_cast<int>(val) : val);
            return std::make_unique<NumberReturnType>(num);
        }
    };
}

#endif //LISP_INTERPRETER_ARITHMETICOPERATORS_HPP
