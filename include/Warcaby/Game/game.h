#pragma once

#include "Warcaby/Board/board.h"
#include "Warcaby/Player/player.h"
#include "Warcaby/Bot/bot.h"

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
    void update(string player);

    // funkcja renderujaca, bedzie wywolywana po kazdym update, narazie bedzie wypisywac plansze do cout czy cos
    void render();

    //funkcja zwracajaca obecna pozycje na planszy
    Board getGameBoard();

private:
    // funkcja sprawdzajaca czy ruch jest legalny
    bool isMoveLegal(int xp, int yp, int xk, int yk, Symbol currentMove);

    // plansza
    Board board;
};