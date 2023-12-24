#include <Warcaby/TextRenderer/textrenderer.hpp>

AsciiRenderer::AsciiRenderer() 
{
    initscr();
    keypad(stdscr, TRUE);
    //printw("Hello World !!!\n");    
    refresh();
}

void AsciiRenderer::printBoard(BoardArray board)
{
    erase();
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            printw("%s", piece_art[ board.field[i][j] ]);
        }
        
        printw("\n");
        refresh();
    }
}

void AsciiRenderer::closeRenderer()
{
    endwin();
}

void AsciiRenderer::getUserInput()
{
    
}