#pragma once

#include "Warcaby/Player/player.h"

class Bot : public Player{
    public:
    Move getMove() override;
};