cmake_minimum_required(VERSION 3.27)
project(feup_da_proj1)

set(CMAKE_CXX_STANDARD 14)

include_directories(classes)

add_executable(feup_da_proj1
        classes/City.cpp
        classes/City.h
        classes/Graph.h
        classes/Parser.cpp
        classes/Parser.h
        classes/Reservoir.cpp
        classes/Reservoir.h
        classes/Station.cpp
        classes/Station.h
        main.cpp)
