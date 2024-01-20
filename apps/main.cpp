#include <iostream>
#include "Warcaby/Game/game.h"
#include "Warcaby/types.h"

using namespace std;

int main() {
    
    // tworzymy obiekt gry
    Game game;

    int xp, yp, xk, yk;
    

    // glowna petla gry
    while(game.gameState == ONGOING){
        game.render();
        string player = game.currentMove == SYMBOL_WHITE ? "Bialy" : "Czarny";
        cout << "Ruch gracza: " << player << endl;
        cout << "Podaj ruch: " << endl;
        cin >> xp >> yp >> xk >> yk;
        cout << game.update(xp, yp, xk, yk) << endl;        
    }

    // wypisujemy kto wygral
    cout << "Wygral gracz: " << game.gameState << endl;
    
    return 0;
}
