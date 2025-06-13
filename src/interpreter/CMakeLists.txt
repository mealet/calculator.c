add_library(interpreter interpreter.c)

target_include_directories(interpreter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
