#include <iostream>
#include "Warcaby/Game/game.h"
#include "Warcaby/types.h"


int main() {
    
    // tworzymy obiekt gry

    Game game;

    // glowna petla gry
    while(game.gameState == ONGOING){
        
        game.update();
        game.render();
    }

    
    return 0;
}
