#include <board.h>

Board::Board(){
    // ustawiamy plansze na poczatkowa
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            array[i][j] = EMPTY;
        }
    }
}