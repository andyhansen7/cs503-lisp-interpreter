//
// Created by andyh on 2/3/22.
//

#ifndef LISP_INTERPRETER_PARENTHESISUTILS_HPP
#define LISP_INTERPRETER_PARENTHESISUTILS_HPP

// src
#include "Debug.cpp"
#include <utility>

namespace parsers
{
    typedef struct parenthesis_locations
    {
        std::size_t front;
        std::size_t rear;
    } ParenthesisLocations;

    typedef struct all_parenthesis_locations
    {
        std::vector<ParenthesisLocations> pairs;
    } AllParenthesisLocations;

    [[maybe_unused]]
    static bool compareLocations(const ParenthesisLocations& a, const ParenthesisLocations& b)
    {
        return a.front > b.front;
    }

    // Returns indices of innermost (last) pair of parenthesis
    [[maybe_unused]]
    static ParenthesisLocations getInnermostParenthesis(const std::string& data)
    {
        std::size_t frontIndex = data.find_last_of('(');
        std::size_t rearIndex = data.find_first_of(')', frontIndex);

        return {.front = frontIndex, .rear = rearIndex};
    }

    // Returns indices of outermost (first) pair of parenthesis
    [[maybe_unused]]
    static ParenthesisLocations getOutermostParenthesis(const std::string& data)
    {
        std::size_t frontIndex = data.find_first_of('(');
        std::size_t rearIndex = data.find_last_of(')');

        return {.front = frontIndex, .rear = rearIndex};
    }

    [[maybe_unused]]
    static bool hasSinglePair(const std::string& data)
    {
        auto outerPair = getOutermostParenthesis(data);
        auto innerPair = getInnermostParenthesis(data);
        return (outerPair.front == innerPair.front && outerPair.rear == innerPair.rear);
    }

    [[maybe_unused]]
    static bool hasNoPairs(const std::string& data)
    {
        auto outerPair = getOutermostParenthesis(data);
        return (outerPair.front == std::string::npos) && (outerPair.rear == std::string::npos);
    }

    [[maybe_unused]]
    static AllParenthesisLocations orderParenthesisLocations(const AllParenthesisLocations& locations)
    {
        std::vector<ParenthesisLocations> locationsCopy = locations.pairs;

        std::sort(locationsCopy.begin(), locationsCopy.end(), compareLocations);

        return {.pairs = locationsCopy};
    }

    [[maybe_unused]]
    static AllParenthesisLocations getAllParenthesisLocations(std::string data)
    {
        std::vector<std::size_t> openings, closings;
        AllParenthesisLocations ret;
        std::string dataCopy = data;

        // Get all relevant indices
        for(std::size_t i = 0; i < dataCopy.size(); i++)
        {
            if(dataCopy[i] == '(')
            {
                openings.push_back(i);
            }
        }
        for(std::size_t i = 0; i < dataCopy.size(); i++)
        {
            if(dataCopy[i] == ')')
            {
                closings.push_back(i);
            }
        }

        if(openings.size() != closings.size())
        {
            output::ErrorHandle::handleError("ParenthesisUtils", "Given unequal number of opening and closing parenthesis in string " + dataCopy);
        }

        std::reverse(openings.begin(), openings.end());
//        for(const auto& it : openings) { std::cout << it << std::endl; }
//        std::cout << std::endl;
//        std::cout << std::endl;
//        for(const auto& it : closings) { std::cout << it << std::endl; }
//        std::cout << openings.size() << " " << closings.size() << std::endl;

        size_t numberOfPairs = openings.size();
        for(std::size_t i = 0; i < numberOfPairs; i++)
        {
            ParenthesisLocations pair;
            pair.front = openings.at(i);
            for(std::size_t j = 0; j < closings.size(); j++)
            {
                if(closings.at(j) > openings.at(i))
                {
                    pair.rear = closings.at(j);
                    closings.erase(closings.begin() + j);
                    break;
                }
            }

            output::Debug::debugLog("ParenthesisUtils", "Pair located, open is " + std::to_string(pair.front) + ", close is " + std::to_string(pair.rear));
            ret.pairs.push_back(pair);
        }

        return orderParenthesisLocations(ret);
    }
}

#endif //LISP_INTERPRETER_PARENTHESISUTILS_HPP
