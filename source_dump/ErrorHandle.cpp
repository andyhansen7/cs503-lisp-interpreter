//
// Created by andyh on 2/2/22.
//
#ifndef __ERR
#define __ERR
#include "ErrorHandle.hpp"

using namespace output;

void ErrorHandle::handleError(std::string caller, std::string message)
{
    std::string output = boost::str(boost::format("[ %1% ]: %2%") % caller % message);
//    std::cout << "\033[31m" << output << "\033[0m" << std::endl;
    throw std::runtime_error(output);
}
#endif

