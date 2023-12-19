#pragma once
#include <array>

enum GameState{
    BLACK_WIN,
    WHITE_WIN,
    ONGOING,
    WRONG_MOVE
};

enum Symbol{
    SYMBOL_BLACK,
    SYMBOL_WHITE
};

enum FieldType{
    EMPTY,
    WHITE,
    WHITE_QUEEN,
    BLACK,
    BLACK_QUEEN
};

struct Move{
    int row1;
    int colum1;
    int row2;
    int colum2;
};

struct BoardArray{
    std::array<std::array<int, 8>, 8> board;
};