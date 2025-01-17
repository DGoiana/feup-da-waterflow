cmake_minimum_required(VERSION 3.22)
project(feup_da_proj1)

set(CMAKE_CXX_STANDARD 14)

include_directories(classes)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/Doxyfile")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
                    COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
                    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
                    COMMENT "Generating API documentation with Doxygen"
                    VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)


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
        main.cpp
        classes/Edmonds_Karps.cpp
        classes/Edmonds_Karps.h
        classes/Utils.h
        classes/Utils.cpp)
