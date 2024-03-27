cmake_minimum_required(VERSION 3.27)
project(feup_da_proj1)

set(CMAKE_CXX_STANDARD 14)

include_directories(classes)

add_executable(feup_da_proj1
        classes/City.h
        classes/Graph.cpp
        classes/Graph.h
        classes/Parser.cpp
        classes/Parser.h
        classes/Reservoir.h
        classes/Station.h
        classes/Dataset.cpp
        classes/Dataset.h
        classes/NetworkPoint.h
        main.cpp)
