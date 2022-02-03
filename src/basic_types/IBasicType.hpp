//
// Created by andyh on 2/3/22.
//

#ifndef LISP_INTERPRETER_IBASICTYPE_HPP
#define LISP_INTERPRETER_IBASICTYPE_HPP

// STL
#include <string>

namespace basic_types
{
    class IBasicType
    {
    public:
        virtual void operator<<(std::ostream& stream) = 0;
        virtual std::string str() = 0;
    };
}

#endif //LISP_INTERPRETER_IBASICTYPE_HPP
