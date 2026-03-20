cmake_minimum_required(VERSION 3.10)
project(FactoryManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
file(GLOB MAIN "main.cpp")

add_executable(factory_app ${MAIN} ${SOURCES})
