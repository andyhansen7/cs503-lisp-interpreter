//
// Created by andyh on 2/3/22.
//

#ifndef LISP_INTERPRETER_DEBUG_HPP
#define LISP_INTERPRETER_DEBUG_HPP

// STL
#include <iostream>
#include <string>

namespace output
{
    class Debug
    {
    public:
        static bool useDebug;

        static inline void debugLog(const std::string& caller, const std::string& message)
        {
            if(useDebug)
                std::cout << "\033[33m[ " << caller << " ]: " << message << "\033[0m" << std::endl;
        }
    };
}


#endif //LISP_INTERPRETER_DEBUG_HPP
