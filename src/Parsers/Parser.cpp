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

std::vector<std::string> Parser::parse(const std::string& text)
{
    debug("Starting parse with " + text);
    std::string data = text;
    const bool singlePair = hasSinglePair(data);
    std::size_t numberOfListOperands = 0;

    // If no parenthesis, nothing to evaluate
    if(hasNoPairs(data))
    {
        debug("Nothing to evaluate!");
        return { "\'" + data + "\'" };
    }

    // Begin routine call
    std::string beginTest = "";
    std::string whileTest = "";
    std::string defineTest = "";
    if(data.length() > 7)
    {
        defineTest = data.substr(1, 6);
    }
    else if(data.length() > 6)
    {
        beginTest = data.substr(1, 5);
        whileTest = data.substr(1, 5);
    }

    if(beginTest == "begin")
    {
        debug("Beginning recursive parse...");
        std::string copy = data;
        std::vector<std::string> expressions, returnStrings;

        while(true)
        {
            auto pairs = getAllParenthesisLocations(copy);
            std::reverse(pairs.pairs.begin(), pairs.pairs.end());

            if(pairs.pairs.size() < 2)
                break;
            else
            {
                std::string expression = copy.substr(pairs.pairs[1].front, (pairs.pairs[1].rear - pairs.pairs[1].front + 1));
                debug("Located expression " + expression);
                expressions.push_back(expression);
                copy.erase(pairs.pairs[1].front, (pairs.pairs[1].rear - pairs.pairs[1].front + 1));
                debug("Copy is now " + copy);
            }
        }

        for(const auto& s : expressions)
        {
            debug("Evaluating expression " + s);
            auto parsed = parse(s);
            for(const auto& t : parsed)
            {
                returnStrings.push_back(t);
            }
        }

        return returnStrings;
    }

    else if(whileTest == "while")
    {
        debug("Beginning while loop...");
        auto pairs = getAllParenthesisLocations(data);
        std::reverse(pairs.pairs.begin(), pairs.pairs.end());
        if(pairs.pairs.size() < 3)
        {
            error("Wrong number of arguments provided in while!");
        }

        // Extract condition and expression from argument
        std::string condition = data.substr(pairs.pairs[1].front, (pairs.pairs[1].rear - pairs.pairs[1].front + 1));
        std::string expression = data.substr(pairs.pairs[2].front, (pairs.pairs[2].rear - pairs.pairs[2].front + 1));
        std::vector<std::string> returnStrings;
        debug("Condition is " + condition + ", expression is " + expression);

        while(true)
        {
            // Run expression if condition is true
            auto conditionEval = evaluate(condition);
            if(conditionEval.data == "T")
            {
                auto parsed = parse(expression);
                for(const auto& s : parsed)
                {
                    returnStrings.push_back(s);
                }
            }
            else
                break;
        }

        return returnStrings;
    }

    else if(defineTest == "define")
    {
        debug("define called");
        std::string copy = data;

        // Load parenthesis pairs
        auto parenthesisPairs = getAllParenthesisLocations(copy);

        if(parenthesisPairs.pairs.size() != 3)
        {
            error("Define should contain arguments and expression enclosed by parenthesis!");
        }

        std::string functionName = "";
        std::string paramList = "";
        std::string expression = "";

        // Parse argument list and expression
        paramList = copy.substr(parenthesisPairs.pairs[1].front, (parenthesisPairs.pairs[1].rear - parenthesisPairs.pairs[1].front + 1));
        expression = copy.substr(parenthesisPairs.pairs[0].front, (parenthesisPairs.pairs[0].rear - parenthesisPairs.pairs[0].front + 1));
        boost::replace_first(copy, expression, "");
        boost::replace_first(copy, paramList, "");

        // Parse function name, this is the easiest way to do it
        auto ops = OperatorOperandsUtil::getOperatorOperands(copy);

        if(ops.operands.size() != 1)
        {
            error("Define given an inappropriate number of parameters!");
        }
        functionName = ops.operands[0];

        debug("Defining function\'" + functionName +"\' with params " + paramList + " and expression " + expression);

        if(_userFunctions.find(functionName) != _userFunctions.end())
        {
            error("Cannot define function " + functionName + ", it was already defined!");
        }
        else
        {
            // Separate args from string
            std::vector<std::string> params;
            auto p = OperatorOperandsUtil::getOperatorOperands(paramList);
            if(p.operation.length() != 0 && p.operation != " ")
                params.push_back(p.operation);
            for(const auto& s : p.operands)
            {
                debug("Adding parameter \'" + s + "\'");
                if(s.length() != 0 && s != " ")
                    params.push_back(s);
            }

            _userFunctions.emplace(functionName, FunctionDefinition({.params = params, .expression = expression}));
        }

        return { "OK" };
    }

    // Single pair of parenthesis remaining, evaluate expression at face value and return
    else if(singlePair)
    {
        debug("Single atom object, evaluating and returning...");
        std::string functionsEvaluated = evaluateUserFunctions(data);
        return { data, (evaluate(functionsEvaluated)).data };
    }

    // Multiple pairs of parenthesis remaining, got to be a little smarter
    else
    {
        // Load parenthesis pairs
        auto parenthesisPairs = getAllParenthesisLocations(data);

        // Iterate through pairs and evaluate
        for(std::size_t index = 0; index < parenthesisPairs.pairs.size(); index++)
        {
            if(parenthesisPairs.pairs.size() == (numberOfListOperands + 1))   // Add one for outer parentheses
            {
                debug("Down to single pair! Returning single evaluation...");
                return { data, (evaluate(data)).data };
            }

            std::string substring = data.substr(parenthesisPairs.pairs.at(index).front, (parenthesisPairs.pairs.at(index).rear - parenthesisPairs.pairs.at(index).front + 1));
            debug("Current substring is " + substring);

            auto functionsEvaluated = evaluateUserFunctions(substring);
            auto evaluated = evaluate(functionsEvaluated);
            if(evaluated.dataWasList)
            {
                debug("Substring is list! Moving onto next loop");
                numberOfListOperands++;
                continue;
            }

            debug("Evaluation returned " + evaluated.data);
            boost::replace_all(data, substring, evaluated.data);
            debug("Data is now " + data + ", calling parse...");
            return parse(data);
        }

        return { "" };
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
    if(List::isList(data, _userVariables, _userFunctions))
    {
        debug("Data was list! Returning " + cleaned);
        return {.data = data, .dataWasList = true};
    }

    // Split into components
    auto ops = OperatorOperandsUtil::getOperatorOperands(cleaned);

    // Run operation
    if(ops.operation == "set" || ops.operation == "setq")
    {
        debug("Parsing operation " + ops.operation);

        if(ops.operands.size() != 2)
        {
            error("Set cannot take more than 2 inputs, a var name and a value: " + data);
            return {.data = "", .dataWasList = false};
        }

        std::string var = ops.operands[0];
        std::string val = ops.operands[1];
        std::shared_ptr<IBasicType> valType;

        if(Conditional::isConditional(val))
        {
            valType = std::make_shared<Number>(val);
        }
        else if(Number::isNumber(val))
        {
            valType = std::make_shared<Number>(val);
        }
        else if(List::isList(val, _userVariables, _userFunctions))
        {
            valType = std::make_shared<List>(val);
        }
        else
        {
            error("Cannot parse List, Number or Conditional from data: " + val);
        }

        // Set value
        if(_userVariables.find(var) != _userVariables.end())
        {
            // Remove existing var
            _userVariables.erase(_userVariables.find(var));
        }
        _userVariables.emplace(var, valType);

        return {.data = "OK", .dataWasList = false};
    }

    // Evaluate user variables, if there are any
    ops.operands = evaluateUserVars(ops.operands);

    if(arithmeticFunctions.find(ops.operation) != arithmeticFunctions.end())
    {
        debug("Found arithmetic operator " + ops.operation);

        // Cast string objects to their respective types
        auto parameters = getArithmeticParameterType(ops);

        auto result = arithmeticFunctions.at(ops.operation)(parameters);
        return {.data = result->str(), .dataWasList = false};
    }

    else if(listFunctions.find(ops.operation) != listFunctions.end())
    {
        debug("Found list operator " + ops.operation);

        // Cast string objects to their respective types
        auto parameters = getArithmeticParameterType(ops);

        for(auto it : parameters.numberOperands)
        {
            debug(it.str());
        }
        for(auto it : parameters.listOperands)
        {
            debug(it.str());
        }

        auto result = listFunctions.at(ops.operation)(parameters);
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
        if(Conditional::isConditional(ops.operands[0]))
        {
            basicType = std::make_shared<Conditional>(ops.operands[0]);
        }
        if(Number::isNumber(ops.operands[0]))
        {
            basicType = std::make_shared<Number>(ops.operands[0]);
        }
        else if(List::isList(ops.operands[0], _userVariables, _userFunctions))
        {
            basicType = std::make_shared<List>(ops.operands[0]);
        }
        else
        {
            error("Could not parse print argument into any basic type");
            return {.data = "", .dataWasList = false};
        }

        auto result = printFunctions.at(ops.operation)(basicType);
        return {.data = result->str(), .dataWasList = false};
    }

    else if(typeFunctions.find(ops.operation) != typeFunctions.end())
    {
        debug("Found type operator " + ops.operation);

        auto result = typeFunctions.at(ops.operation)(ops);
        return {.data = result->str(), .dataWasList = false};
    }

    else
    {
        error(boost::str(boost::format("Invalid operation provided in input: %1%") % data));
        return {.data = "", .dataWasList = false};
    }
}

ArithmeticParameterType Parser::getArithmeticParameterType(const OperatorOperands& ops)
{
    ArithmeticParameterType params;

    for(const auto& it : ops.operands)
    {
        if(it.length() < 1) // Discount any empty values
        {
            continue;
        }
        if(Number::isNumber(it))
        {
            debug("Adding type Number to return list with value " + it);
            params.numberOperands.push_back(Number(it));
        }
        else if(List::isList(it, _userVariables, _userFunctions))
        {
            debug("Adding type List to return list with value " + it);
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
            debug("Applying user var with value " + it + " to " + _userVariables.at(it)->str());
            it = _userVariables.at(it)->str();
        }
    }

    return evaluated;
}

std::string Parser::evaluateUserFunctions(const std::string& expression)
{
    // Parse operator and operands from expression
    auto ops = OperatorOperandsUtil::getOperatorOperands(expression);

    if(_userFunctions.find(ops.operation) != _userFunctions.end())
    {
        // Call function and return result as string
        FunctionDefinition fun = _userFunctions.at(ops.operation);
        std::string exp = fun.expression;

        if(ops.operands.size() != fun.params.size())
        {
            debug("About to error!");
            std::string funParams = "", givenParams = "";
            for(const auto& it : ops.operands) { givenParams += it; givenParams += " "; }
            for(const auto& it : fun.params) { funParams += it; funParams += " "; }
            givenParams += ", "; givenParams += std::to_string(ops.operands.size());
            funParams += ", "; funParams += std::to_string(fun.params.size());
            debug("Params for function: " + funParams);
            debug("Params given: " + givenParams);

            error("Function call to " + ops.operation + " provided the wrong number of arguments!");
            return "";
        }
        else
        {
            debug("Expression before evaluation: " + exp);
            for(std::size_t i = 0; i < ops.operands.size(); i++)
            {
                boost::replace_all(exp, fun.params[i], ops.operands[i]);
            }
            debug("Expression after evaluation: " + exp);

            return exp;
        }
    }
    else
    {
        // Return original data
        return expression;
    }
}

void Parser::error(const std::string& message)
{
    output::ErrorHandle::handleError("Parser", message);
}

void Parser::debug(const std::string& message)
{
     output::Debug::debugLog("Parser", message);
}
