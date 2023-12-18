#pragma once

#include <ncurses.h>
#include "../Renderer/renderer.h"



// A minimalistic renderer. Every piece is represented by one character.
class AsciiRenderer : Renderer{
    public:
        AsciiRenderer();
        void printBoard(BoardArray board);

    private:
        const char* piece_art[5] = {"_", "o", "O", "x", "X"}; 
};
