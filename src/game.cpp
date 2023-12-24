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

    std::array<std::array<int, 8>, 8> retrievedBoard = board.getBoard();

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++) {
            cout << retrievedBoard[i][j] << " ";
        }
        cout << endl;
    }
    
}
    

void Game::update() {

    std::array<std::array<int, 8>, 8> retrievedBoard = board.getBoard(); // pobieramy aktualny stan planszy

    // pobieramy ruch od gracza
    // row1, colum1, row2, colum2 to zmienne typu int odpowiadajce kolejno za wiersz i kolumne pola z ktorego chcemy sie ruszyc i wiersz i kolumne pola na ktore chcemy sie ruszyc
    int row1, colum1, row2, colum2;
    cin >> row1 >> colum1 >> row2 >> colum2;
    cout << "Ruch gracza: " << row1 << " " << colum1 << " " << row2 << " " << colum2 << endl;

    // na samym poczatku sprawdzamy czy ruch jest na planszy

    if (!(row1 >= 0 && row1 < 8 && colum1 >= 0 && colum1 < 8 && row2 >= 0 && row2 < 8 && colum2 >= 0 && colum2 < 8)) {
        cout << "Ruch poza planszą" << endl;
        // prosimy o podanie ruchu jeszcze raz
    }
    
    // sprawdzamy czy na wybranym polu jest pionek gracza ktory ma aktualnie ruch
    if (currentMove == SYMBOL_WHITE) {
        if (retrievedBoard[row1][colum1] == 1) {
            printf("Wybrano biały pionek\n");
            // sprawdzamy czy ruch jest poprawny, jesli tak to wykonujemy ruch 
        }
        else if (retrievedBoard[row1][colum1] == 3) {
            printf("Wybrano białą damkę\n");
            // sprawdzamy czy ruch jest poprawny, jesli tak to wykonujemy ruch 
        } 
        else {
            printf("Wybrano pole bez pionka lub pole z pionkiem przeciwnika\n");
            // prosimy o podanie ruchu jeszcze raz
        }
    }
    else if (currentMove == SYMBOL_BLACK) {
        if (retrievedBoard[row1][colum1] == 2) {
            printf("Wybrano czarny pionek\n");
            // sprawdzamy czy ruch jest poprawny, jesli tak to wykonujemy ruch 
        }
        else if (retrievedBoard[row1][colum1] == 4) {
            printf("Wybrano czarną damkę\n");
            // sprawdzamy czy ruch jest poprawny, jesli tak to wykonujemy ruch 
        } else {
            printf("Wybrano pole bez pionka lub pole z pionkiem przeciwnika\n");
            // prosimy o podanie ruchu jeszcze raz
        }
    }

    // sprawdzamy czy na planszy zostaly pionki przeciwnika, jesli nie to konczymy gre i ustawiamy stan gry na wygrana gracza ktory ma aktualnie ruch

   // jesli gra sie nie skonczyla to zmieniamy gracza ktory ma aktualnie ruch
    if (currentMove == SYMBOL_WHITE) {
        currentMove = SYMBOL_BLACK;
    } else {
        currentMove = SYMBOL_WHITE;
    }
    

}