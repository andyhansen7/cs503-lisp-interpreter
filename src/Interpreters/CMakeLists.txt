add_library(
    Interpreters

    CommandLineInterpreter.cpp
    FileReadInterpreter.cpp
)

target_link_libraries(
    Interpreters

    Parsers
    BasicTypes
    Output
    Functions
)