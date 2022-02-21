add_executable(
    UnitTests

    UnitTests.cpp
)

target_link_libraries(
    UnitTests

    GTest::gtest_main
    Parsers
    Interpreters
    BasicTypes
    Output
    Functions
)

gtest_add_tests(
    TARGET
    UnitTests

    SOURCES
    UnitTests.cpp
)