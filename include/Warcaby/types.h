#pragma once
#include <array>

enum GameState{
    BLACK_WIN,
    WHITE_WIN,
    ONGOING,
    // WRONG_MOVE narazie nie potrzebujemy tego, bo gdy ruch jest zly to po prostu prosimy gracza o podanie ruchu jeszcze raz
};

enum Symbol{
    SYMBOL_BLACK,
    SYMBOL_WHITE
};

// enum FieldType{
//     EMPTY,
//     WHITE,
//     WHITE_QUEEN,
//     BLACK,
//     BLACK_QUEEN
// };
// type: 0 = puste pole, 1 = bialy pionek, 2 = czarny pionek, 3 = biala damka, 4 = czarna damka

// struct Move{
//     int row1;
//     int colum1;
//     int row2;
//     int colum2;
// };

// struct BoardArray{
//     std::array<std::array<int, 8>, 8> board;
// };