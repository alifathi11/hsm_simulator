cmake_minimum_required(VERSION 3.20.3)
project(client)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)

add_executable(client main.cpp
        ClientApp.cpp
        ISO8583Builder.cpp
        ISO8583Encoder.cpp
        ISO8583Message.cpp
        HSMClient.cpp
        ../common/FieldMapper.cpp
        ISO8583InputManager.cpp
        ../common/Utils.cpp
        HSMClientSocket.cpp
        HSMResponse.cpp
        SSLContext.cpp)

target_link_libraries(client PRIVATE OpenSSL::SSL OpenSSL::Crypto)