#include <iostream>
#include "Warcaby/Game/game.h"
#include "Warcaby/types.h"

using namespace std;

int main() {
    
    // tworzymy obiekt gry
    Game game;

    // glowna petla gry
    while(game.gameState == ONGOING){
        cout << "Ruch gracza: " << game.currentMove << endl;
        cout << "Podaj ruch: " << endl;
        game.update();
        game.render();
        game.gameState = BLACK_WIN;
    }

    // wypisujemy kto wygral

    cout << "Wygral gracz: " << game.gameState << endl;
    
    return 0;
}
