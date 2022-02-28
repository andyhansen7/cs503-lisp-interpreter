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

        EXPECT_EQ(ret.size(), 1);
        EXPECT_EQ(ret[0], "6.000000");
    }

    TEST(SubtractionTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(- 10 1 3)";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 1);
        EXPECT_EQ(ret[0], "6.000000");
    }

    TEST(MultiplicationTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(* 1 2 3)";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 1);
        EXPECT_EQ(ret[0], "6.000000");
    }

    TEST(DivisionTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(/ 36 2 3)";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 1);
        EXPECT_EQ(ret[0], "6.000000");
    }

    TEST(PrintTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(print 6)";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 1);
        EXPECT_EQ(ret[0], "6.000000");
    }

    TEST(IfTrueTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(if T (1) (2))";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 1);
        EXPECT_EQ(ret[0], "1.000000");
    }

    TEST(IfFalseTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(if () (1) (2))";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 1);
        EXPECT_EQ(ret[0], "2.000000");
    }

    TEST(SetTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(set x 1.23)";
        std::string arg2 = "(+ x x)";
        auto ret = p.parse(arg);
        auto ret2 = p.parse(arg2);

        EXPECT_EQ(ret.size(), 1);
        EXPECT_EQ(ret[0], "OK");
        EXPECT_EQ(ret2.size(), 1);
        EXPECT_EQ(ret2[0], "2.460000");
    }

    TEST(DefineTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(define x (a) (print a))";
        std::string arg2 = "(x 1.23)";
        auto ret = p.parse(arg);
        auto ret2 = p.parse(arg2);

        EXPECT_EQ(ret.size(), 1);
        EXPECT_EQ(ret[0], "OK");
        EXPECT_EQ(ret2.size(), 1);
        EXPECT_EQ(ret2[0], "1.230000");
    }

    TEST(BeginTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(begin (print 1) (print 2))";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 2);
        EXPECT_EQ(ret[0], "1.000000");
        EXPECT_EQ(ret[1], "2.000000");
    }

    TEST(WhileTest, Success)
    {
        parsers::Parser p;
        std::string arg1 = "(set var 0)";
        std::string arg2 = "(while (< var 3) (begin (print var) (set var (+ var 1))))";
        auto ret1 = p.parse(arg1);
        auto ret2 = p.parse(arg2);

        EXPECT_EQ(ret1.size(), 1);
        EXPECT_EQ(ret1[0], "OK");

        EXPECT_EQ(ret2.size(), 6);
        EXPECT_EQ(ret2[0], "0.000000");
        EXPECT_EQ(ret2[1], "OK");
        EXPECT_EQ(ret2[2], "1.000000");
        EXPECT_EQ(ret2[3], "OK");
        EXPECT_EQ(ret2[4], "2.000000");
        EXPECT_EQ(ret2[5], "OK");
    }

    TEST(ConsTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(cons 1 2)";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 1);
        EXPECT_EQ(ret[0], "(1.000000 2.000000)");
    }

    TEST(CarTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(car (1 2))";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 1);
        EXPECT_EQ(ret[0], "1.000000");
    }

    TEST(CdrTest, Success)
    {
        parsers::Parser p;
        std::string arg = "(cdr (1 2))";
        auto ret = p.parse(arg);

        EXPECT_EQ(ret.size(), 1);
        EXPECT_EQ(ret[0], "(2.000000)");
    }
}

