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
    debug("Starting parse with " + text);
    std::string data = text;;
    const bool singlePair = hasSinglePair(data);

    // If no parenthesis, nothing to evaluate
    if(hasNoPairs(data))
    {
        debug("Nothing to evaluate!");
        return data;
    }

    // Single pair of parenthesis remaining, evaluate expression at face value and return
    if(singlePair)
    {
        debug("Single atom object, evaluating and returning...");
        return (evaluate(data)).data;
    }

    // Multiple pairs of parenthesis remaining, got to be a little smarter
    else
    {
        // Load parenthesis pairs
        auto parenthesisPairs = getAllParenthesisLocations(data);

        // Iterate through pairs and evaluate
        for(std::size_t index = 0; index < parenthesisPairs.pairs.size(); index++)
        {
            if(hasSinglePair(data))
            {
                return (evaluate(data)).data;
            }

            std::string substring = data.substr(parenthesisPairs.pairs.at(index).front, (parenthesisPairs.pairs.at(index).rear - parenthesisPairs.pairs.at(index).front + 1));
            debug("Current substring is " + substring);

            auto evaluated = evaluate(substring);
            if(evaluated.dataWasList)
            {
                debug("Substring is list! Moving onto next loop");
                continue;
            }

            debug("Evaluation returned " + evaluated.data);
            boost::replace_all(data, substring, evaluated.data);
            debug("Data is now " + data);
        }

        return "";
    }
}

EvaluationReturn Parser::evaluate(const std::string& data)
{
    debug("evaluate() called with " + data);

    // Replace outer parenthesis
    auto pair = getOutermostParenthesis(data);
    std::string cleaned = data.substr(pair.front, (pair.rear - pair.front + 1));

    debug("cleaned data to " + cleaned);

    // Check that param is not list
    if(List::isList(data))
    {
        return {.data = data, .dataWasList = true};
    }

    // Split into components
    auto ops = getOperatorOperands(cleaned);

    // Evaluate user variables, if there are any
    ops.operands = evaluateUserVars(ops.operands);

    // Run operation
    if(arithmeticFunctions.find(ops.operation) != arithmeticFunctions.end())
    {
        debug("Found arithmetic operator " + ops.operation);

        // Cast string objects to their respective types
        auto parameters = getArithmeticParameterType(ops);

        auto result = arithmeticFunctions.at(ops.operation)(parameters);
        return {.data = result->str(), .dataWasList = false};
    }

    else if(booleanFunctions.find(ops.operation) != booleanFunctions.end())
    {
        debug("Found boolean operator " + ops.operation);

        // Cast string objects to their respective types
        auto parameters = getArithmeticParameterType(ops);

        auto result = booleanFunctions.at(ops.operation)(parameters);
        return {.data = result->str(), .dataWasList = false};
    }

    else if(conditionalFunctions.find(ops.operation) != conditionalFunctions.end())
    {
        debug("Found conditional operator " + ops.operation);

        // Cast string objects to condition and expressions
        auto parameters = getConditionalParameterType(ops);

        auto result = conditionalFunctions.at(ops.operation)(parameters);
        return {.data = result->str(), .dataWasList = false};
    }

    else if(printFunctions.find(ops.operation) != printFunctions.end())
    {
        debug("Found print operator " + ops.operation);

        if(ops.operands.size() > 1)
        {
            error("Print can only handle a single argument!");
            return {.data = "", .dataWasList = false};
        }
        else if(ops.operands.size() < 1)
        {
            error("Print called without any arguments!");
            return {.data = "", .dataWasList = false};
        }

        // Create single object to be printed
        std::shared_ptr<IBasicType> basicType;
        if(Number::isNumber(ops.operands[0]))
        {
            basicType = std::make_shared<Number>(ops.operands[0]);
        }
        else if(List::isList(ops.operands[0]))
        {
            basicType = std::make_shared<List>(ops.operands[0]);
        }
        else if(Conditional::isConditional(ops.operands[0]))
        {
            basicType = std::make_shared<Conditional>(ops.operands[0]);
        }
        else
        {
            error("Could not parse print argument into any basic type");
            return {.data = "", .dataWasList = false};
        }

        auto result = printFunctions.at(ops.operation)(basicType);
        return {.data = result->str(), .dataWasList = false};
    }

    else
    {
        error(boost::str(boost::format("Invalid operation provided in input: %1%") % data));
        return {.data = "", .dataWasList = false};
    }
}

OperatorOperands Parser::getOperatorOperands(const std::string& data)
{
    // Assure there are more than 2 arguments
    size_t spaceCount = std::count(data.begin(), data.end(), ' ');

    if(spaceCount < 1)
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

ArithmeticParameterType Parser::getArithmeticParameterType(const OperatorOperands& ops)
{
    ArithmeticParameterType params;

    for(const auto& it : ops.operands)
    {
        if(Number::isNumber(it))
        {
            params.numberOperands.push_back(Number(it));
        }
        else if(List::isList(it))
        {
            params.listOperands.push_back(List(it));
        }
        else
        {
            error("Can't cast argument to type Number or type List: " + it);
        }
    }

    return params;
}

ConditionalParameterType Parser::getConditionalParameterType(const OperatorOperands& ops)
{
    ConditionalParameterType params;

    if(ops.operands.size() < 3)
    {
        error("Conditional operator not given enough arguments!");
        return params;
    }
    else if(ops.operands.size() > 3)
    {
        error("Conditional operator given too many arguments!");
        return params;
    }
    else
    {
       if(Conditional::isConditional(ops.operands[0]))
       {
           params.condition = Conditional(ops.operands[0]);
       }
       params.trueExpression = ops.operands[1];
       params.falseExpression = ops.operands[2];

       return params;
    }
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
    output::ErrorHandle::handleError("Parser", message);
}

void Parser::debug(const std::string& message)
{
     output::Debug::debugLog("Parser", message);
}
