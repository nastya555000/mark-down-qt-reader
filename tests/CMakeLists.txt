project( tests LANGUAGES CXX )
enable_testing(true)

find_package(Qt6 REQUIRED COMPONENTS Test)
add_executable(markdown_parser_test markdown_parser_test_src/main.cpp
                        markdown_parser_test_src/markdown_parser_test.hpp
                        markdown_parser_test_src/markdown_parser_test.cpp
                        ../src/markdown_parser.cpp)

add_test(NAME markdown_parser_test COMMAND markdown_parser_test)
target_include_directories(markdown_parser_test PRIVATE ../src)
target_link_libraries(markdown_parser_test PRIVATE Qt6::Test)

