//
// Created by andyh on 2/3/22.
//

#ifndef LISP_INTERPRETER_CONDITIONAL_HPP
#define LISP_INTERPRETER_CONDITIONAL_HPP

// src
#include <basic_types/IBasicType.hpp>
#include <error/ErrorHandle.hpp>

// STL
#include <string>
#include <iostream>

namespace basic_types
{
    class Conditional : public IBasicType
    {
    public:
        Conditional(const std::string& source);
        Conditional(const Conditional& other);
        Conditional();
        ~Conditional() = default;

        void operator=(const Conditional& other);
        void operator=(const std::string& source);
        operator bool() const;

        void operator<<(std::ostream& stream) override;
        std::string str() override;
    private:
        bool _val;

        bool parseConditional(const std::string& source);
    };
}

#endif //LISP_INTERPRETER_CONDITIONAL_HPP
