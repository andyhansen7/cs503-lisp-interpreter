//
// Created by andyh on 2/2/22.
//

#ifndef LISP_INTERPRETER_FUNCTIONTYPES_HPP
#define LISP_INTERPRETER_FUNCTIONTYPES_HPP

// src
#include <BasicTypes/List.hpp>
#include <BasicTypes/Number.hpp>
#include <BasicTypes/Conditional.hpp>
#include <BasicTypes/Null.hpp>

// STl
#include <vector>
#include <string>

namespace functions
{
    typedef struct arithmetic_parameter_type
    {
        std::vector<basic_types::Number> numberOperands;
        std::vector<basic_types::List> listOperands;
    } ArithmeticParameterType;

    typedef struct conditional_parameter_type
    {
        basic_types::Conditional condition;
        std::string trueExpression;
        std::string falseExpression;
    } ConditionalParameterType;

    class IReturnType
    {
    public:
        IReturnType() {}
        virtual std::string str() = 0;
    };

    class NumberReturnType : public IReturnType
    {
    public:
        NumberReturnType();
        NumberReturnType(basic_types::Number number) : number(number) {}
        basic_types::Number number;
        std::string str() override
        {
            return number.str();
        }
    };

    class ListReturnType : public IReturnType
    {
    public:
        ListReturnType();
        ListReturnType(basic_types::List list) : list(list) {}
        basic_types::List list;
        std::string str() override
        {
            return list.str();
        }
    };

    class ConditionalReturnType : public IReturnType
    {
    public:
        ConditionalReturnType();
        ConditionalReturnType(basic_types::Conditional conditional) : condition(conditional) {}
        basic_types::Conditional condition;
        std::string str() override
        {
            return condition.str();
        }
    };

    class StringReturnType : public IReturnType
    {
    public:
        StringReturnType();
        StringReturnType(std::string data) : data(data) {}
        std::string data;
        std::string str() override
        {
            return data;
        }
    };
}

#endif //LISP_INTERPRETER_FUNCTIONTYPES_HPP
