#pragma once

#include "Warcaby/types.h"
#include <array>

class Board{

    public:
    Board();
    // setField bedzie aktualizowal plansze, czyli zmienial wartosc w array (gdy juz sie upewnimy ze ruch jest poprawny)
    void setField(int x, int y, FieldType type);

    // getBoard zwraca aktualny stan planszy (plansza jest prywatna, wiec nie mozna jej zobaaczyc z zewnatrz)
    
    std::array<std::array<int, 8>, 8> getBoard();

    private:    
    // 0 = puste pole, 1 = bialy pionek, 2 = czarny pionek, 3 = biala damka, 4 = czarna damka
    std::array<std::array<int, 8>, 8> board; 
};