//
// Created by andyh on 1/31/22.
//

#ifndef CS503_LISP_INTERPRETER_LIST_HPP
#define CS503_LISP_INTERPRETER_LIST_HPP

#include "IAtom.hpp"

// STL
#include <vector>
#include <iostream>
#include <memory>

namespace atoms
{
    class List : public IAtom
    {
    public:
        List(std::vector<std::shared_ptr<IAtom>> members);
        ~List() = default;

        List(List& other);
        void operator<<(std::ostream& stream) override;

        // Atom overloads
    private:
        std::shared_ptr<IAtom> _car;
        std::vector<std::shared_ptr<IAtom>> _cdr;
    };
}


#endif //CS503_LISP_INTERPRETER_LIST_HPP
