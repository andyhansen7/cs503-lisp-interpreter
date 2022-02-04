//
// Created by andyh on 2/2/22.
//

#include "List.hpp"

using namespace basic_types;

List::List(const std::string &source)
{
    if(isList(source))
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
    if(isList(source))
    {
        _contents = buildList(source);
    };
}

void List::operator<<(std::ostream& stream)
{
    stream << str();
}
std::string List::str()
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

bool List::isList(const std::string& text, std::map<std::string, std::unique_ptr<IBasicType>> userVariables)
{
    std::string inputText = text;
    const std::string delim = " ";
    std::size_t pos = 0;
    std::vector<std::string> textPieces;

    // Remove initial and end parenthesis
    boost::replace_first(inputText, "(", "");
    boost::replace_last(inputText, ")", "");

    while((pos = inputText.find(delim)) != std::string::npos)
    {
        textPieces.push_back(inputText.substr(0, pos));
        inputText.erase(0, pos + delim.length());
    }

    bool isList = true;
    for(const auto& it : textPieces)
    {
        bool itValid = Number::isNumber(it) || (userVariables.find(it) != userVariables.end()) || isList(it);
        isList &= itValid;
    }

    return isList;
}

bool List::allAreLists(std::vector<std::string> sources)
{
    bool ret = true;

    for(auto it : sources)
    {
        ret &= isList(it);
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
            list.push_back({.number = std::make_unique<Number>(newItem), .list = std::make_unique<List>(), .itemIsList = false});
        else if(isList(newItem))
            list.push_back({.number = std::make_unique<Number>(), .list = std::make_unique<List>(newItem), .itemIsList = true});
        else
            error::ErrorHandle::handleError("List Builder", "Invalid argument given to list builder than cannot be parsed as a number or list: " + source);

        inputText.erase(0, pos + delim.length());
    }

    return list;
}
