cmake_minimum_required(VERSION 3.20.3)
project(client)

set(CMAKE_CXX_STANDARD 20)

add_executable(client main.cpp
        ClientApp.cpp
        ISO8583Builder.cpp
        ISO8583Encoder.cpp
        ISO8583Message.cpp
        HSMClient.cpp
        ../server/FieldMapper.cpp
        ISO8583InputManager.cpp
        Utils.cpp
        HSMClientSocket.cpp)
