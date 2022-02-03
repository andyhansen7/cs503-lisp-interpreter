//
// Created by andyh on 2/2/22.
//

#ifndef LISP_INTERPRETER_LIST_HPP
#define LISP_INTERPRETER_LIST_HPP

// src
#include <basic_types/Number.hpp>

// STL
#include <string>
#include <vector>
#include <boost/algorithm/string/replace.hpp>

namespace basic_types
{
    class List
    {
    public:
        List(const std::string& source);
        ~List() = default;
        void operator=(const List& other);
        void operator=(const std::string& source);

        static bool isList(const std::string& text);
    private:
        std::vector<Number> _contents;

        std::vector<Number> buildList(const std::string& source);
    };
}


#endif //LISP_INTERPRETER_LIST_HPP
