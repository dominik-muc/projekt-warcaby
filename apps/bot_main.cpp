#include <iostream>
#include "Warcaby/Game/game.h"
#include "Warcaby/types.h"
#include "Warcaby/Bot/bot.h"

using namespace std;

// dodac (int argc, char *argv)
// wymyslic testowanie

int main(){
    
    // tworzymy obiekt gry
    Game game;
    int xp, yp, xk, yk;

    string player_white = "human";
    string player_black = "bot";
    // bot gra czarnymi (na razie)

    // glowna petla gry
    while(game.gameState == ONGOING){
        game.render();
        string currentPlayer = game.currentMove == SYMBOL_WHITE ? "Bialy" : "Czarny";
        cout << "Ruch gracza: " << currentPlayer << endl;

        if(currentPlayer == "Bialy")
        {
            
            cin >> xp >> yp >> xk >> yk;
            cout << "Podaj ruch: " << endl;
            game.update(xp, yp, xk, yk, player_white);
        }
        else
        {
            cout << "Podaj ruch: " << endl;
            // zmienic na ruch bota
            game.update(0, 0, 0, 0, player_black);            
        }
    }

    // wypisujemy kto wygral
    cout << "Wygral gracz: " << game.gameState << endl;
    
    return 0;
}
