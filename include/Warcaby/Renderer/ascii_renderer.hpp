#pragma once

#include <array>
#include <string>

#ifdef _WIN32
    #include <curses.h>
#else
    #include <ncurses.h>
#endif


#include <Warcaby/Renderer/renderer.h>


// A minimalistic renderer. Every piece is represented by one character.
class AsciiRenderer : Renderer{
    public:
        AsciiRenderer();
        void printBoard(std::array<std::array<int, 8>, 8> board );
        void closeRenderer();
        std::array<int, 2> getUserInput();
        void printMessage(std::string message);

    private:
        // acording to FieldType from types.h
        const char* piece_art[5] = {"_", "o", "x", "O", "X"};
        std::string message;
        std::array<int, 2> select_square();
};