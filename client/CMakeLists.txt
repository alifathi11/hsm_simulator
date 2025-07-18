cmake_minimum_required(VERSION 3.31)
project(client)

set(CMAKE_CXX_STANDARD 20)

add_executable(client main.cpp ClientApp.cpp ISO8583Builder.cpp ISO8583Encoder.cpp ISO8583Message.cpp)
