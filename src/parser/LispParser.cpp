//
// Created by andyh on 1/31/22.
//

#include "LispParser.hpp"

// STL
#include <boost/algorithm/string/replace.hpp>
#include <iostream>

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
            result = _operations.at(ops._operation)(ops._operands[0], ops._operands[1]);
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

std::string LispParser::addImplementation(std::string basicTypeA, std::string basicTypeB)
{
    bool resultIsInt = isInteger(basicTypeA) && isInteger(basicTypeB);

    auto aConverted = std::stof(basicTypeA);
    auto bConverted = std::stof(basicTypeB);

    if(resultIsInt)
        return std::to_string(static_cast<int>(aConverted + bConverted));
    else
        return std::to_string(aConverted + bConverted);
}

std::string LispParser::subtractImplementation(std::string basicTypeA, std::string basicTypeB)
{
    bool resultIsInt = isInteger(basicTypeA) && isInteger(basicTypeB);

    auto aConverted = std::stof(basicTypeA);
    auto bConverted = std::stof(basicTypeB);

    if(resultIsInt)
        return std::to_string(static_cast<int>(aConverted - bConverted));
    else
        return std::to_string(aConverted - bConverted);
}

std::string LispParser::multiplyImplementation(std::string basicTypeA, std::string basicTypeB)
{
    bool resultIsInt = isInteger(basicTypeA) && isInteger(basicTypeB);

    auto aConverted = std::stof(basicTypeA);
    auto bConverted = std::stof(basicTypeB);

    if(resultIsInt)
        return std::to_string(static_cast<int>(aConverted * bConverted));
    else
        return std::to_string(aConverted * bConverted);
}

std::string LispParser::divideImplementation(std::string basicTypeA, std::string basicTypeB)
{
    bool resultIsInt = isInteger(basicTypeA) && isInteger(basicTypeB);

    auto aConverted = std::stof(basicTypeA);
    auto bConverted = std::stof(basicTypeB);

    if(resultIsInt)
        return std::to_string(static_cast<int>(aConverted / bConverted));
    else
        return std::to_string(aConverted / bConverted);
}

std::string LispParser::greaterThanImplementation(std::string basicTypeA, std::string basicTypeB)
{
    auto aConverted = std::stof(basicTypeA);
    auto bConverted = std::stof(basicTypeB);

    return (aConverted > bConverted) ? "true" : "false";
}

std::string LispParser::equalToImplementation(std::string basicTypeA, std::string basicTypeB)
{
    auto aConverted = std::stof(basicTypeA);
    auto bConverted = std::stof(basicTypeB);

    return (aConverted == bConverted) ? "true" : "false";
}

std::string LispParser::lessThanImplementation(std::string basicTypeA, std::string basicTypeB)
{
    auto aConverted = std::stof(basicTypeA);
    auto bConverted = std::stof(basicTypeB);

    return (aConverted < bConverted) ? "true" : "false";
}

ParenthesisLocations LispParser::getOutermostParenthesis(std::string data)
{
    return { ._front = data.find_first_of("("), ._rear = data.find_last_of(")")};
}

ParenthesisLocations LispParser::getInnermostParenthesis(std::string data)
{
    return { ._front = data.find_last_of("("), ._rear = data.find_first_of(")")};
}

bool LispParser::isInteger(std::string str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
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
