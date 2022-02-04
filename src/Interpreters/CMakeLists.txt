add_library(
    Interpreters

    CommandLineInterpreter.cpp
)

target_link_libraries(
    Interpreters

    Parsers
    BasicTypes
    Output
    Functions
)