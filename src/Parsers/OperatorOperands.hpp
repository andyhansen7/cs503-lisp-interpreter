//
// Created by andyh on 2/4/22.
//

#ifndef LISP_INTERPRETER_OPERATOROPERANDS_HPP
#define LISP_INTERPRETER_OPERATOROPERANDS_HPP

// src
#include <Parsers/ParenthesisUtils.hpp>
#include <BasicTypes/List.hpp>

// STL
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace basic_types;

namespace parsers
{
    class OperatorOperandsUtil
    {
    public:
        // Returns operator and operands given a string
        static OperatorOperands getOperatorOperands(const std::string& data)
        {
            OperatorOperands ops;
            std::vector<std::string> listOps;
            std::string inputText = data;
            const std::string delim = " ";
            std::size_t pos = 0;
            bool operationSet = false;

            // Stop if empty list
            if(data.length() < 1 || data == " ")
            {
                return {.operation = "", .operands = {}};
            }
            else if(Null::isNull(data))
            {
                return {.operation = "", .operands = {}};
            }

            // Remove initial and end parenthesis
//            boost::replace_first(inputText, "(", "");
//            boost::replace_last(inputText, ")", "");
            if(inputText[0] == '(')
                inputText.erase(0,1); // HERE

            // Remove list elements
            auto locations = getAllParenthesisLocations(inputText);
            std::size_t numPairs = locations.pairs.size();
            std::reverse(locations.pairs.begin(), locations.pairs.end());
//            for(const auto& p : locations.pairs)
//            {
//                // Extract lists
//                if(p.front + 1 == p.rear)
//                {
//                    continue;
//                }
//                else
//                {
//                    std::string list = inputText.substr(p.front, (p.rear - p.front + 1));
//                    listOps.push_back(list);
//                    debug("OperatorOperands found list " + list);
//                    inputText.replace(p.front, (p.rear - p.front + 1), "");
//
//                    locations = getAllParenthesisLocations(inputText);
//                    std::reverse(locations.pairs.begin(), locations.pairs.end());
//                }
//            }
            while(numPairs != 0)
            {
                std::string list = inputText.substr(locations.pairs[0].front, (locations.pairs[0].rear - locations.pairs[0].front + 1));
                listOps.push_back(list);
                debug("OperatorOperands found list " + list);
                inputText.replace(locations.pairs[0].front, (locations.pairs[0].rear - locations.pairs[0].front + 1), "");

                locations = getAllParenthesisLocations(inputText);
                std::reverse(locations.pairs.begin(), locations.pairs.end());
                numPairs = locations.pairs.size();
            }
            debug("Input text is now " + inputText);

            while(((pos = inputText.find(delim)) != std::string::npos) && inputText != " ")
            {
                debug("Input text is now " + inputText);

                // Set operation if not yet set
                if(!operationSet)
                {
                    ops.operation = inputText.substr(0, pos);
                    debug("OperatorOperands operation set to " + ops.operation);
                    inputText.erase(0, pos + delim.length());
                    operationSet = true;
                }
                else
                {
                    std::string operand = inputText.substr(0, pos);
                    if(operand != " " && operand.length() > 0)
                    {
                        ops.operands.push_back(operand);
                        debug("OperatorOperands found operand \'" + operand + "\'");
                        inputText.erase(0, pos + delim.length());
                    }
                    else
                    {
                        // Erase space
                        inputText.erase(0, 1);
                    }
                }
            }

            // Grab the last bit
            if(inputText != " " && inputText.length() > 0)
            {
                ops.operands.push_back(inputText);
                debug("OperatorOperands found operand \'" + inputText + "\'");
            }

            // Append lists
            for(auto it : listOps)
            {
                ops.operands.push_back(it);
            }

            return ops;
        }
    private:
        static void error(const std::string& message)
        {
            output::ErrorHandle::handleError("OperatorOperands", message);
        }

        static void debug(const std::string& message)
        {
            output::Debug::debugLog("OperatorOperands", message);
        }
    };
}

#endif //LISP_INTERPRETER_OPERATOROPERANDS_HPP
