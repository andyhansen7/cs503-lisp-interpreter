//
// Created by andyh on 2/3/22.
//

#include "Conditional.hpp"

using namespace basic_types;

Conditional::Conditional(const std::string& source)
    : _val(parseConditional(source))
{

}
Conditional::Conditional(const Conditional& other)
    : _val(other._val)
{

}

Conditional::Conditional(const Number& number)
{
    _val = (number.get() > 0.0f);
}

Conditional::Conditional(const List& list)
{
    _val = (list.size() > 0);
}

Conditional::Conditional()
    : _val(false)
{

}

void Conditional::operator=(const Conditional& other)
{
    _val = other._val;
}

void Conditional::operator=(const std::string& source)
{
    _val = parseConditional(source);
}

Conditional::operator bool() const
{
    return _val;
}

bool Conditional::isConditional(const std::string& source)
{
    return (source == "T" || Null::isNull(source));
}


void Conditional::operator<<(std::ostream& stream)
{
    stream << (_val ? "T" : "()");
}

std::string Conditional::str() const
{
    return (_val ? "T" : "()");
}

bool Conditional::parseConditional(const std::string& source)
{
    if(Number::isNumber(source))
    {
        return (Number(source).get() > 0.0f);
    }
    else if(List::isList(source, {}, {}))
    {
        return (List(source).size() > 0);
    }
    else if(Null::isNull(source))
    {
        return false;
    }
    else
    {
        return true;
    }
}