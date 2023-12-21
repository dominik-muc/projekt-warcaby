set(CMAKE_REQUIRED_VERSION 3.14)
cmake_minimum_required(VERSION ${CMAKE_REQUIRED_VERSION})

project(
    Warcaby
    LANGUAGES CXX
    VERSION 0.1 
    DESCRIPTION "Warcaby w C++. Wow")


#narazie to komentuje -> musimy zrobić to zależnie od platformy, bo z tego co Wojtek mówił nie ma ncurses na windowsa i nie chce się projekt zbudować.
#find_package(Curses REQUIRED)
#include_directories(${CURSES_INCLUDE_DIR})
    

add_subdirectory(apps)
add_subdirectory(src)