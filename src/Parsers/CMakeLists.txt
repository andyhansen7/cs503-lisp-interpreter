add_library(
    Parsers

    Parser.cpp
)

target_link_libraries(
    Parsers

    Functions
    BasicTypes
    Output
)