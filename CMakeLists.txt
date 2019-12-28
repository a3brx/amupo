cmake_minimum_required(VERSION 3.10)
project(amigo_dos_museus)

set(CMAKE_CXX_STANDARD 11)

add_executable(amigo_dos_museus code/main/main.cpp code/Date/Date.cpp code/Address/Address.cpp code/Event/Event.cpp code/Museum/Museum.cpp code/System/System.cpp code/Menu/Menu.cpp code/utils/utils.cpp code/Person/Person.cpp code/Ticket/Ticket.cpp code/utils/InvalidInput.h code/Time/Time.cpp BinaryTree/registoMuseum.cpp BinaryTree/registoMuseum.h)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)

