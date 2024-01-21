#include <iostream>
#include <Warcaby/Renderer/text_renderer.hpp>
#include "Warcaby/Game/game.h"
#include "Warcaby/types.h"
#include "Warcaby/Bot/bot.h"

using namespace std;

// dodac (int argc, char *argv)
// wymyslic testowanie

int main(){
    
    // tworzymy obiekt gry
    Game game;
    array<int, 2> UserInput1, UserInput2;

    string player_white = "human";
    string player_black = "bot";
    // bot gra czarnymi (na razie)

    string currentPlayer;

    string message = "";


    TextRenderer renderer = TextRenderer();

    renderer.printBoard(game.getBoard());
    renderer.open_help();

    // glowna petla gry
    while(game.gameState == ONGOING){
        currentPlayer = game.currentMove == SYMBOL_WHITE ? "Bialy" : "Czarny";
        
        renderer.printMessage(message);
        

        if(currentPlayer == "Bialy")
        {
            renderer.printMessage("Ruch gracza: " + currentPlayer);
            renderer.printBoard(game.getBoard());
            UserInput1 = renderer.getUserInput();
            UserInput2 = renderer.getUserInput();   
            renderer.printMessage("Podaj ruch");
            message = game.update(UserInput1[0], UserInput1[1], UserInput2[0], UserInput2[1], player_white);
            renderer.reset_selection();
        }
        else
        {
            renderer.printMessage("Bot " + currentPlayer + " wykonuje ruch");
            renderer.printBoard(game.getBoard());
            game.update(0, 0, 0, 0, player_black);            
        }
    }

    renderer.open_win_screen(game.gameState);
    renderer.closeRenderer();
    cout << "Wygral gracz: " << (game.currentMove == SYMBOL_WHITE ? "Bialy" : "Czarny") << endl;
    return 0;

    // wypisujemy kto wygral
    cout << "Wygral gracz: " << game.gameState << endl;
    
    return 0;
}
