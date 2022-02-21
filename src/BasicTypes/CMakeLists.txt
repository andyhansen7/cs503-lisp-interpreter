add_library(
    BasicTypes

    Number.cpp
    List.cpp
    Conditional.cpp
    Null.cpp
)

target_link_libraries(
    BasicTypes

    Output
    Functions
)