//
// Created by andyh on 2/2/22.
//

#ifndef LISP_INTERPRETER_LIST_HPP
#define LISP_INTERPRETER_LIST_HPP

// src
#include <BasicTypes/Number.hpp>
#include <BasicTypes/IBasicType.hpp>
#include <Output/ErrorHandle.hpp>

// STL
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <map>
#include <boost/algorithm/string/replace.hpp>

namespace basic_types
{
    class List;

    class ListItem
    {
    public:
        ListItem(std::shared_ptr<Number> number, std::shared_ptr<List> list, bool itemIsList)
            : number(std::move(number)), list(std::move(list)), itemIsList(itemIsList) {}
        ListItem(const ListItem& other)
            : number(std::make_shared<Number>(*(other.number))), list(std::make_shared<List>(*(other.list))), itemIsList(other.itemIsList) {}
        ListItem()
            : number(std::make_shared<Number>()), list(std::make_shared<List>()), itemIsList(false) {}
        void operator=(const ListItem& other)
        {
            number = std::make_shared<Number>(*(other.number));
            list = std::make_shared<List>(*(other.list));
            itemIsList = other.itemIsList;
        }

        std::shared_ptr<Number> number;
        std::shared_ptr<List> list;
        bool itemIsList = false;
    };

    class List : public IBasicType
    {
    public:
        List(const std::string& source);
        List();
        ~List() = default;

        void operator=(const List& other);
        void operator=(const std::string& source);
        void operator<<(std::ostream& stream) override;
        std::string str() override;

        int size() const;
        void push(const Number& number);
        void push(const List& list);
        static bool isList(const std::string& text);
        static bool allAreLists(std::vector<std::string> sources);
    private:
        std::vector<ListItem> _contents;

        std::vector<ListItem> buildList(const std::string& source);
    };
}


#endif //LISP_INTERPRETER_LIST_HPP
