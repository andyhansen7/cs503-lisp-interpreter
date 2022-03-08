//
// Created by andyh on 2/4/22.
//

#ifndef LISP_INTERPRETER_BOOLEANOPERATORS_HPP
#define LISP_INTERPRETER_BOOLEANOPERATORS_HPP

// src
#include "Number.cpp"
#include "List.cpp"
#include "FunctionTypes.hpp"
#include "ErrorHandle.cpp"
#include "Debug.cpp"

// STL
#include <string>
#include <vector>
#include <memory>

namespace functions
{
    class BooleanOperations
    {
    public:
        static std::shared_ptr<ConditionalReturnType> lessThan(ArithmeticParameterType params)
        {
            if(params.listOperands.size() != 0) error("LessThan not possible with list arguments!");
            if(params.numberOperands.size() != 2) error("LessThan must be provided exactly 2 number arguments!");

            double op1 = params.numberOperands[0].get();
            double op2 = params.numberOperands[1].get();

            if(op1 < op2)
            {
                Conditional cond("T");
                return std::make_shared<ConditionalReturnType>(cond);
            }
            else
            {
                Conditional cond("()");
                return std::make_shared<ConditionalReturnType>(cond);
            }
        }

        static std::shared_ptr<ConditionalReturnType> equalTo(ArithmeticParameterType params)
        {
            if(params.listOperands.size() != 0) error("EqualTo not possible with list arguments!");
            if(params.numberOperands.size() != 2) error("EqualTo must be provided exactly 2 number arguments!");

            double op1 = params.numberOperands[0].get();
            double op2 = params.numberOperands[1].get();

            if(op1 == op2)
            {
                Conditional cond("T");
                return std::make_shared<ConditionalReturnType>(cond);
            }
            else
            {
                Conditional cond("()");
                return std::make_shared<ConditionalReturnType>(cond);
            }
        }

        static std::shared_ptr<ConditionalReturnType> greaterThan(ArithmeticParameterType params)
        {
            if(params.listOperands.size() != 0) error("GreaterThan not possible with list arguments!");
            if(params.numberOperands.size() != 2) error("GreaterThan must be provided exactly 2 number arguments!");

            double op1 = params.numberOperands[0].get();
            double op2 = params.numberOperands[1].get();

            if(op1 > op2)
            {
                Conditional cond("T");
                return std::make_shared<ConditionalReturnType>(cond);
            }
            else
            {
                Conditional cond("()");
                return std::make_shared<ConditionalReturnType>(cond);
            }
        }

    private:
        static void error(std::string message)
        {
            return output::ErrorHandle::handleError("BooleanOperator", message);
        }

        static void debug(std::string message)
        {
            return output::Debug::debugLog("BooleanOperator", message);
        }
    };
}

#endif //LISP_INTERPRETER_BOOLEANOPERATORS_HPP
