add_executable(
    arhansen-lisp-interpreter

    main.cpp
)

target_link_libraries(
    arhansen-lisp-interpreter

    Parsers
    Functions
    BasicTypes
    Interpreters
    Output
)