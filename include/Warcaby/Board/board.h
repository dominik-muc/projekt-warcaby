#pragma once

#include "Warcaby/types.h"

class Board{

    public:
    Board();
    // setField bedzie aktualizowal plansze, czyli zmienial wartosc w array
    void setField(int x, int y, FieldType type);

    // getBoard zwraca aktualny stan planszy (plansza jest prywatna, wiec nie mozna jej zobaaczyc z zewnatrz)
    BoardArray getBoard();

    private:
    BoardArray array;
};