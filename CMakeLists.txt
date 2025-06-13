cmake_minimum_required(VERSION 3.21)
project(calculator C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion -fsanitize=undefined -fsanitize-trap -fPIE")

add_subdirectory(src/lexer)
add_subdirectory(src/parser)
add_subdirectory(src/interpreter)
add_subdirectory(src/utils)

add_executable(
  ${PROJECT_NAME}
  src/main.c
)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
  lexer parser interpreter utils
)
