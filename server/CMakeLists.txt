cmake_minimum_required(VERSION 3.28)
project(server)

set(CMAKE_CXX_STANDARD 20)

add_executable(server
        main.cpp
        ServerApp.cpp
        HSMServer.cpp
        ISO8583Processor.cpp
        Utils.cpp)
