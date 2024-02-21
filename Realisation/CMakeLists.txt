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
FetchContent_MakeAvailable(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif ()

#nlohmann_json
FetchContent_Declare(
        nlohmannjson
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.11.3)

FetchContent_GetProperties(nlohmannjson)
FetchContent_MakeAvailable(nlohmannjson)
if (NOT nlohmannjson_POPULATED)
    FetchContent_Populate(nlohmannjson)
    add_subdirectory(${nlohmannjson_SOURCE_DIR} ${nlohmannjson_BINARY_DIR})
endif ()

#CKI
add_library(CKI_lib STATIC
        Util.h
        Util.cpp
        Neuron.cpp
        Neuron.h
        Layer.cpp
        Layer.h
        Network.cpp
        Network.h)
target_link_libraries(CKI_lib nlohmann_json::nlohmann_json)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} CKI_lib)

#Tests
add_executable(testRunner
        test/main.cpp
        test/NeuronTest.cpp
        test/LayerTest.cpp
        test/NetworkTest.cpp
        test/UtilTest.cpp
)
target_link_libraries(testRunner CKI_lib gtest_main gmock_main)