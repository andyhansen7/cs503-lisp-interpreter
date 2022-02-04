add_executable(
    Main

    main.cpp
)

target_link_libraries(
    Main

    Parsers
    Functions
    BasicTypes
    Interpreters
    Output
)