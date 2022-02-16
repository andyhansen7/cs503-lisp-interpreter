//
// Created by andyh on 2/15/22.
//

#ifndef LISP_INTERPRETER_TYPES_HPP
#define LISP_INTERPRETER_TYPES_HPP

namespace parsers
{
    typedef struct operator_operands
    {
        std::string operation;
        std::vector<std::string> operands;
    } OperatorOperands;

    typedef struct evaluation_return
    {
        std::string data = "";
        bool dataWasList = false;
    } EvaluationReturn;

    typedef struct function_definition
    {
        std::vector<std::string> params;
        std::string expression = "";
    } FunctionDefinition;
}

#endif //LISP_INTERPRETER_TYPES_HPP
