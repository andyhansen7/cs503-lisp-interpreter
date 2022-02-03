//
// Created by andyh on 1/31/22.
//

#include "LispParser.hpp"

// STL
#include <boost/algorithm/string/replace.hpp>
#include <boost/format.hpp>
#include <iostream>

#define __DEBUG

using namespace parsers;

LispParser::LispParser()
    : _atomOperations({
        { "+", addImplementation},
        { "-", subtractImplementation},
        { "*", multiplyImplementation},
        { "/", divideImplementation},
        {">", greaterThanImplementation},
        {"=", equalToImplementation},
        {"<", lessThanImplementation}
    }),
    _listOperations({
        {"cons", consImplentation}
    })
{

}

std::string LispParser::parseCommand(std::string data)
//{
//    auto outerPair = getOutermostParenthesis(data);
//    auto innerPair = getInnermostParenthesis(data);
//    const bool singlePair = (outerPair._front == innerPair._front && outerPair._rear == innerPair._rear);
//
//    // If no parenthesis, nothing to evaluate
//    if(outerPair._front == std::string::npos && outerPair._rear == std::string::npos)
//    {
//        return data;
//    }
//
//    // If only single pair remaining, evaluate and return
//    else if(singlePair)
//    {
//        return evaluateAtom(data);
//    }
//    // Evaluate inner parenthesis and recurse
//    else
//    {
//        auto currentPairToBeEvaluated = innerPair;
//
//        // Get the current atom to work on and replace its value into the data string
//        std::string atom = data.substr(innerPair._front, (innerPair._rear - innerPair._front + 1));
//        std::string evaluatedAtom = evaluateAtom(atom);
//        std::string newData = "";
//        debugLog(boost::str(boost::format("Current atom is: %1%") % atom));
//        debugLog(boost::str(boost::format("After evaluation: %1%") % evaluatedAtom));
//
//        // True if atom is in most basic form, or a list
//        if(atom == evaluatedAtom)
//        {
//            if(isList(atom))
//            {
//                // Find second pair of parentheses and recurse
//            }
//        }
//        else
//        {
//            std::string newData = data.replace(innerPair._front, (innerPair._rear - innerPair._front + 1), evaluatedAtom);
//        }
//
//        return parseCommand(newData);
//    }
//}
//
//std::string LispParser::evaluateAtom(std::string data)
//{
//    auto pair = getOutermostParenthesis(data);
//
//    // No evaluation to be done if no parenthesis or list
//    if(pair._front == std::string::npos && pair._rear == std::string::npos)
//    {
//        return data;
//    }
//
//    // Has parenthesis
//    else if(pair._front != std::string::npos && pair._rear != std::string::npos)
//    {
//        // Replace with implementation
//        std::string substring = data.substr(pair._front, (pair._rear - pair._front));
//
//        // Split into components
//        auto ops = getOperatorOperands(substring);
//
//        // Evaluate user variables, if there are any
//        std::vector<std::string> parsedOperands = evaluateUserVars(ops._operands);
//
//        // Run operation
//        std::string result;
//        if(_atomOperations.find(ops._operation) != _atomOperations.end())
//        {
//            result = _atomOperations.at(ops._operation)(parsedOperands);
//            return result;
//        }
//
//        // setq implementation
//        else if(ops._operation == "setq" || ops._operation == "set")
//        {
//            return setqImplementation(parsedOperands);
//        }
//
//        // if then implementation
//        else if(ops._operation == "if")
//        {
//            return ifImplementation(parsedOperands);
//        }
//
//        else
//        {
//            errorLog(boost::str(boost::format("Invalid operation provided in input: %1%") % data));
//            return "";
//        }
//    }
//    // Error case
//    else
//    {
//        errorLog(boost::str(boost::format("Invalid number of parenthesis provided in input: %1%")  % data));
//        return "";
//    }
//}
{
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
        if(isList(data))
            return data;
        else
            return evaluateAtom(data);
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

            // Evaluate list as a list instead of as an atom
            if(isList(substring))
            {
                std::string evaluatedListOperation = evaluateList(data.substr(parenthesisPairs._pairs.at(index + 1)._front, (parenthesisPairs._pairs.at(index + 1)._rear - parenthesisPairs._pairs.at(index + 1)._front + 1)));
                data.replace(parenthesisPairs._pairs.at(index + 1)._front, (parenthesisPairs._pairs.at(index + 1)._rear - parenthesisPairs._pairs.at(index + 1)._front + 1), evaluatedListOperation);
                return parseCommand(data);
            }
            else
            {
                std::string evaluated = evaluateAtom(substring);
                data.replace(parenthesisPairs._pairs.at(index)._front, (parenthesisPairs._pairs.at(index)._rear - parenthesisPairs._pairs.at(index)._front + 1), evaluated);
                return parseCommand(data);
            }
        }

        return "";
    }
}

std::string LispParser::evaluateAtom(std::string data)
{
    // Replace outer parenthesis
    auto pair = getOutermostParenthesis(data);
    std::string cleaned = data.substr(pair._front, (pair._rear - pair._front));

    // Split into components
    auto ops = getOperatorOperands(cleaned);

    // Evaluate user variables, if there are any
    std::vector<std::string> parsedOperands = evaluateUserVars(ops._operands);

    // Run operation
    std::string result;
    if(_atomOperations.find(ops._operation) != _atomOperations.end())
    {
        result = _atomOperations.at(ops._operation)(parsedOperands);
        return result;
    }

    // setq implementation
    else if(ops._operation == "setq" || ops._operation == "set")
    {
        return setqImplementation(parsedOperands);
    }

    // if then implementation
    else if(ops._operation == "if")
    {
        return ifImplementation(parsedOperands);
    }

    else
    {
        errorLog(boost::str(boost::format("Invalid operation provided in input: %1%") % data));
        return "";
    }
}

std::string LispParser::evaluateList(std::string data)
{
    // Replace outer parenthesis
    auto pair = getOutermostParenthesis(data);
    std::string cleaned = data.substr(pair._front, (pair._rear - pair._front));

    // Split into components
    auto ops = getOperatorOperands(cleaned);

    // Evaluate user variables, if there are any
    std::vector<std::string> parsedOperands = evaluateUserVars(ops._operands);

    // Run operation
    std::string result;
    if(_listOperations.find(ops._operation) != _listOperations.end())
    {
        result = _atomOperations.at(ops._operation)(parsedOperands);
        return result;
    }

    else
    {
        errorLog(boost::str(boost::format("Invalid operation provided in input: %1%") % data));
        return "";
    }
}

std::string LispParser::addImplementation(std::vector<std::string> operands)
{
    bool resultIsInt = allOperandsAreIntegers(operands);
    float ret = 0.0f;
    bool firstSet = false;

    for(const auto& it : operands)
    {
        if(!firstSet)
        {
            ret = std::stof(it);
            firstSet = true;
        }
        else
        {
            auto converted = std::stof(it);
            ret += converted;
        }
    }

    if(resultIsInt)
        return std::to_string(static_cast<int>(ret));
    else
        return std::to_string(ret);
}

std::string LispParser::subtractImplementation(std::vector<std::string> operands)
{
    bool resultIsInt = allOperandsAreIntegers(operands);
    float ret = 0.0f;
    bool firstSet = false;

    for(const auto& it : operands)
    {
        if(!firstSet)
        {
            ret = std::stof(it);
            firstSet = true;
        }
        else
        {
            auto converted = std::stof(it);
            ret -= converted;
        }
    }

    if(resultIsInt)
        return std::to_string(static_cast<int>(ret));
    else
        return std::to_string(ret);
}

std::string LispParser::multiplyImplementation(std::vector<std::string> operands)
{
    bool resultIsInt = allOperandsAreIntegers(operands);
    float ret = 0.0f;
    bool firstSet = false;

    for(const auto& it : operands)
    {
        if(!firstSet)
        {
            ret = std::stof(it);
            firstSet = true;
        }
        else
        {
            auto converted = std::stof(it);
            ret *= converted;
        }
    }

    if(resultIsInt)
        return std::to_string(static_cast<int>(ret));
    else
        return std::to_string(ret);
}

std::string LispParser::divideImplementation(std::vector<std::string> operands)
{
    bool resultIsInt = allOperandsAreIntegers(operands);
    float ret = 0.0f;
    bool firstSet = false;

    for(const auto& it : operands)
    {
        if(!firstSet)
        {
            ret = std::stof(it);
            firstSet = true;
        }
        else
        {
            auto converted = std::stof(it);
            ret /= converted;
        }
    }

    if(resultIsInt)
        return std::to_string(static_cast<int>(ret));
    else
        return std::to_string(ret);
}

std::string LispParser::greaterThanImplementation(std::vector<std::string> operands)
{
    bool conditionTrue = true;
    float firstOperand = 0.0f;
    bool firstSet = false;

    for(const auto& it : operands)
    {
        if(!firstSet)
        {
            firstOperand = std::stof(it);
            firstSet = true;
        }
        else
        {
            auto converted = std::stof(it);
            conditionTrue &= (firstOperand > converted) ;
        }
    }

    return conditionTrue ? "T" : "NIL";
}

std::string LispParser::equalToImplementation(std::vector<std::string> operands)
{
    bool conditionTrue = true;
    float firstOperand = 0.0f;
    bool firstSet = false;

    for(const auto& it : operands)
    {
        if(!firstSet)
        {
            firstOperand = std::stof(it);
            firstSet = true;
        }
        else
        {
            auto converted = std::stof(it);
            conditionTrue &= (firstOperand == converted) ;
        }
    }

    return conditionTrue ? "T" : "NIL";
}

std::string LispParser::lessThanImplementation(std::vector<std::string> operands)
{
    bool conditionTrue = true;
    float firstOperand = 0.0f;
    bool firstSet = false;

    for(const auto& it : operands)
    {
        if(!firstSet)
        {
            firstOperand = std::stof(it);
            firstSet = true;
        }
        else
        {
            auto converted = std::stof(it);
            conditionTrue &= (firstOperand < converted) ;
        }
    }

    return conditionTrue ? "T" : "NIL";
}

std::string LispParser::ifImplementation(std::vector<std::string> operands)
{
    if(operands.size() != 3)
    {
        errorLog("Function \'if\' called with the wrong number of arguments");
        return "";
    }
    else
    {
        // Separate condition and true or false expressions
        std::string condition = parseCommand(operands[0]);
        std::string trueCondition = operands[1];
        std::string falseCondition = operands[2];

        if(condition == "T")
        {
            return parseCommand(trueCondition);
        }
        else if(condition == "NIL")
        {
            return parseCommand(falseCondition);
        }
        else
        {
            errorLog("Function \'if\' called with condition not returning \'T\' or \'NIL\': " + operands[0]);
            return "";
        }
    }
}

std::string LispParser::consImplentation(std::vector<std::string> operands)
{
    if(operands.size() != 2)
    {
        errorLog("Function \'cons\' called with the wrong number of arguments");
        return "";
    }
    else
    {
        return boost::str(boost::format("(%1% %2%)") % operands[0] % operands[1]);
    }
}

std::string LispParser::setqImplementation(std::vector<std::string> operands)
{
    if(operands.size() % 2 != 0)
    {
        errorLog("Function \'setq\' called with odd number of arguments");
        return "";
    }
    else
    {
        size_t index = 0;

        while(index < operands.size())
        {
            // Isolate variable and value
            std::string varName = operands[index];
            std::string value = operands[index + 1];

            // Make sure that user isn't inserting a reserved word
            if(_atomOperations.find(varName) != _atomOperations.end())
            {
                errorLog(boost::str(boost::format("Function \'setq\' called with reserved keyword \'%1%\'") % varName));
                return "";
            }

            // Place into map
            if(_userVariables.find(varName) != _userVariables.end())
            {
                _userVariables.at(varName) = value;
            }
            else
            {
                _userVariables.emplace(varName, value);
            }

            // Increase index
            index += 2;
        }

        return "OK";
    }
}

ParenthesisLocations LispParser::getOutermostParenthesis(std::string data)
{
    std::size_t frontIndex = data.find_first_of("(");
    std::size_t rearIndex = data.find_last_of(")");

    return {._front = frontIndex, ._rear = rearIndex};
}

ParenthesisLocations LispParser::getInnermostParenthesis(std::string data)
{
    std::size_t frontIndex = data.find_last_of("(");
    std::size_t rearIndex = data.find_first_of(")", frontIndex);

    return {._front = frontIndex, ._rear = rearIndex};
}

AllParenthesisLocations LispParser::getAllParenthesisLocations(std::string data)
{
    std::vector<std::size_t> openings = {};
    AllParenthesisLocations ret;
    std::string dataCopy = data;

    // Get all relevant indices
    for(std::size_t i = 0; i <= dataCopy.size(); i++)
    {
        if(dataCopy[i] == '(')
        {
            openings.push_back(i);
        }
    }
    std::reverse(openings.begin(), openings.end());

    size_t numberOfPairs = openings.size();
    for(std::size_t i = 0; i < numberOfPairs; i++)
    {
        ParenthesisLocations pair = {._front = 99, ._rear = 99};
        pair._front = openings.at(i);
        pair._rear = dataCopy.find_first_of(")", pair._front);
        dataCopy[pair._rear] = '*';
        ret._pairs.push_back(pair);
    }

    return orderParenthesisLocations(ret);
}

AllParenthesisLocations LispParser::orderParenthesisLocations(AllParenthesisLocations locations)
{
    std::vector<ParenthesisLocations> locationsCopy = locations._pairs;

    std::sort(locationsCopy.begin(), locationsCopy.end(), compareLocations);

    return {._pairs = locationsCopy};
}

bool LispParser::compareLocations(const ParenthesisLocations& a, const ParenthesisLocations& b)
{
    return a._front > b._front;
}

bool LispParser::isInteger(std::string str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

bool LispParser::isList(std::string str)
{
    auto ops = getOperatorOperands(str);

    return !str.empty() &&
            (_atomOperations.find(ops._operation) == _atomOperations.end()) &&
            ops._operation != "set" &&
            ops._operation != "setq" &&
            ops._operation != "if";
}

bool LispParser::allOperandsAreIntegers(std::vector<std::string> operands)
{
    bool ret = true;

    for(const auto& it : operands)
    {
        ret &= isInteger(it);
    }

    return ret;
}

bool LispParser::allOperandsAreLists(std::vector<std::string> operands)
{
    bool ret = true;

    for(const auto& it : operands)
    {
        ret &= isList(it);
    }

    return ret;
}


OperatorOperands LispParser::getOperatorOperands(std::string data)
{
    // Assure there are more than 2 arguments
    size_t spaceCount = std::count(data.begin(), data.end(), ' ');

    if(spaceCount < 2)
    {
        errorLog("Not enough spaces in input: " + data);
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
                ops._operation = inputText.substr(0, pos);
                inputText.erase(0, pos + delim.length());
                operationSet = true;
            }
            else
            {
                ops._operands.push_back(inputText.substr(0, pos));
                inputText.erase(0, pos + delim.length());
            }
        }

        // Grab the last bit
        ops._operands.push_back(inputText);

        return ops;
    }
}

std::vector<std::string> LispParser::evaluateUserVars(std::vector<std::string> operands)
{
    std::vector<std::string> evaluated = operands;

    for(auto& it : evaluated)
    {
        if(_userVariables.find(it) != _userVariables.end())
        {
            // Evaluate variable and apply
            std::string value = _userVariables.at(it);

            if(isInteger(value))
            {
                it = std::to_string(static_cast<int>(std::stof(value)));
            }
            else
            {
                it = std::to_string(std::stof(value));
            }
        }
    }

    return evaluated;
}

void LispParser::debugLog(std::string message)
{
    #ifdef __DEBUG
        std::cout << "[PARSER] Debug: " << message << std::endl;
    #endif
}

void LispParser::errorLog(std::string message)
{
    std::cout << "[PARSER] Error: " << message << std::endl;
    throw std::runtime_error(message);
}
