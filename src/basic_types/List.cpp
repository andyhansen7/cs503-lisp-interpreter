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

bool List::isList(const std::string& text)
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
        isList &= Number::isNumber(it);
    }

    return isList;
}

std::vector<Number> List::buildList(const std::string& source)
{
    std::string inputText = source;
    const std::string delim = " ";
    std::size_t pos = 0;
    std::vector<Number> numbers;

    // Remove initial and end parenthesis
    boost::replace_first(inputText, "(", "");
    boost::replace_last(inputText, ")", "");

    while((pos = inputText.find(delim)) != std::string::npos)
    {
        numbers.push_back(Number(inputText.substr(0, pos)));
        inputText.erase(0, pos + delim.length());
    }

    return numbers;
}
