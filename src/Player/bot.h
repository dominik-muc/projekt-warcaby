#pragma once

#include "player.h"

class Bot : public Player{
    public:
    Move getMove() override;
};