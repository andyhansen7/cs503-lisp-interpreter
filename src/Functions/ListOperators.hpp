//
// Created by andyh on 2/4/22.
//

#ifndef LISP_INTERPRETER_LISTOPERATORS_HPP
#define LISP_INTERPRETER_LISTOPERATORS_HPP

// src
#include <Functions/FunctionTypes.hpp>

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
