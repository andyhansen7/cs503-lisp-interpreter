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


void Conditional::operator<<(std::ostream& stream)
{
    stream << (_val ? "T" : "NIL");
}

std::string Conditional::str()
{
    return (_val ? "T" : "NIL");
}

bool Conditional::parseConditional(const std::string& source)
{
    if(source != "T" && source != "NIL")
        error::ErrorHandle::handleError("Conditional Evaluator", "Argument cannot be parsed as a contitional: " + source);
    return (source == "T");
}