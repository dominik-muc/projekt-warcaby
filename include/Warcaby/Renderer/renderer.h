#pragma once

#include <Warcaby/types.h>
#include <array>

class Renderer{
    public:
    void printBoard(std::array<std::array<int, 8>, 8> board );
    void closeRenderer();
    std::array<int, 2> getUserInput();
};