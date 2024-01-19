set(CMAKE_REQUIRED_VERSION 3.14)
cmake_minimum_required(VERSION ${CMAKE_REQUIRED_VERSION})

project(
    Warcaby
    LANGUAGES CXX
    VERSION 0.1 
    DESCRIPTION "Warcaby w C++. Wow")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# set to 1 for windows
if(1)
    find_package (PDCurses)
    message("---------------------------- ${PDCURSES_FOUND}, ${PDCURSES_LIBRARIES}, ${PDCURSES_INCLUDE_DIR}, ${PDCURSES_PANEL_LIBRARY}")
    if(PDCURSES_FOUND)
        set(CURSES_FOUND ${PDCURSES_FOUND})
        set(CURSES_LIBRARIES ${PDCURSES_LIBRARIES})
        set(CURSES_INCLUDE_DIR ${PDCURSES_INCLUDE_DIR})
    
    else()
        find_package (Curses REQUIRED)
    endif()

else()
    find_package (Curses REQUIRED)
endif()

include_directories(${CURSES_INCLUDE_DIR})
message("---------------------------- ${CURSES_INCLUDE_DIR}")
    

add_subdirectory(apps)
add_subdirectory(src)