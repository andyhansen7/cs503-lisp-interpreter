//
// Created by andyh on 2/2/22.
//

#include "ErrorHandle.hpp"

using namespace error;

void ErrorHandle::handleError(std::string caller, std::string message)
{
    std::string output = boost::str(boost::format("[ %1% ]: %2%") % caller % message);
    std::cerr << output << std::endl;
    throw std::runtime_error(output);
}

