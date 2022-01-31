//
// Created by andyh on 1/31/22.
//

#ifndef CS503_LISP_INTERPRETER_IATOM_HPP
#define CS503_LISP_INTERPRETER_IATOM_HPP

// STL
#include <iostream>

namespace atoms
{
    class IAtom
    {
    public:
        // Ostream overload
        virtual void operator<<(std::ostream& stream) = 0;
    };
}

#endif //CS503_LISP_INTERPRETER_IATOM_HPP
