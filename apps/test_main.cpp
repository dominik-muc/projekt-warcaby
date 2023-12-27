#include <iostream>
#include "Warcaby/Game/game.h"
#include "Warcaby/types.h"

#include "Warcaby/TextRenderer/textrenderer.hpp"

using namespace std;

int main() {
    
    // tworzymy obiekt gry
    Game game;
    AsciiRenderer renderer;

    array<int, 2> UserInput;

    // glowna petla gry
    while(game.gameState == ONGOING){
        //game.render();
        renderer.printBoard(game.getBoard());
        
        //cout << "Ruch gracza: " << game.currentMove << endl;
        //cout << "Podaj ruch: " << endl;
        UserInput = renderer.getUserInput();
        UserInput = renderer.getUserInput();
        UserInput = renderer.getUserInput();
        game.update();
        renderer.printMessage("Example message");

    }

    // wypisujemy kto wygral
    //cout << "Wygral gracz: " << game.gameState << endl;
    
    return 0;
}
