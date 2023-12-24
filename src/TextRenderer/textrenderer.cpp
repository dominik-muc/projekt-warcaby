#include "Warcaby/TextRenderer/textrenderer.hpp"
#include <ncurses.h>

AsciiRenderer::AsciiRenderer() 
{
    initscr();
    keypad(stdscr, TRUE);
    //printw("Hello World !!!\n");    
    refresh();
}

void AsciiRenderer::printBoard( std::array<std::array<int, 8>, 8> board )
{
    erase();
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            printw("%s ", piece_art[ board[i][j] ]);
        }
        
        printw("\n");
        refresh();
    }
}

void AsciiRenderer::closeRenderer()
{
    endwin();
}

std::array<int, 4> AsciiRenderer::getUserInput()
{
    std::array<int, 4> a = {1,1,1,1};
    return a;
}