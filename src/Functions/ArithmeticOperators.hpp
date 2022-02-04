//
// Created by andyh on 2/2/22.
//

#ifndef LISP_INTERPRETER_ARITHMETICOPERATORS_HPP
#define LISP_INTERPRETER_ARITHMETICOPERATORS_HPP

// src
#include <BasicTypes/Number.hpp>
#include <BasicTypes/List.hpp>
#include <Functions/FunctionTypes.hpp>
#include <Output/ErrorHandle.hpp>
#include <Output/Debug.hpp>

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
        static std::unique_ptr<NumberReturnType> add(ArithmeticParameterType params)
        {
            if(params.listOperands.size() != 0)
            {
                debug("About to kill! Given list operands:");
                for(auto op : params.listOperands)
                {
                    debug(op.str());
                }
                error("Addition not possible with list arguments!");
            }
            if(params.numberOperands.size() == 0)
            {
                debug("About to kill! Given number operands:");
                for(auto op : params.numberOperands)
                {
                    debug(op.str());
                }
                error("Addition not given any number arguments!");
            }

            double val = 0.0f;

            for(auto it : params.numberOperands)
            {
                debug(it.str());
                val += it.get();
            }

            Number num(val);
            return std::make_unique<NumberReturnType>(num);
        }

        static std::unique_ptr<NumberReturnType> subtract(ArithmeticParameterType params)
        {
            if(params.listOperands.size() != 0) error("Subtraction not possible with list arguments!");
            if(params.numberOperands.size() == 0) error("Subtraction not given any number arguments!");

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

            Number num(val);
            return std::make_unique<NumberReturnType>(num);
        }

        static std::unique_ptr<NumberReturnType> multiply(ArithmeticParameterType params)
        {
            if(params.listOperands.size() != 0) error("Multiply not possible with list arguments!");
            if(params.numberOperands.size() == 0) error("Multiply not given any number arguments!");

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

            Number num(val);
            return std::make_unique<NumberReturnType>(num);
        }

        static std::unique_ptr<NumberReturnType> divide(ArithmeticParameterType params)
        {
            if(params.listOperands.size() != 0) error("Divide not possible with list arguments!");
            if(params.numberOperands.size() == 0) error("Divide not given any number arguments!");

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

            Number num(val);
            return std::make_unique<NumberReturnType>(num);
        }

    private:
        static void error(std::string message)
        {
            return output::ErrorHandle::handleError("ArithmeticOperator", message);
        }

        static void debug(std::string message)
        {
            return output::Debug::debugLog("ArithmeticOperator", message);
        }
    };
}

#endif //LISP_INTERPRETER_ARITHMETICOPERATORS_HPP
