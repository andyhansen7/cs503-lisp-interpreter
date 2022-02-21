//
// Created by andyh on 2/16/22.
//

// src
#include <Interpreters/CommandLineInterpreter.hpp>
#include <Functions/TypeOperators.hpp>
#include <Parsers/OperatorOperands.hpp>
#include <Parsers/Parser.hpp>

// gtest
#include <gtest/gtest.h>

namespace
{
    TEST(NumberIsNumber, Success)
    {
        std::string numString = "5.43";
        parsers::OperatorOperands ops = {.operation = "N/A", .operands = { numString }};
        auto ret = functions::TypeOperations::isNumber(ops);

        EXPECT_EQ("T", ret->str());
    }

    TEST(NullIsNumber, Success)
    {
        std::string numString = "()";
        parsers::OperatorOperands ops = {.operation = "N/A", .operands = { numString }};
        auto ret = functions::TypeOperations::isNumber(ops);

        EXPECT_EQ("T", ret->str());
    }

    TEST(ListIsNumber, Success)
    {
        std::string numString = "(1 2 3 4)";
        parsers::OperatorOperands ops = {.operation = "N/A", .operands = { numString }};
        auto ret = functions::TypeOperations::isNumber(ops);

        EXPECT_EQ("()", ret->str());
    }

    TEST(ListIsList, Success)
    {
        std::string listString = "(1 2 3 4)";
        parsers::OperatorOperands ops = {.operation = "N/A", .operands = { listString }};
        auto ret = functions::TypeOperations::isList(ops);

        EXPECT_EQ("T", ret->str());
    }

    TEST(NumberIsList, Success)
    {
        std::string listString = "1.23";
        parsers::OperatorOperands ops = {.operation = "N/A", .operands = { listString }};
        auto ret = functions::TypeOperations::isList(ops);

        EXPECT_EQ("()", ret->str());
    }

    TEST(NullIsList, Success)
    {
        std::string listString = "()";
        parsers::OperatorOperands ops = {.operation = "N/A", .operands = { listString }};
        auto ret = functions::TypeOperations::isList(ops);

        EXPECT_EQ("T", ret->str());
    }

    TEST(NullIsNull, Success)
    {
        parsers::OperatorOperands ops = {.operation = "N/A", .operands = { "()" }};
        auto ret = functions::TypeOperations::isNull(ops);

        EXPECT_EQ("T", ret->str());
    }

    TEST(AdditionTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(+ 1 2 3)";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 2);
        EXPECT_EQ(ret[0], arg);
        EXPECT_EQ(ret[1], "6.000000");
    }

    TEST(SubtractionTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(- 10 1 3)";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 2);
        EXPECT_EQ(ret[0], arg);
        EXPECT_EQ(ret[1], "6.000000");
    }

    TEST(MultiplicationTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(* 1 2 3)";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 2);
        EXPECT_EQ(ret[0], arg);
        EXPECT_EQ(ret[1], "6.000000");
    }

    TEST(DivisionTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(/ 36 2 3)";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 2);
        EXPECT_EQ(ret[0], arg);
        EXPECT_EQ(ret[1], "6.000000");
    }

    TEST(PrintTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(print (6))";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 2);
        EXPECT_EQ(ret[0], arg);
        EXPECT_EQ(ret[1], "(6.000000)");
    }

    TEST(IfTrueTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(if T 1 2)";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 2);
        EXPECT_EQ(ret[0], arg);
        EXPECT_EQ(ret[1], "1.000000");
    }

    TEST(IfFalseTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(if () 1 2)";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 2);
        EXPECT_EQ(ret[0], arg);
        EXPECT_EQ(ret[1], "2.000000");
    }
}

