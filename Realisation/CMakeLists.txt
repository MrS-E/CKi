cmake_minimum_required(VERSION 3.26)
project(CKI)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

#googletest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG v1.14.0)

FetchContent_GetProperties(googletest)

if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif ()

add_library(CKI_lib STATIC
        Util.h
        Util.cpp
        Neuron.cpp
        Neuron.h
        Layer.cpp
        Layer.h
        Network.cpp
        Network.h)

add_executable(CKI main.cpp)
target_link_libraries(CKI CKI_lib)

add_executable(testRunner
        test/main.cpp
        test/NeuronTest.cpp
        test/LayerTest.cpp
        test/NetworkTest.cpp
)
target_link_libraries(testRunner CKI_lib gtest_main gmock_main)