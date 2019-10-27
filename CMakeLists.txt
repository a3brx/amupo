cmake_minimum_required(VERSION 3.10)
project(amigo_dos_museus)

set(CMAKE_CXX_STANDARD 11)

add_executable(amigo_dos_museus main.cpp Date.cpp Address.cpp Card.cpp Event.cpp Museum.cpp)