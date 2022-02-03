//
// Created by andyh on 2/3/22.
//

#ifndef LISP_INTERPRETER_PARENTHESISUTILS_HPP
#define LISP_INTERPRETER_PARENTHESISUTILS_HPP

namespace parsers
{
    typedef struct parenthesis_locations
    {
        std::size_t _front;
        std::size_t _rear;
    } ParenthesisLocations;

    typedef struct all_parenthesis_locations
    {
        std::vector<ParenthesisLocations> _pairs;
    } AllParenthesisLocations;

    static bool compareLocations(const ParenthesisLocations& a, const ParenthesisLocations& b)
    {
        return a._front > b._front;
    }

    // Returns indices of innermost (last) pair of parenthesis
    static ParenthesisLocations getInnermostParenthesis(std::string data)
    {
        std::size_t frontIndex = data.find_last_of("(");
        std::size_t rearIndex = data.find_first_of(")", frontIndex);

        return {._front = frontIndex, ._rear = rearIndex};
    }

    // Returns indices of outermost (first) pair of parenthesis
    static ParenthesisLocations getOutermostParenthesis(std::string data)
    {
        std::size_t frontIndex = data.find_first_of("(");
        std::size_t rearIndex = data.find_last_of(")");

        return {._front = frontIndex, ._rear = rearIndex};
    }

    static AllParenthesisLocations orderParenthesisLocations(AllParenthesisLocations locations)
    {
        std::vector<ParenthesisLocations> locationsCopy = locations._pairs;

        std::sort(locationsCopy.begin(), locationsCopy.end(), compareLocations);

        return {._pairs = locationsCopy};
    }

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
            ParenthesisLocations pair = {._front = 99, ._rear = 99};
            pair._front = openings.at(i);
            pair._rear = dataCopy.find_first_of(")", pair._front);
            dataCopy[pair._rear] = '*';
            ret._pairs.push_back(pair);
        }

        return orderParenthesisLocations(ret);
    }
}

#endif //LISP_INTERPRETER_PARENTHESISUTILS_HPP
