add_library(lexer lexer.c token.c)

target_include_directories(lexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
