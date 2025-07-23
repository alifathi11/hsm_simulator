cmake_minimum_required(VERSION 3.28)
project(server)

set(CMAKE_CXX_STANDARD 20)

add_executable(server
        main.cpp
        ServerApp.cpp
        ClientHandler.cpp
        ISO8583Encoder.cpp
        ISO8583Decoder.cpp
        ISO8583Message.cpp
        HSMServer.cpp
        ISO8583Processor.cpp
        Utils.cpp)
