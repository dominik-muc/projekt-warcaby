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

void Game::update()
{
    std::array<std::array<int, 8>, 8> retrievedBoard = board.getBoard(); // pobieramy aktualny stan planszy

    // pobieramy ruch od gracza
    int xp, yp, xk, yk;
    cin >> xp >> yp >> xk >> yk;

    // sprawdzamy czy ruch jest legalny
    int legal = isMoveLegal(xp, yp, xk, yk, currentMove);
    if (legal)
    {
        // aktualizujemy plansze
        board.setField(xk, yk, board.getField(xp, yp));
        board.setField(xp, yp, 0);
    } else {
        cout << "Ruch nie jest legalny" << endl;
        return;
    }

    // sprawdzamy czy na planszy zostaly pionki przeciwnika, jesli nie to konczymy gre i ustawiamy stan gry na wygrana gracza ktory ma aktualnie ruch
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; i < 8; i++)
        {
            if (retrievedBoard[i][j] == 2 || retrievedBoard[i][j] == 4)
            {
                count++;
            }
        }
    }
    if (count == 0)
    {
        gameState = WHITE_WIN;
        return;
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; i < 8; i++)
        {
            if (retrievedBoard[i][j] == 1 || retrievedBoard[i][j] == 3)
            {
                count++;                
            }
        }
    }
    if (count == 0)
    {
        gameState = BLACK_WIN;
        return;
    }

    // jeszcze sprawdzamy czy gracz ktory ma aktualnie ruch moze wykonac jakies bicie, jesli nie to zmieniamy gracza ktory ma aktualnie ruch
    // tu kod...

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

    // jesli gra sie nie skonczyla to zmieniamy gracza ktory ma aktualnie ruch
    if (currentMove == SYMBOL_WHITE)
    {
        currentMove = SYMBOL_BLACK;
    }
    else
    {
        currentMove = SYMBOL_WHITE;
    }
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

    // damka moze isc o 1 na ukos w dowolnym kierunku, tzn w gore lub dol i na ukos o 1 lub 2 jesli bicie
    // sprawdzamy czy ruch jest poprawny, jesli tak to wykonujemy ruch
    // pionek

    if (currentMove == SYMBOL_WHITE)
    {
        if (board.getField(xp, yp) == 1)
        {            
            if (xk == xp - 1 && (yk == yp - 1 || yk == yp + 1))
            {
                return true;
            }
            // sprawdzamy czy mozemy wykonac bicie, tzn czy pomiedzy polem na ktory chcemy przejsc(chcemy przejsc o 2 na ukos), tzn na polu o 1 na ukos jest przeciwnik, wtedy go bijemy
            if ((xk == (xp-2)) && (yk == yp-2) && (board.getField(xp-1, yp-1) == 2 || board.getField(xp-1, yp-1) == 4))
            {
                // wykonujemy bicie
                board.setField(xp-1, yp-1, 0);
                return true;
            }
            else if ((xk == xp-2) && (yk == yp+2) && (board.getField(xp-1, yp+1) == 2 || board.getField(xp-1, yp+1) == 4))
            {
                // wykonujemy bicie
                board.setField(xp-1, yp+1, 0);
                return true;
            }
        }
        else if (board.getField(xp,yp) == 3) {
            if ((xk == xp + 1 || xk == xp - 1 ) && (yk == yp - 1 || yk == yp + 1)) {
                return true;
            }
            // sprawdzamy czy mozemy wykonac bicie, tzn czy pomiedzy polem na ktory chcemy przejsc(chcemy przejsc o 2 na ukos), tzn na polu o 1 na ukos jest przeciwnik, wtedy go bijemy
            if ((xk == (xp-2)) && (yk == yp-2) && (board.getField(xp-1, yp-1) == 2 || board.getField(xp-1, yp-1) == 4))
            {
                // wykonujemy bicie
                board.setField(xp-1, yp-1, 0);
                return true;
            }
            else if ((xk == xp-2) && (yk == yp+2) && (board.getField(xp-1, yp+1) == 2 || board.getField(xp-1, yp+1) == 4))
            {
                // wykonujemy bicie
                board.setField(xp-1, yp+1, 0);
                return true;
            }
            else if ((xk == (xp+2)) && (yk == yp-2) && (board.getField(xp+1, yp-1) == 2 || board.getField(xp+1, yp-1) == 4))
            {
                // wykonujemy bicie
                board.setField(xp+1, yp-1, 0);
                return true;
            }
            else if ((xk == xp+2) && (yk == yp+2) && (board.getField(xp+1, yp+1) == 2 || board.getField(xp+1, yp+1) == 4))
            {
                // wykonujemy bicie
                board.setField(xp+1, yp+1, 0);
                return true;
            }      
        }
    }
    else if (currentMove == SYMBOL_BLACK)
    {
        if (board.getField(xp, yp) == 2)
        {
            if (xk == xp + 1 && (yk == yp - 1 || yk == yp + 1))
            {
                return true;
            }

            if ((xk == (xp+2)) && (yk == yp-2) && (board.getField(xp-1, yp-1) == 1 || board.getField(xp-1, yp-1) == 3))
            {
                // wykonujemy bicie
                board.setField(xp+1, yp-1, 0);
                return true;
            }
            else if ((xk == xp+2) && (yk == yp+2) && (board.getField(xp-1, yp+1) == 1 || board.getField(xp-1, yp+1) == 3))
            {
                // wykonujemy bicie
                board.setField(xp+1, yp+1, 0);
                return true;
            }
        }
        else if (board.getField(xp, yp) == 4)
        {
            // damka czarna robi doslownie to samo co biala, tylko musimy sprawdzic czy na polu pomiedzy biciem jest pionek przeciwnika, a nie nasz, da sie to zrobic lepiej jedna funkcja ale mi sie nie chce
             if ((xk == xp + 1 || xk == xp - 1 ) && (yk == yp - 1 || yk == yp + 1)) {
                return true;
            }
            // sprawdzamy czy mozemy wykonac bicie, tzn czy pomiedzy polem na ktory chcemy przejsc(chcemy przejsc o 2 na ukos), tzn na polu o 1 na ukos jest przeciwnik, wtedy go bijemy
            if ((xk == (xp-2)) && (yk == yp-2) && (board.getField(xp-1, yp-1) == 1 || board.getField(xp-1, yp-1) == 3))
            {
                // wykonujemy bicie
                board.setField(xp-1, yp-1, 0);
                return true;
            }
            else if ((xk == xp-2) && (yk == yp+2) && (board.getField(xp-1, yp+1) == 1 || board.getField(xp-1, yp+1) == 3))
            {
                // wykonujemy bicie
                board.setField(xp-1, yp+1, 0);
                return true;
            }
            else if ((xk == (xp+2)) && (yk == yp-2) && (board.getField(xp+1, yp-1) == 1 || board.getField(xp+1, yp-1) == 3))
            {
                // wykonujemy bicie
                board.setField(xp+1, yp-1, 0);
                return true;
            }
            else if ((xk == xp+2) && (yk == yp+2) && (board.getField(xp+1, yp+1) == 1 || board.getField(xp+1, yp+1) == 3))
            {
                // wykonujemy bicie
                board.setField(xp+1, yp+1, 0);
                return true;
            }      
        }
    }

    // zwracamy falsz jesli nie spelnia zadnego z powyzszych warunkow
    return false;
}