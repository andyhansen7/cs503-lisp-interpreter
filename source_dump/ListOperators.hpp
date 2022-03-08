//
// Created by andyh on 2/4/22.
//

#ifndef LISP_INTERPRETER_LISTOPERATORS_HPP
#define LISP_INTERPRETER_LISTOPERATORS_HPP

// src
#include "FunctionTypes.hpp"

// STL
#include <string>
#include <memory>

namespace functions
{
    class ListOperations
    {
    public:
        static std::shared_ptr<ListReturnType> cons(ArithmeticParameterType params)
        {
            std::size_t numOperands = params.numberOperands.size() + params.listOperands.size();
            if(numOperands < 2) error("Cons not possible without at least 2 number or list arguments!");
            if(numOperands > 2) error("Cons not possible with more than 2 number or list arguments!");

            List newList;
            for(auto it : params.numberOperands)
            {
                newList.push(Number(it));
            }
            for(auto it : params.listOperands)
            {
                newList.push(List(it));
            }

            return std::make_shared<ListReturnType>(newList);
        }

        static std::shared_ptr<IReturnType> car(ArithmeticParameterType params)
        {
            if(params.listOperands.size() < 1) error("Car not possible without a list argument!");
            if(params.listOperands.size() > 1) error("Car not possible with more than 1 list argument!");
            if(params.numberOperands.size() > 1) error("Car not possible with number arguments!");

            auto originalList = params.listOperands[0];
            std::string carItem = originalList.car();

            if(List::isList(carItem, {}, {}))
            {
                return std::make_shared<ListReturnType>(List(carItem));
            }
            else if(Number::isNumber(carItem))
            {
                return std::make_shared<NumberReturnType>(Number(carItem));
            }
            else
            {
                error("Can't cast string \'" + carItem + "\' to either Number or List!");
                return std::make_shared<NumberReturnType>(Number(0));
            }
        }

        static std::shared_ptr<IReturnType> cdr(ArithmeticParameterType params)
        {
            if(params.listOperands.size() < 1) error("Cdr not possible without a list argument!");
            if(params.listOperands.size() > 1) error("Cdr not possible with more than 1 list argument!");
            if(params.numberOperands.size() > 1) error("Cdr not possible with number arguments!");

            auto originalList = params.listOperands[0];
            std::string cdrItem = originalList.cdr();

            if(List::isList(cdrItem, {}, {}))
            {
                return std::make_shared<ListReturnType>(List(cdrItem));
            }
            else if(Number::isNumber(cdrItem))
            {
                return std::make_shared<NumberReturnType>(Number(cdrItem));
            }
            else
            {
                error("Can't cast string \'" + cdrItem + "\' to either Number or List!");
                return std::make_shared<NumberReturnType>(Number(0));
            }
        }

    private:
        static void error(std::string message)
        {
            return output::ErrorHandle::handleError("ListOperator", message);
        }

        static void debug(std::string message)
        {
            return output::Debug::debugLog("ListOperator", message);
        }
    };
}

#endif //LISP_INTERPRETER_LISTOPERATORS_HPP
