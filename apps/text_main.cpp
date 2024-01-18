#include <iostream>
#include "Warcaby/Game/game.h"
#include "Warcaby/types.h"

#include "Warcaby/Renderer/text_renderer.hpp"

using namespace std;

int main() {
    
    // tworzymy obiekt gry
    Game game;
    TextRenderer renderer;

    array<int, 2> UserInput1, UserInput2;
    string player;
    string mess = "";


    renderer.printBoard(game.getBoard());
    renderer.open_help();

    // glowna petla gry
    while(game.gameState == ONGOING){

        
        player = game.currentMove == SYMBOL_WHITE ? "Bialy" : "Czarny";
        renderer.printMessage("Ruch gracza: " + player);
        renderer.printMessage(mess);
        renderer.printBoard(game.getBoard());
        
        UserInput1 = renderer.getUserInput();
        UserInput2 = renderer.getUserInput();
        
        mess = game.update(UserInput1[0], UserInput1[1], UserInput2[0], UserInput2[1]);
        

    }

    
    // wypisujemy kto wygral
    
    renderer.open_win_screen(game.gameState);
    renderer.closeRenderer();

    cout << "Wygral gracz: " << game.gameState << endl;
    
    return 0;
}
