//
// Created by andyh on 2/3/22.
//

#ifndef LISP_INTERPRETER_PARENTHESISUTILS_HPP
#define LISP_INTERPRETER_PARENTHESISUTILS_HPP

// src
#include <Output/Debug.hpp>

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
    static ParenthesisLocations getInnermostParenthesis(std::string data)
    {
        std::size_t frontIndex = data.find_last_of("(");
        std::size_t rearIndex = data.find_first_of(")", frontIndex);

        return {.front = frontIndex, .rear = rearIndex};
    }

    // Returns indices of outermost (first) pair of parenthesis
    [[maybe_unused]]
    static ParenthesisLocations getOutermostParenthesis(std::string data)
    {
        std::size_t frontIndex = data.find_first_of("(");
        std::size_t rearIndex = data.find_last_of(")");

        return {.front = frontIndex, .rear = rearIndex};
    }

    [[maybe_unused]]
    static bool hasSinglePair(std::string data)
    {
        auto outerPair = getOutermostParenthesis(data);
        auto innerPair = getInnermostParenthesis(data);
        return (outerPair.front == innerPair.front && outerPair.rear == innerPair.rear);
    }

    [[maybe_unused]]
    static bool hasNoPairs(std::string data)
    {
        auto outerPair = getOutermostParenthesis(data);
        return (outerPair.front == std::string::npos) && (outerPair.rear == std::string::npos);
    }

    [[maybe_unused]]
    static AllParenthesisLocations orderParenthesisLocations(AllParenthesisLocations locations)
    {
        std::vector<ParenthesisLocations> locationsCopy = locations.pairs;

        std::sort(locationsCopy.begin(), locationsCopy.end(), compareLocations);

        return {.pairs = locationsCopy};
    }

    [[maybe_unused]]
    static AllParenthesisLocations getAllParenthesisLocations(std::string data)
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
            ParenthesisLocations pair = {.front = 99, .rear = 99};
            pair.front = openings.at(i);
            pair.rear = dataCopy.find_first_of(")", pair.front);
            dataCopy[pair.rear] = '*';
            output::Debug::debugLog("ParenthesisUtils", "Pair located, open is " + std::to_string(pair.front) + ", close is " + std::to_string(pair.rear));
            ret.pairs.push_back(pair);
        }

        return orderParenthesisLocations(ret);
    }
}

#endif //LISP_INTERPRETER_PARENTHESISUTILS_HPP
