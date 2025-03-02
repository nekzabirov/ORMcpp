cmake_minimum_required(VERSION 3.22.1)
project(sql_builder)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include/sql_builder)

# Define a header-only library
add_library(sql_builder INTERFACE)

# Use relative path for include directories
target_include_directories(sql_builder INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Installation rules
include(GNUInstallDirs)
install(TARGETS sql_builder EXPORT sql_builderConfig)
install(EXPORT sql_builderConfig DESTINATION lib/cmake/sql_builder)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})