#include <iostream>
#include "Warcaby/Game/game.h"
#include "Warcaby/types.h"

using namespace std;

int main() {
    
    // tworzymy obiekt gry
    Game game;

    // glowna petla gry
    while(game.gameState == ONGOING){
        game.render();
        string player = game.currentMove == SYMBOL_WHITE ? "Bialy" : "Czarny";
        cout << "Ruch gracza: " << player << endl;
        cout << "Podaj ruch: " << endl;
        game.update();        
    }

    // wypisujemy kto wygral
    cout << "Wygral gracz: " << game.gameState << endl;
    
    return 0;
}
