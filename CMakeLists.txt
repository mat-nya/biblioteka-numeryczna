cmake_minimum_required(VERSION 3.15)
project(biblioteka-numeryczna)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(numerical
    src/approximation.cpp
    src/differentialequation.cpp
    src/Euler.cpp
    src/gausselimination.cpp
    src/integration.cpp
    src/lagrange.cpp
    src/lumethod.cpp
    src/newtoninterpolation.cpp
    src/nonlinear.cpp
    src/threeintegrations.cpp
)

file(GLOB EXAMPLES "examples/*_example.cpp")

foreach(example ${EXAMPLES})
    get_filename_component(example_name ${example} NAME_WE)

    add_executable(${example_name} ${example})

    target_link_libraries(${example_name} numerical)
endforeach()
