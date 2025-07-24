cmake_minimum_required(VERSION 3.28)
project(server)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)

add_executable(server
        main.cpp
        ServerApp.cpp
        ClientHandler.cpp
        ISO8583Encoder.cpp
        ISO8583Decoder.cpp
        ISO8583Message.cpp
        HSMServer.cpp
        ISO8583Processor.cpp
        ../common/Utils.cpp
        HSMCommandHandler.cpp
        SecurityService.cpp
        ../common/FieldMapper.cpp
        ConfigLoader.cpp
        SSLContext.cpp)


target_link_libraries(server PRIVATE OpenSSL::SSL OpenSSL::Crypto)
