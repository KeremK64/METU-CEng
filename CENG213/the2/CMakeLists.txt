cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT the2)

file(GLOB ALL_SOURCES "*.c" "*.cc" "*.cpp" "*.cxx")
file(GLOB ALL_HEADERS "*.h" "*.hh" "*.hpp" "*.hxx" "*.ipp" "*.tpp")

set(SOURCES ${ALL_SOURCES})
set(HEADERS ${ALL_HEADERS})

project(${PROJECT} LANGUAGES CXX)
add_executable(${PROJECT} ${SOURCES} ${HEADERS})

target_compile_options(${PROJECT} PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W4>
                       $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>)
