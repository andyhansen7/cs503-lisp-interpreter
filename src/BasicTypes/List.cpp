//
// Created by andyh on 2/2/22.
//

#include "List.hpp"

#include <Functions/Functions.hpp>
#include <Output/Debug.hpp>
#include <Parsers/OperatorOperands.hpp>

using namespace basic_types;

List::List(const std::string &source)
{
    if(isList(source, {}, {}))
    {
        _contents = buildList(source);
    }
}

List::List()
{

}

void List::operator=(const List& other)
{
    _contents = other._contents;
}

void List::operator=(const std::string& source)
{
    if(isList(source, {}, {}))
    {
        _contents = buildList(source);
    };
}

void List::operator<<(std::ostream& stream)
{
    stream << str();
}
std::string List::str() const
{
    std::string ret = "(";
    for(auto it : _contents)
    {
        if(it.itemIsList)
            ret += it.list->str();
        else
            ret += it.number->str();

        ret += " ";
    }
    boost::replace_last(ret, " ", "");
    ret += ")";
    return ret;
}

int List::size() const
{
    return _contents.size();
}

void List::push(const Number& number)
{
    auto n = std::make_shared<Number>(number);
    auto l = std::make_shared<List>();
    _contents.push_back(ListItem(n, l, false));
}

void List::push(const List& list)
{
    auto n = std::make_shared<Number>();
    auto l = std::make_shared<List>(list);
    _contents.push_back(ListItem(n, l, true));
}

std::string List::car()
{
    auto item = _contents[0];

    if(item.itemIsList)
    {
        return item.list->str();
    }
    else
    {
        return item.number->str();
    }
}

std::string List::cdr()
{
    List newList;
    for(std::size_t i = 1; i < _contents.size(); i++)
    {
        auto item = _contents[i];
        if(item.itemIsList)
        {
            newList.push(*(item.list));
        }
        else
        {
            newList.push(*(item.number));
        }
    }

    return newList.str();
}

bool List::isList(const std::string& text, const std::map<std::string, std::shared_ptr<IBasicType>> userVars, std::map<std::string, parsers::FunctionDefinition> userFuncs)
{
    std::string inputText = text;
    const std::string delim = " ";
    std::vector<std::string> textPieces;

    if(Null::isNull(inputText))
    {
        output::Debug::debugLog("IsList", "Returning true for null: " + inputText);
        return true;
    }

    bool containsOpen = (inputText[0] == '(');
    bool containsClose = (inputText[inputText.length() - 1] == ')');
    bool resultIsList = containsOpen && containsClose;

    // Remove initial and end parenthesis
    if(resultIsList)
    {
        inputText.erase(0,1);
        inputText.resize(inputText.size() - 1);
    }
    else
    {
        return false;
    }

    // Check that string is not a single entry
    if(inputText.find(' ') == std::string::npos && resultIsList)
    {
        return Number::isNumber(inputText);
    }

    output::Debug::debugLog("IsList", "Calling OperatorOperands");
    auto operatorOperands = parsers::OperatorOperandsUtil::getOperatorOperands(inputText);

    std::vector<std::string> allOperands;
    allOperands.push_back(operatorOperands.operation);
    for(const auto& it : operatorOperands.operands)
    {
        output::Debug::debugLog("IsList", "Received operand " + it);
        allOperands.push_back(it);
    }

    for(const auto& it : allOperands)
    {
        if(it.length() == 0) continue;

        output::Debug::debugLog("IsList", "Testing " + it);
        bool itValid =  (functions::arithmeticFunctions.find(it) == functions::arithmeticFunctions.end()) &&
                        (functions::listFunctions.find(it) == functions::listFunctions.end()) &&
                        (functions::booleanFunctions.find(it) == functions::booleanFunctions.end()) &&
                        (functions::printFunctions.find(it) == functions::printFunctions.end()) &&
                        (functions::conditionalFunctions.find(it) == functions::conditionalFunctions.end()) &&
                        (functions::typeFunctions.find(it) == functions::typeFunctions.end()) &&
                        (userVars.find(it) == userVars.end()) &&
                        (userFuncs.find(it) == userFuncs.end()) &&
                        (Null::isNull(it) ||
                        Number::isNumber(it));

        if(itValid && (it.find('(') != std::string::npos) && (it.find(')') != std::string::npos))
        {
            itValid &= isList(it, userVars, userFuncs);
        }

        output::Debug::debugLog("IsList", (itValid ? "Found valid list item: " + it : "Invalid list item: " + it));
        resultIsList &= itValid;
    }

    output::Debug::debugLog("IsList", (resultIsList ? "Found valid list: " + inputText : "Invalid list: " + inputText));
    return resultIsList;
}

bool List::allAreLists(std::vector<std::string> sources, const std::map<std::string, std::shared_ptr<IBasicType>> userVars, std::map<std::string, parsers::FunctionDefinition> userFuncs)
{
    bool ret = true;

    for(auto it : sources)
    {
        ret &= isList(it, userVars, userFuncs);
    }

    return ret;
}

std::vector<ListItem> List::buildList(const std::string& source)
{
    std::string inputText = source;
    const std::string delim = " ";
    std::size_t pos = 0;
    std::vector<ListItem> list;

    // Remove initial and end parenthesis
    boost::replace_first(inputText, "(", "");
    boost::replace_last(inputText, ")", "");

    while((pos = inputText.find(delim)) != std::string::npos)
    {
        std::string newItem = inputText.substr(0, pos);
        if(Number::isNumber(newItem))
            list.push_back(ListItem(std::make_shared<Number>(newItem), std::make_shared<List>(), false));
        else if(isList(newItem, {}, {}))
            list.push_back(ListItem(std::make_shared<Number>(), std::make_shared<List>(newItem), true));
        else
            output::ErrorHandle::handleError("List Builder", "Invalid argument given to list builder than cannot be parsed as a number or list: " + source);

        inputText.erase(0, pos + delim.length());
    }
    if(inputText != " " && inputText.length() > 0)
    {
        if(Number::isNumber(inputText))
            list.push_back(ListItem(std::make_shared<Number>(inputText), std::make_shared<List>(), false));
        else if(isList(inputText, {}, {}))
            list.push_back(ListItem(std::make_shared<Number>(), std::make_shared<List>(inputText), true));
        else
            output::ErrorHandle::handleError("List Builder", "Invalid argument given to list builder than cannot be parsed as a number or list: " + source);
    }

    return list;
}
