CMAKE_MINIMUM_REQUIRED(VERSION 3.14 FATAL_ERROR)

PROJECT(Cup.Graphics VERSION 2021.0219 LANGUAGES CXX)

ADD_LIBRARY(Cup.Graphics STATIC Source/Color.cpp)
SET_TARGET_PROPERTIES(Cup.Graphics PROPERTIES CXX_STANDARD 17)
TARGET_INCLUDE_DIRECTORIES(Cup.Graphics PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>)

ENABLE_TESTING()


INCLUDE(Test/CMakeModules/CPM.cmake)

CPMAddPackage(
        GITHUB_REPOSITORY onqtam/doctest
        GIT_TAG 2.4.5
)

MACRO(ADD_CUP_GRAPHICS_TEST _NAME_TARGET _NAME_FILE)
    ADD_EXECUTABLE(${_NAME_TARGET} ${_NAME_FILE})
    SET_TARGET_PROPERTIES(${_NAME_TARGET} PROPERTIES CXX_STANDARD 17)
    TARGET_LINK_LIBRARIES(${_NAME_TARGET} PRIVATE Cup.Graphics)
    TARGET_LINK_LIBRARIES(${_NAME_TARGET} PRIVATE doctest)
    ADD_TEST(NAME ${_NAME_TARGET} COMMAND ${_NAME_TARGET})
ENDMACRO()

ADD_CUP_GRAPHICS_TEST(TestColor Test/TestColor.cpp)