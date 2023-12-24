#pragma once

#ifdef _WIN32
    #include <pdcurses.h>
#else
    #include <ncurses.h>
#endif


#include <Warcaby/Renderer/renderer.h>
#include <array>



// A minimalistic renderer. Every piece is represented by one character.
class AsciiRenderer : Renderer{
    public:
        AsciiRenderer();
        void printBoard(std::array<std::array<int, 8>, 8> board );
        void closeRenderer();
        std::array<int, 4> getUserInput();

    private:
        // acording to FieldType from types.h
        const char* piece_art[5] = {"_", "o", "O", "x", "X"};
};