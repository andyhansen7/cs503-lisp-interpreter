//
// Created by andyh on 2/7/22.
//

#ifndef LISP_INTERPRETER_TYPEOPERATORS_HPP
#define LISP_INTERPRETER_TYPEOPERATORS_HPP

// src
#include <Functions/FunctionTypes.hpp>
#include <Parsers/OperatorOperands.hpp>
#include <Functions/Functions.hpp>

// STL
#include <string>
#include <memory>

using namespace parsers;

namespace functions
{

    class TypeOperations
    {
    public:
        static std::shared_ptr<ConditionalReturnType> isNumber(OperatorOperands ops)
        {
            if(ops.operands.size() != 1) error("isNumber can only test one argument!");

            if(Number::isNumber(ops.operands[0]))
                return std::make_shared<ConditionalReturnType>(ConditionalReturnType(Conditional("T")));
            else
                return std::make_shared<ConditionalReturnType>(ConditionalReturnType(Conditional("()")));
        }

        static std::shared_ptr<ConditionalReturnType> isList(OperatorOperands ops)
        {
            if(ops.operands.size() != 1) error("isList can only test one argument!");

            if(List::isList(ops.operands[0], {}, {}))
                return std::make_shared<ConditionalReturnType>(ConditionalReturnType(Conditional("T")));
            else
                return std::make_shared<ConditionalReturnType>(ConditionalReturnType(Conditional("()")));
        }

        static std::shared_ptr<ConditionalReturnType> isNull(OperatorOperands ops)
        {
            if(ops.operands.size() != 1) error("isNull can only test one argument!");

            if(Conditional::isConditional(ops.operands[0]))
            {
                if(Conditional(ops.operands[0]).isNull())
                    return std::make_shared<ConditionalReturnType>(ConditionalReturnType(Conditional("T")));
                else
                    return std::make_shared<ConditionalReturnType>(ConditionalReturnType(Conditional("()")));
            }
            else if(Number::isNumber(ops.operands[0]))
            {
                if(Number(ops.operands[0]).isNull())
                    return std::make_shared<ConditionalReturnType>(ConditionalReturnType(Conditional("T")));
                else
                    return std::make_shared<ConditionalReturnType>(ConditionalReturnType(Conditional("()")));
            }
            else if(List::isList(ops.operands[0], {}, {}))
            {
                if(List(ops.operands[0]).isNull())
                    return std::make_shared<ConditionalReturnType>(ConditionalReturnType(Conditional("T")));
                else
                    return std::make_shared<ConditionalReturnType>(ConditionalReturnType(Conditional("()")));
            }
            else
            {
                error("isNull couldn't convert data to List, Number or Conditional: " + ops.operands[0]);
                return std::make_shared<ConditionalReturnType>(ConditionalReturnType(Conditional("()")));
            }
        }

        static std::shared_ptr<ConditionalReturnType> isReserved(OperatorOperands ops)
        {
            if(ops.operands.size() != 1) error("isReserved can only test one argument!");
            std::string data = ops.operands[0];
            bool isReserved = false;

            isReserved |= (data == "+");
            isReserved |= (data == "-");
            isReserved |= (data == "*");
            isReserved |= (data == "/");
            isReserved |= (data == "cons");
            isReserved |= (data == "car");
            isReserved |= (data == "cdr");
            isReserved |= (data == "<");
            isReserved |= (data == "=");
            isReserved |= (data == ">");
            isReserved |= (data == "if");
            isReserved |= (data == "print");
            isReserved |= (data == "number?");
            isReserved |= (data == "list?");
            isReserved |= (data == "null?");
            isReserved |= (data == "symbol?");
            isReserved |= (data == "while");
            isReserved |= (data == "begin");
            isReserved |= (data == "define");

            return std::make_shared<ConditionalReturnType>(ConditionalReturnType(Conditional((isReserved ? "T" : "()"))));
        }

    private:
        static void error(std::string message)
        {
            return output::ErrorHandle::handleError("TypeOperator", message);
        }

        static void debug(std::string message)
        {
            return output::Debug::debugLog("TypeOperator", message);
        }
    };
}

#endif //LISP_INTERPRETER_TYPEOPERATORS_HPP
