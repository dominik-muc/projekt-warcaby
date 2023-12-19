#include "Warcaby/Game/game.h"

Game::Game(){
    // ustawiamy aktualny stan gry na ONGOING
    gameState = ONGOING;

    // ustawiamy aktualny ruch na BLACK
    currentMove = SYMBOL_BLACK;

}

void Game::render() {
    // kod metody render
}

void Game::update() {
    // kod metody update
}