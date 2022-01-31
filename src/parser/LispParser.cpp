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
        { "/", divideImplementation}
    }),
    _comparisons({
        {">", greaterThanImplementation},
        {"=", equalToImplementation},
        {"<", lessThanImplementation}
    })
{

}

std::string LispParser::parse(std::string data)
{
    auto pair = getInnermostParenthesis(data);

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
        std::size_t index = substring.find(" ");
        std::string operation = substring.substr(0, index);
        substring = substring.substr(index + 1);

        index = substring.find(" ");
        std::string operand0 = substring.substr(0, index);
        substring = substring.substr(index + 1);

        std::string operand1 = substring;
        // Run operation
        std::string result = _operations.at(operation)(operand0, operand1);

        data.replace(pair._front, pair._rear + 1, result);

        return data;
    }
    // Error case
    else
    {
        throw std::runtime_error("[ERROR] Invalid number of parenthesis provided in input: " + data);
    }

    return data;
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

bool LispParser::greaterThanImplementation(std::string basicTypeA, std::string basicTypeB)
{
    auto aConverted = std::stof(basicTypeA);
    auto bConverted = std::stof(basicTypeB);

    return (aConverted > bConverted);
}

bool LispParser::equalToImplementation(std::string basicTypeA, std::string basicTypeB)
{
    auto aConverted = std::stof(basicTypeA);
    auto bConverted = std::stof(basicTypeB);

    return (aConverted == bConverted);
}

bool LispParser::lessThanImplementation(std::string basicTypeA, std::string basicTypeB)
{
    auto aConverted = std::stof(basicTypeA);
    auto bConverted = std::stof(basicTypeB);

    return (aConverted < bConverted);
}

ParenthesisLocations LispParser::getInnermostParenthesis(std::string data)
{
    return { ._front = data.find_last_of("("), ._rear = data.find_first_of(")")};
}

bool LispParser::isInteger(std::string str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}