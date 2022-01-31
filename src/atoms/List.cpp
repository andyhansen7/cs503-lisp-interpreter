//
// Created by andyh on 1/31/22.
//

#include "List.hpp"

using namespace atoms;

List::List(std::vector<std::shared_ptr<IAtom>> members)
    : _car(members[0]),
      _cdr(members.begin() + 1, members.end())
{

}

List::List(List& other)
{
    _car = other._car;
    _cdr = other._cdr;
}
void List::operator<<(std::ostream& stream)
{
    stream << _car << ", ";

    for(const auto& it : _cdr)
    {
        stream << it << ", ";
    }
}