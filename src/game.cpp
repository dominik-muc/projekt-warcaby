#include "Warcaby/Game/game.h"
#include <iostream>

using namespace std;

Game::Game(){
    // ustawiamy aktualny stan gry na ONGOING
    gameState = ONGOING;

    // ustawiamy aktualny ruch na WHITE
    currentMove = SYMBOL_WHITE;

    // tworzymy plansze
    board = Board();

}

void Game::render() {
    // wypisz planszę board do cout

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++) {
            cout << board.getBoard()[i][j] << " ";
        }
        cout << endl;
    }
    
}
    

void Game::update() {
    // kod metody update
}