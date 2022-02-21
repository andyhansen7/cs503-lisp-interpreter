//
// Created by andyh on 2/2/22.
//

#include "Number.hpp"

using namespace basic_types;

Number::Number(const std::string& source)
{
    if(isNumber(source) && !Null::isNull(source))
    {
        _value = std::stof(source);
    }
    else _value = 0.0f;
}

Number::Number(const int value)
{
    _value = static_cast<double>(value);
}

Number::Number(const double value)
{
    _value = value;
}

Number::Number()
    : _value(0.0f)
{

}

void Number::operator=(const Number& source)
{
    _value = source._value;
}

void Number::operator=(const int val)
{
    _value = static_cast<double>(val);
}
void Number::operator=(const double val)
{
    _value = val;
}

void Number::operator<<(std::ostream& stream)
{
    stream << std::to_string(_value);
}

double Number::get() const
{
    return _value;
}

std::string Number::str() const
{
    return std::to_string(_value);
}

bool Number::isNumber(const std::string& text)
{
    if(Null::isNull(text))
    {
        return true;
    }

    try
    {
        std::stof(text);
    }
    catch(std::logic_error)
    {
        return false;
    }

    return true;
}
