//
// Created by andyh on 2/3/22.
//

#include "Parser.hpp"

using namespace parsers;
using namespace functions;
using namespace basic_types;

Parser::Parser()
{

}

std::string Parser::parse(const std::string& text)
{
    std::string data = text;
    auto outerPair = getOutermostParenthesis(data);
    auto innerPair = getInnermostParenthesis(data);
    const bool singlePair = (outerPair._front == innerPair._front && outerPair._rear == innerPair._rear);

    // If no parenthesis, nothing to evaluate
    if(outerPair._front == std::string::npos && outerPair._rear == std::string::npos)
    {
        return data;
    }

    // Single pair of parenthesis remaining, evaluate expression at face value and return
    if(singlePair)
    {
        if(List::isList(data))
        {
            return data;
        }
        else
        {
            return evaluate(data);
        }
    }

    // Multiple pairs of parenthesis remaining, got to be a little smarter
    else
    {
        // Load parenthesis pairs
        auto parenthesisPairs = getAllParenthesisLocations(data);

        // Iterate through pairs and evaluate
        for(std::size_t index = 0; index < parenthesisPairs._pairs.size(); index++)
        {
            std::string substring = data.substr(parenthesisPairs._pairs.at(index)._front, (parenthesisPairs._pairs.at(index)._rear - parenthesisPairs._pairs.at(index)._front + 1));

            if(List::isList(substring))
            {
                continue;
            }
            else
            {
                std::string evaluated = evaluate(substring);
                data.replace(parenthesisPairs._pairs.at(index)._front, (parenthesisPairs._pairs.at(index)._rear - parenthesisPairs._pairs.at(index)._front + 1), evaluated);
                return parse(data);
            }

        }

        return "";
    }
}

std::string Parser::evaluate(const std::string& data)
{
    // Replace outer parenthesis
    auto pair = getOutermostParenthesis(data);
    std::string cleaned = data.substr(pair._front, (pair._rear - pair._front));

    // Split into components
    auto ops = getOperatorOperands(cleaned);

    // Evaluate user variables, if there are any
    ops.operands = evaluateUserVars(ops.operands);

    // Cast string objects to their respective types
    auto parameters = getOperatorParameters(ops);

    // Run operation
    std::string result;
    if(arithmeticFunctions.find(ops.operation) != arithmeticFunctions.end())
    {
        auto result = arithmeticFunctions.at(parameters.operation)(parameters.params);
        return result->str();
    }

    else
    {
        error(boost::str(boost::format("Invalid operation provided in input: %1%") % data));
        return "";
    }
}

OperatorOperands Parser::getOperatorOperands(const std::string& data)
{
    // Assure there are more than 2 arguments
    size_t spaceCount = std::count(data.begin(), data.end(), ' ');

    if(spaceCount < 2)
    {
        error("Not enough spaces in input: " + data);
        return {};
    }
    else
    {
        OperatorOperands ops;
        std::string inputText = data;
        const std::string delim = " ";
        std::size_t pos = 0;
        bool operationSet = false;

        // Remove initial and end parenthesis
        boost::replace_first(inputText, "(", "");
        boost::replace_last(inputText, ")", "");

        while((pos = inputText.find(delim)) != std::string::npos)
        {
            // Set operation if not yet set
            if(!operationSet)
            {
                ops.operation = inputText.substr(0, pos);
                inputText.erase(0, pos + delim.length());
                operationSet = true;
            }
            else
            {
                ops.operands.push_back(inputText.substr(0, pos));
                inputText.erase(0, pos + delim.length());
            }
        }

        // Grab the last bit
        ops.operands.push_back(inputText);

        return ops;
    }
}

OperatorParameters Parser::getOperatorParameters(OperatorOperands ops)
{
    OperatorParameters params;
    params.operation = ops.operation;

    for(auto& it : ops.operands)
    {
        if(List::isList(it))
        {
            params.params.listOperands.push_back(List(it));
        }
        else if(Number::isNumber(it))
        {
            params.params.numberOperands.push_back(Number(it));
        }
        else
        {
            error("Can't cast argument to type Number or type List: " + it);
        }
    }

    return params;
}

std::vector<std::string> Parser::evaluateUserVars(std::vector<std::string> operands)
{
    std::vector<std::string> evaluated = operands;

    for(auto& it : evaluated)
    {
        if(_userVariables.find(it) != _userVariables.end())
        {
            // Evaluate variable and apply
            it = _userVariables.at(it)->str();
        }
    }

    return evaluated;
}

void Parser::error(const std::string& message)
{
    return error::ErrorHandle::handleError("Parser", message);
}