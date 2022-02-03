//
// Created by andyh on 2/2/22.
//

#ifndef LISP_INTERPRETER_NUMBER_HPP
#define LISP_INTERPRETER_NUMBER_HPP

// STL
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

namespace basic_types
{
    class Number
    {
    public:
        Number(const std::string& source);
        Number(const int value);
        Number(const double value);
        ~Number() = default;
        void operator=(const Number& source);
        void operator=(const int val);
        void operator=(const double val);
        void operator<<(std::ostream& stream);

        double get();
        bool castToInt();

        static bool isNumber(const std::string& text);
        static bool isInteger(const std::string& text);
        static bool isFloat(const std::string& text);
        static bool allAreIntegers(std::vector<Number> numbers);
    private:
        double _value;
        int _castToInt;
    };
}

#endif //LISP_INTERPRETER_NUMBER_HPP
