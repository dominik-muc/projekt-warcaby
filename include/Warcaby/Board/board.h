#pragma once

#include <Warcaby/types.h>

class Board{
    private:
    BoardArray array;
    public:
    void setField(int x, int y, FieldType type);
    BoardArray getBoard();
};