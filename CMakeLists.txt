cmake_minimum_required(VERSION 3.27)
project(PA2)

set(CMAKE_CXX_STANDARD 17)

add_executable(PA2 pa2.cpp
        admin.h
        account.h
        atm.h
        atm.cpp
)
