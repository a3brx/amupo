cmake_minimum_required(VERSION 3.10)
project(amigo_dos_museus)

set(CMAKE_CXX_STANDARD 11)

add_executable(amigo_dos_museus Main/main.cpp Date/Date.cpp Address/Address.cpp Card/Card.cpp Event/Event.cpp Museum/Museum.cpp System/System.cpp Menu/Menu.cpp utils/utils.h utils/utils.cpp)