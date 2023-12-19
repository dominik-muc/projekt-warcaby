#include "Warcaby/Board/board.h"
#include <array>
#include <iostream>

Board::Board(){
    // ustawiamy plansze na poczatkowa
    board = {{
        {0, 2, 0, 2, 0, 2, 0, 2}, // Czarne pionki na nieparzystych miejscach
        {2, 0, 2, 0, 2, 0, 2, 0}, // Czarne pionki na parzystych miejscach
        {0, 2, 0, 2, 0, 2, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 0}, // Środkowa pusta przestrzeń
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1, 0, 1, 0}, // Białe pionki na parzystych miejscach
        {0, 1, 0, 1, 0, 1, 0, 1}, // Białe pionki na nieparzystych miejscach
        {1, 0, 1, 0, 1, 0, 1, 0}
    }};
}

std::array<std::array<int, 8>, 8> Board::getBoard() {
    return board;
}