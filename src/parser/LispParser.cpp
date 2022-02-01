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
    : _operations({
        { "+", addImplementation},
        { "-", subtractImplementation},
        { "*", multiplyImplementation},
        { "/", divideImplementation},
        {">", greaterThanImplementation},
        {"=", equalToImplementation},
        {"<", lessThanImplementation}
    })
{

}

std::string LispParser::parseCommand(std::string data)
{
    auto outerPair = getOutermostParenthesis(data);
    auto innerPair = getInnermostParenthesis(data);
    const bool singlePair = (outerPair._front == innerPair._front && outerPair._rear == innerPair._rear);

    // If only single pair remaining, evaluate and return
    if(singlePair)
    {
        return evaluateAtom(data);
    }
    // Evaluate inner parenthesis and recurse
    else
    {
        std::string atom = data.substr(innerPair._front, (innerPair._rear - innerPair._front + 1));
        std::string newData = data.replace(innerPair._front, (innerPair._rear - innerPair._front + 1), evaluateAtom(atom));
        debugLog(boost::str(boost::format("Current atom is: %1%") % atom));
        debugLog(boost::str(boost::format("New data is: %1%") % newData));
        return parseCommand(newData);
    }
}

std::string LispParser::evaluateAtom(std::string data)
{
    auto pair = getOutermostParenthesis(data);

    // No evaluation to be done
    if(pair._front == std::string::npos && pair._rear == std::string::npos)
    {
        return data;
    }

    // Has parenthesis
    else if(pair._front != std::string::npos && pair._rear != std::string::npos)
    {
        // Replace with implementation
        std::string substring = data.substr(pair._front, (pair._rear - pair._front));

        // Remove parenthesis
        boost::replace_all(substring, "(", "");
        boost::replace_all(substring, ")", "");

        // Split into components
        auto ops = getOperatorOperands(substring);

        // Evaluate user variables, if there are any
        std::vector<std::string> parsedOperands = evaluateUserVars(ops._operands);

        // Run operation
        std::string result;
        if(_operations.find(ops._operation) != _operations.end())
        {
            result = _operations.at(ops._operation)(parsedOperands);
            return result;
        }
        // setq can't be static as it references members
        else if(ops._operation == "setq")
        {
            return setqImplementation(parsedOperands);
        }

        else
        {
            errorLog(boost::str(boost::format("Invalid operation provided in input: %1%") % data));
            return "";
        }
    }
    // Error case
    else
    {
        errorLog(boost::str(boost::format("Invalid number of parenthesis provided in input: %1%")  % data));
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

std::string LispParser::setqImplementation(std::vector<std::string> operands)
{
    if(operands.size() % 2 != 0)
    {
        errorLog("Function \'setq\' called with odd number of arguments");
        return "";
    }
    else
    {
        int index = 0;

        while(index < operands.size())
        {
            // Isolate variable and value
            std::string varName = operands[index];
            std::string value = operands[index + 1];

            // Make sure that user isn't inserting a reserved word
            if(_operations.find(varName) != _operations.end())
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

        return "";
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

bool LispParser::isInteger(std::string str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
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


OperatorOperands LispParser::getOperatorOperands(std::string data)
{
    // Assure there are more than 2 arguments
    size_t spaceCount = std::count(data.begin(), data.end(), ' ');

    if(spaceCount < 2)
    {
        throw std::runtime_error("[ERROR] Not enough spaces in input: " + data);
    }
    else
    {
        OperatorOperands ops;
        std::size_t index = data.find(" ");
        ops._operation = data.substr(0, index);
        std::string substring = data.substr(index + 1);

        index = substring.find(" ");
        while(index != std::string::npos && index < substring.length())
        {
            std::string operand = substring.substr(0, index);
            substring = substring.substr(index + 1);
            ops._operands.push_back(operand);
            index = data.find(" ");
        }
        ops._operands.push_back(substring);

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
