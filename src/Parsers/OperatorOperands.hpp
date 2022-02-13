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

using namespace basic_types;

namespace parsers
{
    typedef struct operator_operands
    {
        std::string operation;
        std::vector<std::string> operands;
    } OperatorOperands;

    class OperatorOperandsUtil
    {
    public:
        // Returns operator and operands given a string
        static OperatorOperands getOperatorOperands(const std::string& data)
        {
            // Assure there are more than 2 arguments
            size_t spaceCount = std::count(data.begin(), data.end(), ' ');

            if(spaceCount < 1)
            {
                error("Not enough spaces in input: " + data);
                return {};
            }
            else
            {
                OperatorOperands ops;
                std::vector<std::string> listOps;
                std::string inputText = data;
                const std::string delim = " ";
                std::size_t pos = 0;
                bool operationSet = false;

                // Remove initial and end parenthesis
                boost::replace_first(inputText, "(", "");
                boost::replace_last(inputText, ")", "");

                // Remove list elements
                auto locations = getAllParenthesisLocations(inputText);
                std::reverse(locations.pairs.begin(), locations.pairs.end());
                for(const auto& p : locations.pairs)
                {
                    std::string list = inputText.substr(p.front, (p.rear - p.front + 1));
                    if(list == "()" || list == "( )" || List::isList(list, {}))
                    {
                        listOps.push_back(list);
                        debug("OperationOperands found list" + list);
                        inputText.replace(p.front, (p.rear - p.front + 1), "");
                    }
                }
                debug("Input text is now " + inputText);

                while(((pos = inputText.find(delim)) != std::string::npos) && inputText != " ")
                {
                    debug("Input text is now " + inputText);

                    // Set operation if not yet set
                    if(!operationSet)
                    {
                        ops.operation = inputText.substr(0, pos);
                        debug("OperationOperands operation set to " + ops.operation);
                        inputText.erase(0, pos + delim.length());
                        operationSet = true;
                    }
                    else
                    {
                        std::string operand = inputText.substr(0, pos);
                        if(operand != " " && operand.length() > 0)
                        {
                            ops.operands.push_back(operand);
                            debug("OperationOperands found operand \'" + operand + "\'");
                            inputText.erase(0, pos + delim.length());
                        }
                    }
                }

                // Grab the last bit
                if(inputText != " " && inputText.length() > 0)
                {
                    ops.operands.push_back(inputText);
                    debug("OperationOperands found operand \'" + inputText + "\'");
                }

                // Append lists
                for(auto it : listOps)
                {
                    ops.operands.push_back(it);
                }

                return ops;
            }
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
