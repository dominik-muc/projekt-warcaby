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
            cout << "Podaj ruch: " << endl;
            game.update(player_white);
        }
        else
        {
            cout << "Podaj ruch: " << endl;
            // zmienic na ruch bota
            game.update(player_black);            
        }
    }

    // wypisujemy kto wygral
    cout << "Wygral gracz: " << game.gameState << endl;
    
    return 0;
}
