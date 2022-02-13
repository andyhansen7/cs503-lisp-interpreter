//
// Created by andyh on 2/3/22.
//

#include "Conditional.hpp"

using namespace basic_types;

Conditional::Conditional(const std::string& source)
    : _val(parseConditional(source)), _isNull(false)
{

}
Conditional::Conditional(const Conditional& other)
    : _val(other._val), _isNull(false)
{

}

Conditional::Conditional(const Number& number)
{
    _val = (number.get() > 0.0f);
    _isNull = false;
}

Conditional::Conditional(const List& list)
{
    _val = (list.size() > 0);
    _isNull = false;
}

Conditional::Conditional()
    : _val(false)
{

}

void Conditional::operator=(const Conditional& other)
{
    _val = other._val;
    _isNull = false;
}

void Conditional::operator=(const std::string& source)
{
    _val = parseConditional(source);
    _isNull = false;
}

Conditional::operator bool() const
{
    return _val;
}

bool Conditional::isConditional(const std::string& source)
{
    return (source == "T" || source == "()");
}


void Conditional::operator<<(std::ostream& stream)
{
    stream << (_val ? "T" : "()");
}

std::string Conditional::str()
{
    return (_val ? "T" : "()");
}

bool Conditional::parseConditional(const std::string& source)
{
    if(Number::isNumber(source))
    {
        return (Number(source).get() > 0.0f);
    }
    else if(List::isList(source))
    {
        return (List(source).size() > 0);
    }
    else if(source == "T" || source == "()")
    {
        return (source == "T");
    }
    else
    {
        output::ErrorHandle::handleError("Conditional Evaluator", "Argument cannot be parsed as a conditional: " + source);
        return false;
    }
}