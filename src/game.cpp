#include "Warcaby/Game/game.h"
#include <iostream>

using namespace std;

Game::Game()
{
    // ustawiamy aktualny stan gry na ONGOING
    gameState = ONGOING;

    // ustawiamy aktualny ruch na WHITE
    currentMove = SYMBOL_WHITE;

    // tworzymy plansze
    board = Board();
}

void Game::render()
{
    // wypisz planszę board do cout

    std::array<std::array<int, 8>, 8> retrievedBoard = board.getBoard();

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << retrievedBoard[i][j] << " ";
        }
        cout << endl;
    }
}

std::string Game::update(int xp, int yp, int xk, int yk, string player)
{
    std::array<std::array<int, 8>, 8> retrievedBoard = board.getBoard(); // pobieramy aktualny stan planszy
    
    if(player != "bot"){

        // pobieramy ruch od gracza

        // sprawdzamy czy ruch jest legalny
        int legal = isMoveLegal(xp, yp, xk, yk, currentMove);
        if (legal)
        {
            // aktualizujemy plansze
            board.setField(xk, yk, board.getField(xp, yp));
            board.setField(xp, yp, 0);
        } else {
            return "Ruch nie jest legalny";
        }

        // sprawdzamy czy na planszy zostaly pionki przeciwnika, jesli nie to konczymy gre i ustawiamy stan gry na wygrana gracza ktory ma aktualnie ruch
        if (piece_counts[1] == 0)
        {
            gameState = WHITE_WIN;
            return "";
        }
        if (piece_counts[0] == 0)
        {
            gameState = BLACK_WIN;
            return "";
        }

        // ponownie pobieramy stan planszy żeby sprawdzić czy pionek zmienił się w damkę
        retrievedBoard = board.getBoard(); 

        // sprawdzamy czy pionek doszedl do konca planszy, jesli tak to zmieniamy go na damke
        for (int i = 0; i < 8; i++)
        {
            if (retrievedBoard[0][i] == 1)
            {
                board.setField(0, i, 3);            
            }
            if (retrievedBoard[7][i] == 2)
            {
                board.setField(7, i, 4);            
            }
        }
    }
    else
    {
        Bot bot;
        std::array<std::array<int, 8>, 8>  botMove = bot.move(currentMove, getBoard());
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                board.setField(i, j, botMove[i][j]);
            }
        }
    }

    // jesli gra sie nie skonczyla to zmieniamy gracza ktory ma aktualnie ruch
    if (currentMove == SYMBOL_WHITE)
    {
        currentMove = SYMBOL_BLACK;
    }
    else
    {
        currentMove = SYMBOL_WHITE;
    }

    return "";
}

bool Game::isMoveLegal(int xp, int yp, int xk, int yk, Symbol currentMove)
{
    // na samym poczatku sprawdzamy czy ruch jest na planszy
    if (xp < 0 || xp > 7 || yp < 0 || yp > 7 || xk < 0 || xk > 7 || yk < 0 || yk > 7)
    {
        cout << "Ruch poza planszą" << endl;
        return false;
    }

    // sprawdzamy czy na polu poczatkowym jest pionek gracza ktory ma aktualnie ruch
    if (currentMove == SYMBOL_WHITE)
    {
        if (!(board.getField(xp, yp) == 1 || board.getField(xp, yp) == 3))
        {
            cout << board.getField(xp, yp) << endl;
            cout << "Na polu początkowym nie ma pionka gracza który ma aktualnie ruch" << endl;
            return false;
        }
    }
    else if (currentMove == SYMBOL_BLACK)
    {
        if (!(board.getField(xp, yp) == 2 || board.getField(xp, yp) == 4))
        {
            cout << "Na polu początkowym nie ma pionka gracza który ma aktualnie ruch" << endl;
            return false;
        }
    }

    // sprawdzamy czy na polu koncowym jest puste pole
    if (board.getField(xk, yk) != 0)
    {
        cout << "Na polu końcowym nie ma pustego pola" << endl;
        return false;
    }

    // sprawdzamy czy w tym ruchu jest możliwe bicie
    // w przypadku białych pionków czy mozemy isc o 2 pola na ukos w gore i czy miedzy tym polem a aktualnym jest przeciwna figura
    if (currentMove == SYMBOL_WHITE)
    {
        if (board.getField(xp, yp) == 1 && isCaptureLegal(xp, yp, xk, yk, 2, 4, 1, -1)){
            return true;
        } // analogicznie dla damki, tylko jeszcze sprawdzamy mozliwosc pojscia w dol
        else if (board.getField(xp,yp) == 3 &&(isCaptureLegal(xp, yp, xk, yk, 2, 4, 1, -1) || isCaptureLegal(xp, yp, xk, yk, 2, 4, 1, 1))){
            return true;
        }
    } // i analogicznie dla czarnych figur, tylko dla pionka zamiast w gore - w dol
    else if (currentMove == SYMBOL_BLACK)
    {
        if (board.getField(xp, yp) == 2 && isCaptureLegal(xp, yp, xk, yk, 1, 3, 0, 1)){
            return true;
        }
        else if (board.getField(xp, yp) == 4 && (isCaptureLegal(xp, yp, xk, yk, 1, 3, 0, 1) || isCaptureLegal(xp, yp, xk, yk, 1, 3, 0, -1))){ 
            return true;
        }
    }

    //Sprawdzamy, czy gdzies indziej jest mozliwe bicie, jesli tak, to nie mozemy wykonac ruchu
    bool canCapture = false;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(currentMove == SYMBOL_WHITE && board.getField(i, j) == 1 && isCapturePossible(i, j, -1)){
                canCapture = true;
                break;
            }
            if(currentMove == SYMBOL_WHITE && board.getField(i, j) == 3 &&
              (isCapturePossible(i, j, -1) || isCapturePossible(i, j, 1))){
                canCapture = true;
                break;
            }
            if(currentMove == SYMBOL_BLACK && board.getField(i, j) == 2 && isCapturePossible(i, j, 1)){
                canCapture = true;
                break;
            }
            if(currentMove == SYMBOL_BLACK && board.getField(i, j) == 4 && 
            (isCapturePossible(i, j, 1) || isCapturePossible(i, j, -1))){
                canCapture = true;
                break;
            }                          
        }
        if(canCapture) break;
    }

    if(canCapture) return false;


    //jesli wczesniej nie bylo mozliwe bicie, to prawdzamy, czy mozemy ruszyc sie pionkiem o jedno pole na skos
    if(currentMove == SYMBOL_WHITE && board.getField(xp, yp) == 1 && (xk == xp - 1 && (yk == yp - 1 || yk == yp + 1)))
    {
        return true;
    }
    else if((currentMove == SYMBOL_WHITE && board.getField(xp, yp) == 3 && xk == xp + 1 || xk == xp - 1 ) && (yk == yp - 1 || yk == yp + 1)){
        return true;
    }
    else if(currentMove == SYMBOL_BLACK && board.getField(xp, yp) == 2 && (xk == xp + 1 && (yk == yp - 1 || yk == yp + 1))){
        return true;
    }
    else if(currentMove == SYMBOL_BLACK && board.getField(xp, yp) == 4 && (xk == xp + 1 || xk == xp - 1 ) && (yk == yp - 1 || yk == yp + 1)){
        return true;
    }


    // zwracamy falsz jesli nie spelnia zadnego z powyzszych warunkow
    return false;
}

bool Game::isCaptureLegal(int xp, int yp, int xk, int yk, int pawn, int pawn2, int color_to_capture, int rowModifier){
    if ((xk == xp+(rowModifier*2)) && (yk == yp-2) && (board.getField(xp+rowModifier, yp-1) == pawn || board.getField(xp+rowModifier, yp-1) == pawn2))
        {
            // wykonujemy bicie
            board.setField(xp+rowModifier, yp-1, 0);
            piece_counts[color_to_capture]--;
            return true;
        }
    else if ((xk == xp+(rowModifier*2)) && (yk == yp+2) && (board.getField(xp+rowModifier, yp+1) == pawn || board.getField(xp+rowModifier, yp+1) == pawn2))
        {
            // wykonujemy bicie
            board.setField(xp+rowModifier, yp+1, 0);
            piece_counts[color_to_capture]--;
            return true;
        }    
    return false;
}

bool Game::isOpponentPiece(int row, int column) {
    int piece = board.getField(row, column);
    if (currentMove == SYMBOL_WHITE) {
        return (piece == 2 || piece == 4);
    } else {
        return (piece == 1 || piece == 3);
    }
}

bool Game::isCapturePossible(int row, int column, int rowModifier){
    if(isOpponentPiece(row+(rowModifier*1), column+1) && board.getField(row+(rowModifier*2), column+2) == 0 && 
    (row+(rowModifier*2) >= 0) && (row+(rowModifier*2) < 8) && column+2 < 8){
        return true;
    }
    if(isOpponentPiece(row+(rowModifier*1), column-1) && board.getField(row+(rowModifier*2), column-2) == 0 && 
    (row+(rowModifier*2) >= 0) && (row+(rowModifier*2) < 8) && column-2 >= 0){
        return true;
    }    
    return false;
}

std::array<std::array<int, 8>, 8> Game::getBoard(){
    return board.getBoard();
}
