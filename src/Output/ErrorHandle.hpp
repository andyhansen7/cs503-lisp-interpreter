//
// Created by andyh on 2/2/22.
//

#ifndef LISP_INTERPRETER_ERRORHANDLE_HPP
#define LISP_INTERPRETER_ERRORHANDLE_HPP

// STL
#include <string>
#include <iostream>
#include <boost/format.hpp>
#include <exception>

namespace output
{
    class ErrorHandle
    {
    public:
        static void handleError(std::string caller, std::string message);
    };
}


#endif //LISP_INTERPRETER_ERRORHANDLE_HPP
