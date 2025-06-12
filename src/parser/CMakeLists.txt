add_library(parser parser.c)

target_include_directories(lexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
