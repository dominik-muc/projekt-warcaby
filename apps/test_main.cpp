#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Warcaby/TextRenderer/textrenderer.hpp>


int main(){
    AsciiRenderer interface;
    
    static const struct timespec sleep_time = {.tv_sec = 2, .tv_nsec = 30000000};

    struct BoardArray board;

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            board.field[i][j] = 0;
        }
    }

    board.field[7][7] = 3;

    nanosleep(&sleep_time, NULL);
    interface.printBoard(board);

    board.field[5][2] = 1;

    nanosleep(&sleep_time, NULL);
    interface.printBoard(board);

    nanosleep(&sleep_time, NULL);

    interface.closeRenderer();
    return 0;
}