cmake_minimum_required(VERSION 3.22)
project(sandwich C)

set(CMAKE_C_STANDARD 99)

add_executable(sandwich src/main.c include/tokenizer.h src/tokenizer.c include/parser.h src/parser.c)
target_include_directories(sandwich PUBLIC include)
