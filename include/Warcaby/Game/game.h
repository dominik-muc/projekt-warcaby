#pragma once

#include <Warcaby/Board/board.h>
#include <Warcaby/Player/player.h>
#include <string>

class Game
{
public:
    // konstruktor
    Game();

    // aktualny stan gry
    GameState gameState;

    // akutalny ruch
    Symbol currentMove;

    // aktualizacja gry, bedzie wywolywana po kazdym ruchu
    std::string update(int xp, int yp, int xk, int yk);

    // funkcja renderujaca, bedzie wywolywana po kazdym update, narazie bedzie wypisywac plansze do cout czy cos
    void render();

    // odkrywa board.getBoard dla innych rendererów
    std::array<std::array<int, 8>, 8> getBoard();

private:
    bool isOpponentPiece(int row, int column);
    // funkcja pomocnicza do sprawdzenia czy jest mozliwe bicie we wskazanym ruchu
    bool isCaptureLegal(int xp, int yp, int xk, int yk, int pawn, int pawn2, int color_to_capture, int rowModifier);

    // funkcja pomocnicza do sprawdzenia czy jest mozliwe jakiekolwiek bicie przez aktualnego
    bool isCapturePossible(int row, int column, int rowModifier);

    // funkcja sprawdzajaca czy ruch jest legalny
    bool isMoveLegal(int xp, int yp, int xk, int yk, Symbol currentMove);

    // ilosc bialych i czarnych pionkow
    std::array<int, 8> piece_counts = {12, 12};

    // plansza
    Board board;
};