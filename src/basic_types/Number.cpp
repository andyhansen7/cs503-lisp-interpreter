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

        if(isInteger(source))
        {
            _castToInt = true;
        }
    }
}

Number::Number(const int value)
{
    _castToInt = true;
    _value = value;
}

Number::Number(const double value)
{
    _castToInt = false;
    _value = value;
}

void Number::operator=(const Number& source)
{
    _value = source._value;
    _castToInt = source._castToInt;
}

void Number::operator=(const int val)
{
    _castToInt = true;
    _value = val;
}
void Number::operator=(const double val)
{
    _castToInt = false;
    _value = val;
}

void Number::operator<<(std::ostream& stream)
{
    stream << (_castToInt ? static_cast<int>(_value) : _value);
}

double Number::get()
{
    return _value;
}

bool Number::castToInt()
{
    return _castToInt;
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

bool Number::isInteger(const std::string& text)
{
    return !text.empty() && std::all_of(text.begin(), text.end(), ::isdigit);
}

bool Number::isFloat(const std::string& text)
{
    return isNumber(text) && !isInteger(text);
}

bool Number::allAreIntegers(std::vector<Number> numbers)
{
    bool ret = true;
    for(auto it : numbers)
    {
        ret &= it.castToInt();
    }

    return ret;
}
