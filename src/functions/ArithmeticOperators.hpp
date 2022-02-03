//
// Created by andyh on 2/2/22.
//

#ifndef LISP_INTERPRETER_ARITHMETICOPERATORS_HPP
#define LISP_INTERPRETER_ARITHMETICOPERATORS_HPP

// src
#include <basic_types/Number.hpp>
#include <basic_types/List.hpp>
#include <functions/FunctionTypes.hpp>
#include <error/ErrorHandle.hpp>

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
            if(params.listOperands.size() != 0) error("Addition not possible with list arguments!");
            if(params.numberOperands.size() == 0) error("Addition not given any number arguments!");

            const bool resultIsInt = basic_types::Number::allAreIntegers(params.numberOperands);
            double val = 0.0f;

            for(auto it : params.numberOperands)
            {
                val += it.get();
            }

            Number num(resultIsInt ? static_cast<int>(val) : val);
            return std::make_unique<NumberReturnType>(num);
        }

        static std::unique_ptr<NumberReturnType> subtract(FunctionParameterType params)
        {
            if(params.listOperands.size() != 0) error("Subtraction not possible with list arguments!");
            if(params.numberOperands.size() == 0) error("Subtraction not given any number arguments!");

            const bool resultIsInt = basic_types::Number::allAreIntegers(params.numberOperands);
            double val = 0.0f;
            bool firstSet = false;

            for(auto it : params.numberOperands)
            {
                if(!firstSet)
                {
                    val = it.get();
                    firstSet = true;
                }
                else
                {
                    val -= it.get();
                }
            }

            Number num(resultIsInt ? static_cast<int>(val) : val);
            return std::make_unique<NumberReturnType>(num);
        }

        static std::unique_ptr<NumberReturnType> multiply(FunctionParameterType params)
        {
            if(params.listOperands.size() != 0) error("Multiply not possible with list arguments!");
            if(params.numberOperands.size() == 0) error("Multiply not given any number arguments!");

            const bool resultIsInt = basic_types::Number::allAreIntegers(params.numberOperands);
            double val = 0.0f;
            bool firstSet = false;

            for(auto it : params.numberOperands)
            {
                if(!firstSet)
                {
                    val = it.get();
                    firstSet = true;
                }
                else
                {
                    val *= it.get();
                }
            }

            Number num(resultIsInt ? static_cast<int>(val) : val);
            return std::make_unique<NumberReturnType>(num);
        }

        static std::unique_ptr<NumberReturnType> divide(FunctionParameterType params)
        {
            if(params.listOperands.size() != 0) error("Divide not possible with list arguments!");
            if(params.numberOperands.size() == 0) error("Divide not given any number arguments!");

            const bool resultIsInt = basic_types::Number::allAreIntegers(params.numberOperands);
            double val = 0.0f;
            bool firstSet = false;

            for(auto it : params.numberOperands)
            {
                if(!firstSet)
                {
                    val = it.get();
                    firstSet = true;
                }
                else
                {
                    val /= it.get();
                }
            }

            Number num(resultIsInt ? static_cast<int>(val) : val);
            return std::make_unique<NumberReturnType>(num);
        }

    private:
        static void error(std::string message)
        {
            return error::ErrorHandle::handleError("ArithmeticOperator", message);
        }
    };
}

#endif //LISP_INTERPRETER_ARITHMETICOPERATORS_HPP
