//
// Created by andyh on 1/31/22.
//

#include "LispParser.hpp"

// STL
#include <boost/algorithm/string/replace.hpp>
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
        debug(atom);
        std::string newData = data.replace(innerPair._front, (innerPair._rear - innerPair._front + 1), evaluateAtom(atom));
        debug(newData);
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

        // Run operation
        std::string result;
        if(_operations.find(ops._operation) != _operations.end())
            result = _operations.at(ops._operation)(ops._operands);
        else
            throw std::runtime_error("[ERROR] Invalid operation provided in input: " + data);

        return result;
    }
    // Error case
    else
    {
        throw std::runtime_error("[ERROR] Invalid number of parenthesis provided in input: " + data);
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
    auto firstOperand = 0.0f;
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
    auto firstOperand = 0.0f;
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
    auto firstOperand = 0.0f;
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
    // Assure there are exactly 2 arguments
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

void LispParser::debug(std::string message)
{
    #ifdef __DEBUG
        std::cout << "[PARSER] Debug: " << message << std::endl;
    #endif
}
