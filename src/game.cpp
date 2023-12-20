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

    // pobieramy ruch od gracza
    // row1, colum1, row2, colum2 to zmienne typu int odpowiadajce kolejno za wiersz i kolumne pola z ktorego chcemy sie ruszyc i wiersz i kolumne pola na ktore chcemy sie ruszyc
    int row1, colum1, row2, colum2;
    cin >> row1 >> colum1 >> row2 >> colum2;
    cout << "Ruch gracza: " << row1 << " " << colum1 << " " << row2 << " " << colum2 << endl;
    /*
    1. sprawdzamy czy ruch jest poprawny
    - jesli jest pionkiem to sprawdzamy czy ruch jest o 1 w gore i w lewo lub w prawo, jesli tak to zmieniamy stan planszy, jesli jest tam pionek przeciwnika to go zbijamy i idziemy o 1 dalej w tym samym kierunku
    - jesli jest damka to sprawdzamy czy ruch jest o 1 w gore i w lewo lub w prawo lub w dol i w lewo lub w prawo, jesli tak to zmieniamy stan planszy, jesli jest tam pionek przeciwnika to go zbijamy i idziemy o 1 dalej w tym samym kierunku
    - sprawdzajac czy ruch jest poprawny musimy sprawdzic czy nie wychodzimy poza plansze
    - jesli ruch jest niepoprawny to wypisujemy komunikat o bledzie i prosimy gracza o podanie ruchu jeszcze raz
    2. sprawdzamy czy ktos wygral
    - jesli ktos wygral to ustawiamy gameState na BLACK_WIN lub WHITE_WIN
    3. zmieniamy currentMove na przeciwny    
    
    */



}