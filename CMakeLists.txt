cmake_minimum_required(VERSION 3.20)
project(NetClient)

set(CMAKE_CXX_STANDARD 20)

add_executable(NetClient main.cpp olc_net.h net_tsqueue.h net_client.h net_server.h net_connection.h)

include_directories(${PROJECT_NAME} C:/Projekty/cpp-lib/asio-1.20.0/asio-1.20.0/include)
