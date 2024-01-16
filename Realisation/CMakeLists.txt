cmake_minimum_required(VERSION 3.26)
project(Realisation)

set(CMAKE_CXX_STANDARD 17)

add_executable(Realisation
        Util.h
        Util.cpp
        Neuron.cpp
        Neuron.h
        Layer.cpp
        Layer.h
        Network.cpp
        Network.h
        main.cpp)
