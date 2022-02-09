//
// Created by andyh on 2/2/22.
//

#include "Number.hpp"

using namespace basic_types;

Number::Number(const std::string& source)
{
    if(isNumber(source))
    {
        _value = std::stof(source);
        _isNull = false;
    }
    else
    {
        _isNull = true;
    }
}

Number::Number(const int value)
{
    _value = static_cast<double>(value);
    _isNull = false;
}

Number::Number(const double value)
{
    _value = value;
    _isNull = false;
}

Number::Number()
    : _value(0.0f), _isNull(true)
{

}

void Number::operator=(const Number& source)
{
    _value = source._value;
    _isNull = false;
}

void Number::operator=(const int val)
{
    _value = static_cast<double>(val);
    _isNull = false;
}
void Number::operator=(const double val)
{
    _value = val;
    _isNull = false;
}

void Number::operator<<(std::ostream& stream)
{
    stream << (_isNull ? "NIL" : std::to_string(_value));
}

double Number::get() const
{
    return _value;
}

std::string Number::str()
{
    return  (_isNull ? "NIL" : std::to_string(_value));
}

bool Number::isNumber(const std::string& text)
{
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
