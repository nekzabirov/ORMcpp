cmake_minimum_required(VERSION 3.22.1)
project(sql_builder)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(sql_builder
        src/sql_stream.cpp
        src/column.cpp
        src/conditional.cpp
        src/quarry_stream.cpp
        src/execute_stream.cpp
)

target_include_directories(sql_builder
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/tool
)