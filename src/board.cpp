#include "Warcaby/Board/board.h"
#include <array>
#include <iostream>

Board::Board(){
    // ustawiamy plansze na poczatkowa
    board = {
        std::array<int, 8>{0, 2, 0, 2, 0, 2, 0, 2},
        std::array<int, 8>{2, 0, 2, 0, 2, 0, 2, 0},
        std::array<int, 8>{0, 2, 0, 2, 0, 2, 0, 2},
        std::array<int, 8>{0, 0, 0, 0, 0, 0, 0, 0},
        std::array<int, 8>{0, 0, 0, 0, 0, 0, 0, 0},
        std::array<int, 8>{1, 0, 1, 0, 1, 0, 1, 0},
        std::array<int, 8>{0, 1, 0, 1, 0, 1, 0, 1},
        std::array<int, 8>{1, 0, 1, 0, 1, 0, 1, 0}
    };
}

std::array<std::array<int, 8>, 8> Board::getBoard() {
    return board;
}

void Board::setField(int x, int y, int type) {
    // type: 0 = puste pole, 1 = bialy pionek, 2 = czarny pionek, 3 = biala damka, 4 = czarna damka
    board[x][y] = type;
}

int Board::getField(int x, int y) {
    return board[x][y];
}