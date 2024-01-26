cmake_minimum_required(VERSION 3.26)
project(CKI)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(FTXUI)
add_subdirectory(mnist)

include_directories(${CMAKE_SOURCE_DIR}/mnist/include)

install(DIRECTORY datasets/ DESTINATION share/CKI)

add_executable(CKI
        Util.h
        Util.cpp
        Neuron.cpp
        Neuron.h
        Layer.cpp
        Layer.h
        Network.cpp
        Network.h
        main.cpp)

target_link_libraries(CKI PRIVATE ftxui::dom ftxui::screen ftxui::component)
target_link_libraries(CKI mnist)